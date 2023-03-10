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
	if (user_frame.move_done){
		test_stage+=1;
	}
	if (test_stage == 0)
	{
		control_frame(1);
	}
	else if (test_stage == 1)
	{
		control_frame(3);
	}
	else if (test_stage == 2)
	{
		control_frame(0);
	}
	else if (test_stage == 3)
	{
		control_frame(2);
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
	}
}
void CGameStateRun::change_frame_down()
{
	if (user_frame.get_height() > 227)
	{
		user_frame.move_frame_horizontal_down();
	}
}
void CGameStateRun::change_frame_add_width()
{
	if (user_frame.get_width() < 1294)
	{
		user_frame.move_frame_to_talk_mode();
	}
}

void CGameStateRun::change_frame_up()
{
	if (user_frame.get_height() < 314)
	{
		user_frame.move_frame_horizontal_up();
	}
}

void CGameStateRun::control_frame(int frame_commend_control)// change move_done to 判斷 move_done=ture can go next act
/*
 * 0 : change talk to normal battle
 * 1 : change talk to long battle
 * 2 : change normal battle to talk
 * 3 : change long battle to talk
 * 4 : idle frame
 */
{
	int frame_commend = 4;
	switch(frame_commend_control)
	{
	case 0://change talk to normal battle
		frame_commend = 0;
		if (user_frame.get_width() <= 416)
		{
			frame_commend = 4;
			user_frame.move_done = true;
			break;
		}
		user_frame.move_done = false;
		break;
	case 1://change talk to long battle
		frame_commend = 0;
		if (user_frame.get_width() <= 416){ frame_commend = 1;}
		if (user_frame.get_height() <=227 && user_frame.get_width() <= 416)
		{
			frame_commend = 4;
			user_frame.move_done = true;
			break;
		}
		user_frame.move_done = false;
		break;
	case 2://change normal battle to talk
		frame_commend = 2;	
		if (user_frame.get_width() >= 1294)
		{
			frame_commend = 4;
			user_frame.move_done = true;
			break;
		}
		user_frame.move_done = false;
		break;
	case 3://change long battle to talk
		frame_commend = 2;	
		if (user_frame.get_width() >= 1294){ frame_commend = 3;}
		if (user_frame.get_height() >= 314&& user_frame.get_width() >= 1294)
		{
			frame_commend = 4;
			user_frame.move_done = true;
			break;
		}
		user_frame.move_done = false;
		break;
	default:
		frame_commend = 4;
		user_frame.move_done = true;
		break;
	}
	check_which_change_frame_need_call(frame_commend);
}

void CGameStateRun::check_which_change_frame_need_call(int frame_commend)
{
	if (frame_commend == 0){
		change_talk_to_normal_battle();
	}
	else if (frame_commend == 1)
	{
		change_frame_down();
	}
	else if (frame_commend == 2)
	{
		change_frame_add_width();
	}
	else if (frame_commend == 3)
	{
		change_frame_up();
	}
}


