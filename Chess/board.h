#ifndef BOARD_H
#define BOARD_H

#include "chesspieces.h"
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>

class Board : public QWidget
{
private:
    Q_OBJECT

    enum {NUM=32};

    //chesspieces
    ChessPieces chesspieces[NUM];


    int r; //the ridiant of chesspieces
    int start_ID;
    bool redTurn;

public:
    explicit Board(QWidget *parent = 0);




    int isExistChesspieces(int row,int col);  //and return the id.
    bool isSameColor(int id1,int id2);






    //count the number of chesspices on the same line
    int chessOnLine(int start_row,int start_col,int target_row,int target_col);

    //overload paintEvent() to draw
    virtual void paintEvent(QPaintEvent *);
    void drawBoard(QPainter & painter,int d);
    void drawChesspieces(QPainter & painter,int id);

    //overload mouseReleaseEvent() to response mouse action
    virtual void mouseReleaseEvent(QMouseEvent *ev);

    bool canSelectChesspice(int id);
    void tryselectChesspice(int id);
    void killChesspice(int id);
    void reliveChesspice(int id);

    //rule methoed
    bool canMove(int moveid,int killedid,int row,int col);
    void trymoveChesspice(int killid,int row,int col);
    void moveChesspice(int moveid, int row, int col);
    void moveChesspice(int moveid, int killid, int row, int col);

    void click(int id,int row,int col);
    void click(QPoint pos);


    QPoint rowAndcol_to_point(int row,int col);
    QPoint rowAndcol_to_point(int id); //overload locate
    bool point_to_rowAndcol(QPoint pt,int& row,int& col);
    bool id_to_rowAndcol(int id,int& row,int& col);

signals:

public slots:
};

#endif // BOARD_H
