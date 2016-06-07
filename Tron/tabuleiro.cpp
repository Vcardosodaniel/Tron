#include "tabuleiro.h"

Tabuleiro::Tabuleiro(QFrame* parent) : QFrame(parent){
    setMinimumSize(800,600);
}

void Tabuleiro::paintEvent(QPaintEvent* event){
    QFrame::paintEvent(event);

    /* Paint white background */

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::white);

    /* Paint black frame around the canvas */

    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width()-1, height()-1);

}


void Tabuleiro::_tick(){

}
