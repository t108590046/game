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
	CEraser::CEraser()
	{
		Initialize(0);
		nowLife = 1;
		life_Max = 1;
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
	void CEraser::Initialize(int n)
	{  
		int X_POS_ALL[3] = { 200 ,50,30};
		int Y_POS_ALL[3] = { 500 ,448,844};
		x = savePointX = X_POS_ALL[n];
		y = savePointY = Y_POS_ALL[n];
		isMovingLeft = isMovingRight = isMovingUp = isBombing = isStepOnBomb = isInPipeGoToDown = isInPipeGoToUp = isPressDown  = isHurt =isJumping =false;
		is_landing = isShowHeart =false;
		showHeartCounter = 30 * 3;
		jumpCounter = 15 * 1;
		isCanPutBomb = true;
		nowLife = life_Max;
	}
	void CEraser::LoadBitmap()
	{
		animation.AddBitmap(IDB_CHICKEN1, RGB(34, 177, 76));
		goToRight.AddBitmap(IDB_CHICKENRIGHT2, RGB(34, 177, 76));
		goToRight.AddBitmap(IDB_CHICKENRIGHT, RGB(34, 177, 76));
		goToLeft.AddBitmap(IDB_CHICKEN2, RGB(34, 177, 76));
		goToLeft.AddBitmap(IDB_CHICKENLEFT, RGB(34, 177, 76));
		heart.LoadBitmapA(IDB_HEART, RGB(34, 177, 76));
		emptyHeart.LoadBitmapA(IDB_EMPTY_HEART, RGB(34, 177, 76));
		cantputBomb.AddBitmap(IDB_CANTPUTBOMB, RGB(34, 177, 76));
	}
	void CEraser::OnMove(CGameMap *m,Bomb *bomb)
	{
		const int STEP_SIZE =5;
		const int PIPE_SIZE = 15;
		const int LANDING_SIZE = 9;
		const int JUMP_SIZE = 7;
		animation.OnMove();
		if (m->checkScreenMoVing() ||check_inPipe()) {
			isMovingLeft = isMovingRight = isBombing  = false;
		}
		if (isJumping) {
			if (m->IsEmpty(x, y - JUMP_SIZE)) {
				y -= JUMP_SIZE;
			}
			jumpCounter--;
			if (jumpCounter < 0) {
				jumpCounter = 15 * 1;
				isJumping = false;
			}
		}//往左
		if (isMovingLeft) { 
			goToLeft.OnMove();
			//人物移動
			if (m->IsEmpty(x - STEP_SIZE, y+ animation.Height()/2 +10)) { 
				x -= STEP_SIZE;
			}
		}//向左水平視角小移動
		if (m->IsLittleMove_horizontal(x, y + animation.Height() / 2) && isMovingLeft)
		{
			m->SetMovingLeftL(true);
		}
		else
		{
			m->SetMovingLeftL(false);
		}//往右
		if (isMovingRight) { 
			goToRight.OnMove();
			if (m->IsEmpty(x + animation.Width() + STEP_SIZE, y + animation.Height()/2 +10)) {
				x += STEP_SIZE;
			}
		}//向右水平視角小移動
		if (m->IsLittleMove_horizontal(x, y + animation.Height() / 2) && isMovingRight)
		{
			m->SetMovingRightL(true);
		}
		else
		{
			m->SetMovingRightL(false);
		}//小雞碰到水管上升
		if (m->IsPipe(x, y, this)!= -1)
		{
			if (isBombing)
			{
				isInPipeGoToUp = true;
			}
		}//水管停止上升或下降
		if(m->IsPipe(x, y, this) == -1 && m->IsPipe(x, y + animation.Height(), this) == -1)
		{
			if (isInPipeGoToUp == true || isInPipeGoToDown == true)
			{
				isInPipeGoToUp = false;
				isInPipeGoToDown = false;
				savePointX = x;
				savePointY = y;
			}
		}//小雞碰到水管下降
		if (m->IsPipe(x, y + animation.Height() + 10, this) !=-1)
		{
			if (isPressDown)
			{
				isInPipeGoToDown = true;
			}
		}//判斷不同的水管種類
		if (isInPipeGoToDown) {
			y += PIPE_SIZE;
			if (m->IsPipe(x, y + animation.Height() + 10, this) == 0) {
				m->SetMovingRight(true);
				m->SetMovingDown(true);
			}
			else if (m->IsPipe(x, y + animation.Height() + 10, this) == 1) {
				m->SetMovingRight(true);
				m->SetMovingDown(true);
			}
			else if (m->IsPipe(x, y + animation.Height() + 10, this) == 2) {
				m->SetMovingRight(true);
				m->SetMovingDown(true);
			}
			else if (m->IsPipe(x, y + animation.Height() + 10, this) == 3) {
				m->SetMovingLeft(true);
				m->SetMovingDown(true);
			}
		}
		if (isInPipeGoToUp) {
			y -= PIPE_SIZE;
			if (m->IsPipe(x, y,this) == 0) {
				m->SetMovingLeft(true);
				m->SetMovingUp(true);
			}
			else if (m->IsPipe(x, y, this) == 1) {
				m->SetMovingLeft(true);
				m->SetMovingUp(true);
			}
			else if (m->IsPipe(x, y, this) == 2) {
				m->SetMovingLeft(true);
				m->SetMovingUp(true);
			}
			else if (m->IsPipe(x, y, this) == 3) {
				m->SetMovingRight(true);
				m->SetMovingUp(true);
			}
		}//放炸彈
		if (isBombing) { 
			cantputBomb.OnMove();
			//頭上不能有障礙物
			if ( ( m->IsEmpty(x, y-10) || m->IsStandingWood(x,y-56) || m->IsPipe(x,y, this) != -1)) {
				isCanPutBomb = true;			
			}
			else {
				isCanPutBomb = false;
			}
		}
		if (m->IsLittleMove_updown(x, y+ animation.Height()) && isCanPutBomb && isBombing)
		{
			m->SetMovingUpL(true);
		}
		else
		{
			m->SetMovingUpL(false);
		}
		//下降
		if (m->IsPipe(x + animation.Width()/2,y + animation.Height()+ LANDING_SIZE,this)==-1 &&!isJumping &&((m->IsEmpty(x, y + LANDING_SIZE + animation.Height()) && m->IsEmpty(x + animation.Width(), y + LANDING_SIZE+ animation.Height())) || m->IsStandingLittleWoodDoor(x + animation.Width() / 2, y + LANDING_SIZE + animation.Height())) && !isStepOnBomb)
		{
			y += LANDING_SIZE;
			is_landing = true;
		}
		else{
			is_landing = false;
		}
		//以下都是小雞與視角的互動
		if (m->IsChangeScreen_UpOrDown(x, y) && (is_landing))
		{
			m->SetMovingDown(true);
		}
		if (m->IsLittleMove_updown(x, y + animation.Height()) && is_landing)
		{
			m->SetMovingDownL(true);
		}
		else
		{
			m->SetMovingDownL(false);
		}
		if (m->IsLittleDown(x, y) && is_landing) {
			m->SetMovingDownL(true);
		}
		if (m->IsChangeScreen_horizontal(x, y + animation.Height()/2) && isMovingRight) {
			m->SetMovingRight(true);
		}
		if (m->IsChangeScreen_horizontal(x, y + animation.Height() / 2) && isMovingLeft) {
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
		if (m->IsChangeScreen_Diagonal_RD(x + animation.Width()/2, y)) {
			m->SetMovingDown(true);
			m->SetMovingRight(true);
		}
		//存檔點
		if (m->IsChangeScreen_Diagonal_RD(x, y)  ||m->IsChangeScreen_Diagonal_RUandLD(x, y) || m->IsChangeScreen_Diagonal_RDandLU(x, y)  || m->IsChangeScreen_UpOrDown(x, y) || m->IsChangeScreen_horizontal(x, y))
		{
			savePointX = x;
			savePointY = y;
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
	bool CEraser::checkOnFloor()
	{
		return !is_landing;
	}
	bool CEraser::checkOnBomb()
	{
		return isStepOnBomb;
	}

	bool CEraser::check_MovingRight()
	{
		return isMovingRight;
	}
	bool CEraser::check_IsBombing()
	{
		return isBombing;
	}
	bool CEraser::checkCanPutBomb()
	{
		return  isCanPutBomb ;
	}
	void CEraser::stopMoving()
	{
		isMovingLeft = isBombing = isMovingRight = is_landing =false;
	}
	void CEraser::minusNowLife()
	{
		nowLife--;
	}
	void CEraser::addNowLife() {
		life_Max++;
		nowLife++;
	}
	void CEraser::setHurt(bool flag) {
		isHurt = flag;
	}
	int CEraser::getNowLife()
	{
		return nowLife;
	}
	void CEraser::returnSavePoint()
	{
		x = savePointX;
		y = savePointY;
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
			if (!isCanPutBomb && isBombing) {
				cantputBomb.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				cantputBomb.OnShow();
			}
			else {
				animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				animation.OnShow();
			}
		}
		if (isShowHeart)
		{
			for (int i = 0; i < nowLife; i++) {
				heart.SetTopLeft(20 +i* heart.Width(), 20);
				heart.ShowBitmap();
			}
			for (int i = life_Max - nowLife; i > 0; i--) {
				emptyHeart.SetTopLeft(20 +  (nowLife-1+i)* heart.Width(), 20);
				emptyHeart.ShowBitmap();

			}
			showHeartCounter--;
			if (showHeartCounter < 0) {
				isShowHeart = false;
				showHeartCounter = 30 * 3;
			}
		}
	}
	void CEraser::healHeart()
	{
		nowLife = life_Max;
	}
	void CEraser::setChickenJumping(bool flag) {
		isJumping = flag;
	}
	bool CEraser::check_inPipe( ) {
		return (isInPipeGoToUp || isInPipeGoToDown);
	}
	bool CEraser::getNowIsPipeGoToUp() {
		return isInPipeGoToUp;
	}
	bool CEraser::getNowIsPipeGoToDown() {
		return isInPipeGoToDown;
	}
}