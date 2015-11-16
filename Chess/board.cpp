#include "board.h"
#include <QPainter>
#include <QPoint>

#include <iostream>
using namespace std;

//constructor
Board::Board(QWidget *parent) : QWidget(parent)
{
    this->resize(800,660);

    //init chesspicese
    for(int i=0;i<32;i++)
    {
       s[i].init(i);
    }

    //init selectedID
    selectedID=-1;

    //init redTurn
    redTurn=true;
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

//locate the most suited col_and_row
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



/******realize mouseEvent******/
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    //get the mouse_click's position
    point=ev->pos();

    int row,col;    //like temp value,and can be changed by the point_to_rowandcol()


    //if clicked out the board or invalid click
    if(point_to_rowAndcol(point,row,col)==false)
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
          if(s[i].isRed==redTurn)
          {
              selectedID=clickedID;
              update();
          }
          else
              return ;
      }
    }
    else        //means I have chosen a cheespiece and prepare to click the next position
    {
        //make sure the chesspiece can move
        if(canMove(selectedID,row,col,clickedID))
        {
            //move chesspiece
            s[selectedID].row=row;
            s[selectedID].col=col;
            if(clickedID!=-1) //meanse I clicked on a chesspiece
            {
                s[clickedID].isDead=true;

            }
            selectedID=-1;
            redTurn=!redTurn;
            update();
        }
    }

}




int Board::chessOnLine(int start_row,int start_col,int target_row,int target_col)
{
    int num=0;

    //can't be the same
    if(start_row==target_row&&start_col==target_col)
        return -1;

    //don't in a line
    if(start_row!=target_row&&start_col!=target_col)
        return -1;

    if(start_row==target_row)
    {
        int min=(start_col>target_col)?target_col:start_col;
        int max=(start_col>target_col)?start_col:target_col;
        for(int i=min;i<max;i++)
        {
            for(int j=0;j<32;j++)
            {
                if(s[j].row==start_row&&s[j].col==i&&s[j].isDead==false)
                    ++num;
            }
        }
    }
    else
    {
        int min=(start_row>target_row)?target_row:start_row;
        int max=(start_row>target_row)?start_row:target_row;
        for(int i=min;i<max;i++)
        {
            for(int j=0;j<32;j++)
            {
                if(s[j].row==start_row&&s[j].col==i&&s[j].isDead==false)
                    ++num;
            }
        }
    }
        return num;
}

bool Board::canMove(int moveid,int row,int col,int killedid)
{

    //can't move on to itself
    if(s[moveid].row==s[killedid].row&&s[moveid].col==s[killedid].col)
        return false;

    //can't kill the same color.
    if(s[moveid].isRed==s[killedid].isRed)
    {
        //change selection
        selectedID=killedid;
        update();

        return false;
    }

    switch(s[moveid].type)
        {
            //JIANG's rule
            case ChessPieces::JIANG:
                {
                    //1.about the col and the row
                    {
                         //judge row
                             if(s[moveid].isRed)
                            {
                                 cout<<s[moveid].isRed<<endl;
                                 if(row>2)
                                    return false;
                             }
                            else
                            {
                                cout<<s[moveid].isRed<<endl;
                                  if(row<7)
                                    return false;
                            }

                         //juege col
                            if(col<3||col>5)
                                return false;
                    }

                    //2.important!!!just one row or one col everytime
                    {


                            int d_r=s[moveid].row-row;
                            int d_c=s[moveid].col-col;
                            int d=abs(d_r)*10+abs(d_c);

                            if(d==1||d==10)
                                return true;
                    }

                     return false;
                }
             //CHE's rule
             case ChessPieces::CHE:
                {
                     break;
                 }
             //PAO's rule
             case ChessPieces::PAO:
                {
                     break;
                }
             //MA's rule
             case ChessPieces::MA:
                {
                    break;
                }

             //BING's rule
            case ChessPieces::BING:
                {
                            //testing fuction
                            int cur_row;
                            int cur_col;
                            point_to_rowAndcol(point,cur_row,cur_col);

                            cout<<chessOnLine(cur_row,cur_col,row,col)<<endl;
                    //1.about the col and the row

                            int d_r=s[moveid].row-row;
                            int d_c=s[moveid].col-col;
                            int d=abs(d_r)*10+abs(d_c);
                         //judge row
                             if(s[moveid].isRed)
                            {
                               //  cout<<s[moveid].isRed<<endl;
                                 if(row<5)
                                 {
                                     if(d_r==-1&&d_c==0)
                                         return true;

                                 }
                                 else
                                 {
                                    if(d_r==1)
                                        return false;
                                    if(d==1||d==10)
                                        return true;

                                 }

                             }
                            else
                            {
                                //test: cout<<s[moveid].isRed<<endl;
                                 if(row>4)
                                 {
                                     if(d_r==1&&d_c==0)
                                         return true;
                                 }
                                 else
                                 {
                                     if(d_r==-1)
                                         return false;
                                     if(d==1||d==10)
                                         return true;

                                 }
                            }
                         //return false;

                }


             //SHI's rule
            case ChessPieces::SHI:
                {
                    //1.about the col and the row
                    {
                         //judge row
                             if(s[moveid].isRed)
                            {
                                 cout<<s[moveid].isRed<<endl;
                                 if(row>2)
                                    return false;
                             }
                            else
                            {
                                cout<<s[moveid].isRed<<endl;
                                  if(row<7)
                                    return false;
                            }

                         //juege col
                            if(col<3||col>5)
                                return false;
                    }

                    //2.important!!!just one row or one col everytime
                    {


                            int d_r=s[moveid].row-row;
                            int d_c=s[moveid].col-col;
                            int d=abs(d_r)*10+abs(d_c);

                            if(d==11)
                                return true;
                    }

                     return false;
                }

             //XIANG's rule
            case ChessPieces::XIANG:
                {
                     break;
                }

        }
       return true;

}












