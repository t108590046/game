#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Bomb.h"
#include "gameMap.h"
#include <ctime>
#include <cmath>
#include "woodDoor.h"
#include "Treasure.h"
#include "Rock.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Bomb: Ball class
	/////////////////////////////////////////////////////////////////////////////
	
	Bomb::Bomb()
	{
		is_alive = is_putBomb = isMovingLeft = isMovingRight = isBombing = isLanding = isOnBomb =false ;		
		x = y = 0;
		bombTimeCounter = 30 * 3;
		bombingTimeCounter = 15 * 1;
	}
	int Bomb::GetX1()
	{
		return x;
	}

	int Bomb::GetY1()
	{
		return y;
	}
	int Bomb::GetHeight()
	{
		return bmp.Height();
	}
	int Bomb::GetX2()
	{
		return x + bmp.Width();
	}

	int Bomb::GetY2()
	{
		return y + bmp.Height();
	}

	bool Bomb::beBombed(woodDoor *door)
	{
		if (isBombing) {
			int tx1 = x ;
			int tx2 = x + bmpBombing.Width();
			int ty1 = y ;
			int ty2 = y + bmpBombing.Height();
			int x1 = door->GetX1();
			int y1 = door->GetY1();
			int x2 = door->GetX2();
			int y2 = door->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
		}
		else
		{
			return false;
		}
	}
	bool Bomb::beEnemyTouched(Enemy *enemy) {
		int type = enemy->returnType();
		if (type == 4) {
			int e_diffx = (enemy->GetX2() - enemy->GetX1()) / 2;
			int e_diffy = (enemy->GetY2() - enemy->GetY1()) / 2;
			int ex = enemy->GetX1() + e_diffx;
			int ey = enemy->GetY1() + e_diffy;

			int bx = x + bmp.Width() / 2;
			int by = y + bmp.Height() / 2;
			return (abs(ex - bx) < 10 && abs(ey - by) < 10);
		}
		else if (type == 0) {
			int x1 = x;
			int x2 = x + bmp.Width();
			int y1 = y;
			int y2 = y + bmp.Height();
			int tx1 = enemy->GetX1();
			int ty1 = enemy->GetY1();
			int tx2 = enemy->GetX2();
			int ty2 = enemy->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2 && abs(ty2-y2)<10);
		}
		else 
			return false;
	}
	bool Bomb::movingBombTouch(Enemy *enemy) {
		int x1 = x;
		int x2 = x + bmp.Width();
		int y1 = y;
		int y2 = y + bmp.Height();
		int tx1 = enemy->GetX1();
		int ty1 = enemy->GetY1();
		int tx2 = enemy->GetX2();
		int ty2 = enemy->GetY2();
		return (tx2 >= x1 && tx1 <= x2  && ty2 >= y1 && ty1 <= y2);
	}
	bool Bomb::beBombed(Enemy *enemy)
	{
		if (isBombing) {
			int tx1 = x;
			int tx2 = x + bmpBombing.Width();
			int ty1 = y;
			int ty2 = y + bmpBombing.Height();
			int x1 = enemy->GetX1();
			int y1 = enemy->GetY1();
			int x2 = enemy->GetX2();
			int y2 = enemy->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
		}
		else
		{
			return false;
		}
	}

	bool Bomb::beBombed(Bomb *bomb)
	{
		if (isBombing) {
			int tx1 = x ;
			int tx2 = x + bmpBombing.Width() ;
			int ty1 = y ;
			int ty2 = y + bmpBombing.Height();
			int x1 = bomb->GetX1();
			int y1 = bomb->GetY1();
			int x2 = bomb->GetX2();
			int y2 = bomb->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
		}
		else
		{
			return false;
		}
	}
	bool Bomb::beBombed(Treasure *trasure)
	{
		if (isBombing) {
			int tx1 = x  ;
			int tx2 = x + bmpBombing.Width() ;
			int ty1 = y  ;
			int ty2 = y + bmpBombing.Height();
			int x1 = trasure->GetX1();
			int y1 = trasure->GetY1();
			int x2 = trasure->GetX2();
			int y2 = trasure->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
		}
		else
		{
			return false;
		}
	}
	bool Bomb::beBombed(Rock *rock)
	{
		if (isBombing) {
			int tx1 = x -30;
			int tx2 = x + bmpBombing.Width()+30;
			int ty1 = y -30 ;
			int ty2 = y + bmpBombing.Height() +30;
			int x1 = rock->GetX1();
			int y1 = rock->GetY1();
			int x2 = rock->GetX2();
			int y2 = rock->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
		}
		else
		{
			return false;
		}
	}
	bool Bomb::beBombed(CEraser *eraser)
	{
		if (isBombing) {
			int tx1 = x;
			int tx2 = x + bmpBombing.Width();
			int ty1 = y;
			int ty2 = y + bmpBombing.Height();
			int x1 = eraser->GetX1();
			int y1 = eraser->GetY1();
			int x2 = eraser->GetX2();
			int y2 = eraser->GetY2();
			return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
		}
		else
		{
			return false;
		}
	}
	void Bomb::setMovingRight(bool flag)
	{
		isMovingRight = flag;
	}	
	void Bomb::setMovingLeft(bool flag) 
	{
		isMovingLeft = flag;
	}

	bool Bomb::chickenPushBomb(CEraser *eraser)
	{
		int tx1 = eraser->GetX1();
		int tx2 = eraser->GetX2();
		int ty1 = eraser->GetY1();
		int ty2 = eraser->GetY2();
		int x1 = x;				
		int y1 = y;				
		int x2 = x1 + bmp.Width();	
		int y2 = y1 + bmp.Height();	
		if (eraser->check_MovingLeft())
			return (tx2 >= x1 && tx1 <= x2 && (abs(ty2 - y2) <= 20 || (ty2 >= y2 && isOnBomb)) && abs(tx1 - x2) < 5);
		else if (eraser->check_MovingRight()) {
			return  (tx2 >= x1 &&  tx1 <= x2 && (abs(ty2 - y2) <= 20 || (ty2 >= y2 && isOnBomb)) && abs(tx2 - x1) < 5);
		}
		else
			return false;
	}
	bool Bomb::isMoving() {
		return (isMovingRight || isMovingLeft);
	}
	bool Bomb::IsBombing() {
		return isBombing ;
	}
	bool Bomb::HitBomb(CEraser *eraser)
	{ 
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Bomb::HitBomb(Bomb *bomb)
	{
		int diffx = (bomb->GetX2() - bomb->GetX1())/2;
		int diffy = (bomb->GetY2() - bomb->GetY1())/2;

		int bx = bomb->GetX1() + diffx;
		int by = bomb->GetY1() + diffy;
		int bx2 = x + diffx;
		int by2 = y + diffy;
		return (abs(bx-bx2)< 10 && abs(by - by2) <10);
	}
	bool Bomb::checkOnBomb(Bomb *bomb) 
	{
		int tx1 = bomb->GetX1();
		int tx2 = bomb->GetX2();
		int ty1 = bomb->GetY1();
		int ty2 = bomb->GetY2();
		int x1 = x;
		int y1 = y;
		int x2 = x1 + bmp.Width();
		int y2 = y1 + bmp.Height();
		return (tx2 >= x1 && tx1 <= x2 && ty1<= y1 && abs(ty1-y1)<= bmp.Height());
	}
	void Bomb::setIsOnBomb(bool flag)
	{
		isOnBomb = flag;
	}
	bool Bomb::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x ;				// 球的左上角x座標
		int y1 = y ;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標 
									// 檢測球的矩形與參數矩形是否有交集
		return (tx2 >= x1 && tx1 <= x2  && abs(ty2-y1)<=20);
	}

	bool Bomb::IsAlive()
	{
		return is_alive;
	}
	
	void Bomb::LoadBitmap()
	{
		bmp.AddBitmap(IDB_Bomb1, RGB(34, 177, 76));			// 載入球的圖形
		bmp.AddBitmap(IDB_Bomb2, RGB(34, 177, 76));				
		bmp.AddBitmap(IDB_Bomb3, RGB(34, 177, 76));		
		bmpBombing.AddBitmap(IDB_Bombfire, RGB(34, 177, 76));
		bmp.SetDelayCount(30);
		
	}

	void Bomb::OnMove(CEraser *eraser, CGameMap *m)
	{
		bmp.OnMove();
		const int STEP_SIZE = 15;
		const int landing_size = 10;
		if (!is_alive) {
			isMovingLeft = false;
			isMovingRight = false;
		}
		if (m->ScreenX(x) >= 640 || m->ScreenX(x) <= 0)
		{
			is_alive = false;
			isMovingLeft = false;
			isMovingRight = false;

		}
		if (is_alive && isMovingLeft)
		{
			if (m->IsEmpty(x- STEP_SIZE, y + bmp.Height())) {
				x -= STEP_SIZE;
			}
			else {
				isMovingLeft = false;
				is_alive = false;
				isBombing = true;
				CAudio::Instance()->Play(3, false);
			}
		}
		else if (is_alive && isMovingRight)
		{
			if (m->IsEmpty(x+ STEP_SIZE+ bmp.Width(), y + bmp.Height())) {
				x += STEP_SIZE;
			}
			else {
				isMovingRight = false;
				is_alive = false;
				isBombing = true;
				CAudio::Instance()->Play(3, false);
			}
		}
		else if (m->IsEmpty(x, y + bmp.Height() + landing_size) && !isOnBomb && !isBombing && !m->IsPipe(x + bmp.Width()/2,y + bmp.Height()) )
				y += landing_size;
	}	
	void Bomb::SetIsAlive(bool alive)
	{
		is_alive = alive;
		if(!alive)
			CAudio::Instance()->Play(3, false);
	}

	void Bomb::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Bomb::OnShow(CGameMap *m)
	{
		if (is_alive)
		{
			bombTimeCounter--;
			if (bombTimeCounter < 0)
			{
				is_alive = false;
				isBombing = true;
				bombTimeCounter = 30 * 3;
				CAudio::Instance()->Play(3, false);
			}
			else
			{
				bmp.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				bmp.OnShow();
			}
		}
		else {
			bombTimeCounter = 30 * 3;
		}
		if (isBombing) {
			bombingTimeCounter--;
			if (bombingTimeCounter < 0)
			{
				isBombing = false;
				bombingTimeCounter = 15 * 1;
			}
			else
			{
				bmpBombing.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				bmpBombing.OnShow();
			}
		}

	}
	void Bomb::SetBomb(bool flag)
	{
		is_putBomb = flag;
	}
	void Bomb::setBombAnimation()
	{
		bmp.Reset();
	}
	void Bomb::setIsBombing(bool flag) 
	{
		isBombing = flag;
	}
}