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
    std::vector<int> UDBdirections = std::vector<int>(10,0);
    int dogAnimation=1;
    bool isBlue=false;
public:
    
    PapyrusRound()=default;
    ~PapyrusRound()=default;

    bool GetIsBlue();
    
    void SetAllData(int selection=-99);

    void SetUDB();
    
    void SelectRound(Move *heart, Character *character,int selection=-99);

    void PincerAttack(int start,int end, Move* heart, int wave, int appearance,Character *character);

    void CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart);
    void UpDownBarrage(Barrage& barrage, int upLimit, int downLimit, int speed, int &UDB);
    void UpDownCompound(Barrage& cover,Barrage& barrage,Move *heart, int upLimit, int downLimit, int speed, int &UDB);
    
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

    
};
