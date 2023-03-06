#include "stdafx.h"
#include "frame.h"
#include "../Library/gameutil.h"
#include <vector>

void Frame::set_size(int hight, int width)
{
    _hight = hight;
    _width = width;
}

std::vector<coordinate> Frame::get_corner()
{
    std::vector<coordinate> v= {_leftTop,_rightTop,_leftButtom,_rightButtom};
    return  v;
}

void Frame::show_frame()
{
    
    
}
