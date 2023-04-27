#pragma once
#include "../BarrageMode.h"

enum EndPoint
{
    leftAtLeft,leftAtRight,vanish
};

enum Position
{
    front,back,frontEqual,backEqual
};

enum Appearance
{
    normal,compound
};

enum DirectionOfNext
{
    goUp,goDown
};

class PapyrusRound: public BarrageMode
{
private:
    int _q;
    int currentRound=-1;
    int UDBdirection=0;
    bool isSet=false;
public:
    PapyrusRound()=default;
    ~PapyrusRound()=default;
    
    void SetAllData();
    
    void SelectRound(Move *heart);

    void GoRight(Barrage& barrage, Move *heart, int speed);
    void GoLeft(Barrage& barrage, Move *heart, int speed);
    void PincerAttack(int range, Move *heart, int wave,int appearance);

    void CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart);
    void UpDownBarrage(Barrage& barrage, int upLimit, int downLimit, int speed);
    
    void DetectRoundEnd(int direction);
    bool DetectLeft(Barrage& barrage,int direction);
    bool DetectCertainPoint(Barrage& barrage,int point,int position);

    
    void roundX(Move *heart);
    void round0(Move *heart);
    void round1(Move *heart);
};
