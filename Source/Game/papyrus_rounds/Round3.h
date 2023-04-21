#pragma once
#include "../BarrageMode.h"

class Round3 : public BarrageMode
{
private:
public:
    Round3(int quantity):BarrageMode(quantity){}

    ~Round3()=default;
    
    virtual void SetAllData() override;
    virtual void recordXYDamageSpeed() override;
    virtual void MovingBarrage(Move *heart) override;
};
