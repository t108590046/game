#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"
#include "door.h"

namespace game_framework {

	Door::Door()
	{
		isOpen = false;
		x = y = 0;
		doorType = 0;
	}

	bool Door::touchDoor(CEraser *eraser)
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Door::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + door[doorType].Width();
		int y2 = y1 + door[doorType].Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Door::isOpenDoor()
	{
		return isOpen;
	}

	void Door::LoadBitmap()
	{
		door[0].LoadBitmap(IDB_DOOR_TYPE_1, RGB(34, 177, 76));
	}
	void Door::setIsOpenDoor(bool flag)
	{
		isOpen = flag;
	}
	void Door::SetXY(int type, int nx, int ny)
	{
		doorType = type; x = nx; y = ny;
	}

	void Door::OnShow(CGameMap *m)
	{
		if (!isOpen)
		{
			door[doorType].SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			door[doorType].ShowBitmap();
		}
	}
}