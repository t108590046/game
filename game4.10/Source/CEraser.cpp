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
		const int Y_POS = 450;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isBombing = isStepOnBomb = isInPipeGoToDown = isInPipeGoToUp = isPressDown = false;
		is_landing = isShowHeart =false;
		nowLife = 1;
		life_Max = 1;
		showHeartCounter = 30 * 3;
	}

	void CEraser::LoadBitmap()
	{
		//animation.SetDelayCount(50);

		animation.AddBitmap(IDB_CHICKEN1, RGB(34, 177, 76));
		goToRight.AddBitmap(IDB_CHICKENRIGHT2, RGB(34, 177, 76));
		goToRight.AddBitmap(IDB_CHICKENRIGHT, RGB(34, 177, 76));
		goToLeft.AddBitmap(IDB_CHICKEN2, RGB(34, 177, 76));
		goToLeft.AddBitmap(IDB_CHICKENLEFT, RGB(34, 177, 76));
		for (int i = 0; i < life_Max; i++) {
			heart[i].LoadBitmapA(IDB_HEART, RGB(34, 177, 76));
		}

	}

	void CEraser::OnMove(CGameMap *m)
	{
		TRACE("x:%d\n", x);
		TRACE("y:%d\n", y);

		const int STEP_SIZE = 5;
		const int PIPE_SIZE = 15;
		const int LANDING_SIZE = 10;
		const int PUT_BOMB_SIZE = 20;
		animation.OnMove();
		if (isMovingLeft) { //往左
			goToLeft.OnMove();
			if (m->IsEmpty(x - STEP_SIZE, y)) { //人物移動
				x -= STEP_SIZE;
			}
		}
		if (m->IsLittleMove_horizontal(x, y) && isMovingLeft)
		{
			m->SetMovingLeftL(true);
		}
		else
		{
			m->SetMovingLeftL(false);
		}

		if (isMovingRight) { //往右
			goToRight.OnMove();
			if (m->IsEmpty(x + animation.Width() + STEP_SIZE, y)) {
				x += STEP_SIZE;
			}
		}
		if (m->IsLittleMove_horizontal(x, y) && isMovingRight)
		{
			m->SetMovingRightL(true);
		}
		else
		{
			m->SetMovingRightL(false);
		}

		if (m->IsPipe(x, y))//小雞碰到水管
		{
			if (isBombing)
			{
				isInPipeGoToUp = true;
			}
		}
		else
		{
			isInPipeGoToUp = false;
		}
		if (m->IsPipe(x, y + animation.Height()))
		{
			if (isPressDown)
			{
				isInPipeGoToDown = true;
			}
		}
		else
		{
			isInPipeGoToDown = false;
		}

		if (isInPipeGoToDown) {
			y += PIPE_SIZE;
			m->SetMovingRight(true);
			m->SetMovingDown(true);
		}

		if (isInPipeGoToUp) {
			y -= PIPE_SIZE;
			m->SetMovingLeft(true);
			m->SetMovingUp(true);
		}

		if (isBombing) { //放炸彈
			if (m->IsEmpty(x, y - PUT_BOMB_SIZE) || m->IsPipe(x, y - PUT_BOMB_SIZE)) {
				y -= PUT_BOMB_SIZE;
			}

		}
		if (m->IsLittleMove_updown(x, y) && isBombing)
		{
			m->SetMovingUpL(true);
		}
		else
		{
			m->SetMovingUpL(false);
		}

		//下降
		if (m->IsEmpty(x, y + LANDING_SIZE + animation.Height()) && !isStepOnBomb && !(m->IsStandingWood(x, y + LANDING_SIZE + (animation.Height())))) {
			y += LANDING_SIZE;
			is_landing = true;
		}
		else {
			is_landing = false;
		}

		if (m->IsChangeScreen_UpOrDown(x, y) && (is_landing))
		{
			m->SetMovingDown(true);
		}
		if (m->IsLittleMove_updown(x, y) && is_landing)
		{
			m->SetMovingDownL(true);
		}
		else
		{
			m->SetMovingDownL(false);
		}



		if (m->IsChangeScreen_horizontal(x, y) && isMovingRight) {//視角平移
			m->SetMovingRight(true);
		}
		if (m->IsChangeScreen_horizontal(x, y) && isMovingLeft) {
			m->SetMovingLeft(true);
		}

		if (m->IsChangeScreen_Diagonal_RDandLU(x, y))
		{
			if (isMovingRight || is_landing)
			{
				m->SetMovingDown(true);
				m->SetMovingRight(true);
			}
			if (isMovingLeft)
			{
				m->SetMovingUp(true);
				m->SetMovingLeft(true);
			}
		}
		if (m->IsChangeScreen_Diagonal_RUandLD(x,y))
		{
			if (isMovingRight)
			{
				m->SetMovingUp(true);
				m->SetMovingRight(true);
			}
			if (isMovingLeft)
			{
				m->SetMovingDown(true);
				m->SetMovingLeft(true);
			}

		}

		if (m->IsScreenStopMoving(x, y)) { //強制停止視角移動
			m->ScreenStopMoving();
		}


	}
	void  CEraser::setShowHeart(bool flag) 
	{
		isShowHeart = flag;
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

	void CEraser::SetPressDown(bool flag)
	{
		isPressDown = flag;
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
	void CEraser::stopMoving()
	{
		isMovingLeft = isBombing = isMovingRight = is_landing =false;
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
		if (isShowHeart)
		{
			for (int i = 0; i < life_Max; i++) {
				heart[i].SetTopLeft(20 +i* heart[i].Width(), 20);
				heart[i].ShowBitmap();
			}
			showHeartCounter--;
			if (showHeartCounter < 0) {
				isShowHeart = false;
				showHeartCounter = 30 * 3;
			}
		}
	}
}