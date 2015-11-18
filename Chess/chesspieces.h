#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QString>


class ChessPieces
{
private:

public:
    ChessPieces();

    int row,col,id;
    bool isDead,isRed;

    enum TYPE {JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    TYPE type;

    //get the name from the type of chesspieces
    QString getName();

    //initialize a chesspiece
    void init(int ID);


};

#endif // CHESSPIECES_H
