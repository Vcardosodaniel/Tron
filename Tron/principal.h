#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QtWidgets>
#include "tabuleiro.h"

class Principal : public QWidget
{
    Q_OBJECT

public:
    Principal(QWidget *parent = 0);
    ~Principal();

private:
    Tabuleiro* tabuleiro;
    QLabel* teste;
    QVBoxLayout* layoutPrincipal;

};

#endif // PRINCIPAL_H
