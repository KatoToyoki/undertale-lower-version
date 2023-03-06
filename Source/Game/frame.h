#pragma once
#include <vector>
#include <iostream>

#include "../Library/gameutil.h"

struct coordinate
{
    int x;
    int y;
};

class Frame
{
public:
    Frame();

    ~Frame();

    void set_size(int hight, int width);
    std::vector<coordinate> get_corner();
    void show_frame();

private:
    int _hight;
    int _width;
    coordinate _leftTop;
    coordinate _rightTop;
    coordinate _leftButtom;
    coordinate _rightButtom;
    game_framework::CMovingBitmap _left_vertical_frame,_right_vertical_frame,horizontal_frame;
};
