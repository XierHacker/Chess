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

    selectedID=-1;
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



//how to draw singal chesspiece
 void Board::drawChesspieces(QPainter & painter,int id)
 {

    //if dead,should not draw that
    if(s[id].isDead)
        return ;
    //get center location
    QPoint c=rowAndcol_to_point(id);

    //choose the rect
    QRect rect=QRect(c.x()-r,c.y()-r,r*2,r*2);

    //set Brush's color
    if(id==selectedID)
        painter.setBrush(Qt::yellow);
    else
        painter.setBrush(QBrush(QColor(128,64,0)));

    painter.setPen(Qt::black);

    painter.drawEllipse(rowAndcol_to_point(s[id].row,s[id].col),r,r);

    if(s[id].isRed)
        painter.setPen(Qt::red);

    painter.setFont(QFont("system",r/3,100));
    painter.drawText(rect,s[id].getName(),QTextOption(Qt::AlignCenter));
 }


 //locate the center position through the row and col of a chesspices
QPoint Board::rowAndcol_to_point(int row,int col)
 {
    QPoint temp;
    temp.rx()=(col+1)*2*r;
    temp.ry()=(row+1)*2*r;
    return temp;
 }

QPoint Board::rowAndcol_to_point(int id)
{
    return rowAndcol_to_point(s[id].row,s[id].col);
}



/******realize mouseEvent******/
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    //get the mouse's position
    QPoint pos=ev->pos();

    int row,col;    //like temp value,and can be changed by the point_to_rowandcol()


    //if clicked out the board
    if(point_to_rowAndcol(pos,row,col)==false)
        return ;


    //find which chesspiece i click
    int i=0;
    int clickedID=-1;
    for(;i<32;i++)
    {
        if(s[i].row==row&&s[i].col==col&&s[i].isDead==false)
        {
            break;
        }
    }

    if(i<32)
    {
        clickedID=i;
     //   update();
    }

    if(selectedID==-1) //means I haven't chosen a chesspiece
    {
      if(clickedID!=-1) //meanse I clicked on a chesspiece
      {
          selectedID=clickedID;
          update();
      }
    }
    else        //means I have chosen a cheespiece and prepare to click the next position
    {
        s[selectedID].row=row;
        s[selectedID].col=col;
        if(clickedID!=-1) //meanse I clicked on a chesspiece
        {
            s[clickedID].isDead=true;

        }
        update();
    }



}



//locate the most suited colandrow
bool Board::point_to_rowAndcol(QPoint pt,int& row,int& col)
{
    for(row=0;row<=9;row++)
    {
        for(col=0;col<=8;col++)
        {
            //get rowAndcol's coordinate
            QPoint c=rowAndcol_to_point(row,col);

            //find the min distance
            int dx=c.x()-pt.x();
            int dy=c.y()-pt.y();
            int d=dx*dx+dy*dy;
            if(d<r*r)
                return true;
         }
    }
    return false;
}















