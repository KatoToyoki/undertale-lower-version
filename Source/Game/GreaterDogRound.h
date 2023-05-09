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
    
    void HPcondition(Move *heart,Character *character,int command=0) override ; 

    
    void DogFindsYou(Move *heart,Character *character);
    void Spear(Move *heart,Character *character);
};
