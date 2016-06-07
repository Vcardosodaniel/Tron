#include "tabuleiro.h"

Tabuleiro::Tabuleiro(QFrame* parent) : QFrame(parent){
    setMinimumSize(800,600);

    _counter = 0;
    _accumulator60 = 0;
    _max_fps = 60;
    _constant_dt = 1000 / _max_fps;
    _last_time_60fps = QDateTime::currentMSecsSinceEpoch();

    _yellow_player = new Player((QFrame*)this, Qt::yellow);

    // Start timer
    QTimer::singleShot(1000/_max_fps, this, SLOT(_tick()));
}

void Tabuleiro::paintEvent(QPaintEvent* event){
    QFrame::paintEvent(event);

    /* Paint white background */

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::darkBlue);

    /* Paint black frame around the canvas */

    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width()-1, height()-1);

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

        _yellow_player->draw();
        qDebug()<<_yellow_player->_x;
        _last_time_60fps = now;
    }

    _counter++;
    _counter = _counter % 60; // Ranges from 0 to 59

    // Reset the timer
    QTimer::singleShot(1000/_max_fps, this, SLOT(_tick()));
}
