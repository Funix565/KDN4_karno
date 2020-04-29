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
    return a.exec();
}

