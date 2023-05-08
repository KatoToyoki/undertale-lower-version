#include "stdafx.h"
#include "GreaterDogRound.h"
#include "PapyrusRound.h"

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
        changeColor=rand()%(330-60+1)+60; 
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
    if(currentRound!=0)
    {
        return;
    }
    enemyBarrage[0].barrage_img.ShowBitmap();
    enemyBarrage[0].barrage_img.SetAnimation(150,false);
    enemyBarrage[0].damege_hit(heart,character,appear);
}

bool GreaterDogRound::BarkLeft(Barrage& barrage)
{
    if(DetectCertainPoint(barrage,630,up)||
        DetectCertainPoint(barrage,545,front||
        DetectCertainPoint(barrage,1380,back)))
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
        if(DetectLeft(enemyBarrage[_quantity-1],leftAtLeft)||LastOneDisappear())
        {
            isSet=false;
            isAttackEnd=true;
        }
        break;
    }
}

void GreaterDogRound::DogFindsYou(Move* heart, Character* character)
{
    
    for(int i=1;i<_quantity;i+=0)
    {
        replacement=GetBase(heart->GetCurrentX()-enemyBarrage[i].GetOnePosition(IMGleft),
            heart->GetCurrentY()-enemyBarrage[i].GetOnePosition(IMGtop));
        GoUp(enemyBarrage[i],heart,replacement.displacementY,character);
        GoRight(enemyBarrage[i],heart,replacement.displacementX,character);
        GoUp(enemyBarrage[i+1],heart,replacement.displacementY,character);
        GoRight(enemyBarrage[i+1],heart,replacement.displacementX,character);
        if(BarkLeft(enemyBarrage[i+1]))
        {
            i+=2;
        }
    }

    DetectRoundEnd();
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
        if(enemyBarrage[0].GetOnePosition(IMGleft)==allData[0].initX-changeColor)
        {
            enemyBarrage[0].barrage_img.SetFrameIndexOfBitmap(1);
        }
        if(enemyBarrage[0].GetOnePosition(IMGleft)==allData[0].initX-2*changeColor)
        {
            enemyBarrage[0].barrage_img.SetFrameIndexOfBitmap(0);
        }
    }

    DetectRoundEnd();
}


