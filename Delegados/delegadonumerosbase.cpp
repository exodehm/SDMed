#include "delegadonumerosbase.h"

DelegadoNumerosBase::DelegadoNumerosBase(QObject *parent):DelegadoBase(parent)
{
    rx = new QRegExp("[-]{0,1}[0-9]{0,5}[\\,\\.]{1}[0-9]{1,3}");
}

QWidget* DelegadoNumerosBase::createEditor(QWidget * parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
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

void DelegadoNumerosBase::setEditorData(QWidget * editor, const QModelIndex&index) const
{
    QLineEdit *mieditor=qobject_cast<QLineEdit*>(editor);
    if (!mieditor)
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
    mieditor->setText(index.data().toString());
}

void DelegadoNumerosBase::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex&index) const
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

void DelegadoNumerosBase::paint( QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    DelegadoBase::paint(painter, option, index);
}

QSize DelegadoNumerosBase::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)    
    return option.rect.size();
}

QString DelegadoNumerosBase::displayText(const QVariant & value, const QLocale & locale) const
{
   float valor = value.toFloat();
   if (valor==0)
   {
       return "";
   }
   else
   {
       return locale.toString(valor,'f',3);
       //return QString("%1").arg(valor,5,'f',4,QLatin1Char('0'));
   }
}
