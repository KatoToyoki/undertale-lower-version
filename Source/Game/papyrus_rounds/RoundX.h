#pragma once
#include "../BarrageMode.h"

class RoundX : public BarrageMode
{
private:
public:
    RoundX(int quantity):BarrageMode(quantity){}
    
    ~RoundX()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;
};
