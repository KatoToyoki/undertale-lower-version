#pragma once
#include "../BarrageMode.h"

class Round2 : public BarrageMode
{
private:
public:
    Round2(int quantity):BarrageMode(quantity){}

    ~Round2()=default;
    
    virtual void SetAllData() override;
    virtual void recordXYDamageSpeed() override;
    virtual int MovingBarrage(Move *heart) override;
    
};
