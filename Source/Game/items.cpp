#include "stdafx.h"
#include "items.h"

Items::Items()
{
    set_items();
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

void Items::set_items()
{
    Text nice_cream_ramdon = get_and_set_ramdon_text(nice_crame_type);
    vector<Text> text_vector= {
        nice_cream_ramdon,
        Text (60,"* You recovered 11 HP!",RGB(255,255,255),600,0,0),
    };
    GameText nice_cream_gmae_text(text_vector, talk_mode);
    Item nice_cream = {
       "NiceCream",
       1,
       15,
        0,
       nice_cream_gmae_text,
       1,
       {0,2}
    };
	vector<Item> item_vector = {
	    nice_cream
	};
    items = item_vector;
}

int Items::random_num_to_select_text(int min, int max)
{
    int _max = max;
    int _min = min;
    int random_num = rand() % (_max - _min + 1) + _min;
    return random_num;
}

Text Items::get_and_set_ramdon_text(item_type type)
{
    GameText game_text;
    if (type == nice_crame_type)
    {
        vector<Text> text_vector ={
            Text (60,"* You're super spiffy!",RGB(255,255,255),600,0,0),
            Text (60,"* Are those claws natural?",RGB(255,255,255),600,0,0),
            Text (60,"* Love yourself! I love you!",RGB(255,255,255),600,0,0),
            Text (60,"* You look nice today!",RGB(255,255,255),600,0,0),
            Text (60,"* (An illustration of a hug)",RGB(255,255,255),600,0,0),
            Text (60,"* Have a wonderful day!",RGB(255,255,255),600,0,0),
            Text (60,"* Is this as sweet as you?",RGB(255,255,255),600,0,0),
            Text (60,"* You're just great!",RGB(255,255,255),600,0,0)
        };
        game_text = GameText (text_vector,talk_mode);
    }
    
    int random_num = random_num_to_select_text(0,game_text.get_vector_len()-1);
    return game_text._data[random_num];
}

void Items::set_item_cost_round_init(int current_selection)
{
    set_items();
	_current_selection = current_selection;
    times = 0;
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
		Item* item = &items[_current_selection];
		if (times < item->cost_round-1)
		{
			times+=1;
			item->index+=item->item_after_len_list[times];
			*stage-=1;
		}
	}
}

int Items::get_now_item_after_index()
{
    return items[_current_selection].index;
}

int Items::get_now_item_after_text_len()
{
    return items[_current_selection].item_after_len_list[times+1];
}

GameText Items::get_item_after_game_text()
{
    return items[_current_selection].item_after_game_text;
}
