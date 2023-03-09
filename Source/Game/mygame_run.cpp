#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <iostream>

	// #define MID ((1920/2)-(UserFrame.horizontal_up_frame.GetWidth()/2));

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}
void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (stage == 0){
		change_talk_to_normal_battle();
	}
	else if (stage == 1)
	{
		change_frame_down();
	}
	else if (stage == 2)
	{
		change_frame_add_width();
	}
	else
	{
		change_frame_up();
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	// all the material here
	user_frame.lord_img();
	user_frame.create_frame(314,1294,312,563);
	// user_frame.create_frame(314,416,751,563);
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	user_frame.show_frame();
}

void CGameStateRun::change_talk_to_normal_battle()
{
	if (user_frame.get_width() > 416)
	{
		user_frame.move_frame_to_battle_mode();
		if (user_frame.get_width() < 416)
		{
			stage = 1;
		}
	}
}
void CGameStateRun::change_frame_down()
{
	if (user_frame.get_height() > 227)
	{
		user_frame.move_frame_horizontal_down();
		if (user_frame.get_height() <=227)
		{
			stage = 2;
		}
	}
	
}
void CGameStateRun::change_frame_add_width()
{
	if (user_frame.get_width() < 1294)
	{
		user_frame.move_frame_to_talk_mode();
		if (user_frame.get_width() >= 1294)
		{
			stage = 3;
		}
	}
	
}

void CGameStateRun::change_frame_up()
{
	if (user_frame.get_height() < 314)
	{
		user_frame.move_frame_horizontal_up();
		if (user_frame.get_height() >= 314)
		{
			stage = 0;
		}
		
	}
	
}
