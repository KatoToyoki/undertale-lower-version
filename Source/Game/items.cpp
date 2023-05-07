#include "stdafx.h"
#include "items.h"

#include "ButtonFrame.h"

Items::Items()
{
    text_content.load("Item");
    set_items_init();
}

GameText Items::get_item_list()
{
    vector<Text> text_vector = {};
    for(Item item : items)
    {
        Text text(60,item.name,RGB(255,255,255),600,0,0);
        text_vector.push_back(text);
    }
    GameText data(text_vector, act_item_mode);
    return data;
}

int Items::get_selection_heal_num()
{
    return items[_current_selection].heal_num;
}

void Items::set_items_init()
{
    Item nice_cream = {
        "NiceCream",
        1,
        15,
    };
    Item bisicle ={
        "Bisicle",
        2,
        11,
    };
    Item instant_noodles ={ 
        "InstaNood",
        1,
        4,
    };
    
    Item temmie_flakes ={
        "tem flake",
        1,
        2,
    };
    
	vector<Item> item_vector = {
	    nice_cream,
	    bisicle,
	    instant_noodles,
	    temmie_flakes
	};
    items = item_vector;
}

void Items::set_items(int current_selection)
{
    for (Item &item_in : items)
    {
        if (item_in.name == "Bisicle" && item_in.useable_times == 1)
        {
           item_in.name = "Unisicle";
        }
    }
}

int Items::generate_random_num(int min, int max)
{
    return ( rand() % ((max-1) - min + 1) + min );
}

std::string Items::get_and_set_ramdon_text(std::string str)
{
    vector<std::string> random_text_vector;
    if (str == "NiceCream")
    {
        item_text = text_content.get_reaction("NiceCream_random");
         for(unsigned int j=0;j<item_text[0].size();j++)
         {
             random_text_vector.push_back(item_text[0][j]);
         }
    }
    
    int random_num = generate_random_num(0,random_text_vector.size());
    return random_text_vector[random_num];
}

void Items::set_item_cost_round_init(int current_selection, int button_selection)
{
    if (!_enable)
    {
        check_and_del_item();
        _current_selection = current_selection;
        times = 0;
        set_items(_current_selection);
        _button_selection = button_selection;
        nice_cream_random_text = get_and_set_ramdon_text("NiceCream");
    }
}

void Items::set_item_updata()
{
    Item *item = get_item_by_index(_current_selection);
    text_vector.clear();
    text_vector.shrink_to_fit();
    
    if (item->name == "NiceCream")
    {
        item_text = text_content.get_reaction("NiceCream");
        item_text[0].insert(item_text[0].begin(),nice_cream_random_text);
    }
    else if (item->name == "Bisicle")
    {
        item_text = text_content.get_reaction("Bisicle");
    }
    else if (item->name == "Unisicle")
    {
        item_text = text_content.get_reaction("Unisicle");
    }
    else if (item->name == "InstaNood"){
        item_text = text_content.get_reaction("InstaNood");
    }
    else if (item->name == "tem flake")
    {
        item_text = text_content.get_reaction("tem_flake");
    }
    
	 for(unsigned int j=0;j<item_text[times].size();j++)
	 {
		   text_vector.push_back(TEXXT(item_text[times][j]));
	 }
	item_after = GameText(text_vector,talk_mode);
	cost_round = item_text.size();
}

void Items::set_control_updata(bool enable)
{
    _enable = enable;
}

void Items::item_after_stage_control_updata(UINT nChar, int* stage)
{
	_stage = stage;
	if ((nChar == VK_RETURN || nChar == 0x5A) && _enable)
	{
		Item* item = get_item_by_index(_current_selection);
		if (times < cost_round-1)
		{
			times+=1;
			*stage-=1;
		    if (times == cost_round-2)
		    {
		       item->useable_times-=1; 
		    }
		}
        if (cost_round == 1)
        {
           item->useable_times-=1; 
        }
	}
}

GameText Items::get_item_after_game_text()
{
    return item_after;
}

Item* Items::get_item_by_index(int current_selection)
{
    Item *item = &items[current_selection];
    return item;
}

void Items::check_and_del_item()
{
    Item *item = &items[_current_selection];
    if (item->useable_times == 0)
    {
        items.erase(items.begin() + _current_selection);
        if (items.empty())
        {
            Item item = {
               "no_item",
               1,
               0,
            };
            vector<Item> item_vector = {
                item
            };
            items = item_vector;
        }
    }
}

bool Items::is_items_empty()
{
    return (items[0].heal_num == 0 && *_stage == 1 && _button_selection == 2);
}