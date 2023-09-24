#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include "TCPClientThread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TCPClientThread client;
    QObject::connect(&w, SIGNAL(sendData(QString)), &client, SLOT(sendDataToTCPServer(QString)));
    w.show();
    return a.exec();
}
