#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 250;
		const int Y_POS = 250;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isBombing = false;
	}

	void CEraser::LoadBitmap()
	{
		//animation.SetDelayCount(50);

		animation.AddBitmap(IDB_CHICKEN1, RGB(34, 177, 76));
		goToRight.AddBitmap(IDB_CHICKENRIGHT2, RGB(34, 177, 76));
		goToRight.AddBitmap(IDB_CHICKENRIGHT, RGB(34, 177, 76));
		goToLeft.AddBitmap(IDB_CHICKEN2, RGB(34, 177, 76));
		goToLeft.AddBitmap(IDB_CHICKENLEFT, RGB(34, 177, 76));

	}

	void CEraser::OnMove(CGameMap *m)
	{
		const int STEP_SIZE = 8;
		const int LANDING_SIZE = 8;
		const int PUT_BOMB_SIZE = 25;
		animation.OnMove();
		if (isMovingLeft) {
			goToLeft.OnMove();
			if (m->IsEmpty(x -STEP_SIZE, y )) {    
				x -= STEP_SIZE;
			}
		}
		if (isMovingRight) {
			goToRight.OnMove();
			if (m->IsEmpty(x  + goToRight.Width()+ STEP_SIZE, y )) {
				x += STEP_SIZE;
			}
		}
		if (isBombing) {
			if (m->IsEmpty(x, y - PUT_BOMB_SIZE)) {
				y -= PUT_BOMB_SIZE;
			}
		}


		////µø¨¤²¾°Ê
		if (m->ScreenX(x) > 400 && isMovingRight) {
			m->SetMovingRight(true);
		}
		else {
			m->SetMovingRight(false);
		}
		if (m->ScreenX(x) < 100 && isMovingLeft) {
			m->SetMovingLeft(true);
		}
		else {
			m->SetMovingLeft(false);
		}
		////¤U­°
		if (m->IsEmpty(x, y + LANDING_SIZE+ animation.Height())) {
			y += LANDING_SIZE;
		}
	}

	void CEraser::SetBombing(bool flag)
	{
		isBombing = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow(CGameMap *m)
	{
		if (isMovingRight) {
			
			goToRight.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			goToRight.OnShow();
			animation.deleteBmp();
			animation.AddBitmap(IDB_CHICKEN1, RGB(34, 177, 76));
		}
		else if(isMovingLeft){

			goToLeft.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			goToLeft.OnShow();
			animation.deleteBmp();
			animation.AddBitmap(IDB_CHICKEN4, RGB(34, 177, 76));
		}
		else {
			animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			animation.OnShow();
		}

	}
}