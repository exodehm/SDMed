#include "delegadoeditornumeros.h"

DelegadoEditorNumeros::DelegadoEditorNumeros(QObject *parent):DelegadoBase(parent)
{
    rx = new QRegExp("[-]{0,1}[0-9]{0,5}[\\,\\.]{1}[0-9]{1,3}");
}

QWidget* DelegadoEditorNumeros::createEditor(QWidget * parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const QAbstractItemModel * model = index.model();
    if (!model)
    {
        return QStyledItemDelegate::createEditor(parent,option, index);
    }
    QLineEdit* mieditor = new QLineEdit(parent);
    mieditor->setValidator(new QRegExpValidator(*rx));
    return mieditor;
}

void DelegadoEditorNumeros::setEditorData(QWidget * editor, const QModelIndex&index) const
{
    QLineEdit *mieditor=qobject_cast<QLineEdit*>(editor);
    if (!mieditor)
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
    mieditor->setText(index.data().toString());
}

void DelegadoEditorNumeros::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex&index) const
{
    if (!index.isValid()) return;
    QLineEdit * mieditor=qobject_cast<QLineEdit * >(editor);    
    if (!mieditor)
    {
        return QStyledItemDelegate::setModelData(editor, model, index);
    }
    QString dato = mieditor->text();
    dato.replace(",",".");
    model->setData(index,dato,Qt::DisplayRole);
    model->setData(index,dato,Qt::EditRole);
}

void DelegadoEditorNumeros::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{ 
    /*QAbstractItemModel *model =const_cast<QAbstractItemModel *>(index.model());
    PrincipalModel* modelo=qobject_cast<PrincipalModel*>(model);
    if (modelo && /*modelo->LeeObra()->HayDescomposicion() && modelo->HayListaDatos() && index.isValid())
    {              
        QModelIndex indice = index;
        qDebug()<<"indice 1: "<<indice.row()<<"--"<<indice.column();
        if (modelo->HayFilaVacia() && modelo->HayListaDatos())
        {
            if (index.row()>=modelo->FilaVacia())
            {
                //indice = modelo->index(indice.row()-1,indice.column());
                indice = modelo->index(0,0);
                //indice.row() = indice.row()-1;
            }
        }
        qDebug()<<"indice 2: "<<indice.row()<<"##"<<indice.column();

        painter->save();
        painter->setPen(modelo->LeeColor(indice.row()+1,indice.column()));
        qDebug()<<"El dato en: "<<indice.row()<<","<<indice.column()<<" es: "<<indice.data()<<" y el color es: "<<modelo->LeeColorS(indice.row()+1,indice.column());
        painter->drawText(option.rect, Qt::AlignCenter, displayText(indice.data(), QLocale::system()));
        painter->restore();
    }
    else*/
    {
        //painter->drawText(option.rect, Qt::AlignCenter, displayText(index.data(), QLocale::system()));
        QStyledItemDelegate::paint(painter, option, index);
    }    
}

QSize DelegadoEditorNumeros::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //return QSize( 45, 15);
    return option.rect.size();
}

QString DelegadoEditorNumeros::displayText(const QVariant & value, const QLocale & locale) const
{
   float valor = value.toFloat();
   if (valor==0)
   {
       return "";
   }
   else
   {
       return locale.toString(valor,'f',2);
   }
}
