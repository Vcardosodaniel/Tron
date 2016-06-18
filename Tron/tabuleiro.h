#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QtWidgets>
#include "player.h"
#include "squad.h"

class Tabuleiro : public QFrame
{
    Q_OBJECT
public:
    explicit Tabuleiro(QFrame *parent = 0);
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void draw();
    bool colisaoP1();

private:
    Player* _yellow_player;
    qint64 _last_time_60fps;
    qint64 _accumulator60;
    qint64 movePlayer;
    int _max_fps, _x, _y;
    int _counter;
    float _constant_dt, deslocamentoXP1, deslocamentoYP1;
    QSize* tamanhoTabuleiro;
    bool mostrarMenu;
    char direction;
    Squad* _squad[40][54];
    int _corXY[40][54];
    bool esquerda, direita, cima, baixo;

private slots:
    void _tick();
};

#endif // TABULEIRO_H
