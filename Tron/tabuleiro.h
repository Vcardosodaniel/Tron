#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QtWidgets>

class Tabuleiro : public QFrame
{
    Q_OBJECT
public:
    explicit Tabuleiro(QWidget *parent = 0);
    void paintEvent(QKeyEvent* event);

signals:

public slots:
};

#endif // TABULEIRO_H
