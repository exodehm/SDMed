#include "abrirguardarseg.h"

AbrirGuardarSEG::AbrirGuardarSEG():AbrirGuardar()
{

}

Obra* AbrirGuardarSEG::Leer(QString nombrefichero)
{
    Obra* obra = nullptr;//= new Obra;
    QFile fichero(nombrefichero);
    if(!fichero.open(QIODevice::ReadOnly))
    {
        qFatal("No puedo abrir el fichero");
        return obra;
    }
    QDataStream datos(&fichero);
    quint32 numbermagic;
    datos>>numbermagic;
    if (numbermagic!=0xA0B0C0D0)
    {
        qFatal("Numero magico incorrecto");
        return obra;
    }
    //version
    quint32 version;
    datos>>version;
    int numNodos;
    datos>>numNodos;
    qDebug()<<"El numero de nodos es: "<<numNodos;
    Concepto concepto;
    leerConcepto(concepto,datos);
    obra = new Obra(concepto.LeeCodigo(),concepto.LeeResumen());
    pNodo indice = obra->LeeGrafo()->LeeRaiz();
    indice->datonodo.EscribeTexto(concepto.LeeTexto());//para poner el texto de la partida raiz
    indice->datonodo.EscribeImportePres(concepto.LeeImportePres());//poner el precio a la raizr
    obra->InsertarMapa(concepto.LeeCodigo(),indice);
    //hago la lista de nodos
    for (int i=0;i<numNodos-1;i++)//-1 porque la raiz se mete antes, fuera del bucle
    {
        leerConcepto(concepto,datos);
        pNodo nodo = new t_nodo(concepto);
        obra->InsertarMapa(concepto.LeeCodigo(),nodo);
        indice->siguiente=nodo;        
        indice = indice->siguiente;        
    }
    //lista de aristas por cada nodo
    int numhijos;
    for (int i=0;i<numNodos;i++)//recorro la lista de nodos
    {
        datos>>numhijos;
        std::cout<<"Numero de hijos: "<<numhijos<<std::endl;
        TEXTO padre;
        datos>>padre;
        std::cout<<"padre: "<<padre.toStdString()<<std::endl;
        for (int i=0;i<numhijos;i++)
        {
            TEXTO hijo;
            datos>>hijo;
            float cantidad;
            datos>>cantidad;
            std::cout<<"Hijo "<<i<<":"<<hijo.toStdString()<<std::endl;
            MedCert M;
            leerMedicion(M,datos);
            if (M.hayMedCert())
            {
                obra->CrearPartida(padre,M, hijo);
            }
            else
            {
                obra->CrearPartida(padre,cantidad,hijo);
            }
        }
    }   
    return obra;
}

void AbrirGuardarSEG::leerConcepto(Concepto &C, QDataStream &datos)
{
    TEXTO codigo;datos>>codigo;    
    C.EscribeCodigo(codigo);//datos<<C.LeeCodigo();
    TEXTO unidad;datos>>unidad;
    C.EscribeUd(unidad);//datos<<C.LeeUd();
    int nat;datos>>nat;
    C.EscribeNaturaleza(nat);//datos<<(int)C.LeeNat();
    int div;datos>>div;
    //datos<<(int)C.LeeDivisa();//pendiente de asignacion
    int dur;datos>>dur;
    //datos<<(int)C.LeeDuracion();//pendiente de asignacion
    int exis;datos>>exis;
    //datos<<(int)C.LeeExistencias();//pendiente de asignacion
    float fac;datos>>fac;
    //datos<<(float)C.LeeFactorRendimiento();//pendiente de asignacion
    int form;datos>>form;
    //datos<<(int)C.LeeFormula();//pendiente de asinacion
    int info;datos>>info;
    //datos<<(int)C.LeeInfo();//pendiente de asignacion
    TEXTO fecha;datos>>fecha;
    Fecha efe(fecha.toStdString());
    C.EscribeFecha(efe);//datos<<C.LeeFecha();
    TEXTO res;datos>>res;
    C.EscribeResumen(res);//datos<<C.LeeResumen();
    float impres;datos>>impres;
    C.EscribeImportePres(impres);//datos<<(float)C.LeeImportePres();
    float impcert;datos>>impcert;
    C.EscribeImporteCert(impcert);//datos<<(float)C.LeeImporteCert();
    TEXTO tex;datos>>tex;
    C.EscribeTexto(tex);//datos<<C.LeeTexto();
    std::cout<<"codigo:"<<codigo.toStdString()<<" importe: "<<impres<<std::endl;
}

void AbrirGuardarSEG::leerMedicion(MedCert& MC, QDataStream &datos)
{
    int tamListamedicion;
    datos>>tamListamedicion;
    Medicion med;
    for (int i=0;i<tamListamedicion;i++)
    {
        LineaMedicion l;
        leerLineaMedicion(l,datos);
        med.Insertar(i,l);
    }
    MC.EscribeMedicion(med);
}

void AbrirGuardarSEG::leerLineaMedicion(LineaMedicion& l,  QDataStream &datos)
{    
    int fase;datos>>fase;
    l.EscribeFase(fase);
    TEXTO comentario;datos>>comentario;
    l.EscribeComentario(comentario);
    float ud;datos>>ud;
    l.EscribeUds(ud);
    float largo;datos>>largo;
    l.EscribeLargo(largo);
    float ancho;datos>>ancho;
    l.EscribeAncho(ancho);
    float alto;datos>>alto;
    l.EscribeAlto(alto);
    TEXTO formula;datos>>formula;
    l.EscribeFormula(formula);
    int tipo;datos>>tipo;
    l.EscribeTipo(tipo);
    float subtotal;datos>>subtotal;
    l.EscribeSubtotal(subtotal);
    //el parcial se escribe en funcion de los otros campos
    l.EscribeParcial();
}

/*********************GUARDAR****************************************/

void AbrirGuardarSEG::Escribir(QFile &fichero, Obra *obra)
{
    std::cout<<"Funcion Escribir SEG"<<std::endl;
    QDataStream datos(&fichero);
    //Write a header with a "magic number" and a version
    datos << (quint32)0xA0B0C0D0;
    datos << (qint32)90;
    datos.setVersion(QDataStream::Qt_5_4);
    //
    std::list<pNodo>listanodos = obra->ListaConceptos();
    datos << (int)listanodos.size();    
    for (auto elem:listanodos)
    {
        EscribirConcepto(elem->datonodo,datos);
    }
    for (auto elem:listanodos)
    {
        Obra::ListaAristasNodos lista = obra->LeeGrafo()->recorrerHijos(elem);
        datos<<(int)lista.size();//inserto el numero de hijos de cada nodo de la lista
        datos<<elem->datonodo.LeeCodigo();//inserto el codigo del nodo padre
        for (auto elem:lista)
        {
            datos<<elem.first->destino->datonodo.LeeCodigo();//inserto los codigos de los nodos hijos
            datos<<(float)elem.first->datoarista.LeeMedicion().LeeTotal();
            escribirMedicion(elem.first,datos,MedCert::MEDICION);
        }
    }
    std::cout<<"Fichero escrito"<<std::endl;
}

void AbrirGuardarSEG::EscribirConcepto(Concepto &C, QDataStream& datos)
{
    datos<<C.LeeCodigo();
    datos<<C.LeeUd();
    datos<<(int)C.LeeNat();
    datos<<(int)C.LeeDivisa();
    datos<<(int)C.LeeDuracion();
    datos<<(int)C.LeeExistencias();
    datos<<(float)C.LeeFactorRendimiento();
    datos<<(int)C.LeeFormula();
    datos<<(int)C.LeeInfo();
    datos<<C.LeeFecha();
    datos<<C.LeeResumen();
    datos<<(float)C.LeeImportePres();
    datos<<(float)C.LeeImporteCert();
    datos<<C.LeeTexto();    
}

void AbrirGuardarSEG::escribirMedicion(pArista a, QDataStream &datos, int tabla)
{
    int numlineasmedicion=a->datoarista.LeeMedCer(tabla).LeeLista().size();
    datos<<numlineasmedicion;
    for (auto elem:a->datoarista.LeeMedCer(tabla).LeeLista())
    {
        datos<<(int)elem.LeeFase();
        datos<<elem.LeeComentario();
        datos<<(float)elem.Lee_N_Uds();
        datos<<(float)elem.LeeLargo();
        datos<<(float)elem.LeeAncho();
        datos<<(float)elem.LeeAlto();
        datos<<elem.LeeFormula();
        datos<<(int)elem.LeeTipo();
        datos<<(float)elem.LeeSubtotal();
    }
}
