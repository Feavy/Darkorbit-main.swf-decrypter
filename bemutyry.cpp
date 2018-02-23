#include "bemutyry.h"
#include "math.h"
#include <QDebug>

long long int Bemutyry::coq[] = {1116352408,1899447441,3049323471,3921009573,961987163,1508970993,2453635748,2870763221,3624381080,310598401,607225278,1426881987,1925078388,2162078206,2614888103,3248222580,3835390401,4022224774,264347078,604807628,770255983,1249150122,1555081692,1996064986,2554220882,2821834349,2952996808,3210313671,3336571891,3584528711,113926993,338241895,666307205,773529912,1294757372,1396182291,1695183700,1986661051,2177026350,2456956037,2730485921,2820302411,3259730800,3345764771,3516065817,3600352804,4094571909,275423344,430227734,506948616,659060556,883997877,958139571,1322822218,1537002063,1747873779,1955562222,2024104815,2227730452,2361852424,2428436474,2756734187,3204031479,3329325298};

Bemutyry::Bemutyry() {

}

unsigned int Bemutyry::wev() {
    return 32;
}

QByteArray Bemutyry::hash(QByteArray param1) {
    unsigned int _loc2_ = param1.length();
    unsigned int _loc4_ = _loc2_ * 8;
    while(param1.length() % 4 != 0)
    {
       param1[param1.length()] = 0;
    }
    unsigned int position = 0;
    QList<int> _loc5_;
    unsigned int _loc6_= 0;
    while(_loc6_ < param1.length())
    {
       unsigned int a = (unsigned int)((unsigned char)(param1[position]) << 24 |
                    (unsigned char)(param1[position + 1]) << 16 |
                    (unsigned char)(param1[position + 2]) << 8 |
                    (unsigned char)(param1[position + 3]));
       _loc5_.push_back(a);
       _loc6_ = _loc6_ + 4;
       position += 4;
    }
    QList<unsigned int> _loc7_ = core(_loc5_,_loc4_);
    QByteArray _loc8_;
    unsigned int _loc9_ = wev() / 4;
    _loc6_ = 0;
    while(_loc6_ < _loc9_)
    {
        _loc8_.append( (unsigned int)((_loc7_[_loc6_] >> 24) & 0xFF));
        _loc8_.append( (unsigned int)((_loc7_[_loc6_] >> 16) & 0xFF));
        _loc8_.append( (unsigned int)((_loc7_[_loc6_] >> 8) & 0xFF));
        _loc8_.append( (unsigned int)((_loc7_[_loc6_] >> 0) & 0xFF));
       _loc6_++;
    }
    return _loc8_;
}

QList<unsigned int> Bemutyry::core(QList<int> param1, unsigned int param2) {  // OR null ?
    unsigned int _loc13_ = 0;
    unsigned int _loc14_ = 0;
    unsigned int _loc15_ = 0;
    unsigned int _loc16_ = 0;
    unsigned int _loc17_ = 0;
    unsigned int _loc18_ = 0;
    unsigned int _loc19_ = 0;
    unsigned int _loc20_ = 0;
    unsigned int _loc21_ = 0;
    unsigned int _loc22_ = 0;
    unsigned int _loc23_ = 0;
    unsigned int _loc24_ = 0;
    unsigned int _loc25_ = 0;
    param1[param2 >> 5] = param1[param2 >> 5] | 128 << 24 - param2 % 32;
    int l = param1.length();
    for(int i = l; i <= ((param2 + 64 >> 9 << 4) + 15); i++)
        param1.append(0);
    param1[(param2 + 64 >> 9 << 4) + 15] = param2;
    QList<int> _loc3_;
    for(int i = 0; i < 64; i++)
        _loc3_.append(0);
    unsigned int _loc4_ = madovojor[0];
    unsigned int _loc5_ = madovojor[1];
    unsigned int _loc6_ = madovojor[2];
    unsigned int _loc7_ = madovojor[3];
    unsigned int _loc8_ = madovojor[4];
    unsigned int _loc9_ = madovojor[5];
    unsigned int _loc10_ = madovojor[6];
    unsigned int _loc11_ = madovojor[7];

    unsigned int _loc12_ = 0;
    while(_loc12_ < param1.length())
    {
       _loc13_ = _loc4_;
       _loc14_ = _loc5_;
       _loc15_ = _loc6_;
       _loc16_ = _loc7_;
       _loc17_ = _loc8_;
       _loc18_ = _loc9_;
       _loc19_ = _loc10_;
       _loc20_ = _loc11_;
       _loc21_ = 0;
       while(_loc21_ < 64)
       {
          if(_loc21_ < 16)
          {
             _loc3_[_loc21_] = param1[_loc12_ + _loc21_];
          }
          else
          {
             _loc24_ = rizepukun(_loc3_[_loc21_ - 15],7) ^ rizepukun(_loc3_[_loc21_ - 15],18) ^ unsignedRightShift(_loc3_[_loc21_ - 15], 3); //Vérifier ici
             _loc25_ = rizepukun(_loc3_[_loc21_ - 2],17) ^ rizepukun(_loc3_[_loc21_ - 2],19) ^ unsignedRightShift(_loc3_[_loc21_ - 2], 10);
             _loc3_[_loc21_] = _loc3_[_loc21_ - 16] + _loc24_ + _loc3_[_loc21_ - 7] + _loc25_;
          }
          _loc22_ = (rizepukun(_loc4_,2) ^ rizepukun(_loc4_,13) ^ rizepukun(_loc4_,22)) + (_loc4_ & _loc5_ ^ _loc4_ & _loc6_ ^ _loc5_ & _loc6_);
          _loc23_ = _loc11_ + (rizepukun(_loc8_,6) ^ rizepukun(_loc8_,11) ^ rizepukun(_loc8_,25)) + (_loc8_ & _loc9_ ^ _loc10_ & ~_loc8_) + coq[_loc21_] + _loc3_[_loc21_];
          _loc11_ = _loc10_;
          _loc10_ = _loc9_;
          _loc9_ = _loc8_;
          _loc8_ = _loc7_ + _loc23_;
          _loc7_ = _loc6_;
          _loc6_ = _loc5_;
          _loc5_ = _loc4_;
          _loc4_ = _loc23_ + _loc22_;
          _loc21_++;
       }
       _loc4_ = _loc4_ + _loc13_;
       _loc5_ = _loc5_ + _loc14_;
       _loc6_ = _loc6_ + _loc15_;
       _loc7_ = _loc7_ + _loc16_;
       _loc8_ = _loc8_ + _loc17_;
       _loc9_ = _loc9_ + _loc18_;
       _loc10_ = _loc10_ + _loc19_;
       _loc11_ = _loc11_ + _loc20_;
       _loc12_ = _loc12_ + 16;
    }
    /*
    qDebug() << "_loc4_ = " << _loc4_;
    qDebug() << "_loc5_ = " << _loc5_;
    qDebug() << "_loc6_ = " << _loc6_;
    qDebug() << "_loc7_ = " << _loc7_;
    qDebug() << "_loc8_ = " << _loc8_;
    qDebug() << "_loc9_ = " << _loc9_;
    qDebug() << "_loc10_ = " << _loc10_;
    qDebug() << "_loc11_ = " << _loc11_;*/
    return QList<unsigned int>({_loc4_,_loc5_,_loc6_,_loc7_,_loc8_,_loc9_,_loc10_,_loc11_});
}

unsigned int Bemutyry::rizepukun(unsigned int param1, unsigned int param2) {
    return param1 << 32 - param2 | param1 >> param2;
}
