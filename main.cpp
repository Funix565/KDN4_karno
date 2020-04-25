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

    int salo = 8;
    qDebug() << salo;

    // LARGE COMMENT AHAHAH
    // GIT IS NOT EASY

    return a.exec();
}

void save (int a)
{
    return a % 2; // new func
}
