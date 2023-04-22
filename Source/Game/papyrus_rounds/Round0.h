#pragma once
#include "../BarrageMode.h"

class Round0 : public BarrageMode
{
private:
public:
    Round0(int quantity):BarrageMode(quantity){}

    ~Round0()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;
};
