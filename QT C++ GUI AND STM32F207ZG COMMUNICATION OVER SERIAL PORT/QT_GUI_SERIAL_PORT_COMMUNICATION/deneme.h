#ifndef DENEME_H
#define DENEME_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class denemeData;

class deneme : public QMainWindow
{
    Q_OBJECT
public:
    explicit deneme(QWidget *parent = nullptr);
    deneme(const deneme &);
    deneme &operator=(const deneme &);
    ~deneme();

signals:


private:
    QSharedDataPointer<denemeData> data;
};

#endif // DENEME_H
