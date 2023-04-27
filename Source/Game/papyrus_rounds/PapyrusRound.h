#pragma once
#include "../BarrageMode.h"

enum EndPoint
{
    leftAtLeft,leftAtRight,vanish
};

enum Position
{
    front,back,frontEqual,backEqual
};

enum Appearance
{
    normal,updown,compound
};

enum DirectionOfNext
{
    goUp,goDown
};

class PapyrusRound: public BarrageMode
{
private:
    int _q=0;
    int currentRound=-1;
    int UDBdirection=0;
    bool isSet=false;
public:
    PapyrusRound()=default;
    ~PapyrusRound()=default;
    
    void SetAllData();
    
    void SelectRound(Move *heart,int selection=-99);

    void GoRight(Barrage& barrage, Move *heart, int speed);
    void GoLeft(Barrage& barrage, Move *heart, int speed);

    void CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart);
    void UpDownBarrage(Barrage& barrage, int upLimit, int downLimit, int speed);
    
    void DetectRoundEnd(int direction);
    bool DetectLeft(Barrage& barrage,int direction);
    bool DetectCertainPoint(Barrage& barrage,int point,int position);
    
    void roundX(Move *heart);
    void round0(Move *heart);
    void round1(Move *heart);
    void round2(Move *heart);
    void round3(Move *heart);
    void round4(Move *heart);
    void round5(Move *heart);
    void round6(Move *heart);
    void round7(Move *heart);
    void round8(Move *heart);
    void round9(Move *heart);
    void round10(Move *heart);
    void round11(Move *heart);

    void Test()
    {
        std::string a;
        if(isAttackEnd==true)
        {
            a="True";
        }
        else{
            a="False";
        }
        
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 100, 200, a);
        game_framework::CDDraw::ReleaseBackCDC();
    }
};
