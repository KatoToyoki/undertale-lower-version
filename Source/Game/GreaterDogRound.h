#pragma once
#include "./BarrageMode.h"
#include <math.h>
#include <cmath>
#include <cstdlib> 

struct coorderinate{
    int displacementX, displacementY;
};

class GreaterDogRound: public BarrageMode
{
private:
    bool isSet=false;
    int currentRound=-99;
    coorderinate replacement;
    int changeColor=0;
public:
    GreaterDogRound()=default;
    ~GreaterDogRound()=default;

    void SetAllData();

    void SelectRound(Move *heart, Character *character,int selection=-99);
    bool xBigger(double x, double y);
    coorderinate GetBase(int deltaX,int deltaY);
    void DogAnimation(Move *heart,Character *character);
    
    bool BarkLeft(Barrage& barrage);
    void DetectRoundEnd();
    
    void DogFindsYou(Move *heart,Character *character);
    void Spear(Move *heart,Character *character);

    void Test2()
    {
        if(isSet)
        {
            int position=0;
            position=enemyBarrage[0].barrage_img.GetTop();
            CDC *pDC = game_framework::CDDraw::GetBackCDC();
            game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 255), 800);
            game_framework::CTextDraw::Print(pDC, 0, 200, "p "+to_string(position));
            game_framework::CDDraw::ReleaseBackCDC();    
        }
        
    }
};
