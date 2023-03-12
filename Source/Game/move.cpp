#include "stdafx.h"
#include "move.h"

void Move::load_img()
{
    heart.LoadBitmapByString({"resources/heart.bmp"},RGB(255,255,255));
    heart.SetTopLeft(1000,700);
}


void Move::check_range(Corner corner)
{
    int x = heart.GetLeft();
    int y = heart.GetTop();
    int height_half = heart.GetHeight()/2;
    int width_half = heart.GetWidth()/2;
    
}


void Move::move_control()
{
    
    Vec2 force = {0 ,0};
	
	if ( GetKeyState(VK_UP)&0x8000)
	{
		force.x+=0;
		force.y-=1;
	}
	
	if ( GetKeyState(VK_DOWN)&0x8000)
	{
		force.x+=0;
		force.y+=1;
	}
	
	if ( GetKeyState(VK_LEFT)&0x8000)
	{
		force.x-=1;
		force.y+=0;
	}
	
	if ( GetKeyState(VK_RIGHT)&0x8000)
	{
		force.x+=1;
		force.y+=0;
	}
	move_act(normalize(force));
	
}

Vec2 Move::normalize(const Vec2 force)
{
	if (force.x == 0 && force.y == 0)
	{
		return force;
	}
	
	float temp = sqrt( pow(force.x,2)+ pow(force.y,2) );
	return Vec2{force.x / temp, force.y /temp};
}


void Move::move_act(Vec2 force)
{
	heart.SetTopLeft(
		heart.GetLeft() + (int)(force.x * move_num),
		heart.GetTop() + (int)(force.y * move_num));
}

