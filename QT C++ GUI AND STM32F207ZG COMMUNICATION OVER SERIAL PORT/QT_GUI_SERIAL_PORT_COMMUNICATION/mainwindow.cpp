#include <qmainwindow.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialportthread.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    connect(serial,SIGNAL(readyRead()),this,SLOT(ReadDataFromSTM32F207ZG()));
    serial->setPortName("COM9");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    serial->waitForReadyRead(30000);
}

MainWindow::~MainWindow()
{
    serial->close();
    delete serial;
    delete ui;
}


void MainWindow::on_pushButton_pressed()
{
    qDebug()<<"LEDS ARE TURN ON\n";
    serial->write("LED ON");
}


void MainWindow::on_pushButton_2_pressed()
{
    qDebug()<<"LEDS ARE TURN OFF\n";
    serial->write("LED OFF");
}

void MainWindow::ReadDataFromSTM32F207ZG()
{
    QString ReceivedBuffer = serial->readAll();
    if(!ReceivedBuffer.isEmpty())
    {
        ui->lineEdit->setText(ReceivedBuffer);
        qDebug()<<ReceivedBuffer;

    }




}
