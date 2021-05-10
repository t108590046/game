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
		gemNumber_digits[0].LoadBitmapA(IDB_ZERO, RGB(34, 177, 76));
		gemNumber_digits[1].LoadBitmapA(IDB_ONE, RGB(34, 177, 76));
		gemNumber_digits[2].LoadBitmapA(IDB_TWO, RGB(34, 177, 76));
		gemNumber_digits[3].LoadBitmapA(IDB_THREE, RGB(34, 177, 76));
		gemNumber_digits[4].LoadBitmapA(IDB_FOUR, RGB(34, 177, 76));
		gemNumber_digits[5].LoadBitmapA(IDB_FIVE, RGB(34, 177, 76));
		gemNumber_digits[6].LoadBitmapA(IDB_SIX, RGB(34, 177, 76));
		gemNumber_digits[7].LoadBitmapA(IDB_SEVEN, RGB(34, 177, 76));
		gemNumber_digits[8].LoadBitmapA(IDB_EIGHT, RGB(34, 177, 76));
		gemNumber_digits[9].LoadBitmapA(IDB_NINE, RGB(34, 177, 76));
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
		if (flag) {
			numberOfGem++;
		}
	}
	void Gem::OnShow(CGameMap *m)
	{
		int tens = numberOfGem / 10;
		int digits = numberOfGem % 10;
		if (is_alive) {
			gem_bitmap.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			gem_bitmap.ShowBitmap();
		}
		if(isShowNumGem)
		{
			gemLeft.SetTopLeft(650, 20);
			gemLeft.ShowBitmap();
			switch (tens) {
			case 0:
				gemNumber_digits[0].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[0].ShowBitmap();
				break;
			case 1:
				gemNumber_digits[1].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[1].ShowBitmap();
				break;
			case 2:
				gemNumber_digits[2].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[2].ShowBitmap();
				break;
			case 3:
				gemNumber_digits[3].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[3].ShowBitmap();
				break;

			case 4:
				gemNumber_digits[4].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[4].ShowBitmap();
				break;
			case 5:
				gemNumber_digits[5].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[5].ShowBitmap();
				break;
			case 6:
				gemNumber_digits[6].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[6].ShowBitmap();
				break;
			case 7:
				gemNumber_digits[7].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[7].ShowBitmap();
				break;
			case 8:
				gemNumber_digits[8].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[8].ShowBitmap();
				break;
			case 9:
				gemNumber_digits[9].SetTopLeft(650 + gemLeft.Width(), 20);
				gemNumber_digits[9].ShowBitmap();
				break;
			default:
				ASSERT(0);
			}
			switch (digits) {
			case 0:
				gemNumber_digits[0].SetTopLeft(650 + gemLeft.Width()+gemNumber_digits[0].Width(), 20);
				gemNumber_digits[0].ShowBitmap();
				break;
			case 1:
				gemNumber_digits[1].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[1].ShowBitmap();
				break;
			case 2:
				gemNumber_digits[2].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[2].ShowBitmap();
				break;
			case 3:
				gemNumber_digits[3].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[3].ShowBitmap();
				break;

			case 4:
				gemNumber_digits[4].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[4].ShowBitmap();
				break;
			case 5:
				gemNumber_digits[5].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[5].ShowBitmap();
				break;
			case 6:
				gemNumber_digits[6].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[6].ShowBitmap();
				break;
			case 7:
				gemNumber_digits[7].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[7].ShowBitmap();
				break;
			case 8:
				gemNumber_digits[8].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[8].ShowBitmap();
				break;
			case 9:
				gemNumber_digits[9].SetTopLeft(650 + gemLeft.Width() + gemNumber_digits[0].Width(), 20);
				gemNumber_digits[9].ShowBitmap();
				break;
			default:
				ASSERT(0);
			}
			showNumGemCounter--;
			if(showNumGemCounter < 0)
			{
				isShowNumGem = false;
				showNumGemCounter = 30 * 3;
			}
		}

	}
}