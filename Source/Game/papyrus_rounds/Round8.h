#pragma once
#include "../BarrageMode.h"

class Round8 : public BarrageMode
{
private:
public:
    Round8(int quantity):BarrageMode(quantity){}

    ~Round8()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;
};
