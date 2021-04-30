#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gameMap.h"
#include "Bomb.h"
#include "CEraser.h"
namespace game_framework {
	CGameMap::CGameMap() :sx(0), sy(200), MW(38), MH(21)
	{
		//0障礙物 1空氣 2視角水平小移動 3 視角水平移動 4視角右下或左上移動 5視角上下小移動
		NowShowStage = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isMovingLeftL = isMovingRightL = isMovingUpL = isMovingDownL = upMoreThanRight = false;
		int map_init[30][80] = {
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,5,5,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,4,5,5,5,5,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,1,1,1,1,1,1,1,1,4,5,5,5,5,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,1,1,1,1,1,1,1,1,4,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

		};
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 80; j++) {
				map[i][j] = map_init[i][j];
			}
		}
	}
	void CGameMap::LoadBitmap() {
		blue.LoadBitmap(IDB_BLUE);
		green.LoadBitmap(IDB_GREEN);
		yellow.LoadBitmap(IDB_YELLOW);
		stage1.LoadBitmap(IDB_Stage1);
	}
	void CGameMap::OnShow() {
		int x = 0 - sx;
		int y = 0 - sy;
		stage1.SetTopLeft(x, y);
		stage1.ShowBitmap();

		/*
		for (int i = 0; i < 2; i++) {
			int x = i * 1139 - sx;
			int y =  sy;
			stage1[i].SetTopLeft(x, y);
			stage1[i].ShowBitmap();
		}
		*/
		//stage1_2.SetTopLeft(0, 0);
		//stage1_2.ShowBitmap();
		/*
		for (int i = 0; i <30; i++) {
			for (int j = 0; j < 20; j++) {
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
				case 3:
					green.SetTopLeft(x, y);
					green.ShowBitmap();
					break;

				case 4:
					green.SetTopLeft(x, y);
					green.ShowBitmap();
					break;
				case 5:
					green.SetTopLeft(x, y);
					green.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
		*/
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
		return (map[gy][gx] == 1 || map[gy][gx] == 2 || map[gy][gx] == 3 || map[gy][gx] == 4 || map[gy][gx] == 5 || map[gy][gx] == 6);  // 設定1為空  
	}
	bool CGameMap::IsLittleMove_horizontal(int x, int y) {
		int gx = x / MW;
		int gy = y / MH;
		return (map[gy][gx] == 2);
	}
	bool CGameMap::IsLittleMove_updown(int x, int y) {
		int gx = x / MW;
		int gy = y / MH;
		return (map[gy][gx] == 5);
	}

	bool CGameMap::IsChangeScreen_horizontal(int x, int y) { //轉換場景
		int gx = x / MW;
		int gy = y / MH;
		return (map[gy][gx] == 3);
	}
	bool CGameMap::IsChangeScreen_Diagonal_RDandLU(int x, int y) { //轉換場景
		int gx = x / MW;
		int gy = y / MH;
		if (map[gy][gx] == 4) {
			upMoreThanRight = false;
		}
		return (map[gy][gx] == 4);
	}
	bool CGameMap::IsChangeScreen_Diagonal_RUandLD(int x, int y) { //轉換場景
		int gx = x / MW;
		int gy = y / MH;
		if (map[gy][gx] == 6) {
			upMoreThanRight = true;
		}
		return (map[gy][gx] == 6);
	}


	void CGameMap::OnMove() {
		const int STEP_SIZE = 7;
		const int STEP_upanddown_SIZE = 2;
		const int STEP_upanddownL_SIZE = 4;
		const int CHANGVIEW_xSIZE = 10;
		const int CHANGVIEW_ySIZE = 10;
		if (isMovingLeft)
			sx -= CHANGVIEW_xSIZE;
		if (isMovingRight)
			sx += CHANGVIEW_xSIZE;
		if (isMovingUp && !upMoreThanRight)
			sy -= STEP_upanddown_SIZE;
		if (isMovingUp && upMoreThanRight)
			sy -= STEP_upanddownL_SIZE;
		if (isMovingDown && upMoreThanRight)
			sy += STEP_upanddownL_SIZE;
		if (isMovingDown && !upMoreThanRight)
			sy += STEP_upanddown_SIZE;

		if (isMovingLeftL)
			sx -= STEP_SIZE;
		if (isMovingRightL)
			sx += STEP_SIZE;
		if (isMovingUpL)
			sy -= STEP_upanddownL_SIZE;
		if (isMovingDownL)
			sy += STEP_upanddownL_SIZE - 1;

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
	void CGameMap::SetMovingDownL(bool flag)
	{
		isMovingDownL = flag;
	}

	void CGameMap::SetMovingLeftL(bool flag)
	{
		isMovingLeftL = flag;
	}

	void CGameMap::SetMovingRightL(bool flag)
	{
		isMovingRightL = flag;
	}

	void CGameMap::SetMovingUpL(bool flag)
	{
		isMovingUpL = flag;
	}

	bool CGameMap::ShowMovingDown() {
		return isMovingDown;
	}

	bool CGameMap::ShowMovingUp() {
		return isMovingUp;
	}

	bool CGameMap::ShowMovingRight() {
		return isMovingRight;
	}

	bool CGameMap::ShowMovingLeft() {
		return isMovingLeft;
	}
	void CGameMap::ScreenStopMoving(){
		isMovingDown = isMovingUp = isMovingRight = isMovingLeft = false;
	}
}
