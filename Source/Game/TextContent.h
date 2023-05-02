#pragma once

#include "stdafx.h"
#include "BarrageMode.h"
#include <vector>
#include <cstdlib>
#include <string>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Library/json.hpp"
using json = nlohmann::json;

class TextContent
{
private:
    // the container of the all reaction of one situation
    // it's three layers
                // reaction   //frame    //content
    std::vector<std::vector<std::vector<std::string>>> act;

    // inside one reaction may have multiple frames
    // but using this can only use one situation
    // it's two layers
    std::vector<std::vector<std::string>> actOneReaction;
    
public:
    TextContent()=default;
    ~TextContent()=default;

    // file name is the source of the json, situation is what you want to call
    void HandleActContent(std::string fileName,std::string situation);

    // when the reaction only have one situation, use this can that situation
    // -> only 2 layers rather than 3 layers
    void ActNormalSituation();

    // when the reaction have more than one situation, use this can that one of the situation randomly
    // -> only 2 layers rather than 3 layers
    void ActRandomSitionation();

    //testing
    void PrintItOut();
};
