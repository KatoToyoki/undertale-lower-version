#pragma once
#include "../BarrageMode.h"

class Round5 : public BarrageMode
{
private:
public:
    Round5(int quantity):BarrageMode(quantity){}

    ~Round5()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;

    void SecondWave(Move *heart);
    void ThirdWave(Move *heart);
};
