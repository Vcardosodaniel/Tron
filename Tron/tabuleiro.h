#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QtWidgets>

class Tabuleiro : public QFrame
{
    Q_OBJECT
public:
    explicit Tabuleiro(QFrame *parent = 0);
    void paintEvent(QPaintEvent* event);

signals:

public slots:
    void _tick();
};

#endif // TABULEIRO_H
