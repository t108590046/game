#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"
#include "doorButton.h"
#include "Bomb.h"
namespace game_framework {

	Button::Button()
	{
		isTouched = false;
		x = y = 0;
		btnDirection = 0;
	}

	bool Button::touchButton(CEraser *eraser)
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Button::touchButton(Bomb *bomb)
	{
		return HitRectangle(bomb->GetX1(), bomb->GetY1(),
			bomb->GetX2(), bomb->GetY2());
	}

	bool Button::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + button[btnDirection].Width();
		int y2 = y1 + button[btnDirection].Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Button::IsTouched()
	{
		return isTouched;
	}

	void Button::LoadBitmap()
	{
		button[0].LoadBitmap(IDB_BUTTON, RGB(34, 177, 76));
		button[1].LoadBitmap(IDB_BUTTON_LEFT, RGB(34, 177, 76));
		button[2].LoadBitmap(IDB_BUTTON_RIGHT, RGB(34, 177, 76));
		button[3].LoadBitmap(IDB_BUTTON_DOWN, RGB(34, 177, 76));
	}
	void Button::SetIsTouched(bool touched)
	{
		isTouched = touched;
	}
	void Button::SetXY(int direction,int nx, int ny)
	{
		btnDirection = direction; x = nx; y = ny;
	}

	void Button::OnShow(CGameMap *m)
	{	
		if (!isTouched) 
		{
			button[btnDirection].SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			button[btnDirection].ShowBitmap();
		}
	}
}