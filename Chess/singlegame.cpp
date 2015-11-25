#include "singlegame.h"

SingleGame::SingleGame()
{

}

//over write the click function
void SingleGame::click(int id,int row,int col)
{
    if(!this->redTurn)
        return ;
    //human move the chess
    Board::click(id,row,col);

    //black turn and computer move the chess
    if(!(this->redTurn))
    {
        computerMove();
    }

}

void SingleGame::computerMove()
{
    //1.find out all possible move and save it
    QVector<Step*> steps;
    getAllPossibleMove(steps);

    //2.try to move a step(not real move,just a try)
    for(auto it=steps.begin();it!=steps.end();it++)
    {
        Step* step=*it;

    }

}

void SingleGame::getAllPossibleMove(QVector<Step*>& steps)
{
    //black chess
    for(int i=16;i<32;i++)
    {
        for(int row=0;row<=9;row++)
        {
            for(int col=0;col<=8;col++)
            {
                int killid=isExistChesspieces(row,col);
                if(isSameColor(killid,i))
                    continue;

                if(canMove(i,killid,row,col))
                {
                    saveStep(i,killid,row,col,steps);
                }
            }
        }
    }
}
