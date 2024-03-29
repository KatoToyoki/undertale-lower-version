#include "stdafx.h"
#include "BarrageMode.h"

void BarrageMode::SetQuantity(int q)
{
    _quantity=q;
}

bool BarrageMode::GetIsSet()
{
    return isSet;
}

void BarrageMode::SetIsRightTime(bool rt)
{
    isRightTime=rt;
}

void BarrageMode::PushEmpty()
{
    Barrage temp=Barrage(0,white);
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage.push_back(temp);
    }
}

std::string BarrageMode::HandleJsonString(std::string str){
    std::string temp=str;
    temp=temp.erase(0,0);
    temp=temp.erase(temp.size(),1);

    return temp;
}

void BarrageMode::FormatImgPath(std::vector<std::string> &imgArr){
    int a=imgArr.size();
    for(int i=0;i<a;i++){
        imgArr[i]="resources/"+imgArr[i]+".bmp";
    }
}

void BarrageMode::HandleMultImg(nlohmann::basic_json<> imgArr, std::vector<std::string>& img){
    for (auto& imgPathElement : imgArr) {
        int i=0;
        while (true){
            if(imgPathElement.contains("path"+std::to_string(i))){
                img.push_back(HandleJsonString(imgPathElement["path"+std::to_string(i)]));
                i++;
            }
            else{
                break;
            }
        }
    }
    FormatImgPath(img);
}

void BarrageMode::HandleJsonData(std::string round, std::string fileName){
    json data;
    std::ifstream file("Source/Game/json/"+fileName+".json");
    file >> data;
    
    for (const auto& round : data[round]) {
        DataSet temp;

        for (const auto& element : round.items()) {
            if(element.key()=="damage"){
                temp.damage=element.value();
            }
            else if(element.key()=="speed"){
                temp.speed=element.value();
            }
            else if(element.key()=="initX"){
                temp.initX=element.value();
            }
            else if(element.key()=="initY"){
                temp.initY=element.value();
            }
            else if(element.key()=="barrage_mode"){
                if(HandleJsonString(element.value())=="white"){
                    temp.mode=white;
                }
                else{
                    temp.mode=blue;
                }
            }
            else if(element.key()=="imgPath"){
                auto& imgPathArray = round["imgPath"];
                HandleMultImg(imgPathArray,temp.imgPath);
            }
        }
        allData.push_back(temp);
    }
}

Barrage BarrageMode::Setup(DataSet data)
{
    Barrage current;
    current.LoadMultImg(data.imgPath);
    current.SetDamage(data.damage);
    current.SetMode(data.mode);
    current.set_positon(data.initX,data.initY);

    return current;
}

void BarrageMode::RandomBarrage()
{
    srand((unsigned) time(NULL)); 
    for(int i=0;i<_quantity;i++)
    {
        int temp = rand();
        if(temp%3==0)
        {
            enemyBarrage[i]=Setup(allData[_quantity-_quantity]);
            enemyBarrage[i].set_positon(allData[i].initX,allData[_quantity-_quantity].initY);
        }
        else if(temp%3==1)
        {
            enemyBarrage[i]=Setup(allData[_quantity-1]);
            enemyBarrage[i].set_positon(allData[i].initX,allData[_quantity-1].initY);
        }
        else if(_quantity>=3)
        {
            enemyBarrage[i]=Setup(allData[_quantity-2]);
            enemyBarrage[i].set_positon(allData[i].initX,allData[_quantity-2].initY);
        }
    }
}

void BarrageMode::NormalBarrage()
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i]=Setup(allData[i]);
    }
}

void BarrageMode::ShowBarrage()
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].show_img();
    }
}

void BarrageMode::UnshowBarrage()
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].UnshowIMG();
    }
}

void BarrageMode::GoLeft(Barrage& barrage, Move* heart, int speed,Character* character,isDisappear command)
{
    barrage.set_show_enable(true);
    barrage.damege_hit(heart,character,command);
    barrage.left_move(speed);
}

void BarrageMode::GoRight(Barrage& barrage, Move* heart, int speed,Character* character,isDisappear command)
{
    barrage.set_show_enable(true);
    barrage.damege_hit(heart,character,command);
    barrage.right_move(speed);
}

void BarrageMode::GoUp(Barrage& barrage, Move* heart, int speed, Character* character,isDisappear command)
{
    barrage.set_show_enable(true);
    barrage.damege_hit(heart,character,command);
    barrage.up_move(speed);
}

bool BarrageMode::DetectCertainPoint(Barrage& barrage,int point ,int position)
{
    switch (position)
    {
    case front:
        return barrage.GetOnePosition(IMGleft)<point;
    case back:
        return barrage.GetOnePosition(IMGleft)>point;
    case frontEqual:
        return barrage.GetOnePosition(IMGleft)<=point;
    case backEqual:
        return barrage.GetOnePosition(IMGleft)>=point;
    case up:
        return barrage.GetOnePosition(IMGtop)<point;
    }
    
    return false;
}

bool  BarrageMode::DetectLeft(Barrage& barrage,int direction)
{
    switch (direction)
    {
    case leftAtLeft:
        return barrage.GetOnePosition(IMGleft)<650;
    case leftAtRight:
        return barrage.GetOnePosition(IMGleft)>1250;
    case vanish:
        return barrage.GetOnePosition(IMGtop)==0;
    }

    return false;
}

void BarrageMode::SetIsAttack(bool a)
{
    isAttackEnd=a;
}

void BarrageMode::HPcondition(Move* heart, Character* character,int command)
{
    GetMinusHP_M(heart,character,command);
}

bool BarrageMode::GetIsAttackEnd()
{
    return isAttackEnd;
}

void BarrageMode::GetMinusHP_M(Move *heart,Character *character, int command)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,character,command);
    }
}

bool BarrageMode::LeaveAtRight()
{
    return enemyBarrage[_quantity-1].GetOnePosition(IMGleft)>1270;
}

bool BarrageMode::LeaveAtLeft()
{
    return enemyBarrage[_quantity-1].GetOnePosition(IMGleft)<665;
}

bool BarrageMode::LastOneDisappear()
{
    return enemyBarrage[_quantity-1].GetOnePosition(IMGtop)==0;
}

void BarrageMode::RevealBarrage()
{
    isRightTime ? ShowBarrage() : UnshowBarrage();
}