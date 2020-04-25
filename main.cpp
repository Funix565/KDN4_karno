//#include <QtGui/QApplication>
#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int b;
    cin >> b;
    return a.exec();
}
