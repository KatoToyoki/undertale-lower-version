#pragma once
#include "game_text.h"
#include <stdlib.h>

struct Item
{
    std::string name;
    int useable_times;
    int heal_num;
    int index;
    GameText item_after_game_text;
    int cost_round;
    vector<int> item_after_len_list;
};

class Items
{
public:
    Items();
    
    GameText get_item_list();
    int get_now_item_after_index();
    int get_now_item_after_text_len();
    int get_selection_heal_num();
    GameText get_item_after_game_text();
    
    void set_item_cost_round_init(int current_selection);
    void item_after_stage_control_updata(UINT nChar,int *stage);
    void set_control_updata(bool enable);
    bool is_items_empty();
    
    vector<Item> items;
private:
    int times = 0;
    int *_stage;
    int _current_selection = 0;
    void set_items(int current_selection);
    bool _enable = false;

    Item* get_item_by_index(int current_selection);
    int random_num_to_select_text(int min, int max);
    Text get_and_set_ramdon_text(std::string str);
    void set_items_init();

    void check_and_del_item();
    

    GameText nice_cream_random_text_list;
};
