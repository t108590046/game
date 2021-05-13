#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "Treasure.h"
#include "gameMap.h"

namespace game_framework {

	Treasure::Treasure()
	{
		is_Open = false;
		x = y = 0;
	}
	int Treasure::GetX1() {
		return x;
	}
	int Treasure::GetX2() {
		return x + treasureBmp.Width();
	}
	int Treasure::GetY1() {
		return y;
	}
	int Treasure::GetY2() {
		return y + treasureBmp.Height();
	}
	bool Treasure::touchTreasure(CEraser *eraser)
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Treasure::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + treasureBmp.Width();
		int y2 = y1 + treasureBmp.Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Treasure::isOpen()
	{
		return is_Open;
	}

	void Treasure::LoadBitmap()
	{
		treasureBmp.LoadBitmap(IDB_TREASURE, RGB(34, 177, 76));			// 載入球的圖形
	}
	void Treasure::SetIsOpen(bool alive)
	{
		is_Open = alive;
	}

	void Treasure::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void Treasure::OnShow(CGameMap *m)
	{
		if (!is_Open) {
			treasureBmp.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			treasureBmp.ShowBitmap();
		}

	}
}