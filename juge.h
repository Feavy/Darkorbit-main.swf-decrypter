#ifndef JUGE_H
#define JUGE_H

#include "QByteArray.h"
#include <QList>
#include <array>
#include <vector>
#include "bemutyry.h"

class Juge
{
public:
    Juge(QByteArray param1);
    void lapih(QByteArray &param1);
    QByteArray pus(QList<unsigned int> param1);
    void noc(QList<unsigned int> param1, unsigned int param2, QList<unsigned int> &param3, unsigned int param4, unsigned int param5);
    void nake(QList<int> param1);
    QList<int> pufy(QByteArray param1);
    QList<unsigned int> vucaha(QByteArray param1);
    int lebopof(QList<int> param1, unsigned int param2);
    unsigned int qyfoluko();

    QList<unsigned int> kili;

    QList<unsigned int> haw;

    unsigned int paf;

    unsigned int zekep;

    QList<int> key;

    std::array<long long int, 10> dehy;

    Bemutyry cagij;
};

#endif // JUGE_H
