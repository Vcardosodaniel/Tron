#include "squad.h"


Squad::Squad(): draw_shape1(true)
{

}

Squad::~Squad(){

}

void Squad::draw(int x, int y, QPainter &painter, const QBrush &brush){

    _pos_x = x;
    _pos_y = y;

    painter.fillRect(x, y, 50, 50, brush);
}

int Squad::x(){
    return _pos_x;
}

int Squad::y(){
    return _pos_y;
}

int Squad::w(){
    return (50);
}

int Squad::h(){
    return (50);
}

QPainterPath Squad::shape() const
{
    QPainterPath path;
    path.addRect(_pos_x, _pos_y, 50, 50);
    return path;
}
