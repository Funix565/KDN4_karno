#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTableWidget>
#include <cmath>
#include <deque>
#include <QMessageBox>
using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_2var_stateChanged(int arg1) {

    ui->tableWidget_ist->setRowCount(8);
    ui->tableWidget_ist->setColumnCount(4);
    char str[3] = {'A', 'B', 'C'};
    QStringList headersClmn;
    QStringList headersRow;
    for (int i = 0; i < ui->tableWidget_ist->rowCount(); i++)
    {
        ui->tableWidget_ist->setVerticalHeaderLabels(headersRow << QString::number(i)); // строки
    }
    for (int j = 0; j < ui->tableWidget_ist->columnCount(); j++)
    {
        if (j == ui->tableWidget_ist->columnCount() -1) {
            ui->tableWidget_ist->setHorizontalHeaderLabels(headersClmn << "F(ABC)");
            break;
        }
        ui->tableWidget_ist->setHorizontalHeaderLabels(headersClmn << (QString)str[j]);
    }
    int zeros = pow(2, 3);
    int coef = 1;
    int pov = 1;

    for (int i = 0; i < 3; i++) {
        int row = 0;
        for (int k = 0; k < coef; k++) {
            int j;
            for (j = 0; j < zeros / 2; j++)
            {
                QTableWidgetItem *zero = new QTableWidgetItem (QObject::tr("%1").arg(0));
                zero->setFlags(Qt::ItemIsEnabled);
                ui->tableWidget_ist->setItem(row, i, zero);
                row++;
            }
            for ( ; j < zeros; j++)
            {
                QTableWidgetItem *one = new QTableWidgetItem (QObject::tr("%1").arg(1));
                one->setFlags(Qt::ItemIsEnabled);
                ui->tableWidget_ist->setItem(row, i, one);
                row++;
            }
        }
        zeros = zeros / 2;
        coef = pow(2.0, (double)pov);
        pov++;
    }
    ui->tableWidget_ist->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // блокировка для редактирования столбцов
    ui->tableWidget_ist->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);   // блокировка для редактирования рядов
    ui->tableWidget_ist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_ist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int w = ui->tableWidget_ist->verticalHeader()->width() +4;                                      // считаем размер окна для таблицы (+4 нужно!)
    for (int i = 0; i < ui->tableWidget_ist->columnCount(); i++)                                    // считаем ширину
    {
        w += ui->tableWidget_ist->columnWidth(i);
    }
    int h = ui->tableWidget_ist->horizontalHeader()->height() + 4;
    for (int i = 0; i < ui->tableWidget_ist->rowCount(); i++)                                       // считаем высоту
    {
        h += ui->tableWidget_ist->rowHeight(i);
    }
    QSize p = QSize(w, h);
    ui->tableWidget_ist->setFixedSize(p);
    ui->tableWidget_karno->setRowCount(4);
    ui->tableWidget_karno->setColumnCount(6);
    ui->tableWidget_karno->setSpan(0,0,2,2);
    ui->tableWidget_karno->setSpan(2,0,2,1);
    ui->tableWidget_karno->setSpan(0,2,1,4);

    ui->tableWidget_karno->verticalHeader()->hide();
    ui->tableWidget_karno->horizontalHeader()->hide();
    ui->tableWidget_karno->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_karno->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // блокировка для редактирования столбцов
    ui->tableWidget_karno->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);   // блокировка для редактирования рядов
    ui->tableWidget_karno->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_karno->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w = ui->tableWidget_karno->verticalHeader()->width() +4;                                      // считаем размер окна для таблицы (+4 нужно!)
    for (int i = 0; i < ui->tableWidget_karno->columnCount(); i++)                                    // считаем ширину
    {
        w += ui->tableWidget_karno->columnWidth(i);
    }
    h = ui->tableWidget_karno->horizontalHeader()->height() + 4;
    for (int i = 0; i < ui->tableWidget_karno->rowCount(); i++)                                       // считаем высоту
    {
        h += ui->tableWidget_karno->rowHeight(i);
    }
    p = QSize(w, h);
    ui->tableWidget_karno->setFixedSize(p);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignHCenter);
    item->setText("AB");
    ui->tableWidget_karno->setItem(0,2, item);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setTextAlignment(Qt::AlignCenter);
    item2->setText("C");
    ui->tableWidget_karno->setItem(2, 0, item2);
    QTableWidgetItem *item_00 = new QTableWidgetItem;
    item_00->setTextAlignment(Qt::AlignCenter);
    item_00->setText("00");
    ui->tableWidget_karno->setItem(1, 2, item_00);
    QTableWidgetItem *item_01 = new QTableWidgetItem;
    item_01->setTextAlignment(Qt::AlignCenter);
    item_01->setText("01");
    ui->tableWidget_karno->setItem(1, 3, item_01);
    QTableWidgetItem *item_11 = new QTableWidgetItem;
    item_11->setTextAlignment(Qt::AlignCenter);
    item_11->setText("11");
    ui->tableWidget_karno->setItem(1, 4, item_11);
    QTableWidgetItem *item_10 = new QTableWidgetItem;
    item_10->setTextAlignment(Qt::AlignCenter);
    item_10->setText("10");
    ui->tableWidget_karno->setItem(1, 5, item_10);
    QTableWidgetItem *item_0 = new QTableWidgetItem;
    item_0->setTextAlignment(Qt::AlignCenter);
    item_0->setText("0");
    ui->tableWidget_karno->setItem(2, 1, item_0);
    QTableWidgetItem *item_1 = new QTableWidgetItem;
    item_1->setTextAlignment(Qt::AlignCenter);
    item_1->setText("1");
    ui->tableWidget_karno->setItem(3, 1, item_1);
}

void MainWindow::on_pushButton_map_carno_clicked()
{
    int i = 3;
    for (int j = 0; j < ui->tableWidget_ist->rowCount(); j++) {
        QTableWidgetItem *item_tabl_ist(ui->tableWidget_ist->item(j,i));
        if(!item_tabl_ist) {         // проверка на заполнение
            QMessageBox::warning(this, "Warning", "You haven't filled the last column!");
            return;
        }
    }
    QString str_ist;
    QString karno;
    int column_karno = 2, row_karno = 2;
    for (int i = 0; i < ui->tableWidget_ist->rowCount(); i++) {
        str_ist = "";
        for (int j = 0; j < ui->tableWidget_ist->columnCount(); j++) {
            if (j == ui->tableWidget_ist->columnCount() - 1) {
                karno = ui->tableWidget_ist->item(i, j)->text();
            }
            else {
                str_ist += ui->tableWidget_ist->item(i,j)->text();
            }
        }
        QTableWidgetItem *k = new QTableWidgetItem;
        if (karno == '1') {
            k->setText("1");
            if (column_karno == 4)
                ui->tableWidget_karno->setItem(row_karno, column_karno + 1, k);
            else if (column_karno == 5) {
                 ui->tableWidget_karno->setItem(row_karno, column_karno - 1, k);
            }
            else
                ui->tableWidget_karno->setItem(row_karno, column_karno, k);
            row_karno++;
            row_karno == 4 ? row_karno = 2, column_karno++ : true;
        }
        if (karno == '0') {
            k->setText("0");
            if (column_karno == 4)
                ui->tableWidget_karno->setItem(row_karno, column_karno + 1, k);
            else if (column_karno == 5) {
                ui->tableWidget_karno->setItem(row_karno, column_karno - 1, k);
            }
            else
                ui->tableWidget_karno->setItem(row_karno, column_karno, k);
            row_karno++;
            row_karno == 4 ? row_karno = 2, column_karno++ : true;
        }
    }
}
