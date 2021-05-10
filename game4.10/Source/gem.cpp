#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gem.h"
#include "gameMap.h"

namespace game_framework {

	Gem::Gem()
	{
		is_alive = true;
		isShowNumGem = false;
		x = y =  0;
		numberOfGem = 0;
		showNumGemCounter = 30 * 3;
	}
	Gem::~Gem() {

	}
	void Gem::numGemAdd()
	{
		numberOfGem++;
	}

	bool Gem::HitChicken(CEraser *eraser)
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Gem::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x ;				
		int y1 = y ;			
		int x2 = x1 + gem_bitmap.Width();	
		int y2 = y1 + gem_bitmap.Height();	
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Gem::IsAlive()
	{
		return is_alive;
	}

	void Gem::LoadBitmap()
	{
		gem_bitmap.LoadBitmap(IDB_GEM, RGB(34, 177, 76));			// 載入球的圖形
		gemLeft.LoadBitmap(IDB_GEMLEFT, RGB(34, 177, 76));
	}
	void Gem::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Gem::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void Gem::setShowNumGem(bool flag)
	{
		isShowNumGem = flag;
	}
	void Gem::OnShow(CGameMap *m)
	{
		if (is_alive) {
			gem_bitmap.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			gem_bitmap.ShowBitmap();
		}
		if(isShowNumGem)
		{
			gemLeft.SetTopLeft(650, 20);
			gemLeft.ShowBitmap();
			showNumGemCounter--;
			if(showNumGemCounter < 0)
			{
				isShowNumGem = false;
				showNumGemCounter = 30 * 3;
			}
		}

	}
}