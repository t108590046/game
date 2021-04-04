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

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Bomb: Ball class
	/////////////////////////////////////////////////////////////////////////////
	
	Bomb::Bomb()
	{
		is_alive = is_putBomb= false;
		x = y = 0;
	}
	Bomb::Bomb(int ix,int iy)
	{
		is_alive = is_putBomb = false;
		x = ix;
		y = iy;
	}

	
	bool Bomb::HitBomb(CEraser *eraser)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Bomb::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x ;				// �y�����W��x�y��
		int y1 = y ;				// �y�����W��y�y��
		int x2 = x1 + bmp.Width();	// �y���k�U��x�y��
		int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	
	bool Bomb::IsAlive()
	{
		return is_alive;
	}
	
	void Bomb::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_Bomb1, RGB(34, 177, 76));			// ���J�y���ϧ�
		//bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0));	// ���J�y��ߪ��ϧ�
	}

	void Bomb::OnMove(CEraser *eraser)
	{
		/*
		if (!is_alive)
			return;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;
			//
			// �p��y�V����ߪ��첾�qdx, dy
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
				bmp.ShowBitmap();
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