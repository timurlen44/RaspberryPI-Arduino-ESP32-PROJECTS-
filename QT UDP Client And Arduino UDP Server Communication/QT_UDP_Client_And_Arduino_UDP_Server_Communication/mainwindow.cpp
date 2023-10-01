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
    QString firstLineOfLCD_qstr = ui->lineEdit->text();
    QString secondLineOfLCD_qstr = ui->lineEdit_2->text();

    QString buffer(firstLineOfLCD_qstr);
    for(int i = firstLineOfLCD_qstr.size();i<16;i++)
    {
        buffer.append(" ");
    }

    buffer.append(secondLineOfLCD_qstr);
    for(int i = secondLineOfLCD_qstr.size();i<16;i++)
    {
        buffer.append(" ");
    }
    buffer.append("\n");
    qDebug()<<"Data: "<<buffer;
    qDebug()<<"Size: "<<buffer.size();

    emit sendMessage(buffer);
}

