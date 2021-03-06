#include "./abrirguardarbc3.h"

float tofloat(std::string cadena);

AbrirGuardarBC3::AbrirGuardarBC3():AbrirGuardar()
{

}

Obra*  AbrirGuardarBC3::Leer(TEXTO nombrefichero)
{
    Obra* obra = nullptr;//= new Obra;
    QFile fichero(nombrefichero);
    if(!fichero.open(QIODevice::ReadOnly))
    {
        qFatal("No puedo abrir el fichero");
        return obra;
    }
    QTextStream datos(&fichero);
    datos.setCodec("Windows-1252");
    QStringList registros = datos.readAll().split('~');
    qDebug()<<"Total lineas: "<<registros.size();
    QStringList registroD;
    QStringList registroM;
    QStringList registroC;
    QStringList registroT;

    foreach (QString linea, registros)
    {
        if (linea[0]=='C')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroC.append(linea);
        }
        if (linea[0]=='D' && linea[1]=='|')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroD.append(linea);
        }
        if (linea[0]=='M' && linea[1]=='|')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroM.append(linea);
        }
        if (linea[0]=='T')
        {
            linea.chop(2);
            linea.remove(0,2);
            //qDebug()<<linea;
            registroT.append(linea);
        }
    }
    qDebug()<<"Total lineas Resitro C: "<<registroC.size();
    qDebug()<<"Total lineas Resitro D: "<<registroD.size();
    qDebug()<<"Total lineas Resitro M: "<<registroM.size();
    qDebug()<<"Total lineas Resitro T: "<<registroT.size();
    //empiezo construyendo el grafo solo con los codigos-->registroD
    clock_t t_ini, t_fin;
    double secs;
    t_ini = clock();
    foreach (const QString& linea, registroD)
    {
        procesarRelaciones(obra,linea,registroM);
    }
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    qDebug()<<"Procesadas las relaciones en: "<<secs<<" segundos";
    procesarConceptos(obra,registroC);
    qDebug()<<"Procesados los conceptos";
    procesarTexto(obra,registroT);
    qDebug()<<"Procesados los textos";
    fichero.close();
    return obra;
}

void AbrirGuardarBC3::procesarRelaciones (Obra* &obra, const QString &linea, QStringList &registroM)
{
    //Miro si el registro tiene 2 o 3 campos
    //3 campos->verson FIEBDC-3/2012->tener en cuenta porcentajes
    //2 campos->version anterior->no considera porcentajes

    QStringList lista = linea.split("|");
    TEXTO padre = lista.at(0);

    int nHijos=(linea.count("\\")/3);
    int nCampos = lista.size()-1;
    TEXTO resto;
    if (nCampos == 2)
    {
        resto = lista.at(1);
    }
    else
    {
        resto = lista.at(2);
    }
    TEXTO nombreRaiz="";
    if (!obra)
    {
        obra= new Obra(padre);
    }
    //guardo el nombre de la raiz para ponerlo al principio
    if (esRaiz(padre))
    {
        nombreRaiz=padre;
    }
    quitarSimbolos(padre);

    TEXTO registros[3]; //nombrehijo, factor, cantidad
    QStringList relaciones = resto.split("\\");
    for (int i=0; i<nHijos; i++)
    {
        //qDebug()<<"Vuelta "<<i<<nHijos<<" - "<<relaciones.size()<<"Num hjijos: "<<nHijos;
        for (int j=0;j<3;j++)
        {
            registros[j] = relaciones.first();
            relaciones.pop_front();
        }
        //qDebug()<<"Padre: "<<padre<<" - "<<"Hijo: "<<registros[0];
        float cant =  registros[2].toFloat();
        MedCert medi = procesarMediciones(registroM, padre, registros[0]);//registros[0]==nombrehijo
        if (medi.hayMedCert())
        {
            obra->CrearPartida(padre, medi, registros[0]);
        }
        else
        {
            obra->CrearPartida(padre, cant, registros[0]);
        }
    }
    //si tengo la raiz la pongo al comienzo
    if (nombreRaiz.length()>0)
    {
        quitarSimbolos(nombreRaiz);
        obra->EscribeRaiz(nombreRaiz);
    }
}

void AbrirGuardarBC3::procesarConceptos(Obra* &obra, QStringList &registroC)
{
    foreach (const QString& linea, registroC)
    {
        QStringList datos = linea.split("|");
        QString codigo = datos.at(0);
        QString codigo_comp = datos.at(0);
        codigo.remove('#');
        pNodo minodo = obra->ExisteConcepto(codigo);
        if (minodo)
        {
            //unidad
            Unidad U;
            int numUd= U.LeeNumUd(datos.at(1).toStdString());
            minodo->datonodo.EscribeUd(numUd);
            //resumen
            minodo->datonodo.EscribeResumen(datos.at(2));
            //cantidad
            float cantidad = datos.at(3).toFloat();
            minodo->datonodo.EscribePrecio(cantidad);
            //fecha
            std::string cadenafecha = datos.at(4).toStdString();
            Fecha F(cadenafecha);
            minodo->datonodo.EscribeFecha(F);
            //naturaleza
            int nat=0; //inicializo a 0 (sin definir)
            if (datos.at(5)!="0")
            {
                nat=datos.at(5).toInt();
            }
            else if (codigo_comp.contains("#"))
            {
                nat=Codificacion::Capitulo;
            }
            else
            {
                nat=Codificacion::Partida;
            }
            minodo->datonodo.EscribeNaturaleza(nat);
        }
    }
}

MedCert AbrirGuardarBC3::procesarMediciones(QStringList &registroM, TEXTO nombrepadre, TEXTO nombrehijo)
{
    //QString linea;
    int i=0;
    foreach (const QString &linea, registroM)
    {
        QStringList datos = linea.split("|");
        QStringList padrehijo = datos.at(0).split("\\");
        QString padre = padrehijo.at(0);
        quitarSimbolos(padre);
        QString hijo = padrehijo.at(1);
        if (padre==nombrepadre && hijo == nombrehijo)
        {
            Medicion eme;
            QStringList medicion = datos.at(3).split("\\");
            int lineasmedicion = medicion.size()/6;
            std::string conceptos[6];
            for (int i=0;i<lineasmedicion;i++)
            {
                for (int j=0;j<6;j++)
                {
                    conceptos[j]= medicion.first().toStdString();
                    medicion.pop_front();
                }
                float cantidades[4];
                for (int i=0; i<4; i++)
                {
                    conceptos[i+2].length()>0 ? cantidades[i]=tofloat(conceptos[i+2]) : cantidades[i]=0;
                    //std::cout<<conceptos[i+2]<<" -- "<<cantidades[i]<<std::endl;
                }
                TipoLinea tipo;
                if (conceptos[0].size()==0)
                {
                    tipo=TipoLinea::NORMAL;
                }
                else
                {
                    tipo= (TipoLinea)(std::stoi(conceptos[0]));//casting de int a TipoLinea
                }
                if (tipo==TipoLinea::FORMULA)
                {
                    eme.Insertar(i,"",cantidades[0],cantidades[1],cantidades[2],cantidades[3], QString::fromStdString(conceptos[1]),tipo);
                }
                else
                {
                    eme.Insertar(i,QString::fromStdString(conceptos[1]),cantidades[0],cantidades[1],cantidades[2],cantidades[3], "",tipo);
                }

            }
            MedCert MC;
            MC.EscribeMedicion(eme);
            registroM.removeAt(i);
            return MC;
        }
        i++;
    }
    return MedCert();
}

void AbrirGuardarBC3::procesarTexto(Obra *&obra,const QStringList &registroT)
{
    QString linea;
    foreach (linea, registroT)
    {
        QStringList datos = linea.split("|");
        QString codigo = datos.at(0);
        codigo.remove('#');
        pNodo minodo = obra->ExisteConcepto(codigo);
        if (minodo)
        {
            minodo->datonodo.EscribeTexto(datos.at(1));
        }
    }
}

/*********************GUARDAR****************************************/

void AbrirGuardarBC3::Escribir(QFile &fichero, Obra *obra)
{
    TEXTO cadenabc3;
    EscribirRegistroV(cadenabc3);
    EscribirRegistroK(cadenabc3);
    /********Registros C y D**************/
    pNodo indice=obra->G->LeeRaiz();
    for (int i=0; i<obra->G->LeeNumNodos(); i++)
    {
        EscribirRegistroC(indice,cadenabc3,obra);
        if (indice->adyacente)
        {
            EscribirRegistroD(indice,cadenabc3,obra);
        }
        indice=indice->siguiente;
    }
    /*******Registro M y N************/
    /**vuelvo al inicio**/
    indice=obra->G->LeeRaiz();
    while(indice)
    {
        if (indice->adyacente)
        {
            pArista A = indice->adyacente;
            while (A)
            {
                EscribirRegistroM(indice, A, cadenabc3,obra);
                A=A->siguiente;
            }
        }
        indice=indice->siguiente;
    }
    /******************Registro T*************/
    indice=obra->G->LeeRaiz();
    while(indice)
    {
        if (!indice->datonodo.LeeTexto().isEmpty())
        {
            EscribirRegistroT(indice,cadenabc3);
        }
        indice=indice->siguiente;
    }
    QTextStream texto(&fichero);
    texto.setCodec("Windows-1252");
    texto<<cadenabc3;
    //ofs<<FinDeArchivo;
}

void AbrirGuardarBC3::EscribirRegistroV(TEXTO &cadena)
{
    cadena.append("~V|EGSOFT S.A.|FIEBDC-3/2012|SDMed 0.1||ANSI||||||");
    cadena.append("\n");
}

void AbrirGuardarBC3::EscribirRegistroK(TEXTO &cadena)
{
    cadena.append("~K|\\2\\2\\3\\2\\2\\2\\2\\EUR\\|0|");
    cadena.append("\r\n");
}

void AbrirGuardarBC3::EscribirRegistroC(const pNodo concepto, TEXTO& cadena, const Obra* obra)
{
    cadena.append("~C|");
    cadena.append(concepto->datonodo.LeeCodigo());
    escribirAlmohadilla(concepto,obra,cadena);
    cadena.append("|");
    cadena.append(concepto->datonodo.LeeUd());
    cadena.append("|");
    cadena.append(concepto->datonodo.LeeResumen());
    cadena.append("|");
    cadena.append(QString::number(concepto->datonodo.LeeImportePres()));
    cadena.append("|");
    cadena.append(concepto->datonodo.LeeFecha());
    cadena.append("|");
    cadena.append(QString::number(concepto->datonodo.LeeNat()));
    cadena.append("|");
    cadena.append("\r\n");
}

void AbrirGuardarBC3::EscribirRegistroD(const pNodo concepto, TEXTO& cadena, const Obra* obra)
{
    TEXTO factor="1";//por ahora factor vale 1...en el futuro puede tener un valor
    cadena.append("~D|");
    cadena.append(concepto->datonodo.LeeCodigo());
    escribirAlmohadilla(concepto,obra,cadena);
    cadena.append("|");
    if (concepto->adyacente)
    {
        pArista A=concepto->adyacente;
        while (A)
        {
            cadena.append(A->destino->datonodo.LeeCodigo());
            cadena.append("\\");
            cadena.append(factor);
            cadena.append("\\");
            cadena.append(QString::number(A->datoarista.LeeMedicion().LeeTotal()));
            cadena.append("\\");
            A=A->siguiente;
        }
    }
    cadena.append("|");
    cadena.append("\r\n");
}

void AbrirGuardarBC3::EscribirRegistroM(pNodo padre, pArista A, TEXTO& cadena, const Obra* obra)
{
    cadena.append("~M|");
    //pNodo padre = buscarPadre (A,obra);
    cadena.append(padre->datonodo.LeeCodigo());
    escribirAlmohadilla(padre,obra,cadena);
    cadena.append("\\");
    cadena.append(A->destino->datonodo.LeeCodigo());
    cadena.append("||");//por ahora obvio el campo de POSICION
    cadena.append(QString::number(A->datoarista.LeeMedicion().LeeTotal()));
    cadena.append("|");
    /********empezamos con las lineas de medicion******************/
    for (auto it=A->datoarista.LeeMedicion().LeeLista().begin(); it!=A->datoarista.LeeMedicion().LeeLista().end(); ++it)
    {
        /*ofs<<(*it).LeeTipo()<<"\\"<<(*it).LeeComentario()<<"\\"<<(*it).Lee_N_Uds()<<"\\"<<(*it).LeeLargo()<<"\\"
           <<(*it).LeeAncho()<<"\\"<<(*it).LeeAlto()<<"\\";*/
        cadena.append(QString::number((int)(it->LeeTipo())));
        cadena.append("\\");
        cadena.append(it->LeeComentario());
        cadena.append("\\");
        cadena.append(QString::number(it->Lee_N_Uds()));
        cadena.append("\\");
        cadena.append(QString::number(it->LeeLargo()));
        cadena.append("\\");
        cadena.append(QString::number(it->LeeAncho()));
        cadena.append("\\");
        cadena.append(QString::number(it->LeeAlto()));
        cadena.append("\\");
    }
    cadena.append("|");
    cadena.append("\r\n");
}

void AbrirGuardarBC3::EscribirRegistroT(const pNodo concepto, TEXTO& cadena)
{
    cadena.append("~T|");
    cadena.append(concepto->datonodo.LeeCodigo());
    cadena.append("|");
    QTextDocument doc;
    doc.setHtml(concepto->datonodo.LeeTexto());
    TEXTO cadenaSinHtml = doc.toPlainText();
    cadena.append(cadenaSinHtml);
    cadena.append("|");
    cadena.append("\r\n");
}

/*********************VARIOS**************************/
bool AbrirGuardarBC3::esRaiz(const QString& S)
{
    return (S.at(S.length()-1)=='#' && S.at(S.length()-2)=='#');
}

void AbrirGuardarBC3::quitarSimbolos (TEXTO &codigo)
{
    //int posicion=-1;
    int posicion = codigo.indexOf('#');
    if (posicion>0 || posicion==0)
    {
        codigo.truncate(posicion);
    }
}

void AbrirGuardarBC3::escribirAlmohadilla(const pNodo concepto, const Obra* obra, TEXTO &cadena)
{
    if (concepto==obra->G->LeeRaiz())
    {
        cadena.append("##");
    }
    if (obra->G->LeeRaiz()->adyacente)
    {
        pArista A=obra->G->LeeRaiz()->adyacente;
        while (A)
        {
            if (concepto==A->destino)
            {
                cadena.append("#");
            }
            A=A->siguiente;
        }
    }
}

template <typename T>
std::string AbrirGuardarBC3::tostr(const T& t)
{
    std::ostringstream os;
    os<<t;
    return os.str();
}

float tofloat(std::string cadena)
{
    size_t pos = cadena.find(("."));
    float valor=0;
    if (pos<cadena.size())
    {
        int num_decimales = cadena.size()-pos-1;
        int divisor=1;
        for (int i=0;i<num_decimales;i++)
        {
            divisor*=10;
        }
        cadena.replace(pos,1,"");
        valor = std::stof(cadena)/divisor;
    }
    else
    {
        valor=stof(cadena);
    }
    return valor;
}
