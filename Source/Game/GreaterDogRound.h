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
    int currentRound=-99;
    coorderinate replacementA={-1,-1},replacementB={-1,-1};
    int changeColor=0;
    int dogFindQ=1;
    int dogFindCounter=0;
    
public:
    GreaterDogRound()=default;
    ~GreaterDogRound()=default;
    
    void SetAllData(int selection=-99);

    int GetCurrentRound();
    void SetReplacement(coorderinate &replacement,Move *heart,Character *character,int index);
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