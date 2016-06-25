#include "tabuleiro.h"
#include <QDebug>

using namespace std;

Tabuleiro::Tabuleiro(QFrame* parent) : QFrame(parent){

    tamanhoTabuleiro = new QSize(800,600);
    _accumulator60 = 0;
    _max_fps = 60;
    _constant_dt = 1000 / _max_fps;
    _last_time_60fps = QDateTime::currentMSecsSinceEpoch();
    movePlayer = 2;
    setMinimumSize(800,600);

    QIcon* _icon = new QIcon(":/icon.jpg");
    setWindowIcon(*_icon);

    // Start timer
    QTimer::singleShot(1000/_max_fps, this, SLOT(_tick()));

    startGame();
}

void Tabuleiro::startGame(){
    _yellow_player = new Player(*tamanhoTabuleiro, 'u');
    _green_player = new Player(*tamanhoTabuleiro, 'u');
    _x = 0;
    _y = 0;
    _counter = 0;
    mostrarMenu = false;
    deslocamentoXP1 = 2;
    deslocamentoYP1 = 2;
    deslocamentoXP2 = 2;
    deslocamentoYP2 = 2;
    caminhoP1.clear();
    caminhoP2.clear();
    esquerda = direita2 =  true;
    direita = cima = baixo = false;
    esquerda2 = cima2 = baixo2 = false;
    fps = true;

    for(int linha=0; linha<40; linha++){
        for(int coluna=0; coluna<53; coluna++){
            _squad[linha][coluna] = new Squad();
            _corXY[linha][coluna] = 0;
        }
    }

    _green_player->_pos.setX(155);
    _green_player->position.setX(_green_player->_pos.x()+7);
    _green_player->_pos.setY(98);
    _green_player->position.setY(_green_player->_pos.y()+7);

    _yellow_player->_pos.setX(550);
    _yellow_player->position.setX(_yellow_player->_pos.x()+7);
    _yellow_player->_pos.setY(448);
    _yellow_player->position.setY(_yellow_player->_pos.y()+7);

    caminhoP1.push_back(_yellow_player->_pos);
    caminhoP2.push_back(_green_player->_pos);
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
    QPen *caneta = new QPen();
    caneta->setWidth(7);

    _yellow_player->setArenaSize(this->size());
    _green_player->setArenaSize(this->size());

    if(mostrarMenu){
        painter.setBrush(Qt::Dense2Pattern);
        painter.drawRect(0, this->y()+10, width(), 200);
    }else{

        painter.setBrush(Qt::yellow);

        _yellow_player->draw(&painter);
        _yellow_player->move(_constant_dt);

        painter.setBrush(Qt::green);
        _green_player->draw(&painter);
        _green_player->move(_constant_dt);

        if(fps){
            QString _fps = QString::number(_accumulator60);
            painter.setPen(Qt::white);
            painter.drawText(400,10,40,20,1,_fps);
        }

        caneta->setColor(Qt::yellow);

        painter.setPen(*caneta);
        QPolygon* yellowWay = new QPolygon(caminhoP1);
        painter.drawPolyline(*yellowWay);
        painter.drawLine(caminhoP1.last().x()+7, caminhoP1.last().y()+7, _yellow_player->_pos.x()+7, _yellow_player->_pos.y()+7);


        caneta->setColor(Qt::green);
        painter.setPen(*caneta);
        QPolygon* greenWay = new QPolygon(caminhoP2);
        painter.drawPolyline(*greenWay);
        painter.drawLine(caminhoP2.last(), _green_player->_pos);
//        painter.drawLine(_yellow_player->position.x(),_yellow_player->position.y(),_yellow_player->_pos.x()+7, _yellow_player->_pos.y()+7);

//        for(int linha=0; linha<40; linha++){
//            for(int coluna=0; coluna<53; coluna++){
//                if(_corXY[linha][coluna] == 1){
//                    painter.setBrush(Qt::yellow);
//                }

//                if(_corXY[linha][coluna] == -1){
//                    painter.setBrush(Qt::green);
//                }

//                if(_corXY[linha][coluna] == 0){
//                    painter.setBrush(Qt::transparent);
//                }
//                _squad[linha][coluna]->draw(_x,_y,painter,painter.brush());
//                _x += 15;
//            }
//            _y += 15;
//            _x = 0;
//        }
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

    colisaoYellowPlayer();
    moveP1();
    colisaoGreenPlayer();
    moveP2();

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

    if(keypress == Qt::Key_H){
        if(fps){
            fps = false;
        } else
            fps = true;
    }

    if(keypress == Qt::Key_F2){
        startGame();
    }

    if(keypress == Qt::Key_F4){
        exit(0);
    }

    if(keypress == Qt::Key_V){
        deslocamentoXP1 ++;
        deslocamentoYP1 ++;
    }

    if(keypress == Qt::Key_I){
        cima = true;
        baixo = false;
        esquerda = false;
        direita = false;
    }
    if(keypress == Qt::Key_K){
        baixo = true;
        cima = false;
        esquerda = false;
        direita = false;
    }
    if(keypress == Qt::Key_J){
        esquerda = true;
        direita = false;
        cima = false;
        baixo = false;
    }
    if(keypress == Qt::Key_L){
        direita = true;
        esquerda = false;
        cima = false;
        baixo = false;
    }


    if(keypress == Qt::Key_W){
        cima2 = true;
        baixo2 = false;
        esquerda2 = false;
        direita2 = false;
    }
    if(keypress == Qt::Key_S){
        baixo2 = true;
        cima2 = false;
        esquerda2 = false;
        direita2 = false;
    }
    if(keypress == Qt::Key_A){
        esquerda2 = true;
        direita2 = false;
        cima2 = false;
        baixo2 = false;
    }
    if(keypress == Qt::Key_D){
        direita2 = true;
        esquerda2 = false;
        cima2 = false;
        baixo2 = false;
    }
}

void Tabuleiro::moveP1(){
    if(cima == true){
        deslocamentoYP1 = -2 ;
        _yellow_player->setSpeed(QVector2D(0,deslocamentoYP1));
        caminhoP1.push_back(_yellow_player->_pos);
    }
    if(baixo == true){
        deslocamentoYP1 = 2;
        _yellow_player->setSpeed(QVector2D(0,deslocamentoYP1));
        caminhoP1.push_back(_yellow_player->_pos);
    }
    if(esquerda == true){
        deslocamentoXP1 = -2 ;
        _yellow_player->setSpeed(QVector2D(deslocamentoXP1,0));
        caminhoP1.push_back(_yellow_player->_pos);
    }
    if(direita == true){
        deslocamentoXP1 = 2;
        _yellow_player->setSpeed(QVector2D(deslocamentoXP1,0));
        caminhoP1.push_back(_yellow_player->_pos);
        }
}

void Tabuleiro::moveP2(){
    if(cima2 == true){
        deslocamentoYP2 = -2 ;
        _green_player->setSpeed(QVector2D(0,deslocamentoYP2));
        caminhoP2.push_back(_green_player->_pos);
    }
    if(baixo2 == true){
        deslocamentoYP2 = 2;
        _green_player->setSpeed(QVector2D(0,deslocamentoYP2));
        caminhoP2.push_back(_green_player->_pos);
    }
    if(esquerda2 == true){
        deslocamentoXP2 = -2 ;
        _green_player->setSpeed(QVector2D(deslocamentoXP2,0));
        caminhoP2.push_back(_green_player->_pos);
    }
    if(direita2 == true){
        deslocamentoXP2 = 2;
        _green_player->setSpeed(QVector2D(deslocamentoXP2,0));
        caminhoP2.push_back(_green_player->_pos);
    }
}

void  Tabuleiro::colisaoYellowPlayer(){

//    for(int linha = 0; linha < 40; linha++){
//        for(int coluna = 0; coluna < 53; coluna++){
//            if(_corXY[linha][coluna] == 0){
//                if((_yellow_player->_pos.x() + 15 >= _squad[linha][coluna]->x()) && (_yellow_player->_pos.x() <= _squad[linha][coluna]->x() + _squad[linha][coluna]->w()) &&
//                   (_yellow_player->_pos.y() + 15 >= _squad[linha][coluna]->y()) && (_yellow_player->_pos.y() <= _squad[linha][coluna]->y() + _squad[linha][coluna]->h())){
//                    _corXY[linha][coluna] = 1;
//                }
//            }else {
//               qDebug() << "bati";
//            }
//        }
//    }

        if( caminhoP1.contains(_yellow_player->_pos) ){
            qDebug() << "batiiiiiii";

    }
}

void Tabuleiro::colisaoGreenPlayer(){

//    for(int linha = 0; linha < 40; linha++){
//        for(int coluna = 0; coluna < 53; coluna++){
//            if(_corXY[linha][coluna] == 0){
//                if((_green_player->_pos.x() + 15 >= _squad[linha][coluna]->x()) && (_green_player->_pos.x() <= _squad[linha][coluna]->x() + _squad[linha][coluna]->w()) &&
//                   (_green_player->_pos.y() + 15 >= _squad[linha][coluna]->y()) && (_green_player->_pos.y() <= _squad[linha][coluna]->y() + _squad[linha][coluna]->h())){
//                    _corXY[linha][coluna] = -1;
//                }
//            }else {
//               qDebug() << "bati";
//            }
//        }
//    }
}
