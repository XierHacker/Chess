#ifndef BOARD_H
#define BOARD_H

#include "chesspieces.h"
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);

    enum {NUM=32};
    //chesspieces
    ChessPieces s[NUM];


    int r; //the ridiant of chesspieces
    int selectedID;

    QPoint rowAndcol_to_point(int row,int col);
    QPoint rowAndcol_to_point(int id); //overload locate
    bool   point_to_rowAndcol(QPoint pt,int& row,int& col);

    void drawChesspieces(QPainter & painter,int id);


    //overload paintEvent() to draw
    virtual void paintEvent(QPaintEvent *);

    //overload mouseReleaseEvent() to response mouse action
    virtual void mouseReleaseEvent(QMouseEvent *ev);

signals:

public slots:
};

#endif // BOARD_H
