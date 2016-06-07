#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QtWidgets>
#include "player.h"

class Tabuleiro : public QFrame
{
    Q_OBJECT
public:
    explicit Tabuleiro(QFrame *parent = 0);
    void paintEvent(QPaintEvent* event);

private:
    Player* _yellow_player;
    qint64 _last_time_60fps;
    qint64 _accumulator60;
    int _max_fps;
    int _counter;
    float _constant_dt;

private slots:
    void _tick();
};

#endif // TABULEIRO_H
