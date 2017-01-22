#ifndef FILTER_H
#define FILTER_H

#include <QObject>
//#include <QTableView>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
//#include <QLineEdit>
//#include <QStyledItemDelegate>

#include "./Tablas/tablamedcert.h"


class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = nullptr);
    bool eventFilter(QObject* object, QEvent *event) override;

signals:

public slots:
};

#endif // FILTER_H
