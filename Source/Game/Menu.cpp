#include "stdafx.h"
#include "Menu.h"

#include "../Library/gameutil.h"
#include "../Library/gamecore.h"

void Stage::SetCoordinate(int x, int y) {
    _coordinate.x = x;
    _coordinate.y = y;
}

int Stage::GetID()
{
    return _ID;
}

std::string Stage::GetName()
{
    return _stageName;
}

int Stage::GetX()
{
    return _coordinate.x;
}

int Stage::GetY()
{
    return _coordinate.y;
}

// =======================================================

void MenuStart::ChangeColor(Stage stage, int state) {
    if (state == toOff) {
        ChangeFontLog(stage._pDC, 21, "微軟正黑體",
                                 RGB(color.off.r, color.off.g, color.off.b));
    } 
    else if (state == toOn) {
        ChangeFontLog(stage._pDC, 21, "微軟正黑體",
                                 RGB(color.on.r, color.on.g, color.on.b));
    }
}

void MenuStart::SetUpStages() {
    for (int i = 0; i < 3; i++) {
        stages.push_back(Stage(i, "Stage" + std::to_string(i)));
    }
}

void MenuStart::ShowStages() {
    for (int i = 0; i < 3; i++) {
        ChangeColor(stages[i], toOn);
        stages[i].SetCoordinate(400+450*i,320);
        Print(stages[i]._pDC, stages[i].GetX(), stages[i].GetY(), stages[i].GetName());
    }
}

void MenuStart::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
    if (nChar == VK_LEFT && currentStage != 0) {
        ChangeColor(stages[currentStage], toOff);
        currentStage -= 1;
        ChangeColor(stages[currentStage], toOn);
    }
    else if (nChar == VK_RIGHT && currentStage != 3) {
        ChangeColor(stages[currentStage], toOff);
        currentStage += 1;
        ChangeColor(stages[currentStage], toOn);
    }
}

