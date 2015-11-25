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
       chesspieces[i].init(i);
    }

    //init selectedID
    start_ID=-1;

    //init redTurn
    redTurn=true;
}



/*******realize paintEvent******/
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int d=60;
    r=d/2;

    //draw Board
    drawBoard(painter,d);
    //draw chesspieces
    for(int i=0;i<32;i++)
    {
        drawChesspieces(painter,chesspieces[i].id);
    }

}

//draw Board
void Board::drawBoard(QPainter & painter,int d)
{

    //basic structure
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
}

//draw chesspiece
 void Board::drawChesspieces(QPainter & painter,int id)
 {

    //if dead,should not draw that
    if(chesspieces[id].isDead)
        return ;

    //get center location
    QPoint c=rowAndcol_to_point(id);

    //choose the rect
    QRect rect=QRect(c.x()-r,c.y()-r,r*2,r*2);

    //set Brush's color
    if(id==start_ID)
        painter.setBrush(Qt::yellow);
    else
        painter.setBrush(QBrush(QColor(128,64,0)));

    painter.setPen(Qt::black);

    painter.drawEllipse(rowAndcol_to_point(chesspieces[id].row,chesspieces[id].col),r,r);

    if(chesspieces[id].isRed)
        painter.setPen(Qt::red);

    painter.setFont(QFont("system",r/3,100));
    painter.drawText(rect,chesspieces[id].getName(),QTextOption(Qt::AlignCenter));
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
    return rowAndcol_to_point(chesspieces[id].row,chesspieces[id].col);
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

//judge whether there exist a chesspices
int Board::isExistChesspieces(int row,int col)
{
   for(int i=0;i<32;i++)
   {
       if(chesspieces[i].row==row&&chesspieces[i].col==col&&chesspieces[i].isDead==false)
           return i;
   }
   return -1;
}

//juege same color
bool Board::isSameColor(int id1,int id2)
{
    if(chesspieces[id1].isRed==chesspieces[id2].isRed)
        return true;

    return false;
}

/******realize mouseEvent******/
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
    {
        return;
    }
    click(ev->pos());
}


bool Board::canSelectChesspice(int id)
{
    return (redTurn==chesspieces[id].isRed);
}

void Board::tryselectChesspice(int id)
{
    if(id==-1)
        return ;
    if(!canSelectChesspice(id))
        return ;
    start_ID=id;
    update();
}
void Board::killChesspice(int id)
{
    if(id==-1)      //meanse I didn't clicked on a chesspiece
        return ;
    else
    {
        chesspieces[id].isDead=true;
    }
}

void Board::reliveChesspice(int id)
{
    if(id==-1)      //meanse I didn't clicked on a chesspiece
        return ;
    else
    {
        chesspieces[id].isDead=false;
    }
}

void Board::trymoveChesspice(int killid,int row,int col)
{
    if(canMove(start_ID,killid,row,col))
    {
        moveChesspice(start_ID,killid,row,col);
        start_ID=-1;
        update();
    }
    else
        return ;

}

void Board::moveChesspice(int moveid, int row, int col)
{
    chesspieces[moveid].row=row;
    chesspieces[moveid].col=col;

    redTurn=!redTurn;
}


void Board::click(int id,int row,int col)
{
    if(this->start_ID==-1)  //means there is nothing have been choosen
    {
        tryselectChesspice(id);
    }
    else
    {
        trymoveChesspice(id,row,col);
    }
}
void Board::click(QPoint pos)
{
    int row, col;
    bool valid_Clicked =point_to_rowAndcol(pos, row, col);

    if(!valid_Clicked)  //may clicked out the board and is invalid click
        return  ;

    int id = isExistChesspieces(row, col);
    click(id, row, col);
}

void Board::moveChesspice(int moveid, int killid, int row, int col)
{
    killChesspice(killid);
    moveChesspice(moveid, row, col);
}




int Board::chessOnLine(int start_row,int start_col,int target_row,int target_col)
{
    int num=0;

    //don't in a line
    if(start_row!=target_row&&start_col!=target_col)
        return -1;


    if(start_row==target_row)   //in same line
    {
        int min=(start_col>target_col)?target_col:start_col;
        int max=(start_col>target_col)?start_col:target_col;
        for(int i=min+1;i<max;i++)
        {
            if(isExistChesspieces(start_row,i)!=-1)
                ++num;
        }
       // return num;
    }
    if(start_col==target_col)
    {
        int min=(start_row>target_row)?target_row:start_row;
        int max=(start_row>target_row)?start_row:target_row;
        for(int i=min+1;i<max;i++)
        {
            if(isExistChesspieces(i,start_col)!=-1)
                ++num;
        }
       // return num;
    }
       return num;
}

bool Board::canMove(int moveid,int killedid,int row,int col)
{

    //can't move on to itself
    if(chesspieces[moveid].row==chesspieces[killedid].row&&chesspieces[moveid].col==chesspieces[killedid].col)
        return false;

    //can't kill the same color.
    if(isSameColor(moveid,killedid))
    {
        //change selection
        start_ID=killedid;
        update();

        return false;
    }

    int d_r=chesspieces[moveid].row-row;
    int d_c=chesspieces[moveid].col-col;
    int d=abs(d_r)*10+abs(d_c);

    switch(chesspieces[moveid].type)
        {
            /*JIANG's rule*/
            case ChessPieces::JIANG:
                {
                    //judge row
                    if(chesspieces[moveid].isRed) //red
                    {
                        if(row>2)
                            return false;
                    }
                    else                //black
                    {
                        if(row<7)
                            return false;
                    }
                    //juege col
                    if(col<3||col>5)
                        return false;


                    //only one strait step
                    if(d==1||d==10)
                       return true;

                    return false;
                }


             /*CHE's rule*/
             case ChessPieces::CHE:
                {
                    //test
                    cout<<chessOnLine(chesspieces[moveid].row,chesspieces[moveid].col,row,col)<<endl;

                    //should in a line
                    if(chesspieces[moveid].row!=row&&chesspieces[moveid].col!=col)
                        return false;

                    //should exist nothin in front of CHE
                    if(chessOnLine(chesspieces[moveid].row,chesspieces[moveid].col,row,col)!=0)
                        return false;

                    return true;

                 }


             /*PAO's rule*/
             case ChessPieces::PAO:
                {
                    //test
                        cout<<chessOnLine(chesspieces[moveid].row,chesspieces[moveid].col,row,col)<<endl;

                    //should in a line
                       if(chesspieces[moveid].row!=row&&chesspieces[moveid].col!=col)
                          return false;

                    //should exist no more than tow chesspices in front of CHE
                       if(chessOnLine(chesspieces[moveid].row,chesspieces[moveid].col,row,col)>1)
                       {
                            return false;
                       }
                      else if(chessOnLine(chesspieces[moveid].row,chesspieces[moveid].col,row,col)==1)
                       {
                           int ID=isExistChesspieces(row,col);
                           if(ID!=-1&&chesspieces[moveid].isRed!=chesspieces[ID].isRed)
                           {
                               return true;
                           }

                           return false;

                       }
                       else if(chessOnLine(chesspieces[moveid].row,chesspieces[moveid].col,row,col)==0)
                       {
                           if(isExistChesspieces(row,col)!=-1)
                               return false;

                       }
                       else
                       {
                           return false;
                       }

                       return true;

                }


             /*MA's rule*/
             case ChessPieces::MA:
                {
                    if(d!=12&&d!=21)
                        return false;
                    else
                    {
                        if(abs(d_r)>abs(d_c))
                        {
                            if(chesspieces[moveid].row>row)
                            {
                                if(isExistChesspieces(row+1,chesspieces[moveid].col)!=-1)
                                    return false;

                            }
                            else
                            {
                                if(isExistChesspieces(row-1,chesspieces[moveid].col)!=-1)
                                    return false;
                            }
                        }
                        else
                        {
                            if(chesspieces[moveid].col>col)
                            {
                                if(isExistChesspieces(chesspieces[moveid].row,col+1)!=-1)
                                    return false;

                            }
                            else
                            {
                                if(isExistChesspieces(chesspieces[moveid].row,col-1)!=-1)
                                    return false;
                            }

                        }
                    }

                    return true;

                }

             /*BING's rule*/
            case ChessPieces::BING:
                {
                    //test
                    cout<<chessOnLine(chesspieces[moveid].row,chesspieces[moveid].col,row,col)<<endl;

                    if(chesspieces[moveid].isRed)        //red BING
                    {
                        if(row<5)
                        {
                            if(d_r==-1&&d_c==0)
                                return true;
                            else
                                return false;

                        }
                        else
                        {
                            if(d_r==1)
                                return false;
                            if(d==1||d==10)
                                return true;
                        }

                     }
                    else                //black BING
                    {
                        if(row>4)
                        {
                            if(d_r==1&&d_c==0)
                                 return true;
                            else
                                 return false;
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


             /*SHI's rule*/
            case ChessPieces::SHI:
                {
                    int d_r=chesspieces[moveid].row-row;
                    int d_c=chesspieces[moveid].col-col;
                    int d=abs(d_r)*10+abs(d_c);

                     //judge row
                    if(chesspieces[moveid].isRed)     //red
                    {
                        if(row>2)
                        return false;
                    }
                   else                     //black
                    {
                        if(row<7)
                        return false;
                    }

                    //juege col
                    if(col<3||col>5)
                       return false;

                    //2.just one slash
                    if(d==11)
                       return true;
                    return false;
                }

             /*XIANG's rule*/
            case ChessPieces::XIANG:
                {
                    //can't pass the river
                    if(chesspieces[moveid].isRed)         //red
                    {
                        if(row>4)
                            return false;
                    }
                    else                        //black
                    {
                        if(row<5)
                            return false;

                    }

                    if(d!=22)
                        return false;
                    else
                    {
                         if(chesspieces[moveid].row>row)
                         {
                            if(chesspieces[moveid].col>col)
                            {
                                if(isExistChesspieces(row+1,col+1)!=-1)
                                    return false;
                            }
                            else
                            {
                                if(isExistChesspieces(row+1,col-1)!=-1)
                                    return false;
                            }

                         }
                         else
                         {
                             if(chesspieces[moveid].col>col)
                             {
                                 if(isExistChesspieces(row-1,col+1)!=-1)
                                     return false;
                             }
                             else
                             {
                                 if(isExistChesspieces(row-1,col-1)!=-1)
                                     return false;
                             }
                         }

                    }

                    return true;
                }

        }
       return true;
}

void Board::saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps)
{
   // GetRowCol(row1, col1, moveid);
    Step* step = new Step;
    step->_colFrom = chesspieces[moveid].col;
    step->_colTo = col;
    step->_rowFrom = chesspieces[moveid].col;
    step->_rowTo = row;
    step->_moveid = moveid;
    step->_killid = killid;

    steps.append(step);
}










