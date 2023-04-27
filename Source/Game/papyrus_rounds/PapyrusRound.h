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
    int current_round;
    int UDBdirection=0;
public:
    PapyrusRound()=default;
    ~PapyrusRound()=default;

    void SelectRound();

    void GoRight(Barrage& barrage, Move *heart, int speed);
    void GoLeft(Barrage& barrage, Move *heart, int speed);
    void PincerAttack(int range, Move *heart, int wave,int appearance);

    void CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart);
    void UpDownBarrage(Barrage& barrage, int upLimit, int downLimit, int speed);
    
    void DetectRoundEnd(int direction);
    bool DetectLeft(Barrage& barrage,int direction);
    bool DetectCertainPoint(Barrage& barrage,int point,int position);
    
    void roundX();
    void round0();
    void round1();
};
