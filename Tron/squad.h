#ifndef SQUAD_H
#define SQUAD_H
#pragma once
#include <QtWidgets>



class Squad
{
public:
    Squad();
    ~Squad();
    void draw(int x, int y, QPainter& painter, const QBrush& brush);
    QPainterPath shape() const;
    int x();
    int y();
    int w();
    int h();


private:
    int _pos_x;
    int _pos_y;
    bool draw_shape1;

};

#endif // SQUAD_H
