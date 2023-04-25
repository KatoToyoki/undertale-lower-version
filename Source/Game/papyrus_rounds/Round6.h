#pragma once
#include "../BarrageMode.h"

class Round6 : public BarrageMode
{
private:
public:
    Round6(int quantity):BarrageMode(quantity){}

    ~Round6()=default;
    
    virtual void SetAllData() override;
    virtual void MovingBarrage(Move *heart) override;

    void SecondWave(Move *heart);
    void ThirdWave(Move *heart);

    /*
     * 由左至右
       135上69下 2組 <15+30> <210+30> 60上 135下 2組<15+30>
       <260+30> 204B 到 1110時 0123 4
       [5] 135由右至左 到750時
       135上69下 2組 左右夾擊 結束
     */
     
    void Test2()
    {
        std::string lastFive;
        lastFive=to_string(allData[9].speed);
        lastFive=lastFive+" "+to_string(allData[10].speed);
        lastFive=lastFive+" "+to_string(allData[11].speed);
        lastFive=lastFive+" "+to_string(allData[12].speed);
        lastFive=lastFive+" "+to_string(allData[13].speed);
        
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 100, 200, "speed "+lastFive);
        game_framework::CDDraw::ReleaseBackCDC();
    }
};
