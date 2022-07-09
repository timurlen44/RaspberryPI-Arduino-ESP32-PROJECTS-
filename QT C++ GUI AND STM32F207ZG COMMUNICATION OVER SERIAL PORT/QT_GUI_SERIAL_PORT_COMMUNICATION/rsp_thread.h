#ifndef RSP_THREAD_H
#define RSP_THREAD_H

#include <QObject>

class RSP_Thread : public QObject
{
    Q_OBJECT
public:
    explicit RSP_Thread(QObject *parent = nullptr);

signals:

};

#endif // RSP_THREAD_H
