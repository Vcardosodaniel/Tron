#include "principal.h"

Principal::Principal(QWidget *parent)
    : QWidget(parent)
{
    tabuleiro = new Tabuleiro();
    layoutPrincipal = new QVBoxLayout(this);
    teste = new QLabel("Tabuleiro: ");

    layoutPrincipal ->addWidget(teste);
    layoutPrincipal ->addWidget(tabuleiro);

}

Principal::~Principal()
{

}
