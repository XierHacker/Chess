#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "board.h"

class SingleGame:public Board
{
public:
    SingleGame();
    virtual void click(int id,int row,int col);

    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);

    void fakemove(Step* step);
    void unfakemove(Step* step);
    int cal_Score();




};

#endif // SINGLEGAME_H
