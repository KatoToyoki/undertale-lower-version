#include "stdafx.h"
#include "GreaterDogRound.h"

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
        changeColor=rand()%(220-90+1)+90; 
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
    return x>y ? true : false;
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
    if(enemyBarrage[dogFindQ].GetOnePosition(IMGtop) == 920)
    {
        SetReplacement(replacementA,heart,character,dogFindQ);
    }
    else if(abs(enemyBarrage[dogFindQ].GetOnePosition(IMGtop)-enemyBarrage[dogFindQ+1].GetOnePosition(IMGtop)) - 70 > 0 && dogFindCounter==0)
    {
        SetReplacement(replacementB,heart,character,dogFindQ+1);
        dogFindCounter++;
    }

    GoUp(enemyBarrage[dogFindQ],heart,abs(replacementA.displacementY),character);
    GoRight(enemyBarrage[dogFindQ],heart,replacementA.displacementX,character);
    GoUp(enemyBarrage[dogFindQ+1],heart,replacementB.displacementY==-1?0:abs(replacementB.displacementY),character);
    GoRight(enemyBarrage[dogFindQ+1],heart,replacementB.displacementX==-1?0:replacementB.displacementX,character);

    if(BarkLeft(enemyBarrage[dogFindQ+1]) && !BarkLeft(enemyBarrage[dogFindQ]))
    {
        replacementB.displacementX=-1;
        replacementB.displacementY=-1;
    }
    else if(BarkLeft(enemyBarrage[dogFindQ+1]) && BarkLeft(enemyBarrage[dogFindQ]))
    {
        dogFindQ+=2;
        dogFindCounter = 0;
        replacementB.displacementX=-1;
        replacementB.displacementY=-1;
    }

}

void GreaterDogRound::SetReplacement(coorderinate &replacement,Move *heart,Character *character,int index)
{
    replacement = GetBase(heart->GetCurrentX()-enemyBarrage[index].GetOnePosition(IMGleft)-20,
                    heart->GetCurrentY()-enemyBarrage[index].GetOnePosition(IMGtop)-20);
    replacement.displacementX = abs(replacement.displacementX*4)>12 ? 12 : replacement.displacementX*4;
    
    replacement.displacementY = abs(replacement.displacementY*4)>12 ? 12 : replacement.displacementY*4;
    replacement.displacementY = replacement.displacementY < 8 ? 8 : replacement.displacementY;
    replacement.displacementY= replacement.displacementY > replacementA.displacementY ? replacementA.displacementY-1 : replacement.displacementY;
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
        if(enemyBarrage[0].GetOnePosition(IMGleft)-(allData[0].initX-3*changeColor)<20)
        {
            enemyBarrage[0].barrage_img.SetFrameIndexOfBitmap(0);
            enemyBarrage[0].switch_mode(white);
        }
    }
}