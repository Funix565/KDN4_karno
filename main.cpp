//#include <QtGui/QApplication>
#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include <iostream>
using namespace std;
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int b;
    cin >> b;

    return a.exec();
}

bool pair (int a ){
    if (a %2 == 0)
        return true;
    else {
        return false;
    }
}

void save (int a)
{
    return a % 2; // new func
}
