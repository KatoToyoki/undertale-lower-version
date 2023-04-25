#pragma once
#include "../BarrageMode.h"

class Round7 : public BarrageMode
{
private:
public:
    Round7(int quantity):BarrageMode(quantity){}

    ~Round7()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;

    void Wave(Move *heart);
};
