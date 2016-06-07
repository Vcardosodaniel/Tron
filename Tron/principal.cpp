#include "principal.h"
#include <QDebug>

Principal::Principal(QWidget *parent)
    : QWidget(parent)
{
    tabuleiro = new Tabuleiro();
    layoutPrincipal = new QVBoxLayout(this);
    teste = new QLabel("Tabuleiro: ");

    layoutPrincipal ->addWidget(teste);
    layoutPrincipal ->addWidget(tabuleiro);

    setLayout(layoutPrincipal);

}

Principal::~Principal()
{

}
