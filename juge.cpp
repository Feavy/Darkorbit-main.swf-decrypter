#include "juge.h"
#include "math.h"

#include <QDebug>

Juge::Juge(QByteArray param1) : zekep(0),
    paf(0) {

    QList<int> _loc3_ = {1,2,3,4,5,6,7,8,9,10};
    key = pufy(param1);
    nake(_loc3_);
}

QList<int> Juge::pufy(QByteArray param1) {
    param1 = cagij.hash(param1);
    QList<int> _loc2_;
    int _loc3_= 0;
    unsigned position = 0;
    while(_loc3_ < param1.length())
    {
       _loc2_.push_back(param1[position]);
       _loc3_++;
       position++;
    }
    return _loc2_;
}

int Juge::lebopof(QList<int> param1, unsigned int param2) {
   return param1[param2 + 3] << 24 | (param1[param2 + 2] & 255) << 16 | (param1[param2 + 1] & 255) << 8 | param1[param2] & 255;
}

void Juge::nake(QList<int> param1) {
    unsigned long int _loc3_ = 0;
    unsigned long int  _loc4_ = 0;
    unsigned long int  _loc5_ = 0;
    dehy[0] = lebopof(key,0);
    dehy[1] = lebopof(key,4);
    dehy[2] = key[8] & 255 | key[9] << 8 & 65280;
    dehy[3] = lebopof(param1,0);
    dehy[4] = lebopof(param1,4);
    dehy[5] = param1[8] & 255 | param1[9] << 8 & 65280;
    dehy[6] = 0;
    dehy[7] = 0;
    dehy[8] = 0;
    dehy[9] = 28672;

    unsigned int _loc2_ = 0;
    while(_loc2_ < 4 * 9)
    {
       _loc3_ = (dehy[2] << 96 - 66 | unsignedRightShift(dehy[1], 66 - 64)) ^ (dehy[2] << 96 - 93 | unsignedRightShift(dehy[1], 93 - 64));
       _loc4_ = (dehy[5] << 96 - 69 | unsignedRightShift(dehy[4], 69 - 64)) ^ (dehy[5] << 96 - 84 | unsignedRightShift(dehy[4], 84 - 64));
       _loc5_ = (dehy[8] << 96 - 66 | unsignedRightShift(dehy[7], 66 - 64)) ^ (dehy[9] << 128 - 111 | unsignedRightShift(dehy[8], 111 - 96));

       _loc3_ = _loc3_ ^ ((dehy[2] << 96 - 91 | unsignedRightShift(dehy[1], 91 - 64)) & (dehy[2] << 96 - 92 | unsignedRightShift(dehy[1], 92 - 64)) ^ (dehy[5] << 96 - 78 | unsignedRightShift(dehy[4], 78 - 64)));
       _loc4_ = _loc4_ ^ ((dehy[5] << 96 - 82 | unsignedRightShift(dehy[4], 82 - 64)) & (dehy[5] << 96 - 83 | unsignedRightShift(dehy[4], 83 - 64)) ^ (dehy[8] << 96 - 87 | unsignedRightShift(dehy[7], 87 - 64)));
       _loc5_ = _loc5_ ^ ((dehy[9] << 128 - 109 | unsignedRightShift(dehy[8], 109 - 96)) & (dehy[9] << 128 - 110 | unsignedRightShift(dehy[8], 110 - 96)) ^ (dehy[2] << 96 - 69 | unsignedRightShift(dehy[1], 69 - 64)));
       dehy[2] = dehy[1];
       dehy[1] = dehy[0];
       dehy[0] = _loc5_;
       dehy[5] = dehy[4];
       dehy[4] = dehy[3];
       dehy[3] = _loc3_;
       dehy[9] = dehy[8];
       dehy[8] = dehy[7];
       dehy[7] = dehy[6];
       dehy[6] = _loc4_;
       _loc2_++;
    }

}

void Juge::lapih(QByteArray &param1) {
    QList<unsigned int> _loc2_;
    noc(vucaha(param1), 0, _loc2_, 0, param1.length());
    QByteArray _loc3_ = pus(_loc2_);
    param1.clear();
    param1.append(_loc3_);
}

QList<unsigned int> Juge::vucaha(QByteArray param1) {
    unsigned int _loc4_ = 0;
    QList<unsigned int> _loc2_;
    unsigned int _loc3_ = param1.length();
    unsigned int position = 0;
    while(position < _loc3_)
    {
       _loc4_ = (unsigned char)param1[position];
       _loc2_.push_back(_loc4_);
       position ++;
    }
    return _loc2_;
}

QByteArray Juge::pus(QList<unsigned int> param1) {
    unsigned int _loc4_ = 0;
    QByteArray _loc2_;
    unsigned int _loc3_ = 0;
    while(_loc3_ < param1.length())
    {
       _loc4_ = param1[_loc3_];
       _loc2_.append(_loc4_);
       _loc3_++;
    }
    return _loc2_;
}

void Juge::noc(QList<unsigned int> param1, unsigned int param2, QList<unsigned int> &param3, unsigned int param4, unsigned int param5) {
    unsigned int _loc6_ = param4 + param5;

    int l = param3.length();
    for(int i = l; i < _loc6_; i++)
        param3.push_back(0);
    while(param4 < _loc6_)
    {
       if(zekep == 0)
       {
          paf = qyfoluko();
          zekep = 4;
       }
       param3[param4] = (param1[param2] ^ paf) & 255;
       paf = paf >> 8;
       zekep--;
       param4 = param4 + 1;
       param2 = param2 + 1;
    }
    qDebug() << "noc success";
}

unsigned int Juge::qyfoluko() {

    unsigned int _loc1_= 0;
    unsigned int _loc2_ = 0;
    unsigned int _loc3_ = 0;
    _loc1_ = (dehy[2] << 96 - 66 | unsignedRightShift(dehy[1], 66 - 64)) ^ (dehy[2] << 96 - 93 | unsignedRightShift(dehy[1], 93 - 64));
    _loc2_ = (dehy[5] << 96 - 69 | unsignedRightShift(dehy[4], 69 - 64)) ^ (dehy[5] << 96 - 84 | unsignedRightShift(dehy[4], 84 - 64));
    _loc3_ = (dehy[8] << 96 - 66 | unsignedRightShift(dehy[7], 66 - 64)) ^ (dehy[9] << 128 - 111 | unsignedRightShift(dehy[8], 111 - 96));
    unsigned int _loc4_= _loc1_ ^ _loc2_ ^ _loc3_;
    _loc1_ = _loc1_ ^ ((dehy[2] << 96 - 91 | unsignedRightShift(dehy[1], 91 - 64)) & (dehy[2] << 96 - 92 | unsignedRightShift(dehy[1], 92 - 64)) ^ (dehy[5] << 96 - 78 | unsignedRightShift(dehy[4], 78 - 64)));
    _loc2_ = _loc2_ ^ ((dehy[5] << 96 - 82 | unsignedRightShift(dehy[4], 82 - 64)) & (dehy[5] << 96 - 83 | unsignedRightShift(dehy[4], 83 - 64)) ^ (dehy[8] << 96 - 87 | unsignedRightShift(dehy[7], 87 - 64)));
    _loc3_ = _loc3_ ^ ((dehy[9] << 128 - 109 | unsignedRightShift(dehy[8], 109 - 96)) & (dehy[9] << 128 - 110 | unsignedRightShift(dehy[8], 110 - 96)) ^ (dehy[2] << 96 - 69 | unsignedRightShift(dehy[1], 69 - 64)));
    dehy[2] = dehy[1];
    dehy[1] = dehy[0];
    dehy[0] = _loc3_;
    dehy[5] = dehy[4];
    dehy[4] = dehy[3];
    dehy[3] = _loc1_;
    dehy[9] = dehy[8];
    dehy[8] = dehy[7];
    dehy[7] = dehy[6];
    dehy[6] = _loc2_;
    return _loc4_;
}
