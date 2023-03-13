#include "stdafx.h"
#include "move.h"

void Move::load_img()
{
    heart.LoadBitmapByString({"resources/heart.bmp"},RGB(255,255,255));
    heart.SetTopLeft(1000,700);
}


Vec2 Move::check_range(Corner corner,Vec2 force)
{
	int border_left = corner._leftTop.x + 11;
	int border_right = corner._rightTop.x - (heart.GetWidth() /2) -7;
	int border_top = corner._leftTop.y;
	int border_bottom = corner._rightBottom.y - heart.GetHeight() ;
	Vec2 force_new = force;
	force_new.x = force.x * move_num;
	force_new.y = force.y * move_num;
	
	int move_step =(int) (force.x * move_num);
	
	
	if (heart.GetLeft() + move_step >= border_right )
	{
		force_new.x = (float) (border_right - heart.GetLeft());
	}

	if (heart.GetLeft() + (int)(force.x * move_num) <= border_left )
	{
		force_new.x = (float) (border_left - heart.GetLeft());
	}

	if (heart.GetTop() + (int)(force.y * move_num) >=border_bottom )
	{
		force_new.y = (float) (border_bottom - heart.GetTop());
	}
	
	if (heart.GetTop() + (int)(force.y * move_num) <=border_top )
	{
		force_new.y = (float) (border_top - heart.GetTop());
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

	force = normalize(force);
	force = check_range(corner, force);
	move_act(force);
	
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
		heart.GetLeft() + (int)(force.x),
		heart.GetTop() + (int)(force.y));
}

