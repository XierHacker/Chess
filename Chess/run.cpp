#include <QApplication>
#include "board.h"
#include "singlegame.h"
#include <iostream>
using namespace std;

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);
    SingleGame board;
    board.show();
    return app.exec();
}
