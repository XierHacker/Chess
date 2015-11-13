#include <QApplication>
#include "board.h"
#include <iostream>
using namespace std;

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);
    Board board;
    board.show();
    return app.exec();
}
