#pragma once

#include "text.h"
#include <vector>

enum mode
{
    talk_mode,
    act_mode
};
class GameText
{
public:
    GameText(std::vector<Text> data = {},mode mode_command = act_mode);

    void set_enable(bool enable);
    void set_text_index(int head, int text_len);
    void print_vector();
    void print_text();
    
private:
    std::vector<Text> _data;
    bool _enable = false;
    int _text_len = 3;
    int print_index = 0;
  
};
