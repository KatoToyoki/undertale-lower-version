#pragma once
#include "../BarrageMode.h"
#include <iostream>
#include <fstream>
#include "../Library/json.hpp"
using json = nlohmann::json;

class RoundX : public BarrageMode
{
private:
public:
    RoundX(int quantity):BarrageMode(quantity){}
    
    ~RoundX()=default;
    
    virtual void SetAllData() override;
    virtual void recordXYDamageSpeed() override;
    virtual void MovingBarrage(Move *heart) override;

    
    json roundXData;
    
    void test();
};
