#pragma once
#include "./BarrageMode.h"
#include <math.h>
#include <cmath>
#include <cstdlib> 

struct coorderinate{
    int displacementX=0, displacementY=0;
};

class GreaterDogRound: public BarrageMode
{
private:
    bool isSet=false;
    int currentRound=-99;
    coorderinate replacement;
    int changeColor=0;
    int dogFindQ=1;
    int dogFindCounter=0;
    int mode=0;
public:
    GreaterDogRound()=default;
    ~GreaterDogRound()=default;

    void SetAllData();

    int GetCurrentRound()
    {
        return currentRound;   
    }

    void SelectRound(Move *heart, Character *character,int selection=-99);
    bool xBigger(double x, double y);
    coorderinate GetBase(int deltaX,int deltaY);
    void DogAnimation(Move *heart,Character *character);
    
    bool BarkLeft(Barrage& barrage);
    void DetectRoundEnd();
    
    void HPcondition(Move *heart,Character *character,int command=0) override ; 
    
    void DogFindsYou(Move *heart,Character *character);
    void Spear(Move *heart,Character *character);

    // for printing in real time
    void Test44()
    {
        
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        //game_framework::CTextDraw::Print(pDC, 0, 350, Set);
        game_framework::CTextDraw::Print(pDC, 0, 50, to_string(aaa));

        game_framework::CDDraw::ReleaseBackCDC();
        
        
    }

    void Test43()
    {
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 0, 150, "round "+to_string(currentRound));
        game_framework::CDDraw::ReleaseBackCDC();
        
    }


    int aaa=0;
    void Test42()
    {
        std::string Set;
        if(isSet)
        {
            Set="set:Set";
        }
        else
        {
            Set="set:Not Set";
        }
        
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 0, 250, Set);
        game_framework::CDDraw::ReleaseBackCDC();
        
    }

    void Test41()
    {
       std::string Set;
               if(isAttackEnd)
               {
                   Set="end:attack end";
               }
               else
               {
                   Set="end:attack not end";
               }
        
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 0, 350, Set);
        game_framework::CDDraw::ReleaseBackCDC();
    }
};
