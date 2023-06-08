#pragma once
#include <string>

enum TEXT_MODE
{
    NO_TYPE,
    TYPE
};

class Text
{
public:
    Text(int size = 21, std::string str = "",
        COLORREF color = RGB(255,255,255),
        int weight = 800, int x = 0, int y = 0,
        TEXT_MODE text_mode = NO_TYPE,
        std::string font_name = "Determination Mono Web" );

    void set_color(COLORREF color);
    void set_positon(int x,int y);
    void set_enable(bool enable);
    void type_mode();
    void print();
    void effect();

    bool get_print_over() {return  print_over;}

    int _x,_y;
    std::string _print_text;
    std::string _str;
private:
    bool _enable = false;

    int _size;
    int _str_index;
    int timer = 0;
    COLORREF _color;
    int _weight;
    std::string _font_name;
    TEXT_MODE _text_mode = NO_TYPE;
    bool print_over = false;
    
};
