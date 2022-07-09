#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H

//#include <QMainWindow>
#include <QtCore>
#include <QSerialPort>
#include "mainwindow.h"
//extern QSerialPort serial;//Global object

class SerialPortThread:public QThread
{
public:
    //static QSerialPort serial;
    //QSerialPort serial;
    SerialPortThread();
    void run();
};

#endif // SERIALPORTTHREAD_H
