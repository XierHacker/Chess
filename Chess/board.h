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
    bool redTurn;

    QPoint point; //record the current mouse's click position



    //rule methoed
    bool canMove(int moveid,int row,int col,int killedid);

    //count the number of chesspices on the same line
    int chessOnLine(int start_row,int start_col,int target_row,int target_col);

    //overload paintEvent() to draw
    virtual void paintEvent(QPaintEvent *);
    void drawChesspieces(QPainter & painter,int id);

    //overload mouseReleaseEvent() to response mouse action
    virtual void mouseReleaseEvent(QMouseEvent *ev);

    QPoint rowAndcol_to_point(int row,int col);
    QPoint rowAndcol_to_point(int id); //overload locate
    bool   point_to_rowAndcol(QPoint pt,int& row,int& col);

signals:

public slots:
};

#endif // BOARD_H
