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
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Bomb: Ball class
	/////////////////////////////////////////////////////////////////////////////
	
	Bomb::Bomb()
	{
		is_alive = is_putBomb = is_bePushLeft = is_bePushRight = false;
		x = y = 0;
	}
	Bomb::Bomb(int ix,int iy)
	{
		is_alive = is_putBomb = false;
		x = ix;
		y = iy;
	}
	bool Bomb::PushBomb(CEraser *eraser)
	{
		return chickenPushBomb(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Bomb::chickenPushBomb(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;				
		int y1 = y;				
		int x2 = x1 + bmp.Width();	
		int y2 = y1 + bmp.Height();	
		return(tx2 >= x1 && tx1 <= x2 && ty2 >= y2);
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
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 &&  ty1 <= y1);
	}
	
	bool Bomb::IsAlive()
	{
		return is_alive;
	}
	
	void Bomb::LoadBitmap()
	{
		bmp.AddBitmap(IDB_Bomb1, RGB(34, 177, 76));			// 載入球的圖形
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// 載入球圓心的圖形
	}

	void Bomb::OnMove(CEraser *eraser, CGameMap *m)
	{
		const int STEP_SIZE = 300;
		if (!is_alive)
			return;
		bmp.OnMove();
		if(eraser->check_MovingLeft())
		{
			if (m->IsEmpty(x - STEP_SIZE, y)) 
			{
				x -= STEP_SIZE;
			}

		}
		else if (eraser->check_MovingRight())
		{
			if (m->IsEmpty(x + bmp.Width() + STEP_SIZE, y))
			{
				x += STEP_SIZE;
			}
		}

		/*
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// 計算球向對於圓心的位移量dx, dy
			//
			const int STEPS = 18;
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}*/
	}
	/*
	void Bomb::SetDelay(int d)
	{
		delay = d;
	}
*/
	
	void Bomb::SetIsAlive(bool alive)
	{
		is_alive = alive;
		if (alive == true)
		{
			start = clock();
		}
	}

	void Bomb::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Bomb::OnShow(CGameMap *m)
	{
		if (is_alive)
		{
			finish = clock();
			if((double)(finish - start) / CLOCKS_PER_SEC >= 3)
			{
				is_alive = false;
			}
			else 
			{
				bmp.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				bmp.OnShow();
			}
		}

		/*
		if (is_alive) {
			bmp.SetTopLeft(x + dx, y + dy);
			bmp.ShowBitmap();
			bmp_center.SetTopLeft(x, y);
			bmp_center.ShowBitmap();
		}*/
	}
	void Bomb::SetBomb(bool flag)
	{
		is_putBomb = flag;
	}
	
}