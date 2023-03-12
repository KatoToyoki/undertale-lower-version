#include "stdafx.h"
#include "move.h"

void Move::load_img()
{
    heart.LoadBitmapByString({"resources/heart.bmp"},RGB(255,255,255));
    heart.SetTopLeft(1000,700);
}


Vec2 Move::check_range(Corner corner,Vec2 force)
{
	int range_x_begin = corner._leftTop.x + 10;
	int range_x_end = corner._rightTop.x - (heart.GetWidth() /2) -6;
	int range_y_begin = corner._leftTop.y;
	int range_y_end = corner._rightBottom.y - heart.GetHeight() +1 ;
	Vec2 force_new = force;

	if (heart.GetLeft() + (int)(force.x * move_num) >=range_x_end && force.x == 1)
	{
		force_new.x = 0;
	}

	if (heart.GetLeft() + (int)(force.x * move_num) <=range_x_begin && force.x == -1)
	{
		force_new.x = 0;
	}

	if (heart.GetTop() + (int)(force.y * move_num) >=range_y_end && force.y == 1)
	{
		force_new.y = 0;
	}
	
	if (heart.GetTop() + (int)(force.y * move_num) <=range_y_begin && force.y == -1)
	{
		force_new.y = 0;
	}

	return force_new;
    
}


void Move::move_control(Corner corner)
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

		
	move_act(normalize(check_range(corner,force)));
	
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

