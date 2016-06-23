#include "player.h"

Player::Player(QSize arena_size, char direction){
    _arena_sz = arena_size;

     _speed.setX(0);
     _speed.setY(0);

}

void Player::move(qint64 dt){
    _x = _pos.x();
    _y = _pos.y();

    _pos.setX(dt);

    if (_speed.x() > 0) {
        _x += std::ceil((_speed.x() * dt * 60) / 1000);
        _pos.setX(_x);
    }
    else {
        _x += std::floor((_speed.x() * dt * 60) / 1000);
        _pos.setX(_x);
    }
    if (_speed.y() > 0) {
        _y += std::ceil((_speed.y() * dt * 60) / 1000);
        _pos.setY(_y);
    }
    else {
        _y += std::floor((_speed.y() * dt * 60) / 1000);
        _pos.setY(_y);
    }

//    if ( _x <= 0 || (_x >= (_arena_sz.width()-1) - 15) ) {
//        _dx *= -1;
//    }

//    if ( _y <= 0 || (_y >= (_arena_sz.height()-1) - 15) ) {
//        _dy *= -1;
//    }

 }

void Player::draw(QPainter* painter){
    QRect playerTron(_pos.x() ,_pos.y(), 15, 15);

    painter->drawRoundedRect(playerTron, 1.0, 1.0);
}

void Player::setArenaSize(QSize arena_size){
    _arena_sz = arena_size;
}

void Player::setSpeed(QVector2D speed){
    _speed.setX(speed.x());
    _speed.setY(speed.y());
}

void Player::reset(QPoint initial_pos){
    _pos.setX(600);
    _pos.setY(300);
}

