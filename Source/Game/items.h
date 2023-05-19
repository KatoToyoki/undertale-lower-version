#pragma once
#include "game_text.h"
#include <stdlib.h>

#include "TextContent.h"

#define TEXXT(content) Text(60, content, RGB(255,255,255), 600, 420, 69)

struct Item
{
    std::string name;
    int useable_times;
    int heal_num;
};

class Items
{
public:
    Items();
    
    GameText get_item_list();
    int get_selection_heal_num();
    GameText get_item_after_game_text();
    void set_item_updata();
    
    void set_item_cost_round_init(int current_selection, int button_selection);
    void item_after_stage_control_updata(UINT nChar);
    void set_control_updata(bool enable);
    void check_and_del_item();
    bool is_items_empty();

    bool stage_stop = false;
    vector<Item> items;
private:
    int _times = 0;
    int *_stage;
    int _current_selection = 0;
    bool _enable = false;
    int _button_selection;

    Item* get_item_by_index(int current_selection);
    std::vector<std::vector<std::string>> get_and_set_ramdon_text(std::string str);
    void set_items_init();
    void set_items(int current_selection);

    
    GameText set_vector_vector_to_game_text(std::vector<std::vector<std::string>> text,int times);

    TextContent text_content;
	GameText item_after;
    int cost_round;

    std::string nice_cream_random_text;
    
    std::vector<std::vector<std::string>> random_text;
};
