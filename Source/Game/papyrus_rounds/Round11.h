#pragma once
#include "../BarrageMode.h"

class Round11 : public BarrageMode
{
private:
public:
    Round11(int quantity):BarrageMode(quantity){}

    ~Round11()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;
};
