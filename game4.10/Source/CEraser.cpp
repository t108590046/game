#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"
#include "Bomb.h"
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
		const int X_POS = 200;
		const int Y_POS =200;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isBombing = isStepOnBomb = false;
		is_landing = false;
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
		const int STEP_SIZE = 5;
		const int LANDING_SIZE = 15;
		const int PUT_BOMB_SIZE = 20;
		animation.OnMove();
		if (isMovingLeft) { //往左
			goToLeft.OnMove();
			if (m->IsEmpty(x -STEP_SIZE, y )) { //人物移動
				x -= STEP_SIZE;
			}
		}
		if (isMovingRight) { //往右
			goToRight.OnMove();
			if (m->IsEmpty(x  + animation.Width()+ STEP_SIZE, y )) { 
				x += STEP_SIZE;
			}			
		}
		if (isBombing) { //放炸彈
			if (m->IsEmpty(x, y - PUT_BOMB_SIZE)) {
				y -= PUT_BOMB_SIZE;
			}
		}
		////下降
		if (m->IsEmpty(x, y + LANDING_SIZE + (animation.Height() - 20)) && !isStepOnBomb) {
			y += LANDING_SIZE;
			is_landing = true;
		}
		else {
			is_landing = false;
		}

		if (m->IsChangeScreen_horizontal(x, y))
		{
			if (isMovingRight) {
				m->SetMovingRight(true);
			}
			if (isMovingLeft) {
				m->SetMovingLeft(true);
			}
		}
		if (m->IsChangeScreen_Diagonal_RDandLU(x, y))
		{
			if (isMovingRight) {
				m->SetMovingRight(true);
				m->SetMovingDown(true);
			}
			if (isMovingLeft) {
				m->SetMovingLeft(true);
				m->SetMovingUp(true);
			}
		}
		if (m->IsChangeScreen_Diagonal_RUandLD(x, y))
		{
			if (isMovingRight) {
				m->SetMovingRight(true);
				m->SetMovingUp(true);
			}
			if (isMovingLeft) {
				m->SetMovingLeft(true);
				m->SetMovingDown(true);
			}
		}

		if (m->IsLittleMove_horizontal(x,y) && isMovingLeft)
		{
			m->SetMovingLeftL(true);
		}
		else
		{
			m->SetMovingLeftL(false);
		}

		if (m->IsLittleMove_horizontal(x, y) && isMovingRight)
		{
			m->SetMovingRightL(true);
		}
		else
		{
			m->SetMovingRightL(false);
		}
		
		if (m->IsLittleMove_updown(x, y) && isBombing)
		{
			m->SetMovingUpL(true);
		}
		else
		{
			m->SetMovingUpL(false);
		}

		if (m->IsLittleMove_updown(x, y) && is_landing)
		{
			m->SetMovingDownL(true);
		}
		else
		{
			m->SetMovingDownL(false);
		}
		if (m->ScreenX(x) < 100) {
			m->SetMovingRight(false);
			m->SetMovingDown(false);
		}
		if (m->ScreenX(x) > 700) {
			m->SetMovingLeft(false);
			m->SetMovingUp(false);
		}
		if(m->ShowMovingDown() || m->ShowMovingLeft() || m->ShowMovingUp() || m->ShowMovingRight()) //視角移動時腳色不能移動
		{
			isMovingLeft = false;
			isMovingRight = false;
			isBombing = false;
			is_landing = false;
		}
		
	}
	void CEraser::SetStepOnBomb(bool flag)
	{
		isStepOnBomb = flag;
	}
	void CEraser::SetLanding(bool flag)
	{
		is_landing = flag;
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
	bool CEraser::check_MovingLeft()
	{
		return isMovingLeft;
	}
	bool CEraser::check_MovingRight()
	{
		return isMovingRight;
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