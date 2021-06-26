#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"
#include "Hammer.h"
#include "Bomb.h"
namespace game_framework {
	Hammer::Hammer()
	{
		x = y = delay = 0;
	}
	int Hammer::GetX1()
	{
		return x;
	}
	int Hammer::GetY1()
	{
		return y;
	}
	int Hammer::GetX2()
	{
		return x + hammer.Width();
	}
	int Hammer::GetY2()
	{
		return y + hammer.Height();
	}
	void Hammer::touchChicken(CEraser *eraser)
	{
		if (eraser->check_MovingLeft()) {
			if (HitRectangle(eraser->GetX1() - 10, (eraser->GetY1() + eraser->GetY2()) / 2,
				eraser->GetX2() + 5, eraser->GetY2())) {
				eraser->SetMovingLeft(false);
			}
		}
		if (eraser->check_MovingRight()) {
			if (HitRectangle(eraser->GetX1() - 5, (eraser->GetY1() + eraser->GetY2()) / 2,
				eraser->GetX2() + 10, eraser->GetY2())) {
				eraser->SetMovingRight(false);
			}
		}
	}
	bool Hammer::hammerTouchBomb(Bomb *bomb)
	{
		return HitRectangle(bomb->GetX1(), bomb->GetY1(),
			bomb->GetX2(), bomb->GetY2());
	}
	bool Hammer::pressChicken(CEraser *eraser) 
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Hammer::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + 10;
		int y1 = y;
		int x2 = x1 + hammer.Width() -10;
		int y2 = y1 + hammer.Height()-10;
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	void Hammer::OnMove()
	{
		if(delay>0)
		delay--;
		if (delay <= 0) {
			hammer.OnMove();
			
		}
	}
	void Hammer::LoadBitmap()
	{
		hammer.AddBitmap(IDB_HAMMER1, RGB(34, 177, 76));
		hammer.AddBitmap(IDB_HAMMER2, RGB(34, 177, 76));
		hammer.SetDelayCount(60);
	}
	void Hammer::SetXY(int inputdelay, int nx, int ny)
	{
		x = nx; y = ny;
		delay = inputdelay*30;
		hammer.Reset();
	}
	void Hammer::OnShow(CGameMap *m)
	{
		hammer.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
		hammer.OnShow();
	}
}