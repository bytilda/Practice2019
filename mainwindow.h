#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mapwidget.h"
#include "windows.h"
#include "QTimer"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private slots:
    void on_StartButton_clicked();

    void on_nextStep_button_clicked();

    void on_auto_button_clicked();





    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QTimer* timer = new QTimer(this);
    bool isAutoStarted = false;
    //MapWidget *mw;
};

#endif // MAINWINDOW_H
