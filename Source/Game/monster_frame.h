#pragma once

#include "../Library/gameutil.h"

struct DataText
{
    
};

class MonsterFrame
{
public:
    void load_img();
    void print_text(DataText text);
    void show_monster_frame_img();
    
    
private:
    game_framework::CMovingBitmap monster_frame_img;
    std::vector<DataText> texts;
    
};
