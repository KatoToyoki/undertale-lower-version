#include "stdafx.h"
#include "items.h"

#include "ButtonFrame.h"
#include "../Library/audio.h"

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

std::vector<std::vector<std::string>> Items::get_and_set_ramdon_text(std::string str)
{
    std::vector<std::vector<std::string>> item_text;
    item_text = text_content.get_reaction(str);
    return item_text;
}

void Items::set_item_cost_round_init(int current_selection, int button_selection)
{
    if (!_enable)
    {
        _current_selection = current_selection;
        _times = 0;
        set_items(_current_selection);
        _button_selection = button_selection;
        random_text = get_and_set_ramdon_text("NiceCream");// random need read in init
    }
}

void Items::set_item_updata()
{
    Item *item = get_item_by_index(_current_selection);
    std::vector<std::vector<std::string>> item_text = {{}};
    
    if (item->name == "NiceCream")
    {
        item_text = random_text;
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
    
    item_after = set_vector_vector_to_game_text(item_text,_times);
	cost_round = item_text.size();
}

void Items::set_control_updata(bool enable)
{
    _enable = enable;
}

void Items::item_after_stage_control_updata(UINT nChar)
{
    stage_stop = false;
	if ((nChar == VK_RETURN || nChar == 0x5A) && _enable)
	{
		Item* item = get_item_by_index(_current_selection);
		if (_times < cost_round-1)
		{
			_times+=1;
            stage_stop = true;
		    if (_times == cost_round-2)
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
    for (Item &item : items)
    {
        if (item.useable_times == 0)
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
}

bool Items::is_items_empty()
{
    return (items[0].heal_num == 0 && *_stage == 1 && _button_selection == 2);
}

GameText Items::set_vector_vector_to_game_text(std::vector<std::vector<std::string>> text, int times)
{
    vector<Text> text_vector;
	 for(unsigned int j=0;j<text[times].size();j++)
	 {
		   text_vector.push_back(TEXXT(text[times][j]));
	 }
	return GameText(text_vector,talk_mode);
}
