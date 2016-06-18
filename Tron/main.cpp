#include "tabuleiro.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Tabuleiro tron;
    tron.show();

    return a.exec();
}
