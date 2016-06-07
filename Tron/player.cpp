#include "player.h"

Player::Player(QFrame* parent, const QColor color) : QFrame(parent),_color(color){
    _x = _y = 50;
    _dx = 2;
    _dy = 1;
    _sq_sz = 40;
}

void Player::paintEvent(QPaintEvent* event){
    QFrame::paintEvent(event);
    QPainter painter(this);

    painter.fillRect(_x, _y, _sq_sz, _sq_sz, _color);

}

void Player::draw()
{
    repaint();
}
