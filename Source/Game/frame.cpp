#include "stdafx.h"
#include "frame.h"
#include <vector>
#include "../Library/gameutil.h"

void Frame::create_frame(int height, int width, int leftTop_x, int leftTop_y)
{
    pixel = 11;
    coordinate ori_point;
    ori_point.x = leftTop_x;
    ori_point.y = leftTop_y;
    set_frame_size(height, width);
    set_coordinate(ori_point);
    set_position();
}

void Frame::set_frame_size(int height, int width)
{
    _height = height;
    _width = width;
}

void Frame::set_coordinate(coordinate leftTop)
{
    /*
        座標指向當前設置的框內部四點
     */
    _leftTop.x = leftTop.x+pixel;
    _leftTop.y = leftTop.y+pixel;
    _leftBottom.x = leftTop.x+pixel;
    _leftBottom.y = leftTop.y+_height-pixel;

    _rightTop.x = leftTop.x+_width-pixel;
    _rightTop.y = leftTop.y+pixel;
    _rightBottom.x = leftTop.x+_width-pixel;
    _rightBottom.y = leftTop.y+_height-pixel;
}

void Frame::set_position()
{
	up_horizontal_frame.SetTopLeft(_leftTop.x-pixel,_leftTop.y-pixel);
	down_horizontal_frame.SetTopLeft(_leftTop.x-pixel,_leftTop.y-pixel-pixel+_height);
	left_vertical_frame.SetTopLeft(_leftTop.x+pixel-left_vertical_frame.GetWidth(),_leftTop.y-pixel);
	right_vertical_frame.SetTopLeft(_leftTop.x-pixel+up_horizontal_frame.GetWidth(),_leftTop.y-pixel);
    
}

std::vector<coordinate> Frame::get_corner() const
{
    std::vector<coordinate> v= {_leftTop,_rightTop,_leftBottom,_rightBottom};
    return  v;
}

void Frame::show_frame()
{
    down_horizontal_frame.ShowBitmap();    
    up_horizontal_frame.ShowBitmap();
    left_vertical_frame.ShowBitmap();
    right_vertical_frame.ShowBitmap();
}
