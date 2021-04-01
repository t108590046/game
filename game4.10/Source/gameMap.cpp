#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gameMap.h"

namespace game_framework {
	CGameMap::CGameMap() :sx(0), sy(0), MW(32), MH(32)
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		int map_init[15][25] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1} };
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 25; j++) {
				map[i][j] = map_init[i][j];
			}
		}
	}
	void CGameMap::LoadBitmap() {
		blue.LoadBitmap(IDB_BLUE);
		green.LoadBitmap(IDB_GREEN);
		yellow.LoadBitmap(IDB_YELLOW);
	}
	void CGameMap::OnShow() {
		for (int i = 0; i <25; i++) {
			for (int j = 0; j < 15; j++) {
				int x = i * MW - sx;
				int y = j * MH - sy;
				switch (map[j][i]) {
				case 0:
					blue.SetTopLeft(x, y);
					blue.ShowBitmap();
					break;
				case 1:
					yellow.SetTopLeft(x, y);
					yellow.ShowBitmap();
					break;
				case 2:
					green.SetTopLeft(x, y);
					green.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
	}
	int CGameMap::ScreenX(int x) {//x為地圖的點座標
		return (x - sx);			//回傳螢幕的點座標
	}

	int CGameMap::ScreenY(int y) {//y為地圖的點座標
		return (y - sy);			//回傳螢幕的點座標
	}

	bool CGameMap::IsEmpty(int x, int y) {
		int gx = x / MW;		//地圖格座標
		int gy = y / MH;
		return ((map[gy][gx] == 1 ) && y <= 642 && y >= 0);  // 設定1為空  
	}
	void CGameMap::OnMove() {
		const int STEP_SIZE = 8;
		if (isMovingLeft)
			sx -= STEP_SIZE;
		if (isMovingRight)
			sx += STEP_SIZE;
		if (isMovingUp)
			sy -= STEP_SIZE;
		if (isMovingDown)
			sy += STEP_SIZE;
	}
	void CGameMap::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CGameMap::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CGameMap::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CGameMap::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

}