#pragma once
#include "../BarrageMode.h"

class Round1 : public BarrageMode
{
private:
public:
    Round1(int quantity):BarrageMode(quantity){}

    ~Round1()=default;
    
    virtual void SetAllData() override;
    virtual void recordXYDamageSpeed() override;
    virtual int MovingBarrage(Move *heart) override;
};
