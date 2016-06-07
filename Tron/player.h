#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>

class Player : public QFrame
{
    Q_OBJECT
public:
    explicit Player(QFrame *parent = 0, const QColor color = Qt::black);
    void paintEvent(QPaintEvent* event);
    void draw();


    QColor _color;
    int _sq_sz;
    int _x, _y;
    int _dx, _dy;
};

#endif // PLAYER_H
