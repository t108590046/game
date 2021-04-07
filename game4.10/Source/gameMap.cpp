#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gameMap.h"
#include "Bomb.h"

namespace game_framework {
	CGameMap::CGameMap() :sx(0), sy(0), MW(32), MH(32)
	{
		NowShowStage = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		int map_init[20][80] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 80; j++) {
				map[i][j] = map_init[i][j];
			}
		}
	}
	void CGameMap::LoadBitmap() {
		blue.LoadBitmap(IDB_BLUE);
		green.LoadBitmap(IDB_GREEN);
		yellow.LoadBitmap(IDB_YELLOW);
		stage1[0].LoadBitmap(IDB_Stage1_1);
		stage1[1].LoadBitmap(IDB_Stage1_2);
	}
	void CGameMap::OnShow() {
		if (isMovingRight) 
		{
			NowShowStage++;
		}
		if (isMovingLeft)
		{
			NowShowStage--;
		}
		int x = NowShowStage * 1139 - sx;
		int y = sy;
		stage1[NowShowStage].SetTopLeft(x, y);
		stage1[NowShowStage].ShowBitmap();
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
		for (int i = 0; i <80; i++) {
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
				default:
					ASSERT(0);
				}
			}
		}
		*/
	}
	int CGameMap::ScreenX(int x) {//x���a�Ϫ��I�y��
		return (x - sx);			//�^�ǿù����I�y��
	}

	int CGameMap::ScreenY(int y) {//y���a�Ϫ��I�y��
		return (y - sy);			//�^�ǿù����I�y��
	}

	bool CGameMap::IsEmpty(int x, int y) {
		int gx = x / MW;		//�a�Ϯ�y��
		int gy = y / MH;
		return (map[gy][gx] == 1 || map[gy][gx] == 2);  // �]�w1����  
	}
	bool CGameMap::IsLittleMove(int x, int y) {
		int gx = x / MW;		//�a�Ϯ�y��
		int gy = y / MH;
		return ( map[gy][gx] == 2);  // �]�w1�������n�p����  
	}

	void CGameMap::OnMove() {
		const int STEP_SIZE = 8;
		const int CHANGVIEW_xSIZE = 1139;
		const int CHANGVIEW_ySIZE = 641;
		if (isMovingLeft)
			sx -= CHANGVIEW_xSIZE;
		if (isMovingRight)
			sx += CHANGVIEW_xSIZE;
		if (isMovingUp)
			sy -= CHANGVIEW_ySIZE;
		if (isMovingDown)
			sy += CHANGVIEW_ySIZE;
		if (isMovingLeftL  && stage1[NowShowStage].Width()>1140) // �e�׶W�L�e���~�ݭn�p����
			sx -= STEP_SIZE;
		if (isMovingRightL && stage1[NowShowStage].Width() > 1140)
			sx += STEP_SIZE;
		if (isMovingUpL && stage1[NowShowStage].Height() > 642) //���׶W�L�e���~�ݭn�p����
			sy -= STEP_SIZE;
		if (isMovingDownL && stage1[NowShowStage].Height() > 642)
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

}