#include "stdafx.h"
#include "move.h"

#include "../Library/gamecore.h"

void Move::load_img()
{
    heart.LoadBitmapByString({"resources/heart.bmp","resources/heart_blue.bmp"},RGB(255,255,255));
    heart.SetTopLeft(1000,700);
	heart.SetFrameIndexOfBitmap(heart_red);
}

void Move::set_show_img_enable(bool enable)
{
	_enable_img = enable;
}

void Move::set_heart_mode(HeartMode heart_mode)
{
	_heart_mode = heart_mode;
	heart.SetFrameIndexOfBitmap(heart_mode);
}


Vec2 Move::check_range(Corner corner,Vec2 force)
{
	int border_left = corner._leftTop.x ;
	int border_right = corner._rightTop.x - heart.GetWidth();
	int border_top = corner._leftTop.y;
	int border_bottom = corner._rightBottom.y - heart.GetHeight() ;
	Vec2 force_new = force;
	force_new.x = force.x * move_num_x;
	force_new.y = force.y * move_num_y;
	
	if (heart.GetLeft() + (int)(force.x * move_num_x) >= border_right )
	{
		force_new.x = (float) (border_right - heart.GetLeft());
	}

	if (heart.GetLeft() + (int)(force.x * move_num_x) <= border_left )
	{
		force_new.x = (float) (border_left - heart.GetLeft());
	}

	if (heart.GetTop() + (int)(force.y * move_num_y) >=border_bottom ) //timer = 0 , timer++ if up press, if timer>contain num press up not work
	{
		force_new.y = (float) (border_bottom - heart.GetTop());
		_enable_blue_heart_jump = true;
		jump_time_count = 0;
		jump_time_count_max_up = 330;
		jump_time_count_max_down = 0;
	}
	
	if (heart.GetTop() + (int)(force.y * move_num_y) <=border_top )
	{
		force_new.y = (float) (border_top - heart.GetTop());
	}

	return force_new;
    
}


void Move::move_control(Corner corner,bool enable)
{
	_enable_move = enable;
    Vec2 force = {0 ,0};
	
	if (_enable_move){
		if (_heart_mode == heart_red)
		{
			move_num_x = 8.5;
			move_num_y = 8.5;
			force = red_mode();
			force = normalize(force);
		}
		else if (_heart_mode == heart_blue)
		{
			DWORD time;
			if (_enable_blue_heart_jump)
			{
				time = (jump_time_count_max_up - jump_time_count)/45;
			}
			else
			{
				time = (jump_time_count_max_down - jump_time_count)/30;
			}

			float v = (time * time * 0.25f);
			move_num_x = 6.5;
			move_num_y =(v);
			force = blue_mode();
		}
		
		force = check_range(corner, force);
		move_act(force);
	}
}

Vec2 Move::red_mode()
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
	return force;
}

Vec2 Move::blue_mode()
{
    Vec2 force = {0 ,1};
		if ( GetKeyState(VK_UP)&0x8000 && _enable_blue_heart_jump)
		{
			if (jump_time_count > 300)
			{
				_enable_blue_heart_jump = false;
				jump_time_count_max_down = jump_time_count+20;
			}
			else
			{
				jump_time_count += game_framework::CSpecialEffect::GetEllipseTime();
				jump_time_count_max_down = jump_time_count+100;
				force.x+=0;
				force.y-=2;
			}
		}
		else
		{
			_enable_blue_heart_jump = false;
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

		if (!_enable_blue_heart_jump && jump_time_count>10 )
		{
			jump_time_count -= game_framework::CSpecialEffect::GetEllipseTime();
		}
	return force;
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

void Move::set_heart_postion(int x, int y)
{
	heart.SetTopLeft(x,y);
}
void Move::set_shine_mode(bool enable)
{
	_shine_mode = enable;
}

void Move::show_heart_img()
{
	if (_enable_img)
	{
		if (_shine_mode)
		{
			heart.UnshowBitmap();
		}
		else
		{
			heart.ShowBitmap();
		}
	}
}

void Move::shine_two_second()
{
	if (shine_time_count >= 400)
	{
		_shine_mode = false;
	}
	else
	{
		if (shine_time_count % 10 > 5) {_shine_mode = !_shine_mode;}
	}
}

void Move::shine_count()
{
	shine_time_count += game_framework::CSpecialEffect::GetEllipseTime();
}


void Move::set_heart_jump_enable_and_init(bool enable)
{
	_enable_blue_heart_jump = enable;
	jump_time_count = 170;
	jump_time_count_max_up = 330;
	jump_time_count_max_down = 200;
}

int Move::GetCurrentX()
{
	return heart.GetLeft();
}

int Move::GetCurrentY()
{
	return heart.GetTop();
}

