#include "mainwindow.h"

#include <QApplication>

#include "UDPClientThread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    UDPClientThread udp;
    udp.start(); // for thread
    QObject::connect(&w,SIGNAL(sendMessage(QString)),&udp,SLOT(sendMessage(QString)));
    w.show();
    return a.exec();
}
