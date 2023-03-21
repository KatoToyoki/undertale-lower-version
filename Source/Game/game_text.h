#pragma once

#include "text.h"
#include <vector>

#include "move.h"

enum mode
{
    talk_mode,
    target_mode,
    act_item_mode
};
class GameText
{
public:
    GameText(std::vector<Text> data = {},mode mode_command = act_item_mode);

    int get_positon_x(int index);
    int get_positon_y(int index);
    void set_enable(bool enable);
    void set_text_index(int head, int text_len);
    void print_vector();
    void print_text();

    int get_vector_len();
    std::vector<Text> _data;
    int _mode;
    
private:
    bool _enable = false;
    int _text_len = 3;
    int print_index = 0;
  
};
