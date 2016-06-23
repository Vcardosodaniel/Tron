#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>

class Player
{
public:
    Player(QSize arena_size, char direction);

    void move(qint64 dt);
    void draw(QPainter* painter);

    void setArenaSize(QSize arena_size);
    void setSpeed(QVector2D speed);
    void reset(QPoint initial_pos);

    QPoint position;
    QSize size();
    QPoint _pos;

private:
    QSize _arena_sz;
    QVector2D _speed;
    float _dx, _dy;
    int _x, _y;
};

#endif // PLAYER_H
