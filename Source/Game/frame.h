#pragma once
#include <vector>

#include "../Library/gameutil.h"
struct coordinate
{
    int x;
    int y;
};

class Frame : public game_framework::CMovingBitmap
{
public:
    Frame()=default;
    ~Frame()=default;

    void create_frame(int height, int width, int leftTop_x,int leftTop_y);
    void set_frame_size(int height, int width);
    void set_coordinate(coordinate leftTop);
    void set_position();
    std::vector<coordinate> get_corner() const;
    int get_height() const { return _height; }
    int get_width() const { return _width; }
    void show_frame();
    
    CMovingBitmap left_vertical_frame,right_vertical_frame,up_horizontal_frame,down_horizontal_frame;

private:
    int _height;
    int _width;
    int pixel;
    coordinate _leftTop;
    coordinate _rightTop;
    coordinate _leftBottom;
    coordinate _rightBottom;
};
