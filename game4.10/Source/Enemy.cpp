#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "gameMap.h"
#include "Enemy.h"
#include "Bomb.h"

namespace game_framework {

	Enemy::Enemy()
	{
		is_alive = false;
		x = y = 0;
		typeEnemy = 0;
	}
	int Enemy::GetX1()
	{
		return x;
	}
	int Enemy::GetY1()
	{
		return y;
	}
	int Enemy::GetX2()
	{
		return x + enemy[typeEnemy][0].Width();
	}
	int Enemy::GetY2()
	{
		return y + enemy[typeEnemy][0].Height();
	}

	bool Enemy::touchChicken(CEraser *eraser)
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool Enemy::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + enemy[typeEnemy][0].Width();
		int y2 = y1 + enemy[typeEnemy][0].Height();
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool Enemy::isAlive()
	{
		return is_alive;
	}
	void Enemy::OnMove(CGameMap *m)
	{
		const int STEP_SIZE = 5;
		if (m->IsEmpty(x + 5, y)) {
			x += STEP_SIZE;
		}
	}
	void Enemy::LoadBitmap()
	{
		enemy[0][0].AddBitmap(IDB_ENEMY_01_LEFT, RGB(34, 177, 76));
		enemy[0][1].AddBitmap(IDB_ENEMY_01_RIGHT, RGB(34, 177, 76));

	}
	void Enemy::setIsAlive(bool flag)
	{
		is_alive = flag;
	}
	void Enemy::SetXY(int type,int nx, int ny)
	{
		typeEnemy = type;
		x = nx; y = ny;
	}

	void Enemy::OnShow(CGameMap *m)
	{

	}
}