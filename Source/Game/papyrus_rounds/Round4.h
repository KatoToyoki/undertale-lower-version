#pragma once
#include "../BarrageMode.h"

class Round4 : public BarrageMode
{
private:
public:
    Round4(int quantity):BarrageMode(quantity){}

    ~Round4()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;
    void LastOneFast(Move* heart);
};
