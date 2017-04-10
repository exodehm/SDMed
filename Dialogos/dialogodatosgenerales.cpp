#include "dialogodatosgenerales.h"

DialogoDatosGenerales::DialogoDatosGenerales(Obra* O, QWidget *parent) : QDialog(parent)
{
    //(***POR AHORA EL COMBO DE LOS IDIOMAS ESTA RELLENADO EN EL DESIGNER
    setupUi(this);
    QBrush *fondo= new QBrush(Qt::lightGray);
    /**************COMBO LISTA CODIFICACIONES*************************/
    for (int i=0;i<O->Codificacion.LeeTam();i++)
    {
        //this->comboListaCuadroPrecios->addItem(QString::fromStdString(O->Codificacion.LeeNombre(i)));
    }
    this->comboListaCuadroPrecios->setCurrentIndex(1);//selecciono como actual PREOC_EOCE
    /**************FIN COMBO LISTA CODIFICACIONES*************************/

    /*******************TABLA DE REDONDEOS****************************/
    QStringList CabeceraRedondeos;
    CabeceraRedondeos<<"Nombre"<<"Decimales";
    this->TablaCoeficientes->setColumnCount(2);
    this->TablaCoeficientes->setRowCount(O->Redondeos.Factores.size());
    this->TablaCoeficientes->setHorizontalHeaderLabels(CabeceraRedondeos);
    int i=0;
    for (auto it=O->Redondeos.Factores.begin();it!=O->Redondeos.Factores.end();it++)
    {
        QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString((*it).first));
        item->setBackground(*fondo);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        this->TablaCoeficientes->setItem(i,0,item);
        this->TablaCoeficientes->setItem(i,1,new QTableWidgetItem(QString::number((*it).second)));
        i++;
    }
    this->TablaCoeficientes->setColumnWidth(0,400);
    this->TablaCoeficientes->verticalHeader()->hide();
    this->TablaCoeficientes->resize(505,305);
    //!!!!!!!QUEDA PENDIENTE LA VALIDACION DE LOS COEFICIENTES!!!!!!!!!!!!!!!!
    /*************************FIN TABLA REDONDEOS**************************************/

    /*********CUADRO COSTES INDIRECTOS**********************************/
    QValidator *validador = new QIntValidator(1, 999, this);
    this->lineEditCostesIndirectos->setValidator(validador);
    /*******FIN CUADRO COSTES INDIRECTOS**********************************/

    /************LISTA OPCIONES**********************************/
    /*for (int i=0;i<O->DatosDeObra.TamLista();i++)
    {
        this->comboListaDatos->addItem(QString::fromStdString(O->DatosDeObra.LeeElementoListaDeDatos(i)));
    }*/
    /***********FIN LISTA OPCIONES******************************/

    /********TABLA LISTA DATOS GENERALES******************/
    crearTablaDatosGenerales(0);


    /******FIN TABLA LISTA DATOS GENERALES****************/

    QObject::connect(this->comboListaDatos,SIGNAL(currentIndexChanged(int)), this,SLOT(crearTablaDatosGenerales(int)));
}

void DialogoDatosGenerales::crearTablaDatosGenerales (int n)
{
    /*this->TablaDatosGenerales->setColumnCount(2);
    this->TablaDatosGenerales->setRowCount(n);*/

    QStringList CabeceraDatosGenerales;
    CabeceraDatosGenerales<<"Nombre"<<"Valor";
   // this->TablaDatosGenerales->setHorizontalHeaderLabels(CabeceraDatosGenerales);
    /*i=0;
    for (auto it=O->DatosDeObra.LeerPorcentajes().ListaPorcentajes.begin();it!=O->DatosDeObra.LeerPorcentajes().ListaPorcentajes.end();++it)
    {
        QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString((*it).first));
        item->setBackground(*fondo);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        this->TablaDatosGenerales->setItem(i,0,item);
        this->TablaDatosGenerales->setItem(i,1,new QTableWidgetItem(QString::number((*it).second,'g',2)));
        qDebug()<<QString::fromStdString((*it).first)<<"\n";
        i++;
    }*/
    //this->TablaDatosGenerales->setColumnWidth(0,400);
    //this->TablaDatosGenerales->setColumnWidth(1,30);
    //this->TablaDatosGenerales->verticalHeader()->hide();
    //this->TablaDatosGenerales->resize(430,305);
}

int DialogoDatosGenerales::LeeCodificacion()
{
    return this->comboListaCuadroPrecios->currentIndex();
}
