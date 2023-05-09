#include "stdafx.h"
#include "GreaterDogRound.h"
#include <iostream>
void GreaterDogRound::SetAllData()
{
    allData.clear();
    allData.shrink_to_fit();
    enemyBarrage.clear();
    enemyBarrage.shrink_to_fit();
    
    if(currentRound==-99)
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
}

void GreaterDogRound::SelectRound(Move* heart, Character* character, int selection)
{
    static bool tempIsSet = isSet;
    if(selection!=-99)
    {
        currentRound=selection;
    }
     
    if(!isSet)
    {
        SetAllData();
    }
    
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

    if (tempIsSet != isSet)
    {
        std::cout << tempIsSet;
    }
    tempIsSet = isSet;
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
        if(enemyBarrage[_quantity-1].GetOnePosition(IMGleft)<=620)
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
        }
        break;
    case 3:
        if(BarkLeft(enemyBarrage[dogFindQ+1]))
        {
            dogFindQ=5;
        }
        break;
    }
    
    if(dogFindCounter==0 && dogFindQ%2!=0)
    {
        replacement=GetBase(heart->GetCurrentX()-enemyBarrage[dogFindQ+1].GetOnePosition(IMGleft)-20,
          heart->GetCurrentY()-enemyBarrage[dogFindQ+1].GetOnePosition(IMGtop)-20);
        dogFindCounter+=1;
    }
    else if(dogFindCounter<50)
    {
        dogFindCounter+=1;
    }
    else
    {
        dogFindCounter=0;
    }
    
    GoUp(enemyBarrage[dogFindQ],heart,(abs(replacement.displacementY))*2,character);
    GoRight(enemyBarrage[dogFindQ],heart,replacement.displacementX*3,character);
    GoUp(enemyBarrage[dogFindQ+1],heart,(abs(replacement.displacementY))*2,character);
    GoRight(enemyBarrage[dogFindQ+1],heart,replacement.displacementX*3,character);
}

void GreaterDogRound::Spear(Move* heart, Character* character)
{
    bool secondWave=false;
    if(enemyBarrage[0].GetOnePosition(IMGtop)>665)
    {
        GoUp(enemyBarrage[0],heart,allData[0].speed,character);
    }
    else
    {
        secondWave=true;
    }

    if(secondWave)
    {
        GoLeft(enemyBarrage[0],heart,allData[0].speed,character);
        
        if(enemyBarrage[0].GetOnePosition(IMGleft)-(allData[0].initX-changeColor)<10)
        {
            enemyBarrage[0].barrage_img.SetFrameIndexOfBitmap(1);
            if(mode==0)
            {
                enemyBarrage[0].switch_mode();
                mode=1;
            }
        }
        if(enemyBarrage[0].GetOnePosition(IMGleft)-(allData[0].initX-2*changeColor)<10)
        {
            if (mode==1)
            {
                mode=2;
            }
            enemyBarrage[0].barrage_img.SetFrameIndexOfBitmap(0);
            if(mode==2)
            {
                enemyBarrage[0].switch_mode();
                mode=3;
            }
        }
    }
}


