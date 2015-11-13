#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QString>


class ChessPieces
{
public:
    ChessPieces();

    enum TYPE {JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    int row;
    int col;
    int id;
    bool isDead;
    bool isRed;
    TYPE type;

    QString getName()
    {
        switch(this->type)
        {
            case JIANG:
                return "JIANG";
            case CHE:
                return "CHE";
            case PAO:
                return "PAO";
            case MA:
                return "MA";
            case BING:
                return "BING";
            case SHI:
                return "SHI";
            case XIANG:
                return "XIANG";
         }
             return "ERROR";
    }

    void init(int ID)
    {
       struct
       {
           int row,col;
           ChessPieces::TYPE type;
       }chess[16]={

            {0,0,ChessPieces::CHE},
            {0,1,ChessPieces::MA},
            {0,2,ChessPieces::XIANG},
            {0,3,ChessPieces::SHI},
            {0,4,ChessPieces::JIANG},
            {0,5,ChessPieces::SHI},
            {0,6,ChessPieces::XIANG},
            {0,7,ChessPieces::MA},
            {0,8,ChessPieces::CHE},


            {2,1,ChessPieces::PAO},
            {2,7,ChessPieces::PAO},

            {3,0,ChessPieces::BING},
            {3,2,ChessPieces::BING},
            {3,4,ChessPieces::BING},
            {3,6,ChessPieces::BING},
            {3,8,ChessPieces::BING}
          };

       id=ID;
       isDead=false;
       isRed=(id<16);

       if(id<16)
       {
           row=chess[id].row;
           col=chess[id].col;
           type=chess[id].type;
       }
       else
       {
           row=9-chess[id-16].row;
           col=8-chess[id-16].col;
           type=chess[id-16].type;

       }
    }

};

#endif // CHESSPIECES_H
