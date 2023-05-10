#pragma once
#include "./BarrageMode.h"

enum Appearance
{
    normal,compoundUp,compoundDown
};

enum DirectionOfNext
{
    goUp,goDown
};

class PapyrusRound: public BarrageMode
{
private:
    int currentRound=-1;
    int UDBdirection=0;
    int dogAnimation=1;
public:
    
    PapyrusRound()=default;
    ~PapyrusRound()=default;
    
    void SetAllData(int selection=-99);
    
    void SelectRound(Move *heart, Character *character,int selection=-99);

    void PincerAttack(int start,int end, Move* heart, int wave, int appearance,Character *character);

    void CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart);
    void UpDownBarrage(Barrage& barrage, int upLimit, int downLimit, int speed);
    
    void DetectRoundEnd(int direction);
    
    int GetCurrentRound();
    void ToGetEnterCount(UINT nChar);
    void DogAnimation(Move *heart,Character *character);

    void HPcondition(Move *heart,Character *character,int command=0) override ; 

    void roundX(Move *heart,Character *character);
    void round0(Move *heart,Character *character);
    void round1(Move *heart,Character *character);
    void round2(Move *heart,Character *character);
    void round3(Move *heart,Character *character);
    void round4(Move *heart,Character *character);
    void round5(Move *heart,Character *character);
    void round6(Move *heart,Character *character);
    void round7(Move *heart,Character *character);
    void round8(Move *heart,Character *character);
    void round9(Move *heart,Character *character);
    void round10(Move *heart,Character *character);
    void round11(Move *heart,Character *character);
    void round12(Move *heart,Character *character);
    void round13(Move *heart,Character *character);
    void round14(Move *heart,Character *character);
    void round15(Move *heart,Character *character);
    void round16(Move *heart,Character *character);
    void round17(Move *heart,Character *character);
    void round18(Move *heart,Character *character);
    void round19(Move *heart,Character *character);
    void round20(Move *heart,Character *character);
    void round21(Move *heart,Character *character);

    void Test2()
    {
        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 0, 50, "current "+to_string(currentRound));
        game_framework::CDDraw::ReleaseBackCDC();
    }
};
