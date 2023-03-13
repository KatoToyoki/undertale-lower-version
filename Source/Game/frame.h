#pragma once
#include <vector>

#include "../Library/gameutil.h"
struct Coordinate
{
    int x;
    int y;
};

struct FrameData
{
    int hieght;
    int width;
    Coordinate LeftTop;
};

struct Corner
{
    Coordinate _leftTop;
    Coordinate _rightTop;
    Coordinate _leftBottom;
    Coordinate _rightBottom;
};

class Frame
{
public:
    Frame()=default;
    ~Frame()=default;

    void create_frame(int height, int width, int leftTop_x,int leftTop_y);

    Corner get_corner() const;
    int get_height() const { return _height; }
    int get_width() const { return _width; }
    int get_pixel() const { return  pixel; }
    void set_position(Coordinate inner_leftTop);
    
    void show_frame();
    void off_frame();
    
    game_framework::CMovingBitmap left_vertical_frame;
    game_framework::CMovingBitmap right_vertical_frame;
    game_framework::CMovingBitmap up_horizontal_frame;
    game_framework::CMovingBitmap down_horizontal_frame;
    game_framework::CMovingBitmap down_black;
    FrameData user_frame_size = {314, 1294,{312,563}};
    FrameData battle_frame_size = {314, 416,{715,563}};

private:
    void set_frame_size(int height, int width);
    void set_inner_position(Coordinate leftTop);
    
    int _height;
    int _width;
    int pixel;
    Corner _corner;
    
};
