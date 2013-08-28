#include <QtGui/QApplication>

#include "ItemManager.h"
#include "Workbench.h"
// debug
#include <iostream>

using namespace std;

int main( int argc, char **argv )
{
    cout << "Launching app ..." << endl;
    QApplication a(argc, argv);
    Workbench w;
    w.show();

    return a.exec();
}
