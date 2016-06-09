#ifndef PLAYER_H
#define PLAYER_H

#include <QtWidgets>

class Player
{
public:
    Player(QSize arena_size);

    void move(qint64 dt);
    void draw(QPainter* painter);

    void setArenaSize(QSize arena_size);
    void setSpeed(QVector2D speed);

    void reset();
    QPoint position();

private:
    QSize _arena_sz;
    QPoint _pos;
    QVector2D _speed;
};

#endif // PLAYER_H
