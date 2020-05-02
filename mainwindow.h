#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Build_clicked(); // ��� �����
    void ChosenRadio ();  // connect. �� �㦭� �� ࠧ� ��뢠�� �㭪�� ��� ������, � ��� � �����

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
