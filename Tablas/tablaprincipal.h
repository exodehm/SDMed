#ifndef TABLAPRINCIPAL_H
#define TABLAPRINCIPAL_H

#include <QTableView>
#include <QKeyEvent>
#include <QHeaderView>
#include <QDebug>

class TablaPrincipal : public QTableView
{
    Q_OBJECT
public:
    explicit TablaPrincipal(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // TABLAPRINCIPAL_H
