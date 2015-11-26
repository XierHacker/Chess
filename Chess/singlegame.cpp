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
        Step* step=getBestMove();
        moveChesspice(step->_moveid,step->_killid,step->_rowTo,step->_colTo);
    }

}



Step* SingleGame::getBestMove()
{
    //1.find out all possible move and save it
    QVector<Step*> steps;
    getAllPossibleMove(steps);


    //2.try to move a step(not real move,just try!)
    int maxScore=-10000000;
    Step* ret;

    for(QVector<Step*>::iterator it=steps.begin();it!=steps.end();it++)
    {
        Step* step=*it;
        fakemove(step);
        int score=cal_Score();
        unfakemove(step);
        if(score>maxScore)
        {
            maxScore=score;
            ret=step;
        }
    }

    //return the most suitable result
    return ret;
}

void SingleGame::getAllPossibleMove(QVector<Step*>& steps)
{

    //black chess
    for(int i=16;i<32;i++)
    {
        if(chesspieces[i].isDead)
            continue;
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

void SingleGame::fakemove(Step* step)
{
    killChesspice(step->_killid);
    trymoveChesspice(step->_moveid,step->_rowTo,step->_colTo);
}

void SingleGame::unfakemove(Step* step)
{
    reliveChesspice(step->_killid);
    trymoveChesspice(step->_moveid,step->_rowFrom,step->_colFrom);
}

int SingleGame::cal_Score()
{
    int redTotalScore=0;
    int blackTotalScore=0;
    static int chessScore[]={100,50,50,20,1500,10,10};

    for(int i=0;i<16;i++)
    {
        if(chesspieces[i].isDead)
            continue;
        redTotalScore+=chessScore[chesspieces[i].type];
    }
    for(int i=16;i<32;i++)
    {
        if(chesspieces[i].isDead)
            continue;
        blackTotalScore+=chessScore[chesspieces[i].type];
    }

    return (blackTotalScore-redTotalScore);
}
