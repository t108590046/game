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
		isOpen = false;
		x = y = 0;
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
		return x + rock.Width();
	}
	int Rock::GetY2()
	{
		return y + rock.Height();
	}


	void Rock::openRock(CGameMap *m) {
		int x1 = x;
		int y1 = y;
		int x2 = x1 + rock.Width();
		int y2 = y1 + rock.Height();
		m->beAir(x1, y1, x2, y2);
	}
	bool Rock::touchRock(Bomb *bomb)
	{
		return HitRectangle(bomb->GetX1(), bomb->GetY1(),
			bomb->GetX2(), bomb->GetY2());
	}

	bool Rock::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + rock.Width();
		int y2 = y1 + rock.Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Rock::isOpenRock()
	{
		return isOpen;
	}

	void Rock::LoadBitmap()
	{
		rock.LoadBitmap(IDB_ROCK, RGB(34, 177, 76));
	}
	void Rock::setIsOpenRock(bool flag)
	{
		isOpen = flag;
	}
	void Rock::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Rock::OnShow(CGameMap *m)
	{
		if (!isOpen)
		{
			rock.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			rock.ShowBitmap();
		}
	}
}