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
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Bomb: Ball class
	/////////////////////////////////////////////////////////////////////////////
	
	Bomb::Bomb()
	{
		is_alive = is_putBomb = isMovingLeft = isMovingRight = isBombing = false;		
		x = y = 0;
		bombTimeCounter = 35 * 2;
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
			int tx1 = door->GetX1();
			int tx2 = door->GetX2();
			int ty1 = door->GetY1();
			int ty2 = door->GetY2();
			int x1 = x;
			int y1 = y;
			int x2 = x1 + bmpBombing.Width();
			int y2 = y1 + bmpBombing.Height();
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
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y2);
	}
	
	bool Bomb::HitBomb(CEraser *eraser)
	{ 
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Bomb::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x ;				// 球的左上角x座標
		int y1 = y ;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
									// 檢測球的矩形與參數矩形是否有交集
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
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
		bmp.SetDelayCount(25);
	}

	void Bomb::OnMove(CEraser *eraser, CGameMap *m)
	{

		bmp.OnMove();
		const int STEP_SIZE = 15;
		if (!is_alive)
			return;
		if (m->ScreenX(x) >= 760 || m->ScreenX(x) <= 0)
		{
			is_alive = false;
			isMovingLeft = false;
			isMovingRight = false;

		}
		if (is_alive && isMovingLeft)
		{
			if (m->IsEmpty(x, y)) {
				x -= STEP_SIZE;
			}
			else {
				isMovingLeft = false;
				is_alive = false;
				isBombing = true;
			}
		}
		else if (is_alive && isMovingRight)
		{
			if (m->IsEmpty(x+ STEP_SIZE+ bmp.Width(), y)) {
				x += STEP_SIZE;
			}
			else {
				isMovingRight = false;
				is_alive = false;
				isBombing = true;
			}
		}
		
	}	
	void Bomb::SetIsAlive(bool alive)
	{
		is_alive = alive;
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
			if(bombTimeCounter < 0)
			{
				is_alive = false;
				isBombing = true;
				bombTimeCounter = 35 * 2;
			}
			else 
			{
				bmp.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				bmp.OnShow();
			}
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
}