#ifndef FILTER_H
#define FILTER_H

#include <QApplication>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include "./Tablas/tablabase.h"

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = nullptr);
    bool eventFilter(QObject* object, QEvent *event) override;
};

#endif // FILTER_H
