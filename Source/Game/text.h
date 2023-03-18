#pragma once
#include <string>

class Text
{
public:
    Text(int size = 21, std::string str = "", COLORREF color = RGB(255,255,255), int weight = 800, int x = 0, int y = 0);

    void set_color(COLORREF color);
    void set_positon(int x,int y);
    void set_enable(bool enable);
    void print();
private:
    bool _enable = false;

    int _size;
    std::string _str;
    COLORREF _color;
    int _weight;
    int _x,_y;
    
};
