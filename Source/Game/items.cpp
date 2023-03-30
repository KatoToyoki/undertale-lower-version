#include "stdafx.h"
#include "items.h"

#include "ButtonFrame.h"

Items::Items()
{
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
    Text nice_cream_ramdon = get_and_set_ramdon_text("NiceCream");
    vector<Text> text_vector= {
        nice_cream_ramdon,
        Text (60,"* You recovered 15 HP!",RGB(255,255,255),600,0,0),
    };
    GameText nice_cream_game_text(text_vector, talk_mode);
    Item nice_cream = {
        "NiceCream",
        1,
        15,
         0,
        nice_cream_game_text,
        1,
        {0,2}
    };
    text_vector= {
        Text (60,"* You eat one half of",RGB(255,255,255),600,0,0),
        Text (60,"  the Bisicle.",RGB(255,255,255),600,0,0),
        Text (60,"* You recovered 11 HP!",RGB(255,255,255),600,0,0),
    };
    GameText bisicle_game_text(text_vector, talk_mode);
    Item bisicle ={
        "Bisicle",
        2,
        11,
         0,
        bisicle_game_text,
        1,
        {0,3}
    };

    text_vector= {
        Text (60,"* You remove the Instant",RGB(255,255,255),600,0,0),//0
        Text (60,"  Noodles from their",RGB(255,255,255),600,0,0),
        Text (60,"  packaging.",RGB(255,255,255),600,0,0),
        
        Text (60,"* You put some water in",RGB(255,255,255),600,0,0),//3
        Text (60,"  the pot and place it on",RGB(255,255,255),600,0,0),
        Text (60,"  the heat.",RGB(255,255,255),600,0,0),
        
        Text (60,"* You wait for the water",RGB(255,255,255),600,0,0),//6
        Text (60,"  to boil...",RGB(255,255,255),600,0,0),
        
        Text (60,"* ...",RGB(255,255,255),600,0,0),//8
        Text (60,"* ...",RGB(255,255,255),600,0,0),
        Text (60,"* ...",RGB(255,255,255),600,0,0),
        
        Text (60,"* It's boiling.",RGB(255,255,255),600,0,0),//11
        
        Text (60,"* You place the noodles",RGB(255,255,255),600,0,0),//12
        Text (60,"  into the pot.",RGB(255,255,255),600,0,0),
        
        Text (60,"* 4 minutes left until",RGB(255,255,255),600,0,0),//14
        Text (60,"  the noodles are finished.",RGB(255,255,255),600,0,0),
        Text (60,"* 3 minutes left until",RGB(255,255,255),600,0,0),//16
        Text (60,"  the noodles are finished.",RGB(255,255,255),600,0,0),
        Text (60,"* 2 minutes left until",RGB(255,255,255),600,0,0),//18
        Text (60,"  the noodles are finished.",RGB(255,255,255),600,0,0),
        Text (60,"* 1 minutes left until",RGB(255,255,255),600,0,0),//20
        Text (60,"  the noodles are finished.",RGB(255,255,255),600,0,0),
        
        Text (60,"* The noodles are finished.",RGB(255,255,255),600,0,0),//22
        
        Text (60,"* ... they don't taste very",RGB(255,255,255),600,0,0),//23
        Text (60,"  good.",RGB(255,255,255),600,0,0),
        
        Text (60,"* You add the flavor packet.",RGB(255,255,255),600,0,0),//25
        
        Text (60,"* That's better.",RGB(255,255,255),600,0,0),//26
        
        Text (60,"* Not great, but better.",RGB(255,255,255),600,0,0),//27
        
        Text (60,"* You ate the Instant Noodles.",RGB(255,255,255),600,0,0),//28
        Text (60,"* You recovered 4 HP!",RGB(255,255,255),600,0,0),
        Text (60,"* You recovered 4 HP!",RGB(255,255,255),600,0,0)
    };
    GameText instant_noodles_game_text(text_vector, talk_mode);
    Item instant_noodles ={
        "InstaNood",
        1,
        4,
        0,
        instant_noodles_game_text,
        16,
        {0,3,3,2,3,1,2, 2,2,2,2, 1,2,1, 1,1,2}
    };
    
    text_vector= {
        Text (60,"* You eat the tem flake",RGB(255,255,255),600,0,0),
        Text (60,"* You recovered 2 HP!",RGB(255,255,255),600,0,0),
    };
    GameText tem_game_text(text_vector, talk_mode);
    Item temmie_flakes ={
        "tem flake",
        1,
        2,
         0,
        tem_game_text,
        1,
        {0,2}
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
    Item *item = get_item_by_index(current_selection);
   if ( item->name == "NiceCream")
   {
        Text nice_cream_ramdon = get_and_set_ramdon_text("NiceCream");
        vector<Text> text_vector= {
            nice_cream_ramdon,
            Text (60,"* You recovered 11 HP!",RGB(255,255,255),600,0,0),
        };
        GameText nice_cream_gmae_text(text_vector, talk_mode);
       item->item_after_game_text = nice_cream_gmae_text;
   }
    if (item->name == "Bisicle" && item->useable_times == 1)
    {
       item->name = "Unisicle";
        vector<Text> text_vector= {
            Text (60,"* You eat the Unsicle",RGB(255,255,255),600,0,0),
            Text (60,"* You recovered 11 HP!",RGB(255,255,255),600,0,0),
        };
        GameText game_text(text_vector, talk_mode);
        item->item_after_game_text = game_text;
        item->item_after_len_list = {0,2};
        item->index = 0;
    }
}


int Items::random_num_to_select_text(int min, int max)
{
    int _max = max;
    int _min = min;
    int random_num = rand() % (_max - _min + 1) + _min;
    return random_num;
}

Text Items::get_and_set_ramdon_text(std::string str)
{
    GameText game_text;
    if (str == "NiceCream")
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

void Items::set_item_cost_round_init(int current_selection, int button_selection)
{
    check_and_del_item();
	_current_selection = current_selection;
    times = 0;
    set_items(_current_selection);
    _button_selection = button_selection;
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
		if (times < item->cost_round-1)
		{
			times+=1;
			item->index+=item->item_after_len_list[times];
			*stage-=1;
		    if (times == item->cost_round-2)
		    {
		       item->useable_times-=1; 
		    }
		}
        if (item->cost_round == 1)
        {
           item->useable_times-=1; 
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
                0,
               {},
               0,
               {0,0}
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
    return (items[0].cost_round == 0 && *_stage == 2 && _button_selection == 2);
}