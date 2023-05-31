#include "stdafx.h"
#include "GreaterDogRound.h"
#include <iostream>
void GreaterDogRound::SetAllData(int selection)
{
    allData.clear();
    allData.shrink_to_fit();
    enemyBarrage.clear();
    enemyBarrage.shrink_to_fit();
    
    if(selection!=-99)
    {
        currentRound=selection;
    }
    else
    {
        currentRound=rand()%2;
    }
    
    switch(currentRound)
    {
    case 0:
        HandleJsonData("DogFindYou","GreaterDogRounds");   
        break;
    case 1:
        changeColor=rand()%(170-100+1)+100; 
        HandleJsonData("Spear","GreaterDogRounds");   
        break;
    }
    
    SetQuantity(allData.size());
    PushEmpty();
    NormalBarrage();
    isSet=true;
    isAttackEnd=false;
    dogFindQ=1;
    dogFindCounter=0;
    isRightTime=false;
}

void GreaterDogRound::SelectRound(Move* heart, Character* character, int selection)
{
    switch (currentRound)
    {
    case 0:
        DogFindsYou(heart,character);
        break;
    case 1:
        Spear(heart,character);
        break;
    }
    DetectRoundEnd();
}

int GreaterDogRound::GetCurrentRound()
{
    return currentRound;
}

bool GreaterDogRound::xBigger(double x, double y)
{
    if(x>y){
        return true;
    }

    return false;
}

coorderinate GreaterDogRound::GetBase(int deltaX, int deltaY)
{
    coorderinate movement;
    int multiplier;
    double base=sqrt(pow(deltaX,2)+pow(deltaY,2));

    if(xBigger(fabs(deltaX/base), fabs(deltaY/base))){
        multiplier=(int)(std::ceil(1/abs(deltaY/base)));
    }
    else{
        multiplier=(int)(std::ceil(1/abs(deltaX/base)));
    }
    
    movement.displacementX=(int)((deltaX*1.0/base)*multiplier);
    movement.displacementY=(int)((deltaY*1.0/base)*multiplier);
    
    return movement;    
}

void GreaterDogRound::DogAnimation(Move* heart, Character* character)
{
    if(currentRound==0 &&!isAttackEnd)
    {
        enemyBarrage[0].barrage_img.ShowBitmap();
        enemyBarrage[0].barrage_img.SetAnimation(150,false);
        enemyBarrage[0].damege_hit(heart,character,appear);
    }
}

bool GreaterDogRound::BarkLeft(Barrage& barrage)
{
    if(DetectCertainPoint(barrage,520,up)||
        DetectCertainPoint(barrage,650,front||
        DetectCertainPoint(barrage,1270,back)))
    {
        return true;
    }

    return false;
}

void GreaterDogRound::DetectRoundEnd()
{
    switch (currentRound)
    {
    case 0:
        if(BarkLeft(enemyBarrage[_quantity-1])||LastOneDisappear())
        {
            isSet=false;
            isAttackEnd=true;
        }
        break;
    case 1:
        if(enemyBarrage[0].GetOnePosition(IMGleft)<=620)
        {
            isSet=false;
            isAttackEnd=true;
        }
        break;
    }
}

void GreaterDogRound::HPcondition(Move* heart, Character* character, int command)
{
    enemyBarrage[0].set_show_enable(true);
    enemyBarrage[0].damege_hit(heart,character,appear);

    if(currentRound==1)
    {
        return;
    }
    
    for(int i=1;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,character,disappear);
    }
}

void GreaterDogRound::DogFindsYou(Move* heart, Character* character)
{
    switch (dogFindQ)
    {
    case 1:
        if(BarkLeft(enemyBarrage[dogFindQ+1]))
        {
            dogFindQ=3;
            dogFindCounter=0;
        }
        break;
    case 3:
        if(BarkLeft(enemyBarrage[dogFindQ+1]))
        {
            dogFindQ=5;
            dogFindCounter=0;
        }
        break;
    }

    if(dogFindCounter==0 || (dogFindQ%2==0 && DetectCertainPoint(enemyBarrage[dogFindQ],720,up)))
    {
        replacement=GetBase(heart->GetCurrentX()-enemyBarrage[dogFindQ+1].GetOnePosition(IMGleft)-20,
                heart->GetCurrentY()-enemyBarrage[dogFindQ+1].GetOnePosition(IMGtop)-20);

        if(abs(replacement.displacementX*4)>12)
        {
            replacement.displacementX=12;
        }
        else
        {
            replacement.displacementX*=4;
        }
        if(abs(replacement.displacementY*4)>12)
        {
            replacement.displacementY=12;
        }
        else
        {
            replacement.displacementY*=4;
        }
        dogFindCounter++;
    }    

    GoUp(enemyBarrage[dogFindQ],heart,(abs(replacement.displacementY)),character);
    GoRight(enemyBarrage[dogFindQ],heart,replacement.displacementX,character);
    GoUp(enemyBarrage[dogFindQ+1],heart,(abs(replacement.displacementY)),character);
    GoRight(enemyBarrage[dogFindQ+1],heart,replacement.displacementX,character);
}

void GreaterDogRound::Spear(Move* heart, Character* character)
{
    bool secondWave=false;
    if(enemyBarrage[0].GetOnePosition(IMGtop)>665)
    {
        GoUp(enemyBarrage[0],heart,allData[0].speed,character,appear);
    }
    else
    {
        secondWave=true;
    }

    if(secondWave)
    {
        GoLeft(enemyBarrage[0],heart,allData[0].speed,character,appear);
        
        if(enemyBarrage[0].GetOnePosition(IMGleft)-(allData[0].initX-changeColor)<10)
        {
            enemyBarrage[0].barrage_img.SetFrameIndexOfBitmap(1);
            enemyBarrage[0].switch_mode(blue);
        }
        else if(enemyBarrage[0].GetOnePosition(IMGleft)-(allData[0].initX-4*changeColor)<10)
        {
            enemyBarrage[0].barrage_img.SetFrameIndexOfBitmap(0);
            enemyBarrage[0].switch_mode(white);
        }
    }
}