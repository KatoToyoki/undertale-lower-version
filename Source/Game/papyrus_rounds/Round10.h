#pragma once
#include "../BarrageMode.h"

class Round10 : public BarrageMode
{
private:
public:
    Round10(int quantity):BarrageMode(quantity){}

    ~Round10()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;
};
