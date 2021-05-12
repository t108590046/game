#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"
#include "woodDoor.h"
#include "Bomb.h"

namespace game_framework {

	woodDoor::woodDoor()
	{
		isOpen = false;
		x = y = 0;
	}
	int woodDoor::GetX1()
	{
		return x;
	}
	int woodDoor::GetY1()
	{
		return y;
	}
	int woodDoor::GetX2()
	{
		return x+door.Width();
	}
	int woodDoor::GetY2()
	{
		return y+door.Height();
	}


	void woodDoor::openDoor(CGameMap *m) {
		int x1 = x;
		int y1 = y;
		int x2 = x1 + door.Width();
		int y2 = y1 + door.Height();
		m->beAir(x1, y1, x2, y2);
	}
	bool woodDoor::touchDoor(Bomb *bomb)
	{
		return HitRectangle(bomb->GetX1(), bomb->GetY1(),
			bomb->GetX2(), bomb->GetY2());
	}

	bool woodDoor::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + door.Width();
		int y2 = y1 + door.Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool woodDoor::isOpenDoor()
	{
		return isOpen;
	}

	void woodDoor::LoadBitmap()
	{
		door.LoadBitmap(IDB_WOOD_DOOR, RGB(34, 177, 76));
	}
	void woodDoor::setIsOpenDoor(bool flag)
	{
		isOpen = flag;
	}
	void woodDoor::SetXY(int nx, int ny)
	{
		 x = nx; y = ny;
	}

	void woodDoor::OnShow(CGameMap *m)
	{
		if (!isOpen)
		{
			door.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			door.ShowBitmap();
		}
	}
}