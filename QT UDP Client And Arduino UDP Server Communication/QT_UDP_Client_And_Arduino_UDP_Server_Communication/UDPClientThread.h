#ifndef UDPCLIENTTHREAD_H
#define UDPCLIENTTHREAD_H

#include <QThread>
#include <QObject>
#include <QUdpSocket>
class UDPClientThread : public QThread
{
    Q_OBJECT
public:
    UDPClientThread();
    void sendMessageOverUDP(QString message, quint16 port_i16);
    void run();
private:
    QUdpSocket *m_UDPSocket = nullptr;
    QString m_message;
    bool m_sendFlag = false;
public slots:
    void sendMessage(QString message);

};

#endif // UDPCLIENTTHREAD_H
