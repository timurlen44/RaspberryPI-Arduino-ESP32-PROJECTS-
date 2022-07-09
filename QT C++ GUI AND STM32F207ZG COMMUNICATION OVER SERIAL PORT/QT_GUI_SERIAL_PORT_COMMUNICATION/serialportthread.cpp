#include "serialportthread.h"

SerialPortThread::SerialPortThread()
{
    qDebug()<<"SerialPortThread begin\n";
    QSerialPort serial;
    /*
    serial.setPortName("COM9");
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);
    */
    //serial.write("LED ON\n");

    //serial.write("LED ON\n");
}

void SerialPortThread::run(){

    while(true)
    {
        /*
        qDebug()<<"emre\n";
        QThread::msleep(1000);
        */
        /*
        serial.waitForReadyRead();
        QString ReceivedBuffer = serial.readLine();
        if(!ReceivedBuffer.isEmpty())
        {
            qDebug()<<ReceivedBuffer;

        }
        */

        qDebug()<<"emre\n";
        QThread::msleep(1000);
        /*
        qDebug()<<"LED ON\n";
        serial.write("LED ON\n");
        QThread::msleep(1000);
        qDebug()<<"LED OFF\n";
        serial.write("LED OFF\n");
        QThread::msleep(1000);
        */

    }
}

