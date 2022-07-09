#include "deneme.h"

class denemeData : public QSharedData
{
public:

};

deneme::deneme(QWidget *parent)
    : QMainWindow{parent}, data(new denemeData)
{

}

deneme::deneme(const deneme &rhs)
    : data{rhs.data}
{

}

deneme &deneme::operator=(const deneme &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

deneme::~deneme()
{

}
