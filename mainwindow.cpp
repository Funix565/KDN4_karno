#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTableWidget>
#include <cmath>
#include <deque>
#include <QMessageBox>
#include <map>
#include <header.h>
#include <QDebug>

using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect'ы кружочков
    connect(ui->radioButton_2vars, SIGNAL(clicked()), this, SLOT(ChosenRadio()));
    connect(ui->radioButton_3vars, SIGNAL(clicked()), this, SLOT(ChosenRadio()));
    connect(ui->radioButton_4vars, SIGNAL(clicked()), this, SLOT(ChosenRadio()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO: цикл вайл тру, для динамической постройки, а не по кнопке
void MainWindow::ChosenRadio() // построение таблицы по выбору кружочка
{
    ui->tableWidget_ist->clear();
    ui->tableWidget_karno->clear();

    int varCnt;

    QRadioButton *rb = (QRadioButton *)sender(); // от connect'a

    // проверка текста кнопки, для того, чтобы знать, сколько переменных
    if (rb->text() == "2vars")
    {
        varCnt = 2;
    }
    else if (rb->text() == "3vars")
    {
        varCnt = 3;
    }
    else if (rb->text() == "4vars")
    {
        varCnt = 4;
    }

    // Таблица истинности
    ui->tableWidget_ist->setRowCount(pow(2.0, varCnt));
    ui->tableWidget_ist->setColumnCount(varCnt + 1);
    char str[4] = {'A', 'B', 'C', 'D'}; // заголовки переменных

    QStringList headersClmn;
    QStringList headersRow;

    // Заполнение вертикальных заголовков числами
    for (int i = 0; i < ui->tableWidget_ist->rowCount(); i++)
    {
        ui->tableWidget_ist->setVerticalHeaderLabels(headersRow << QString::number(i));
    }
    // заполнение горизонтальных заголовков переменными
    for (int j = 0; j < ui->tableWidget_ist->columnCount() - 1; j++)
    {
        ui->tableWidget_ist->setHorizontalHeaderLabels(headersClmn << (QString)str[j]);
    }

    // Условие на заполнение последней колонки - ИМЯ ФУНКЦИИ
    switch (varCnt)
    {
    case 2:
    {
        ui->tableWidget_ist->setHorizontalHeaderLabels(headersClmn << "F(AB)");
    }
        break;
    case 3:
    {
        ui->tableWidget_ist->setHorizontalHeaderLabels(headersClmn << "F(ABC)");
    }
        break;
    case 4:
    {
        ui->tableWidget_ist->setHorizontalHeaderLabels(headersClmn << "F(ABCD)");
    }
        break;
    }

        // Заполнение нулями и единиицами
        int zeros = pow(2.0, (double)varCnt);
        int coef = 1;   // количесвто выводов
        int pov = 1;    // начальная степень

        for (int i = 0; i < varCnt; i++) // столбцы
        {
            int row = 0;
            for (int k = 0; k < coef; k++) // строки
            {
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
            zeros = zeros / 2;  // уменьшение количества нулей в столбце вдвое
            coef = pow(2.0, (double)pov);
            pov++;
        }

        ui->tableWidget_ist->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // блокировка для редактирования размера столбцов
        ui->tableWidget_ist->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);   // блокировка для редактирования размера рядов
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
}

void MainWindow::on_pushButton_Build_clicked()
{
    // Проверка на заполнение последней колонки
    ui->tableWidget_karno->clear();
    for (int j = 0, i = (ui->tableWidget_ist->columnCount() - 1); j < ui->tableWidget_ist->rowCount(); j++)
    {
        QTableWidgetItem *item_tabl_ist = ui->tableWidget_ist->item(j,i);
        if(!item_tabl_ist) // проверка на заполнение
        {
            QMessageBox::warning(this, "Warning", "You haven't filled the last column!");
            return;
        }
    }

    int rows = ui->tableWidget_ist->rowCount();
    int clmns = ui->tableWidget_ist->columnCount() - 1;
    Indexes coordinates;

    ui->tableWidget_karno->verticalHeader()->hide();
    ui->tableWidget_karno->horizontalHeader()->hide();

    // Построение карты карно
    switch(clmns)
    {
    case 2:
    {
        ui->tableWidget_karno->setRowCount(4);
        ui->tableWidget_karno->setColumnCount(4);

        ui->tableWidget_karno->setSpan(0, 0, 2, 2);
        ui->tableWidget_karno->setSpan(2, 0, 2, 1);
        ui->tableWidget_karno->setSpan(0, 2, 1, 2);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setBackgroundColor(Qt::lightGray);
        item->setTextAlignment(Qt::AlignHCenter);
        item->setText("A");
        ui->tableWidget_karno->setItem(0, 2, item);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setBackgroundColor(Qt::lightGray);
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setText("B");
        ui->tableWidget_karno->setItem(2, 0, item2);

        QTableWidgetItem *item_0 = new QTableWidgetItem;
        item_0->setTextAlignment(Qt::AlignCenter);
        item_0->setBackgroundColor(Qt::green);
        item_0->setText("0");
        ui->tableWidget_karno->setItem(2, 1, item_0);

        QTableWidgetItem *item_1 = new QTableWidgetItem;
        item_1->setTextAlignment(Qt::AlignCenter);
        item_1->setBackgroundColor(Qt::green);
        item_1->setText("1");
        ui->tableWidget_karno->setItem(3, 1, item_1);

        QTableWidgetItem *itm_0 = new QTableWidgetItem (*item_0);
        ui->tableWidget_karno->setItem(1, 2, itm_0);

        QTableWidgetItem *itm_1 = new QTableWidgetItem (*item_1);
        ui->tableWidget_karno->setItem(1, 3, itm_1);

        coordinates = coordinates2;
    }
        break;
    case 3:
    {
        ui->tableWidget_karno->setRowCount(4);
        ui->tableWidget_karno->setColumnCount(6);

        ui->tableWidget_karno->setSpan(0, 0, 2, 2);
        ui->tableWidget_karno->setSpan(2, 0, 2, 1);
        ui->tableWidget_karno->setSpan(0, 2, 1, 4);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter);
        item->setBackgroundColor(Qt::lightGray);
        item->setText("AB");
        ui->tableWidget_karno->setItem(0, 2, item);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setBackgroundColor(Qt::lightGray);
        item2->setText("C");
        ui->tableWidget_karno->setItem(2, 0, item2);

        QTableWidgetItem *item_00 = new QTableWidgetItem;
        item_00->setTextAlignment(Qt::AlignCenter);
        item_00->setBackgroundColor(Qt::green);
        item_00->setText("00");
        ui->tableWidget_karno->setItem(1, 2, item_00);

        QTableWidgetItem *item_01 = new QTableWidgetItem;
        item_01->setTextAlignment(Qt::AlignCenter);
        item_01->setBackgroundColor(Qt::green);
        item_01->setText("01");
        ui->tableWidget_karno->setItem(1, 3, item_01);

        QTableWidgetItem *item_11 = new QTableWidgetItem;
        item_11->setTextAlignment(Qt::AlignCenter);
        item_11->setBackgroundColor(Qt::green);
        item_11->setText("11");
        ui->tableWidget_karno->setItem(1, 4, item_11);

        QTableWidgetItem *item_10 = new QTableWidgetItem;
        item_10->setTextAlignment(Qt::AlignCenter);
        item_10->setBackgroundColor(Qt::green);
        item_10->setText("10");
        ui->tableWidget_karno->setItem(1, 5, item_10);

        QTableWidgetItem *item_0 = new QTableWidgetItem;
        item_0->setTextAlignment(Qt::AlignCenter);
        item_0->setBackgroundColor(Qt::green);
        item_0->setText("0");
        ui->tableWidget_karno->setItem(2, 1, item_0);

        QTableWidgetItem *item_1 = new QTableWidgetItem;
        item_1->setTextAlignment(Qt::AlignCenter);
        item_1->setBackgroundColor(Qt::green);
        item_1->setText("1");
        ui->tableWidget_karno->setItem(3, 1, item_1);

        coordinates = coordinates34;
    }
        break;
    case 4:
    {
        ui->tableWidget_karno->setRowCount(6);
        ui->tableWidget_karno->setColumnCount(6);

        ui->tableWidget_karno->setSpan(0, 0, 2, 2);
        ui->tableWidget_karno->setSpan(2, 0, 4, 1);
        ui->tableWidget_karno->setSpan(0, 2, 1, 4);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter);
        item->setBackgroundColor(Qt::lightGray);
        item->setText("AB");
        ui->tableWidget_karno->setItem(0, 2, item);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setBackgroundColor(Qt::lightGray);
        item2->setText("CD");
        ui->tableWidget_karno->setItem(2, 0, item2);

        QTableWidgetItem *item_00 = new QTableWidgetItem;
        item_00->setTextAlignment(Qt::AlignCenter);
        item_00->setBackgroundColor(Qt::green);
        item_00->setText("00");
        ui->tableWidget_karno->setItem(1, 2, item_00);

        QTableWidgetItem *item_01 = new QTableWidgetItem;
        item_01->setTextAlignment(Qt::AlignCenter);
        item_01->setBackgroundColor(Qt::green);
        item_01->setText("01");
        ui->tableWidget_karno->setItem(1, 3, item_01);

        QTableWidgetItem *item_11 = new QTableWidgetItem;
        item_11->setTextAlignment(Qt::AlignCenter);
        item_11->setBackgroundColor(Qt::green);
        item_11->setText("11");
        ui->tableWidget_karno->setItem(1, 4, item_11);

        QTableWidgetItem *item_10 = new QTableWidgetItem;
        item_10->setTextAlignment(Qt::AlignCenter);
        item_10->setBackgroundColor(Qt::green);
        item_10->setText("10");
        ui->tableWidget_karno->setItem(1, 5, item_10);

        QTableWidgetItem *itm_00 = new QTableWidgetItem (*item_00);
        ui->tableWidget_karno->setItem(2, 1, itm_00);

        QTableWidgetItem *itm_01 = new QTableWidgetItem (*item_01);
        ui->tableWidget_karno->setItem(3, 1, itm_01);

        QTableWidgetItem *itm_11 = new QTableWidgetItem (*item_11);
        ui->tableWidget_karno->setItem(4, 1, itm_11);

        QTableWidgetItem *itm_10 = new QTableWidgetItem (*item_10);
        ui->tableWidget_karno->setItem(5, 1, itm_10);

        coordinates = coordinates34;
    }
        break;
    }

    // Заполнение карты карно
    for (int r = 0; r < rows; r++)
    {
        QTableWidgetItem *itm = ui->tableWidget_ist->item(r, clmns);
        QTableWidgetItem *inKarnaugh = new QTableWidgetItem (*itm);
        // получаем номер строки в табл истинности. Находим его в словаре. Получаем номера ячеек для Карно
        int r_k = coordinates[r].row;
        int c_k = coordinates[r].column;

        ui->tableWidget_karno->setItem(r_k, c_k, inKarnaugh);
    }

    ui->tableWidget_karno->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // блокировка для редактирования размера столбцов
    ui->tableWidget_karno->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);   // блокировка для редактирования размера рядов
    ui->tableWidget_karno->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_karno->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int w = ui->tableWidget_karno->verticalHeader()->width() +4;                                      // считаем размер окна для таблицы (+4 нужно!)
    for (int i = 0; i < ui->tableWidget_karno->columnCount(); i++)                                    // считаем ширину
    {
        w += ui->tableWidget_karno->columnWidth(i);
    }
    int h = ui->tableWidget_karno->horizontalHeader()->height() + 4;
    for (int i = 0; i < ui->tableWidget_karno->rowCount(); i++)                                       // считаем высоту
    {
        h += ui->tableWidget_karno->rowHeight(i);
    }
    QSize p = QSize(w, h);
    ui->tableWidget_karno->setFixedSize(p);
}
