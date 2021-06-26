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
		is_alive = true;
		isMovingLeft =  isStanding = isMovingRight= false;
		x = y = height = width = 0;
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
		return x + width;
	}
	int Enemy::GetY2()
	{
		return y + height;
	}
	int Enemy::returnType()
	{
		return typeEnemy;
	}
	bool Enemy::touchChicken(CEraser *eraser)
	{
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}
	bool Enemy::checkOnEnemy(CEraser *eraser)
	{
		int x1 = x;
		int x2 = x + width;
		int y1 = y;
		int y2 = y + height;
		int tx1 = eraser->GetX1();
		int ty1 = eraser->GetY1();
		int tx2 = eraser->GetX2();
		int ty2 = eraser->GetY2();
		return (tx2 >= x1 && tx1 <= x2 && ty1 <= y1 && abs(ty2 - y1) <= 10);
	}
	bool Enemy::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;
		int y1 = y;
		int x2 = x1 + width;
		int y2 = y1 + height;
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool Enemy::isAlive()
	{
		return is_alive;
	}
	void Enemy::OnMove(CGameMap *m)
	{
		enemy[typeEnemy][0].OnMove();
		enemy[typeEnemy][1].OnMove();
		const int STEP_SIZE = 3;
		if (isMovingRight) {
			if (m->IsEmpty(x + STEP_SIZE + width, y+ height)) {
				x += STEP_SIZE;
			}
			else {
				isMovingLeft = true;
				isMovingRight = false;
			}
		}
		if (isMovingLeft) {
			if (m->IsEmpty(x - STEP_SIZE, y + height)) {
				x -= STEP_SIZE;
			}
			else {
				isMovingLeft = false;
				isMovingRight = true;
			}
		}
	}
	void Enemy::LoadBitmap()
	{
		enemy[0][0].AddBitmap(IDB_ENEMY_01_LEFT, RGB(34, 177, 76));
		enemy[0][0].AddBitmap(IDB_ENEMY_01_LEFT_2, RGB(34, 177, 76));
		enemy[0][1].AddBitmap(IDB_ENEMY_01_RIGHT, RGB(34, 177, 76));
		enemy[0][1].AddBitmap(IDB_ENEMY_01_RIGHT_2, RGB(34, 177, 76));
		enemy[1][0].AddBitmap(IDB_ENEMY_02_01, RGB(34, 177, 76));
		enemy[1][0].AddBitmap(IDB_ENEMY_02_02, RGB(34, 177, 76));
		enemy[1][1].AddBitmap(IDB_ENEMY_02_02, RGB(34, 177, 76));
		enemy[2][0].AddBitmap(IDB_ENEMY_03_01, RGB(34, 177, 76));
		enemy[2][0].AddBitmap(IDB_ENEMY_03_02, RGB(34, 177, 76));
		enemy[2][1].AddBitmap(IDB_ENEMY_03_01, RGB(34, 177, 76));
		enemy[3][0].AddBitmap(IDB_ENEMY_04_01, RGB(34, 177, 76));
		enemy[3][0].AddBitmap(IDB_ENEMY_04_02, RGB(34, 177, 76));
		enemy[3][1].AddBitmap(IDB_ENEMY_04_01, RGB(34, 177, 76));
		enemy[4][0].AddBitmap(IDB_BAT_LEFT_1, RGB(34, 177, 76));
		enemy[4][0].AddBitmap(IDB_BAT_LEFT_2, RGB(34, 177, 76));
		enemy[4][1].AddBitmap(IDB_BAT_RIGHT_1, RGB(34, 177, 76));
		enemy[4][1].AddBitmap(IDB_BAT_RIGHT_2, RGB(34, 177, 76));
	}
	void Enemy::setIsAlive(bool flag)
	{
		is_alive = flag;
	}
	void Enemy::SetXY(int type,int nx, int ny)
	{
		if (type == 0 || type == 4)  // 會動的敵人
		{
			isMovingRight = true;
			isMovingLeft = false;
		}
		else {
			isMovingRight = false;
			isMovingLeft = false;
		}
		height = enemy[type][0].Height();
		width = enemy[type][0].Width();
		typeEnemy = type;
		x = nx; y = ny;
	}
	void Enemy::enemyTouchBomb() {
		if (isMovingLeft) {
			isMovingLeft = false;
			isMovingRight = true;
		}
		else if (isMovingRight) {
			isMovingLeft = true;
			isMovingRight = false;
		}
	}
	void Enemy::OnShow(CGameMap *m)
	{
		if (is_alive) {
			if (isMovingRight) {
				enemy[typeEnemy][1].SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				enemy[typeEnemy][1].OnShow();
			}
			else if (isMovingLeft) {
				enemy[typeEnemy][0].SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				enemy[typeEnemy][0].OnShow();
			}
			else {
				enemy[typeEnemy][0].SetTopLeft(m->ScreenX(x), m->ScreenY(y));
				enemy[typeEnemy][0].OnShow();
			}
		}
	}
}