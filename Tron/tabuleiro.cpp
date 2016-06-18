#include "tabuleiro.h"
#include <QDebug>

Tabuleiro::Tabuleiro(QFrame* parent) : QFrame(parent){

    tamanhoTabuleiro = new QSize(800,600);
    _yellow_player = new Player(*tamanhoTabuleiro, 'u');
    _x = 0;
    _y = 0;
    _counter = 0;
    _accumulator60 = 0;
    _max_fps = 60;
    _constant_dt = 1000 / _max_fps;
    _last_time_60fps = QDateTime::currentMSecsSinceEpoch();
    movePlayer = 2;
    setMinimumSize(800,600);
    mostrarMenu = false;
    deslocamentoXP1 = 2;
    deslocamentoYP1 = 2;
    esquerda = direita = cima = baixo = false;

    for(int linha=0; linha<40; linha++){
        for(int coluna=0; coluna<54; coluna++){
            _squad[linha][coluna] = new Squad();
            _corXY[linha][coluna] = 0;
        }
    }

    QIcon* _icon = new QIcon(":/icon.jpg");
    setWindowIcon(*_icon);

    // Start timer
    QTimer::singleShot(1000/_max_fps, this, SLOT(_tick()));
}

void Tabuleiro::paintEvent(QPaintEvent* event){
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width()-1, height()-1);
    painter.setBrush(Qt::CrossPattern);
    painter.setPen(Qt::black);
    painter.fillRect(0, 0, width(), height(), Qt::darkBlue);
    painter.drawRect(0,0,width(),height());

    _yellow_player->setArenaSize(this->size());

    if(mostrarMenu){
        painter.setBrush(Qt::Dense2Pattern);
        painter.drawRect(0, this->y()+10, width(), 200);
    }else{
        /* Paint black frame around the canvas */

        painter.setBrush(Qt::yellow);

        _yellow_player->draw(&painter);
        _yellow_player->move(_constant_dt);

        for(int linha=0; linha<40; linha++){
            for(int coluna=0; coluna<54; coluna++){
                if(_corXY[linha][coluna] == 1){
                    painter.setBrush(Qt::yellow);
                }

                if(_corXY[linha][coluna] == -1){
                    painter.setBrush(Qt::green);
                }

                if(_corXY[linha][coluna] == 0){
                    painter.setBrush(Qt::transparent);
                }
                _squad[linha][coluna]->draw(_x,_y,painter,painter.brush());
                _x += 16;
            }
            _y += 16;
            _x = 0;
        }
        _x = 0;
        _y = 0;
    }
}

void Tabuleiro::_tick()
{
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    {
        qint64 passed = now - _last_time_60fps;

        _accumulator60 += passed;
        while (_accumulator60 >= _constant_dt)
        {
            _accumulator60 -= _constant_dt;
        }

        _last_time_60fps = now;
    }

    _counter++;
    _counter = _counter % 60; // Ranges from 0 to 59
    // Reset the timer
    QTimer::singleShot(1000/_max_fps, this, SLOT(_tick()));

    this->draw();
}

void Tabuleiro::draw(){
    repaint();
}

void Tabuleiro::keyPressEvent(QKeyEvent* event){
    int keypress = event->key();

    if(keypress == Qt::Key_M){
        mostrarMenu = false;
    }


    if(keypress == Qt::Key_I && cima == false){
        cima = true;
        deslocamentoYP1 *= -1;
        _yellow_player->setSpeed(QVector2D(0,deslocamentoYP1));
        baixo = false;
        esquerda = false;
        direita = false;
    }
    if(keypress == Qt::Key_K && baixo == false){
        baixo = true;
        deslocamentoYP1 *= -1;
        _yellow_player->setSpeed(QVector2D(0,deslocamentoYP1));
        cima = false;
        esquerda = false;
        direita = false;
    }
    if(keypress == Qt::Key_J && esquerda == false){
        esquerda = true;
        deslocamentoXP1 *= -1 ;
        _yellow_player->setSpeed(QVector2D(deslocamentoXP1,0));
        direita = false;
        cima = false;
        baixo = false;
    }
    if(keypress == Qt::Key_L && direita == false){
        direita = true;
        deslocamentoXP1 *= -1;
        _yellow_player->setSpeed(QVector2D(deslocamentoXP1,0));
        esquerda = false;
        cima = false;
        baixo = false;
    }
}


