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
    void colisaoYellowPlayer();
    void colisaoGreenPlayer();
    void moveP1();
    void moveP2();
    void startGame();

private:
    Player* _yellow_player, *_green_player;
    qint64 _last_time_60fps;
    qint64 _accumulator60;
    qint64 movePlayer;
    QVector<QPoint> caminhoP1;
    QVector<QPoint> caminhoP2;
    int _max_fps, _x, _y;
    int _counter;
    float _constant_dt, deslocamentoXP1, deslocamentoYP1, deslocamentoXP2, deslocamentoYP2;
    QSize* tamanhoTabuleiro;
    bool mostrarMenu;
    char direction;
    Squad* _squad[40][53];
    int _corXY[40][53];
    bool esquerda, direita, cima, baixo, fps;
    bool esquerda2, direita2, cima2, baixo2;

private slots:
    void _tick();
};

#endif // TABULEIRO_H
