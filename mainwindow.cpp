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
#include <QColor>

using namespace  std;

struct calculating {
    int arr[4];
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect'« т Ј??§т?ч
    connect(ui->radioButton_2vars, SIGNAL(clicked()), this, SLOT(ChosenRadio()));
    connect(ui->radioButton_3vars, SIGNAL(clicked()), this, SLOT(ChosenRadio()));
    connect(ui->radioButton_4vars, SIGNAL(clicked()), this, SLOT(ChosenRadio()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO: ¦рт? ч ?? ў Ј, э?Ї эр? ?р§?Ўт?? ф?Ўў ??тр,   ?? ф? т??фт?
void MainWindow::ChosenRadio() // ф?Ўў ???р? ў ц?р¦« ф? ч«ц? Ј т Ј??§т
{
    ui->tableWidget_ist->clear();
    ui->tableWidget_karno->clear();

    int varCnt;

    QRadioButton *rb = (QRadioButton *)sender(); // ?ў connect'a

    // ф ?ч? т  ў?тЎў  т??фтр, э?Ї ў???, §ў?ц« ?? ў¬, Ўт??¬т? ф? ?????«Ґ
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

    // ? ц?р¦  рЎўр???Ўўр
    ui->tableWidget_ist->setRowCount(pow(2.0, varCnt));
    ui->tableWidget_ist->setColumnCount(varCnt + 1);
    char str[4] = {'A', 'B', 'C', 'D'}; // ? ????чтр ф? ?????«Ґ

    QStringList headersClmn;
    QStringList headersRow;

    // ? ф?????р? ч? ўрт ?¬?«Ґ ? ????чт?ч §рЎ? ?р
    for (int i = 0; i < ui->tableWidget_ist->rowCount(); i++)
    {
        ui->tableWidget_ist->setVerticalHeaderLabels(headersRow << QString::number(i));
    }
    // ? ф?????р? ?? р???ў ?¬?«Ґ ? ????чт?ч ф? ?????«?р
    for (int j = 0; j < ui->tableWidget_ist->columnCount() - 1; j++)
    {
        ui->tableWidget_ist->setHorizontalHeaderLabels(headersClmn << (QString)str[j]);
    }

    // ?Ў??чр? ?  ? ф?????р? ф?Ў??э??? т????тр - ??? ???????
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

    // ? ф?????р? ?Ј?Ї?р р ?эр?рр¦ ?р
    int zeros = pow(2.0, (double)varCnt);
    int coef = 1;   // т??р§?Ўчў? ч«ч?э?ч
    int pov = 1;    // ? § ?¬? Ї Ўў?ф??¬
    for (int i = 0; i < varCnt; i++) // Ўў??ц¦«
    {
        int row = 0;
        for (int k = 0; k < coef; k++) // Ўў ?тр
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
        zeros = zeros / 2;  // Ј???¬Ё??р? т??р§?Ўўч  ?Ј??? ч Ўў??ц¦? чэч??
        coef = pow(2.0, (double)pov);
        pov++;
    }

    ui->tableWidget_ist->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // ц??тр ?чт  э?Ї  ?э тўр ?ч ?рЇ   ???   Ўў??ц¦?ч
    ui->tableWidget_ist->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);   // ц??тр ?чт  э?Ї  ?э тўр ?ч ?рЇ   ???    Їэ?ч
    ui->tableWidget_ist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_ist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int w = ui->tableWidget_ist->verticalHeader()->width() +4;                                      // Ў§рў ??   ???  ?т?  э?Ї ў ц?р¦« (+4 ?Ј???!)
    for (int i = 0; i < ui->tableWidget_ist->columnCount(); i++)                                    // Ў§рў ?? Ёр р?Ј
    {
        w += ui->tableWidget_ist->columnWidth(i);
    }
    int h = ui->tableWidget_ist->horizontalHeader()->height() + 4;
    for (int i = 0; i < ui->tableWidget_ist->rowCount(); i++)                                       // Ў§рў ?? ч«Ў?ўЈ
    {
        h += ui->tableWidget_ist->rowHeight(i);
    }
    QSize p = QSize(w, h);
    ui->tableWidget_ist->setFixedSize(p);
}

void MainWindow::on_pushButton_Build_clicked()
{
    ui->tableWidget_karno->clear();
    for (int j = 0, i = (ui->tableWidget_ist->columnCount() - 1); j < ui->tableWidget_ist->rowCount(); j++)
    {

        QTableWidgetItem *item_tabl_ist = ui->tableWidget_ist->item(j,i);
        if(!item_tabl_ist)
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

    switch(clmns)
    {
    case 2:
    {
        QBrush brush_green = (QColor(Qt::green));
        QBrush brush_grey = (QColor(Qt::lightGray));
        ui->tableWidget_karno->setRowCount(4);
        ui->tableWidget_karno->setColumnCount(4);

        ui->tableWidget_karno->setSpan(0, 0, 2, 2);
        ui->tableWidget_karno->setSpan(2, 0, 2, 1);
        ui->tableWidget_karno->setSpan(0, 2, 1, 2);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setBackground(brush_grey);
        item->setTextAlignment(Qt::AlignHCenter);
        item->setText("B");
        ui->tableWidget_karno->setItem(0, 2, item);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setBackground(brush_grey);
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setText("A");
        ui->tableWidget_karno->setItem(2, 0, item2);

        QTableWidgetItem *item_0 = new QTableWidgetItem;
        item_0->setTextAlignment(Qt::AlignCenter);
        item_0->setBackground(brush_green);
        item_0->setText("0");
        ui->tableWidget_karno->setItem(2, 1, item_0);

        QTableWidgetItem *item_1 = new QTableWidgetItem;
        item_1->setTextAlignment(Qt::AlignCenter);
        item_1->setBackground(brush_green);
        item_1->setText("1");
        ui->tableWidget_karno->setItem(3, 1, item_1);

        QTableWidgetItem *itm_0 = new QTableWidgetItem (*item_0);
        ui->tableWidget_karno->setItem(1, 2, itm_0);

        QTableWidgetItem *itm_1 = new QTableWidgetItem (*item_1);
        ui->tableWidget_karno->setItem(1, 3, itm_1);
        coordinates = coordinates2;
        deque<calculating> deq_k;
        calculating pp;
        for (int i = 2; i < 4; i++) {
            for (int j = 2; j < 4; j++) {
                QTableWidgetItem *itm = ui->tableWidget_karno->item(i, j);
                if (itm->text() == '1') {
                    if (i == 2 && j == 2) {
                        pp.arr[0] = 0, pp.arr[1] = 0;
                    }
                    else if (i == 2 && j == 3) {
                        pp.arr[0] = 0, pp.arr[1] = 1;
                    }
                    else if (i == 3 && j == 2) {
                        pp.arr[0] = 1, pp.arr[1] = 0;
                    }
                    else if (i == 3 && j == 3) {
                        pp.arr[0] = 1, pp.arr[1] = 1;
                    }
                    deq_k.push_back(pp);
                }
            }
        }
        std::deque<calculating>::iterator it1, it2;
        deque<calculating> result;
        bool ok = true, del_two_var = false;
        for (it1 = deq_k.begin(); it1 < deq_k.end(); it1++) {
            ok = true;
            for (it2 = it1 + 1; it2 < deq_k.end(); it2++) {
                for (int i = 0; i < 2; i++) {
                    if (it1->arr[i] != it2->arr[i]) {
                        if (i == 0) {
                            if (it1->arr[i+1] != it2->arr[i+1])
                                break;
                        }
                        else if (i == 1) {
                            if (it1->arr[i-1] != it2->arr[i-1])
                                break;
                        }
                        ok = false;
                        pp.arr[i] = -1;
                    }
                    else {
                        pp.arr[i] = it1->arr[i];
                    }
                }
                if (!ok) {
                    result.push_back(pp);
                    del_two_var = true;
                }
            }
            if (ok) {
                result.push_back(*it1);
            }
        }
        if (del_two_var) {
            int size = result.size();
            while (size--) {
                calculating p = result.front();
                result.pop_front();
                if (p.arr[0] == -1 || p.arr[1] == -1) {
                    if ((p.arr[0] == -1 && p.arr[1] != -1) || (p.arr[0] != -1 && p.arr[1] == -1))
                        result.push_back(p);
                }
            }
        }
        QString res;
        while(!result.empty()) {
            calculating p = result.front();
            result.pop_front();
            for (int i = 0; i < 2; i++) {
                if (p.arr[i] == 1) {
                    if (i == 0) {
                        res += "A";
                    }
                    else if (i == 1) {
                        res += "B";
                    }
                }
                else if (p.arr[i] == 0) {
                    if (i == 0) {
                        res += "A'";
                    }
                    else if (i == 1) {
                        res += "B'";
                    }
                }
            }
            if (!result.empty())
                res += "+";
        }
        ui->label_result->setText(res);
    }
        break;
    case 3:
    {
        QBrush brush_green = (QColor(Qt::green));
        QBrush brush_grey = (QColor(Qt::lightGray));
        ui->tableWidget_karno->setRowCount(4);
        ui->tableWidget_karno->setColumnCount(6);

        ui->tableWidget_karno->setSpan(0, 0, 2, 2);
        ui->tableWidget_karno->setSpan(2, 0, 2, 1);
        ui->tableWidget_karno->setSpan(0, 2, 1, 4);

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter);
        item->setBackground(brush_grey);
        item->setText("BC");
        ui->tableWidget_karno->setItem(0, 2, item);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setBackground(brush_grey);
        item2->setText("A");
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
        deque<calculating> loop_1, result;
        std::deque<calculating>::iterator it1, it2;
        calculating pp;
        for (int i = 2; i < 4; i++) {
            for (int j = 2; j < 6; j++) {
                QTableWidgetItem *itm = ui->tableWidget_karno->item(i, j);
                if (itm->text() == '1') {
                    if (i == 2) {
                        pp.arr[0] = 0;
                        if (j == 2)
                            pp.arr[1] = 0, pp.arr[2] = 0;
                        else if (j == 3)
                            pp.arr[1] = 0, pp.arr[2] = 1;
                        else if (j == 4)
                            pp.arr[1] = 1, pp.arr[2] = 1;
                        else if (j == 5)
                            pp.arr[1] = 1, pp.arr[2] = 0;
                    }
                    else if (i == 3) {
                        pp.arr[0] = 1;
                        if (j == 2)
                            pp.arr[1] = 0, pp.arr[2] = 0;
                        else if (j == 3)
                            pp.arr[1] = 0, pp.arr[2] = 1;
                        else if (j == 4)
                            pp.arr[1] = 1, pp.arr[2] = 1;
                        else if (j == 5)
                            pp.arr[1] = 1, pp.arr[2] = 0;
                    }
                    loop_1.push_back(pp);
                }
            }
        }
        bool ok = true;
        for (it1 = loop_1.begin(); it1 < loop_1.end(); it1++) {
            ok = true;
            for (it2 = it1 + 1; it2 < loop_1.end(); it2++) {
                int compare = 0;
                for (int i = 0; i < 3; i++) {
                    if (it1->arr[i] == it2->arr[i]) {
                        compare++;
                    }
                }
                if (compare == 2) {
                    ok = false;
                    for (int i = 0; i < 3; i++) {
                        if (it1->arr[i] != it2->arr[i]) {
                            pp.arr[i] = -1;
                        }
                        else {
                            pp.arr[i] = it1->arr[i];
                        }
                    }
                    result.push_back(pp);
                }
            }
            if (ok) {
                result.push_back(*it1);
            }
        }
        while(!loop_1.empty()) {
            loop_1.pop_front();
        }
        bool del_two_var = false;
        for (it1 = result.begin(); it1 < result.end(); it1++) {
            ok = true;
            for (it2 = it1 + 1; it2 < result.end(); it2++) {
                int compare = 0;
                for (int i = 0; i < 3; i++) {
                    if (it1->arr[i] == it2->arr[i]) {
                        compare++;
                    }
                }
                if (compare == 2) {
                    ok = false;
                    for (int i = 0; i < 3; i++) {
                        if (it1->arr[i] != it2->arr[i]) {
                            pp.arr[i] = -1;
                        }
                        else {
                            pp.arr[i] = it1->arr[i];
                        }
                    }
                    loop_1.push_back(pp);
                }
            }
            if (ok) {
                del_two_var = true;
                loop_1.push_back(*it1);
            }
            if (del_two_var) {
                int size = loop_1.size();
                while (size--) {
                    calculating p = loop_1.front();
                    loop_1.pop_front();
                    if (p.arr[0] == -1 || p.arr[1] == -1 || p.arr[2] == -1) {
                        if ((p.arr[0] == -1 && p.arr[1] != -1 && p.arr[2] != -1) || (p.arr[0] != -1 && p.arr[1] == -1 && p.arr[2] != -1) || (p.arr[0] != -1 && p.arr[1] != -1 && p.arr[2] == -1))
                            loop_1.push_back(p);
                    }
                }
            }
        }
        while(!result.empty()) {
            result.pop_front();
        }
        for (it1 = loop_1.begin(); it1 < loop_1.end(); it1++) {
            for (it2 = it1 + 1; it2 < loop_1.end(); it2++) {
                int compare = 0;
                for (int i = 0; i < 3; i++) {
                    if (it1->arr[i] == it2->arr[i]) {
                        compare++;
                    }
                }
                if (compare == 3) {
                    loop_1.erase(it1);
                }
            }
        }
        ok = true;
        for (it1 = loop_1.begin(); it1 < loop_1.end(); it1++) {
            ok = true;
            for (it2 = it1 + 1; it2 < loop_1.end(); it2++) {
                int cnt1 = 0, cnt2 = 0;
                for (int i = 0; i < 3; i++) {
                    if (it1->arr[i] == it2->arr[i] && (it1->arr[i] != -1  && it2->arr[i] != -1)) {
                        cnt1++;
                    }
                    else if (it1->arr[i] != it2->arr[i])
                        cnt2++;
                }
                if (cnt1 == cnt2) {
                    for (int i = 0; i < 3; i++) {
                        if (it1->arr[i] != it2->arr[i]) {
                            pp.arr[i] = -1;
                        }
                        else {
                            pp.arr[i] = it1->arr[i];
                        }
                    }
                    result.push_back(pp);
                }
            }
            if (ok)
                result.push_back(*it1);
        }
        QString result_text;
        while(!result.empty()) {     // less_var
            calculating res = result.front();
            for (int k = 0; k < 3; k++) {
                if (res.arr[k] == 1) {
                    if (k == 0)
                        result_text += "A";
                    else if (k == 1)
                        result_text += "B";
                    else if (k == 2)
                        result_text += "C";
                }
                else if (res.arr[k] == 0) {
                    if (k == 0)
                        result_text += "A'";
                    else if (k == 1)
                        result_text += "B'";
                    else if (k == 2)
                        result_text += "C'";
                }
            }
            result.pop_front();
            if (!result.empty())
                result_text += '+';
        }
        ui->label_result->setText(result_text);
        break;
    }
    case 4:
    {
        ui->tableWidget_karno->setRowCount(6);
        ui->tableWidget_karno->setColumnCount(6);

        ui->tableWidget_karno->setSpan(0, 0, 2, 2);
        ui->tableWidget_karno->setSpan(2, 0, 4, 1);
        ui->tableWidget_karno->setSpan(0, 2, 1, 4);
        QBrush brush_green = (QColor(Qt::green));
        QBrush brush_grey = (QColor(Qt::lightGray));
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignHCenter);
        item->setBackground(brush_grey);
        item->setText("AB");
        ui->tableWidget_karno->setItem(0, 2, item);

        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setBackground(brush_grey);
        item2->setText("CD");
        ui->tableWidget_karno->setItem(2, 0, item2);

        QTableWidgetItem *item_00 = new QTableWidgetItem;
        item_00->setTextAlignment(Qt::AlignCenter);
        item_00->setBackground(brush_green);
        item_00->setText("00");
        ui->tableWidget_karno->setItem(1, 2, item_00);

        QTableWidgetItem *item_01 = new QTableWidgetItem;
        item_01->setTextAlignment(Qt::AlignCenter);
        item_01->setBackground(brush_green);
        item_01->setText("01");
        ui->tableWidget_karno->setItem(1, 3, item_01);

        QTableWidgetItem *item_11 = new QTableWidgetItem;
        item_11->setTextAlignment(Qt::AlignCenter);
        item_11->setBackground(brush_green);
        item_11->setText("11");
        ui->tableWidget_karno->setItem(1, 4, item_11);

        QTableWidgetItem *item_10 = new QTableWidgetItem;
        item_10->setTextAlignment(Qt::AlignCenter);
        item_10->setBackground(brush_green);
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
        int column_in_karno = 2, i = 0;
        for (int f = 0; f < 4; f++) {
            if (column_in_karno == 4) {
                column_in_karno++;
            }
            else if (column_in_karno == 6) {
                column_in_karno -= 2;
            }
            for (int row_in_karno = 2; row_in_karno < 6; row_in_karno++) {
                QTableWidgetItem *item_from_ist = ui->tableWidget_ist->item(i, 4);
                QTableWidgetItem *item_to_karno = new QTableWidgetItem;
                if (item_from_ist->text() == '1') {
                    item_to_karno->setText("1");
                    if (row_in_karno == 4) {
                        ui->tableWidget_karno->setItem(row_in_karno + 1, column_in_karno, item_to_karno);
                    }
                    else if (row_in_karno == 5) {
                        ui->tableWidget_karno->setItem(row_in_karno - 1, column_in_karno, item_to_karno);
                    }
                    else
                        ui->tableWidget_karno->setItem(row_in_karno, column_in_karno, item_to_karno);
                }
                else if (item_from_ist->text() == '0') {
                    item_to_karno->setText("0");
                    if (row_in_karno == 4) {
                        ui->tableWidget_karno->setItem(row_in_karno + 1, column_in_karno, item_to_karno);
                    }
                    else if (row_in_karno == 5) {
                        ui->tableWidget_karno->setItem(row_in_karno - 1, column_in_karno, item_to_karno);
                    }
                    else
                        ui->tableWidget_karno->setItem(row_in_karno, column_in_karno, item_to_karno);
                }
                i++;
            }
            column_in_karno++;
        }
        deque<calculating> d;
        calculating calc;
        for (i = 2; i < 6; i++) {          // ряды
            for (column_in_karno = 2; column_in_karno < 6; column_in_karno++) {
                QTableWidgetItem *itm;
                itm = ui->tableWidget_karno->item(i, column_in_karno);
                if (itm->text() == '1') {
                    if (i == 2)
                        calc.arr[2] = 0, calc.arr[3] = 0;
                    else if (i == 3)
                        calc.arr[2] = 0, calc.arr[3] = 1;
                    else if (i == 4)
                        calc.arr[2] = 1, calc.arr[3] = 1;
                    else if (i == 5)
                        calc.arr[2] = 1, calc.arr[3] = 0;
                    if (column_in_karno == 2)
                        calc.arr[0] = 0, calc.arr[1] = 0;
                    else if (column_in_karno == 3)
                        calc.arr[0] = 0, calc.arr[1] = 1;
                    else if (column_in_karno == 4)
                        calc.arr[0] = 1, calc.arr[1] = 1;
                    else if (column_in_karno == 5)
                        calc.arr[0] = 1, calc.arr[1] = 0;
                    d.push_back(calc);
                }
            }
        }

        deque<calculating> less_var, loop_2, devour;
        calculating pp;
        std::deque<calculating>::iterator it1, it2;
        int compare = 0;
        bool simpl = true;
        for (it1 = d.begin(); it1 < d.end(); it1++) {
            for (it2 = it1 + 1; it2 < d.end(); it2++) {
                compare = 0;
                for (int k = 0; k < 4; k++) {
                    if (it1->arr[k] == it2->arr[k]) {
                        compare++;
                    }
                }
                if (compare == 3) {
                    simpl = false;
                    for (int k = 0; k < 4; k++) {
                        if (it1->arr[k] != it2->arr[k]) {
                            pp.arr[k] = -1;
                        }
                        else {
                            pp.arr[k] = it1->arr[k];
                        }
                    }
                    less_var.push_back(pp);
                }
            }
            if (simpl)
                devour.push_back(*it1);
        }
        compare = 0;
        bool compound = false;
        for (it1 = less_var.begin(); it1 < less_var.end(); it1++) {
            compound = false;
            for (it2 = it1 + 1; it2 < less_var.end(); it2++) {
                compare = 0;
                for (int k = 0; k < 4; k++) {
                    if (it1->arr[k] == it2->arr[k]) {
                        compare++;
                    }
                }
                if (compare == 3) {
                    for (int k = 0; k < 4; k++) {
                        if (it1->arr[k] != it2->arr[k]) {
                            pp.arr[k] = -1;
                        }
                        else {
                            pp.arr[k] = it1->arr[k];
                        }
                    }
                    compound = true;
                    loop_2.push_back(pp);
                }
            }
            if (!compound) {
                int minus_one = 0;
                for (int j = 0; j < 4; j++) {    // считаем не -1
                    if (it1->arr[j] != -1)
                        minus_one++;
                }
                if (minus_one >= 3) {          // если 3 или 4 переменные
                    devour.push_back(*it1);     // в отдельный дек, где потом будем проверять нельзя ли полготить их
                }
                else
                    loop_2.push_back(*it1);
            }
        }

        compare = 0, compound = true;
        int size = loop_2.size();
        while (size--) {                  // полгощаем абсолютно одинаковые элементы
            it1 = loop_2.begin();
            compound = true;
            for (; it1 < loop_2.end() && compound; it1++) {
                for (it2 = it1 + 1; it2 < loop_2.end() && compound; it2++) {
                    compare = 0;
                    for (int k = 0; k < 4; k++) {
                        if (it1->arr[k] == it2->arr[k]) {
                            compare++;
                        }
                    }
                    if (compare == 4) {
                        compound = false;
                        loop_2.erase(it2);
                        break;
                    }
                }
            }
        }
        while (!devour.empty()) {                // пытаемся сделать поглощение больших элементов меньшими
            calculating dev = devour.front();
            devour.pop_front();
            bool ok = true;
            vector<int> vec;
            int size1 = 0, size2 = 0;
            for (int j = 0; j < 4; j++) {
                if (dev.arr[j] != -1)
                    size1++;
                vec.push_back(dev.arr[j]);
            }
            for (it1 = loop_2.begin(); it1 < loop_2.end() && ok; it1++) {
                size2 = 0;
                int count_similar = 0;
                for (int j = 0; j < 4; j++) {
                    if (it1->arr[j] != -1)
                        size2++;
                }
                for (int j = 0; j < 4; j++) {
                    if (it1->arr[j] == vec[j] && (it1->arr[j] != -1 && vec[j] != -1)) {
                        count_similar++;
                    }
                }
                if (count_similar >= 2 && size1 > size2) {    // поглотили
                    ok = false;
                }
            }
            if (ok) {                // элемент не поглощается
                loop_2.push_back(dev);
            }
        }
        while(!less_var.empty()) {
            less_var.pop_back();
        }
        for (it1 = loop_2.begin(); it1 < loop_2.end(); it1++) {
            bool ok = true;
            for (it2 = it1 + 1; it2 < loop_2.end() && ok; it2++) {
                for (int j = 0; j < 4; j++) {
                    if (it1->arr[j] != -1 && it2->arr[j] != -1) {
                        for (int k = j + 1; k < 4; k++) {
                            if (it1->arr[k] == it2->arr[k] && (it1->arr[k] != -1 && it2->arr[k] != -1)) {
                                it1->arr[j] = -1;
                                less_var.push_back(*it1);
                                loop_2.erase(it2);
                                ok = false;
                                break;
                            }
                        }
                    }
                }
            }
            if (ok) {                // элемент не поглощается
                less_var.push_back(*it1);
            }
        }
        for (it1 = less_var.begin(); it1 < less_var.end(); it1++) {
            for (it2 = it1 + 1; it2 < less_var.end(); it2++) {
                int odinakovie = 0;
                for (int j = 0; j < 4; j++) {
                    if (it1->arr[j] == it2->arr[j]) {
                        odinakovie++;
                    }
                }
                if (odinakovie == 4) {
                    less_var.erase(it1);
                    break;
                }
            }
        }
        QString result;
        while(!less_var.empty()) {     // less_var
            calculating res = less_var.front();
            for (int k = 0; k < 4; k++) {
                if (res.arr[k] == 1) {
                    if (k == 0)
                        result += "A";
                    else if (k == 1)
                        result += "B";
                    else if (k == 2)
                        result += "C";
                    else if (k == 3)
                        result += "D";
                }
                else if (res.arr[k] == 0) {
                    if (k == 0)
                        result += "A'";
                    else if (k == 1)
                        result += "B'";
                    else if (k == 2)
                        result += "C'";
                    else if (k == 3)
                        result += "D'";
                }
            }
            less_var.pop_front();
            if (!less_var.empty())
                result += '+';
        }
        ui->label_result->setText(result);
        break;
        // coordinates = coordinates34;
    }
    }

    int cnt_zero = 0, cnt_one = 0;
    for (int r = 0; r < rows; r++)
    {
        QTableWidgetItem *itm = ui->tableWidget_ist->item(r, clmns);
        QTableWidgetItem *inKarnaugh = new QTableWidgetItem (*itm);
        // получаем номер строки в табл истинности. Находим его в словаре. Получаем номера ячеек для Карно
        int r_k = coordinates[r].row;
        int c_k = coordinates[r].column;
        if (itm->text() == '1')
            cnt_one++;
        else if (itm->text() == '0')
            cnt_zero++;
        ui->tableWidget_karno->setItem(r_k, c_k, inKarnaugh);
    }
    ui->tableWidget_karno->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // ц??тр ?чт  э?Ї  ?э тўр ?ч ?рЇ   ???   Ўў??ц¦?ч
    ui->tableWidget_karno->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);   // ц??тр ?чт  э?Ї  ?э тўр ?ч ?рЇ   ???    Їэ?ч
    ui->tableWidget_karno->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_karno->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int w = ui->tableWidget_karno->verticalHeader()->width() +4;                                      // Ў§рў ??   ???  ?т?  э?Ї ў ц?р¦« (+4 ?Ј???!)
    for (int i = 0; i < ui->tableWidget_karno->columnCount(); i++)                                    // Ў§рў ?? Ёр р?Ј
    {
        w += ui->tableWidget_karno->columnWidth(i);
    }
    int h = ui->tableWidget_karno->horizontalHeader()->height() + 4;
    for (int i = 0; i < ui->tableWidget_karno->rowCount(); i++)                                       // Ў§рў ?? ч«Ў?ўЈ
    {
        h += ui->tableWidget_karno->rowHeight(i);
    }
    QSize p = QSize(w, h);
    ui->tableWidget_karno->setFixedSize(p);
    if (cnt_zero == rows) {
        ui->label_result->setText("0");
        return;
    }
    else if (cnt_one == rows) {
        ui->label_result->setText("1");
        return;
    }
}

