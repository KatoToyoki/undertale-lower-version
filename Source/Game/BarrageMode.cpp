#include "stdafx.h"
#include "BarrageMode.h"

void BarrageMode::Init()
{
    SetAllData();
    PushEmpty();
    recordXYDamageSpeed();
}

void BarrageMode::PushEmpty()
{
    Barrage temp=Barrage(0,white);
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage.push_back(temp);
        xPosition.push_back(0);
        yPosition.push_back(0);
        allDamage.push_back(0);
        allSpeed.push_back(0);
    }
}

Barrage BarrageMode::Setup(SetData data)
{
    Barrage current;
    current.LoadMultImg(data.imgPath);
    //current.load_img(data.imgPath);
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
            enemyBarrage[i].set_positon(xPosition[i],allData[_quantity-_quantity].initY);
        }
        else if(temp%3==1)
        {
            enemyBarrage[i]=Setup(allData[_quantity-1]);
            enemyBarrage[i].set_positon(xPosition[i],allData[_quantity-1].initY);
        }
        else if(_quantity>=3)
        {
            enemyBarrage[i]=Setup(allData[_quantity-2]);
            enemyBarrage[i].set_positon(xPosition[i],allData[_quantity-2].initY);
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

bool BarrageMode::GetIsAttackEnd()
{
    
    return isAttackEnd;
}

int BarrageMode::GetMinusHP_M(Move *heart, int command)
{
    for(int i=0;i<_quantity;i++)
    {
        damageToCharacter=0;
        enemyBarrage[i].set_show_enable(true);
        damageToCharacter = enemyBarrage[i].damege_hit(heart,command);
        
        if(damageToCharacter!=0)
        {
            return damageToCharacter;
        }
    }

    return 0;
}

std::string BarrageMode::HandleJsonString(std::string str){
    std::string temp=str;
    temp=temp.erase(0,0);
    temp=temp.erase(temp.size(),1);

    return temp;
}

void BarrageMode::FormatImgPath(std::vector<std::string> &imgArr){
    std::string temp;
    int a=imgArr.size();
    for(int i=0;i<a;i++){
        imgArr[i]="resources/"+imgArr[i]+".bmp";
    }
}

void BarrageMode::HandleMultImg(nlohmann::basic_json<> imgArr, std::vector<std::string>& img){
    for (auto& imgPathElement : imgArr) {
        int i=0;
        std::string temp;
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

void BarrageMode::HandleJsonData(std::string round,std::vector<SetData>& all){
    json data;
    std::ifstream file("AllRounds.json");
    file >> data;
    
    for (const auto& round : data[round]) {
        SetData temp;

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
        all.push_back(temp);
    }
}