#include "stdafx.h"
#include "TextContent.h"

void TextContent::HandleActContent(std::string fileName, std::string situation, std::vector<std::vector<std::vector<std::string>>>& act)
{
    json data;
    std::ifstream file("Source/Game/json/"+fileName+".json");
    file >> data;

    std::string temp;

    for (auto &item : data[situation]) {
        for (auto &reaction : item) {
            std::vector<std::vector<std::string>> container;
            for (auto &frame : reaction) {
                std::vector<std::string> _frame;
                for (auto &content : frame) {
                    temp = BarrageMode::HandleJsonString(content);
                    _frame.push_back(temp);
                }
                container.push_back(_frame);
            }
            act.push_back(container);
        }
    }
}

std::vector<std::vector<std::string>> TextContent::ActNormalSituation()
{
    return act[0];
}

std::vector<std::vector<std::string>> TextContent::ActRandomSitionation()
{
    int random=rand()%act.size();
    return act[random];
}

void TextContent::PrintItOut()
{
    for(int i=0;i<actOneReaction.size();)
    {
        std::string b;
        for(int j=0;j<actOneReaction[i].size();j++)
        {
            b+=actOneReaction[i][j]+"\n";
        }

        CDC *pDC = game_framework::CDDraw::GetBackCDC();
        game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(252, 252, 45), 800);
        game_framework::CTextDraw::Print(pDC, 0, 200, b);
        game_framework::CDDraw::ReleaseBackCDC();

        if(testTime==0)
        {
            i++;
        }
    }
}


