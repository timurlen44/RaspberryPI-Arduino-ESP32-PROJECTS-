#include "TCPClientThread.h"

TCPClientThread::TCPClientThread()
{
    m_TCPClientSocket = new QTcpSocket(this);
}

void TCPClientThread::run()
{

}

void TCPClientThread::sendDataToTCPServer(QString data)
{

    m_TCPClientSocket->connectToHost("169.254.69.60",80);

    if(m_TCPClientSocket->waitForConnected(500)){

        QString senderBuffer = "#" + data + "#";
        m_TCPClientSocket->write(senderBuffer.toStdString().c_str());

        m_TCPClientSocket->waitForBytesWritten(500);

    }

    else{

        qDebug()<<"Couldn't Connected To Server !!!\n";

    }

    m_TCPClientSocket->close();
}
