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
    void on_checkBox_2var_stateChanged(int arg1);

    void on_pushButton_map_carno_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
