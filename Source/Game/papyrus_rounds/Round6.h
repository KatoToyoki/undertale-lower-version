#pragma once
#include "../BarrageMode.h"

class Round6 : public BarrageMode
{
private:
public:
    Round6(int quantity):BarrageMode(quantity){}

    ~Round6()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;

    void SecondWave(Move *heart);
    void ThirdWave(Move *heart);
};
