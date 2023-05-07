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
    // inside one reaction may have multiple frames
    // but using this can only use one situation
    // it's two layers
    std::vector<std::vector<std::string>> actOneReaction;
    
public:
    TextContent()=default;
    ~TextContent()=default;

    // file name is the source of the json, situation is what you want to call
    void HandleActContent(std::string fileName,std::string situation);

    std::vector<std::vector<std::string>> get_reaction(std::string situation);
    void get_data(std::string fileName);
    void load(string file_name);
    std::unordered_map<string, vector< vector< string>>> data_context;
    
    //testing
    void PrintItOut();
};
