#include "board.h"
#include <QPainter>
#include <QPoint>

//constructor
Board::Board(QWidget *parent) : QWidget(parent)
{
    this->resize(800,660);
    //init chesspicese
    for(int i=0;i<32;i++)
    {
       s[i].init(i);
    }
}



/*******realize paintEvent******/
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int d=60;
    r=d/2;


    //drawboard
    //draw basic structure
    for(int i=1;i<=10;i++)
    {
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }

    for(int i=1;i<=9;i++)
    {
        if(i==1||i==9)
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        else
        {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }
    }

    //draw details
    {
        painter.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));
        painter.drawLine(QPoint(4*d,3*d),QPoint(6*d,d));
        painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
        painter.drawLine(QPoint(4*d,10*d),QPoint(6*d,8*d));
    }

    {

    }

    //draw chesspieces
    for(int i=0;i<32;i++)
    {
        drawChesspieces(painter,s[i].id);
    }

}







//how to draw chesspieces
 void Board::drawChesspieces(QPainter & painter,int id)
 {
    QPoint c=locate(id);
    QRect rect=QRect(c.x()-r,c.y()-r,r*2,r*2);
    painter.drawEllipse(locate(s[id].row,s[id].col),r,r);
    painter.drawText(rect,s[id].getName(),QTextOption(Qt::AlignCenter));
 }


 //locate the center position through the row and col of a chesspices
QPoint Board::locate(int row,int col)
 {
    QPoint temp;
    temp.rx()=(col+1)*2*r;
    temp.ry()=(row+1)*2*r;
    return temp;
 }

QPoint Board::locate(int id)
{
    return locate(s[id].row,s[id].col);
}

