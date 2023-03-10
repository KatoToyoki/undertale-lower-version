#include "stdafx.h"
#include "frame.h"
#include <vector>
#include "../Library/gameutil.h"

void Frame::create_frame(int height, int width, int leftTop_x, int leftTop_y)
{
    pixel = 11;
    Coordinate ori_point;
    ori_point.x = leftTop_x;
    ori_point.y = leftTop_y;
    set_frame_size(height, width);
    set_inner_position(ori_point);
    set_position(_corner._leftTop);
}

void Frame::set_frame_size(int height, int width)
{
    _height = height;
    _width = width;
}

void Frame::set_inner_position(Coordinate leftTop)
{
    /*
        座標指向當前設置的框內部四點
     */
    _corner._leftTop.x = leftTop.x+pixel;
    _corner._leftTop.y = leftTop.y+pixel;
    _corner._leftBottom.x = leftTop.x+pixel;
    _corner._leftBottom.y = leftTop.y+_height-pixel;

    _corner._rightTop.x = leftTop.x+_width-pixel;
    _corner._rightTop.y = leftTop.y+pixel;
    _corner._rightBottom.x = leftTop.x+_width-pixel;
    _corner._rightBottom.y = leftTop.y+_height-pixel;
}

void Frame::set_position(Coordinate inner_leftTop)
{
	up_horizontal_frame.SetTopLeft(inner_leftTop.x-pixel,inner_leftTop.y-pixel);
	down_horizontal_frame.SetTopLeft(inner_leftTop.x-pixel,inner_leftTop.y-pixel-pixel+_height);
	left_vertical_frame.SetTopLeft(inner_leftTop.x+pixel-left_vertical_frame.GetWidth(),inner_leftTop.y-pixel);
	right_vertical_frame.SetTopLeft(inner_leftTop.x-pixel+_width,inner_leftTop.y-pixel);
    down_black.SetTopLeft(0,inner_leftTop.y-pixel+_height);
}

Corner Frame::get_corner() const
{
    return  _corner;
}

void Frame::show_frame()
{
    down_horizontal_frame.ShowBitmap();    
    up_horizontal_frame.ShowBitmap();
    left_vertical_frame.ShowBitmap();
    right_vertical_frame.ShowBitmap();
    down_black.ShowBitmap();
}
