#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    emit sendData("TURN ON RED LED");
}

void MainWindow::on_pushButton_2_clicked()
{
    emit sendData("TURN OFF RED LED");
}

void MainWindow::on_pushButton_4_clicked()
{
    emit sendData("TURN ON GREEN LED");
}

void MainWindow::on_pushButton_3_clicked()
{
    emit sendData("TURN OFF GREEN LED");
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    emit sendData(QString::number(value));
}

