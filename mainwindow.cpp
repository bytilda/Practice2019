#include "mainwindow.h"
#include "ui_mainwindow.h"


//uic mainwindow.ui>ui_mainwindow.h
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->widget->update();
    //ui->widget->setUpdatesEnabled(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_nextStep_button_clicked()));
    ui->auto_button->setEnabled(false);
    ui->nextStep_button->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_StartButton_clicked()
{    
    ui->widget->setHasStarted(true);
    ui->nextStep_button->setEnabled(true);
    ui->auto_button->setEnabled(true);
    ui->widget->update();    
    ui->StartButton->setEnabled(false);
    ui->checkBox->setEnabled(false);
    if(ui->checkBox->isChecked())ui->widget->enableCrashes();
}



void MainWindow::on_nextStep_button_clicked()
{


    //ui->widget->setUpdatesEnabled(true);
    ui->widget->nextStep(0.03);
    ui->time_value->setText(QString::number(ui->widget->getTime()) + "c.u.");
    ui->Amount->setText(QString::number(ui->widget->getInfoaboutAmountOfTransport()));

    //ui->widget->setUpdatesEnabled(false);

}

void MainWindow::on_auto_button_clicked()
{
    /*int a = 10;
    while(a--){
        Sleep(100);
        ui->widget->setUpdatesEnabled(true);
        ui->widget->nextStep(1);
        this->update();

        ui->widget->setUpdatesEnabled(false);
    }*/
    if(!isAutoStarted){
        timer->start(7);
        isAutoStarted = true;
        ui->auto_button->setText("Stop");
    }
    else{
        timer->stop();
        isAutoStarted = false;
        ui->auto_button->setText("Auto");
    }
}



void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->widget->setStreamLevel(arg1);
}
