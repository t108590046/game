#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"
#include "Rock.h"
#include "Bomb.h"
namespace game_framework {
	Rock::Rock()
	{
		isOpen  = false;
		x = y = rockType = WhichMap = 0;
	}
	int Rock::GetX1()
	{
		return x;
	}
	int Rock::GetY1()
	{
		return y;
	}
	int Rock::GetX2()
	{
		return x + rock[rockType].Width();
	}
	int Rock::GetY2()
	{
		return y + rock[rockType].Height();
	}
	int Rock::returnType()
	{
		return rockType;
	}
	void Rock::openRock(CGameMap *m) {
		int x1 = x;
		int y1 = y;
		int x2 = x1 + rock[rockType].Width();
		int y2 = y1 + rock[rockType].Height();
		if (WhichMap == 0)
			m->beAir(x1, y1, x2, y2);
		else if (WhichMap == 1)
			m->beLittleMovingDown(x1, y1, x2, y2);
		else
			m->beLittleMoving2(x1, y1, x2, y2);
	}
	bool Rock::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + rock[rockType].Width();
		int y2 = y1 + rock[rockType].Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Rock::isOpenRock()
	{
		return isOpen;
	}
	void Rock::LoadBitmap()
	{
		rock[0].LoadBitmap(IDB_ROCK, RGB(34, 177, 76));
		rock[1].LoadBitmap(IDB_ROCK2, RGB(34, 177, 76));
		rock[2].LoadBitmap(IDB_ROCK3, RGB(34, 177, 76));
		rock[3].LoadBitmap(IDB_ROCK4, RGB(34, 177, 76));
		rock[4].LoadBitmap(IDB_ROCK5, RGB(34, 177, 76));
	}
	void Rock::setIsOpenRock(bool flag)
	{
		isOpen = flag;
	}
	void Rock::SetXY(int beWhichMap,int type,int nx, int ny)
	{
		x = nx; y = ny;
		rockType = type;
		WhichMap = beWhichMap;
	}
	void Rock::OnShow(CGameMap *m)
	{
		if (!isOpen)
		{
			rock[rockType].SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			rock[rockType].ShowBitmap();
		}
	}
}