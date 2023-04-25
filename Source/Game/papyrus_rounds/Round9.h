#pragma once
#include "../BarrageMode.h"

class Round9 : public BarrageMode
{
private:
public:
    Round9(int quantity):BarrageMode(quantity){}

    ~Round9()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;
};
