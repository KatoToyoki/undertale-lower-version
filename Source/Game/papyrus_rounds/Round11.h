#pragma once
#include "../BarrageMode.h"

enum DirectionOfNext
{
    goUp,goDown
};

class Round11 : public BarrageMode
{
private:
public:
    int button=0;
    int direction=0; // 0 up 1 down
    
    Round11(int quantity):BarrageMode(quantity){}

    ~Round11()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;

    void UpDownBarrage(Barrage& barrage, int upLimit, int downLimit);
    void CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart);
    
};
