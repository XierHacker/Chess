#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "chesspieces.h"
#include <QPoint>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    //enum {NUM=32};
    //chesspieces
    ChessPieces s[32];
    int r; //the ridiant of chesspieces
    void drawChesspieces(QPainter & painter,int id);
    QPoint locate(int row,int col);
    QPoint locate(int id); //overload locate


    //overload paintEvent()
    virtual void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // BOARD_H
