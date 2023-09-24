#ifndef TCPCLIENTTHREAD_H
#define TCPCLIENTTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
class TCPClientThread : public QThread
{
    Q_OBJECT
public:
    TCPClientThread();
    void run();
public slots:
    void sendDataToTCPServer(QString data);
private:
    QTcpSocket *m_TCPClientSocket;
    QString SenderBuffer;
};

#endif // TCPCLIENTTHREAD_H
