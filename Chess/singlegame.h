#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "board.h"

class SingleGame:public Board
{
public:
    SingleGame();
    virtual void click(int id,int row,int col);

    void computerMove();
    void getAllPossibleMove(QVector<Step*>& steps);



};

#endif // SINGLEGAME_H
