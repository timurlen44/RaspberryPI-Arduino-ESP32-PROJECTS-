#include "UDPClientThread.h"

UDPClientThread::UDPClientThread()
{
    m_UDPSocket = new QUdpSocket(this);
}

void UDPClientThread::sendMessageOverUDP(QString message, quint16 port_i16)
{
    QByteArray data(message.toUtf8());
    QHostAddress hostAddr("169.254.69.60");
    //QHostAddress hostAddr("255.255.255.255");
    m_UDPSocket->writeDatagram(data, hostAddr, port_i16);
}

void UDPClientThread::run()
{
    while(true)
    {
        if(m_sendFlag == true)
        {
            m_sendFlag = false;
            sendMessageOverUDP(m_message,54000);
        }
    }
}

void UDPClientThread::sendMessage(QString message)
{
    m_message.clear();
    m_message.append(message);
    qDebug()<<"m_message: "<<m_message;
    m_sendFlag = true;
    sendMessageOverUDP(m_message,54000);
}
