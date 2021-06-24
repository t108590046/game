/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}
void CGameStateInit::OnBeginState()
{
	

}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	//logo.LoadBitmap(IDB_BACKGROUND);
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
	current = 0;
	start[0].LoadBitmap(IDB_start0, RGB(0, 0, 0));
	start[1].LoadBitmap(IDB_start1, RGB(0, 0, 0));
	start[2].LoadBitmap(IDB_start2, RGB(0, 0, 0));
	start[3].LoadBitmap(IDB_start3, RGB(0, 0, 0));
	start[4].LoadBitmap(IDB_ABOUT, RGB(0, 0, 0));
	start[5].LoadBitmap(IDB_operation, RGB(0, 0, 0));
	start[6].LoadBitmap(IDB_operation_show, RGB(0, 0, 0));

	CAudio::Instance()->Load(AUDIO_init, "sounds\\initBackground.mp3");	// ���J�I���n��
	CAudio::Instance()->Play(AUDIO_init, true);
	CAudio::Instance()->Load(AUDIO_MENU, "sounds\\Menu.mp3");   // ���J��沾���n��

}


void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ENTER = 13;
	const char KEY_UpArrow = 38;
	const char KEY_DownArrow = 40;
	if (nChar >= 0 && current == 0) {						//��l�e���}�l
		current = 1;
	}
	else if (current == 1 && nChar == KEY_ENTER)			//�}�l�C��
	{
		CAudio::Instance()->Stop(AUDIO_init);
		GotoGameState(GAME_STATE_RUN);
	}
	else if (current == 3 && nChar == KEY_ENTER)			//�h�X�C��
	{
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}
	else if (current == 2 && nChar == KEY_ENTER)			//about
	{
		current = 4;
	}
	else if (current == 4 && nChar >= 0)					//���about
	{
		current = 2;
	}
	else if (current == 5 && nChar == KEY_ENTER)			//�ާ@����
	{
		current = 6;
	}
	else if (current == 6 && nChar >= 0)					//��ܾާ@����
	{
		current = 5;
	}
	//-------------�W�U���ʿ��----------------------------
	if (nChar == KEY_UpArrow)								
	{
		CAudio::Instance()->Play(AUDIO_MENU, false);
		if (current == 1) {
			current = 5;
		}
		else if (current == 2) {
			current = 1;
		}
		else if (current == 3) {
			current = 2;
		}
		else if (current == 5) {
			current = 3;
		}
	}
	if (nChar == KEY_DownArrow)
	{
		CAudio::Instance()->Play(AUDIO_MENU, false);
		if (current == 1) {
			current = 2;
		}
		else if (current == 2) {
			current = 3;
		}
		else if (current == 3) {
			current = 5;
		}
		else if (current == 5) {
			current = 1;
		}

	}

}
void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{	

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CAudio::Instance()->Stop(AUDIO_init);
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	start[current].SetTopLeft(0, 0);
	start[current].ShowBitmap();
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	//�����᤭���s�}�l
	counter--;
	if (counter < 0) {
		GotoGameState(GAME_STATE_RUN);
	}
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5;
	CAudio::Instance()->Play(AUDIO_GAMEOVER, false);
}

void CGameStateOver::OnInit()
{
	gameOver.LoadBitmap(IDB_GAMEOVER);
	CAudio::Instance()->Load(AUDIO_GAMEOVER, "sounds\\GameOver.mp3");
}

void CGameStateOver::OnShow()
{
	gameOver.SetTopLeft(0, 0);
	gameOver.ShowBitmap();
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
	: CGameState(g), NUMBOMBS(10), NUMGEM(30), NUMBTN(10), NUM_WOOD_DOOR(10), NUMTREASURE(10), NUMROCK(41), NUMENEMY(20), NUMHAMMER(15)
{
	nowMap = tempNowMap= 0;
	menuState = 0;
	numberBomb = 0;
	bomb = new Bomb[NUMBOMBS];
	gem = new Gem[NUMGEM];
	btn = new Button[NUMBTN];
	door = new Door[NUMBTN];
	wooddoor = new woodDoor[NUM_WOOD_DOOR];
	treasure = new Treasure[NUMTREASURE];
	rock = new Rock[NUMROCK];
	enemy = new Enemy[NUMENEMY];
	hammer = new Hammer[NUMHAMMER];
	nowTotalGem = 0;
	CHEAT_MODE = IS_IN_CHANGE_HEART_MAP = isChange = isDie = isInMenuState =false;
	reBrithCounter = 30 * 1;
}

CGameStateRun::~CGameStateRun()
{
	delete [] bomb;
	delete[] gem;
	delete[] btn;
	delete[] door;
	delete[] wooddoor;
	delete[] treasure;
	delete[] rock;
	delete[] enemy;
	delete[] hammer;
}

void CGameStateRun::OnBeginState()
{
	//�C�@��������ƶq
	menuState = 0;
	NUMGEM = numberOfGemEveryMap[nowMap];
	NUMBTN = numberOfBtnEveryMap[nowMap];
	NUM_WOOD_DOOR = numberOfWoodDoorEveryMap[nowMap];
	NUMTREASURE = numberOfTreasureEveryMap[nowMap];
	NUMROCK = numberOfRockEveryMap[nowMap];
	NUMENEMY = numberOfEnemyEveryMap[nowMap];
	NUMHAMMER = numberOfHammerEveryMap[nowMap];
	//�Ҧ����_�۪��y��
	int allGemXY[3][13][2] = { {{1100,580},{1585,560}, {1718,528},{2045,460},{2320,430},{2320,330},{2320,230},{2930,665},{2930,615},{2665,335},{2690,335},{2715,335}},
							   {{1215,1070},{1285,1070},{2415,876},{2415,776},{2025,802},{2025,702},{2025,602},{1685,330},{1530,330},{1335,330}},
							   {{485,694},{290,694},{1540,248},{1540,348},{1440,248},{1440,348},{1215,248},{1215,348},{1115,248},{1115,348},{3065,1210},{3065,1110},{3065,1310}}
	};
	for (int i = 0; i < NUMGEM; i++) {
		gem[i].SetXY(allGemXY[nowMap][i][0], allGemXY[nowMap][i][1]);
		gem[i].SetIsAlive(true);
		gem[i].updatePriceOfHeart(priceOfGemsEveryMap[nowMap]);
	}
	//�Ҧ������s���y��{��V,x,y}
	int allBtnXY[3][3][3] = { {{0,50,545},{1,2605,670},{3,2670,95}},
							  {{0,1230,1130},{1,2355,1080},{1,2435,575}},
							  {{4,380,590},{3,4030,1505}}
	};
	for (int i = 0; i < NUMBTN; i++) {
		btn[i].SetIsTouched(false);
		btn[i].SetXY(allBtnXY[nowMap][i][0],allBtnXY[nowMap][i][1], allBtnXY[nowMap][i][2]);
	}
	int allDoorXY[3][3][3] = { {{0,565,450},{0,2625,840},{1,2672,266}},
								{{0,1515,1040},{0,2270,930},{0,1965,536}},
								{{0,735,800},{0,4310,1680}}
	};
	for (int i = 0; i < NUMBTN; i++) {
		door[i].SetXY(allDoorXY[nowMap][i][0], allDoorXY[nowMap][i][1], allDoorXY[nowMap][i][2]);
		door[i].setIsOpenDoor(false);
	}
	//�Ҧ�������y��
	int allWoodDoor[3][2] = { {955,445},
							  {1290,515} };
	for (int i = 0; i < NUM_WOOD_DOOR; i++)
	{
		wooddoor[i].setIsOpenDoor(false);
		wooddoor[i].SetXY(allWoodDoor[i][0], allWoodDoor[i][1]);
	}
	//�Ҧ��_�ê��y��
	int allTreasure[3][1][2] = { {{1880,695}},
								  {{240,75}}
	};
	for (int i = 0; i < NUMTREASURE; i++) {
		treasure[i].SetXY(allTreasure[nowMap][i][0], allTreasure[nowMap][i][1]);
		treasure[i].SetIsOpen(false);
	}
	//�Ҧ����Y���y�� {�Q�P�����ܦ����a������,���Y����,x,y}
	int allRock[3][41][4] = { {{0,0,2155,665},{0,0,2155,598}},
							 {{0,1,2657,962},{0,3,2633,996},{0,3,2609,996},{0,3,2585,996},{0,3,2633,962},{0,4,2609,962},{0,3,2585,962},{0,2,800,1080},{0,2,720,1080},{1,3,364,706},{1,3,340,706},{1,2,289,670},{1,2,340,636},{1,3,313,636},{1,3,289,636},{1,3,398,636},{1,4,423,636},{1,3,398,602},{1,3,423,602},{1,3,374,602},{1,3,289,602},{1,3,374,568},{1,2,315,568},{1,3,289,568},{1,2,231,605},{1,4,260,568},{1,3,231,500},{1,3,260,500},{1,3,231,534},{1,3,260,534},{1,2,289,501},{1,3,345,500},{1,3,374,500},{1,3,345,534},{1,3,374,534},{1,3,398,500},{1,3,423,500},{1,1,398,534},{1,3,231,568}}
							,{{0,1,2125,1230},{0,2,2178,1230},{0,3,2125,1298},{0,3,2149,1298},{0,4,2125,1332},{0,2,3205,1862},{0,2,3340,1862},{0,2,3475,1862},{2,2,3575,2344},{2,1,3628,2344},{2,1,3681,2344},{2,1,3734,2344},{2,2,3787,2344},{2,2,3628,2274},{2,2,3734,2274},{2,2,3681,2274},{2,2,3681,2204}}
	};
	for (int i = 0; i < NUMROCK; i++) {
		rock[i].SetXY(allRock[nowMap][i][0],allRock[nowMap][i][1], allRock[nowMap][i][2], allRock[nowMap][i][3]);
		rock[i].setIsOpenRock(false);
	}
	//�Ҧ��ĤH���y�� {�ĤH����,x,y}
	int allEnemy[3][20][3] = { {{0,2000,672},{1,2525,685},{2,2220,830},{3,2500,870},{2,2690,190},{4,2810,597}},
							  {{4,145,250},{2,1535,565},{3,1410,565},{0,1715,300}},
							  {{0,380,660},{4,1805,351},{4,1805,301},{4,1805,249},{4,900,351},{4,900,301},{4,900,249},{4,1095,716},{4,2340,1320},{4,2435,1320},{4,2250,1320},{4,2940,1245},{4,2970,1245},{4,3000,1245},{4,3030,1245},{2,3205,1783},{2,3340,1783},{2,3475,1783},{4,3940,1781},{4,3940,1581}}
	};
	for (int i = 0; i < NUMENEMY; i++) {
		enemy[i].SetXY(allEnemy[nowMap][i][0], allEnemy[nowMap][i][1], allEnemy[nowMap][i][2]);
		enemy[i].setIsAlive(true);
	}
	//�Ҧ��l�l���y�� {����,x,y}
	int allHammer[3][15][3] = { {},{{0,1100,965},{0,1153,965},{1,1340,965},{1,1393,965},{2,1446,965},{2,1552,965},{2,1605,965},{3,1658,965},{3,1711,965},{0,2280,680},{1,2227,680},{2,2174,680},{2,2227,470},{3,2280,470},{2,2333,470}},{}

	};
	for (int i = 0; i < NUMHAMMER; i++) {
		hammer[i].SetXY(allHammer[nowMap][i][0],allHammer[nowMap][i][1], allHammer[nowMap][i][2]);
	}
	//��l�Ƥp���P�a��
	eraser.Initialize(nowMap);
	gamemap.Initialize(nowMap);
	CAudio::Instance()->Play(AUDIO_BAKCGROUND, true);		
	for (int i = 0; i < NUMBOMBS; i++)
	{
		if (bomb[i].IsAlive())
			bomb[i].SetIsAlive(false);
	}

}


void CGameStateRun::OnMove()							// ���ʹC������
{

	if (!isInMenuState) {//�}���ɹC���Ȱ�
		if (isDie) {                    //����ˮ`��Ȱ��@��
			reBrithCounter--;
			if (reBrithCounter < 0) {
				isDie = false;
				reBrithCounter = 30 * 1;
			}
		}
		else {
			//�P�_�p���O�_�I��y��
			if (gamemap.touchThorn(eraser.GetX1(), eraser.GetY1()) || gamemap.touchThorn(eraser.GetX2(), eraser.GetY1()) || gamemap.touchThorn(eraser.GetX1(), eraser.GetY2()) || gamemap.touchThorn(eraser.GetX2(), eraser.GetY2())) {
				ReBrith();
			}
			// �P�_�p���O�_�I��l�l
			for (int i = 0; i < NUMHAMMER; i++) {
				hammer[i].OnMove();
				if (hammer[i].pressChicken(&eraser)) {
					ReBrith();
				}
				hammer[i].touchChicken(&eraser);
			}
			//�P�_���O�_�I���_��
			for (int i = 0; i < NUMGEM; i++)
			{
				if (gem[i].IsAlive() && gem[i].HitChicken(&eraser))
				{
					gem[i].SetIsAlive(false);
					gem[i].setShowNumGem(true);
					nowTotalGem++;
					eraser.setShowHeart(true);
					CAudio::Instance()->Play(AUDIO_GETGEM, false);
				}
				gem[i].getGem(nowTotalGem);
			}
				//�P�_�p����b�ĤH�Y�W���_��
			for (int i = 0; i < NUMENEMY; i++) {
				enemy[i].OnMove(&gamemap);
				if (enemy[i].isAlive() && enemy[i].checkOnEnemy(&eraser) && !eraser.check_inPipe()) {
					enemy[i].setIsAlive(false);
					eraser.setChickenJumping(true);
					CAudio::Instance()->Play(AUDIO_KILLENEMY, false);
				}
				// �ĤH�I��p��
				if (enemy[i].isAlive() && enemy[i].touchChicken(&eraser)) {
					ReBrith();
				}
			}
			// �P�_�p���O�_��b���u�W��
			for (int i = 0; i < NUMBOMBS; i++) {
				if (bomb[i].IsAlive()) {
					if (!bomb[i].HitBomb(&eraser)) {
						eraser.SetStepOnBomb(false);
					}
				}
				if (bomb[i].IsBombing()) {
					if (!bomb[i].HitBomb(&eraser)) {
						eraser.SetStepOnBomb(false);
					}
				}
			}
			for (int i = 0; i < NUMBOMBS; i++)
			{
				if (bomb[i].IsAlive()) {
					if (bomb[i].HitBomb(&eraser)) {
						eraser.SetStepOnBomb(true);
					}
				}
				//�P�_�p�������u
				if (bomb[i].IsAlive() && bomb[i].chickenPushBomb(&eraser)) 
				{
					CAudio::Instance()->Play(AUDIO_PUSHBOMB, false);
					if (eraser.check_MovingLeft())
						bomb[i].setMovingLeft(true);
					if (eraser.check_MovingRight())
						bomb[i].setMovingRight(true);
				}
				//�P�_���u�P���u������
				for (int j = 0; j < NUMBOMBS; j++) {
					if (i != j) {
						if (bomb[j].IsAlive() && (bomb[i].beBombed(&bomb[j]))) {  //���u�Q�t�@�����u����|�z��
							bomb[j].SetIsAlive(false);
							bomb[j].setIsBombing(true);
						}
						if (bomb[j].IsAlive() && bomb[i].IsAlive() && bomb[i].isMoving() && bomb[i].HitBomb(&bomb[j])) { //���ʪ����u���쬵�u�|�z��
							bomb[j].SetIsAlive(false);
							bomb[j].setIsBombing(true);
						}
						if (bomb[j].IsAlive() && bomb[i].IsAlive()) {  //�P�_���u�O�_�|�b�W��
							if (bomb[i].checkOnBomb(&bomb[j])) {
								bomb[j].setIsOnBomb(true);
							}
							else
								bomb[j].setIsOnBomb(false);
						}
					}
				}
				if (bomb[i].beBombed(&eraser)) {  //�P�_�p���Q���u����
					ReBrith();
				}

//-------------------------------���u�P�U�ت��󪺤���------------------------------------------------
				for (int j = 0; j < NUMBTN; j++)
				{
					if (!btn[j].IsTouched() && btn[j].touchButton(&bomb[i]) && bomb[i].IsAlive()) { //���u�}��
						btn[j].SetIsTouched(true);
						door[j].setIsOpenDoor(true);						   //������}
						door[j].openDoor(&gamemap);
						CAudio::Instance()->Play(AUDIO_BUTTONDOOR, false);
					}
				}
				for (int j = 0; j < NUM_WOOD_DOOR; j++) {						// ����Q���u���}
					if (!wooddoor[j].isOpenDoor() && bomb[i].beBombed(&wooddoor[j]))
					{
						wooddoor[j].setIsOpenDoor(true);
						wooddoor[j].openDoor(&gamemap);
						CAudio::Instance()->Play(AUDIO_OPENWOODDOOR, false);
					}
				}
				for (int j = 0; j < NUMROCK; j++) {								// ���Y�Q���u���}
					if (!rock[j].isOpenRock() && bomb[i].beBombed(&rock[j]))
					{
						rock[j].setIsOpenRock(true);
						rock[j].openRock(&gamemap);
						//�������_�۪����Y�|��o�_��
						if (rock[j].returnType() == 1 || rock[j].returnType() == 4) { 
							gem[0].setShowNumGem(true);
							nowTotalGem++;
							eraser.setShowHeart(true);
							CAudio::Instance()->Play(AUDIO_GETGEM, false);
						}
					}
				}
				for (int j = 0; j < NUMTREASURE; j++) {
					if (!treasure[j].isOpen() && bomb[i].beBombed(&treasure[j])) {  //���u���}�_�c
						treasure[j].SetIsOpen(true);
						nowTotalGem += 5;
						gem[0].setShowNumGem(true);
						eraser.setShowHeart(true);
						CAudio::Instance()->Play(AUDIO_OPENTREASURE, false);
					}
				}
				for (int j = 0; j < NUMHAMMER; j++) {
					if (bomb[i].IsAlive() && hammer[j].hammerTouchBomb(&bomb[i])) { //�l�l���쬵�u�|�z��
						bomb[i].SetIsAlive(false);
						bomb[i].setIsBombing(true);
					}
				}
				//�ĤH�I�쬵�u
				for (int j = 0; j < NUMENEMY; j++) {
					if (enemy[j].isAlive() && bomb[i].beBombed(&enemy[j])) {  //�ĤH�Q���u����
						enemy[j].setIsAlive(false);
						CAudio::Instance()->Play(AUDIO_KILLENEMY, false);
					}
					if (enemy[j].isAlive() && bomb[i].IsAlive() && bomb[i].beEnemyTouched(&enemy[j])) {//�|�������ĤH�I���R����u�|��V
						enemy[j].enemyTouchBomb();
					}
					if (bomb[i].IsAlive() && bomb[i].isMoving() && enemy[j].isAlive() && bomb[i].movingBombTouch(&enemy[j])) { //�ĤH�Q���ʪ����u�I��|�z��
						bomb[i].SetIsAlive(false);
						bomb[i].setIsBombing(true);
					}
				}
				bomb[i].OnMove(&eraser, &gamemap); //���u������
			}
			eraser.OnMove(&gamemap, bomb); //�p��������

			if (gamemap.IsChangeHeartMap(eraser.GetX1(), eraser.GetY1())) { //�i�J�i�H���_�۴��ͩR���a��
				gamemap.changeToHeartMap();
				eraser.SetXY(30, 300);
				eraser.healHeart();
				IS_IN_CHANGE_HEART_MAP = true;
				CHEAT_MODE = true;
				CAudio::Instance()->Play(AUDIO_PASS, false);
				CAudio::Instance()->Stop(AUDIO_BAKCGROUND);
				CAudio::Instance()->Play(AUDIO_init, true);
			}
			if (IS_IN_CHANGE_HEART_MAP) { //�P�_�O�_�i�J���ͩR���a��
				eraser.setShowHeart(true);
				gem[0].setShowNumGem(true);
				gem[0].setShowStore(true);
				if (!isChange && eraser.check_IsBombing() && gamemap.ChangeHeart(eraser.GetX1(), eraser.GetY2()) && nowTotalGem >= priceOfGemsEveryMap[nowMap]) { //�Y�_�ۼƶq�����i�H���@���R��
					eraser.addNowLife();
					nowTotalGem -= priceOfGemsEveryMap[nowMap];
					isChange = true;
				}
				if (gamemap.IsGoToNextMap(eraser.GetX1(), eraser.GetY1())) { //�i�J�U�@��
					if (nowMap == 2) {						//�ĤT���L���]��Ĥ@��
						nowMap = 0;
					}
					else {
						nowMap++;
					}
					gamemap.goToNextMap(nowMap);
					CAudio::Instance()->Play(AUDIO_PASS, false);
					CAudio::Instance()->Stop(AUDIO_init);
					GotoGameState(GAME_STATE_RUN);
					IS_IN_CHANGE_HEART_MAP = false;
					CHEAT_MODE = false;
					gem[0].setShowStore(false);
					isChange = false;
				}
			}
			//�P�_�p���I����s
			for (int j = 0; j < NUMBTN; j++)
			{
				if (!btn[j].IsTouched() && btn[j].touchButton(&eraser)) {
					btn[j].SetIsTouched(true);
					door[j].setIsOpenDoor(true); //������}
					CAudio::Instance()->Play(AUDIO_BUTTONDOOR, false);
					door[j].openDoor(&gamemap);
				}
			}
			gamemap.OnMove(&eraser); //�a�ϵ���������

		}
		
	}

}

void CGameStateRun::OnInit()  // �C������Ȥιϧγ]�w
{
	//�N�a�Ϫ�������J
	for (int i = 0; i < NUMBTN; i++) {
		btn[i].LoadBitmap();
		door[i].LoadBitmap();
	}
	for (int i = 0; i < NUMTREASURE; i++) {
		treasure[i].LoadBitmap();
	}
	for (int i = 0; i < NUMROCK; i++) {
		rock[i].LoadBitmap();
	}
	for (int i = 0; i < NUM_WOOD_DOOR; i++) {
		wooddoor[i].LoadBitmap();
	}
	gamemap.LoadBitmap();
	for (int i = 0; i < NUMBOMBS; i++)
		bomb[i].LoadBitmap();
	
	for (int i = 0; i < NUMGEM; i++)
		gem[i].LoadBitmap();
	for (int i = 0; i < NUMENEMY; i++)
		enemy[i].LoadBitmap();
	for (int i = 0; i < NUMHAMMER; i++)
		hammer[i].LoadBitmap();
	//menu �u���T��
	int m[9] = { IDB_MENU1_1,IDB_MENU1_2,IDB_MENU1_3 ,IDB_MENU2_1 ,IDB_MENU2_2 ,IDB_MENU2_3 ,IDB_MENU3_1 ,IDB_MENU3_2 ,IDB_MENU3_3 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			menu[i][j].LoadBitmapA(m[j+i*3]);
		}
	}
   eraser.LoadBitmap();
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	//
	// �~����J��L���
	//
	CAudio::Instance()->Load(AUDIO_BAKCGROUND, "sounds\\background.mp3");	   // ���J�I���n��
	CAudio::Instance()->Load(AUDIO_PUTBOMB, "sounds\\PutBomb.mp3");	           // ���J�񬵼u�n��
	CAudio::Instance()->Load(AUDIO_BOMBING, "sounds\\Bombing.mp3");            // ���J���u�z���n��
	CAudio::Instance()->Load(AUDIO_PUSHBOMB, "sounds\\PushBomb.mp3");          // ���J�����u�n��
	CAudio::Instance()->Load(AUDIO_REBRITH, "sounds\\Rebrith.mp3");            // ���J�_���n��
	CAudio::Instance()->Load(AUDIO_PASS, "sounds\\Pass.mp3");                  // ���J�L���n��
	CAudio::Instance()->Load(AUDIO_KILLENEMY,"sounds\\KillEnemy.mp3");         // ���J�����ĤH�n��
	CAudio::Instance()->Load(AUDIO_OPENTREASURE, "sounds\\OpenTreasure.mp3");  // ���J���}�_�c�n��
	CAudio::Instance()->Load(AUDIO_GETGEM, "sounds\\GetGem.mp3");              // ���J��o�_���n��
	CAudio::Instance()->Load(AUDIO_BUTTONDOOR, "sounds\\ButtonDoor.mp3");      // ���J���s���n��
	CAudio::Instance()->Load(AUDIO_OPENWOODDOOR, "sounds\\OpenWoodDoor.mp3");  // ���J����n��

	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	const char KEY_SPACE = 0x20;// keyboard�ť���
	const char KEY_R = 82;
	const char KEY_r = 114;
	const char KEY_ESC = 27;
	const char KEY_ENTER = 13;
	
	if (!isInMenuState) { 
		if (nChar == KEY_ESC) {
			isInMenuState = true; //�}��menu
			tempNowMap = nowMap;
		}
		if (!gamemap.checkScreenMoVing()) {
			if (nChar == KEY_R ) {
				if (!IS_IN_CHANGE_HEART_MAP) {
					eraser.returnSavePoint();
					gamemap.returnSavePoint();
					eraser.SetStepOnBomb(false);
				}
			}
			if (nChar == KEY_LEFT)
				eraser.SetMovingLeft(true);
			if (nChar == KEY_RIGHT)
				eraser.SetMovingRight(true);
			if (nChar == KEY_UP)
				eraser.SetMovingUp(true);
			if (nChar == KEY_DOWN)
				eraser.SetPressDown(true);
			if (nChar == KEY_UP) {
				if (!CHEAT_MODE)
					CHEAT_MODE = true;
				else
					CHEAT_MODE = false;
			}
			if (nChar == KEY_SPACE)//�P�_�Y�W�O�_���Ŷ��񬵼u
			{
				eraser.SetBombing(true);
				if (gamemap.IsEmpty(eraser.GetX1(), eraser.GetY1() - 20) && eraser.checkOnFloor()) {
					CAudio::Instance()->Play(AUDIO_PUTBOMB, false);
					bomb[numberBomb].SetXY(eraser.GetX1(), eraser.GetY1());
					eraser.SetXY(eraser.GetX1(), eraser.GetY1() - bomb[numberBomb].GetHeight());
					bomb[numberBomb].SetIsAlive(true);
					bomb[numberBomb].setBombAnimation();
					numberBomb++;
					if (numberBomb == NUMBOMBS)
						numberBomb = 0;
				}
			}
		}
	}
	//���ʿ��
	else {
		if (nChar == KEY_ESC || menuState == 1 && nChar == KEY_ENTER) {
			isInMenuState = false; //����menu
			nowMap = tempNowMap;   
		}
		if (menuState == 0 && nChar == KEY_LEFT) {
			CAudio::Instance()->Play(AUDIO_MENU, false);
			if (nowMap > 0)
				nowMap--;
		}
		if (menuState == 0 && nChar == KEY_RIGHT) {
			CAudio::Instance()->Play(AUDIO_MENU, false);
			if (nowMap < 2)
				nowMap++;
		}
		if (nChar == KEY_UP) {
			CAudio::Instance()->Play(AUDIO_MENU, false);
			if (menuState == 0)
				menuState = 2;
			else
				menuState--;
		}
		if (nChar == KEY_DOWN) {
			CAudio::Instance()->Play(AUDIO_MENU, false);
			if (menuState == 2)
				menuState = 0;
			else
				menuState++;
		}
		if (menuState == 0 && nChar == KEY_ENTER) {
			if (IS_IN_CHANGE_HEART_MAP) {
				CAudio::Instance()->Stop(AUDIO_init);
				IS_IN_CHANGE_HEART_MAP = false;
				CHEAT_MODE = false;
				gem[0].setShowStore(false);
				isChange = false;
			}
			gamemap.goToNextMap(nowMap);
			GotoGameState(GAME_STATE_RUN);
			isInMenuState = false;
		}
		if (menuState == 2 && nChar == KEY_ENTER) {
			GotoGameState(GAME_STATE_INIT);
			isInMenuState = false;
		}

	}
}
void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_SPACE = 0x20;// keyboard�ť���

	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetPressDown(false);
	if (nChar == KEY_SPACE)	
		eraser.SetBombing(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//	
	if (!isInMenuState) {
		gamemap.OnShow();
		if (!IS_IN_CHANGE_HEART_MAP) {
			for (int i = 0; i < NUMBTN; i++)
			{
				btn[i].OnShow(&gamemap);
				door[i].OnShow(&gamemap);
			}
			for (int i = 0; i < NUM_WOOD_DOOR; i++) {
				wooddoor[i].OnShow(&gamemap);
			}
			for (int i = 0; i < NUMTREASURE; i++)
			{
				treasure[i].OnShow(&gamemap);
			}
			for (int i = 0; i < NUMROCK; i++)
			{
				rock[i].OnShow(&gamemap);
			}
			for (int i = 0; i < NUMENEMY; i++) {
				enemy[i].OnShow(&gamemap);
			}
			for (int i = 0; i < NUMHAMMER; i++) {
				hammer[i].OnShow(&gamemap);
			}
		}
		for (int i = 0; i < NUMGEM; i++)
		{
			gem[i].OnShow(&gamemap);
		}

		for (int i = 0; i < NUMBOMBS; i++)
		{
			bomb[i].OnShow(&gamemap);
		}
		eraser.OnShow(&gamemap);
	}
	else{
		menu[nowMap][menuState].SetTopLeft(0, 0);
		menu[nowMap][menuState].ShowBitmap();
	}
}
void CGameStateRun::ReBrith() { //����ˮ`��
	eraser.SetStepOnBomb(false);
	eraser.setShowHeart(true);
	gem[0].setShowNumGem(true);
	if (!CHEAT_MODE) {
		for (int i = 0; i < NUMBOMBS; i++)
		{
			if (bomb[i].IsAlive())
				bomb[i].SetIsAlive(false);
		}
		isDie = true;
		eraser.setHurt(true);
		eraser.minusNowLife();
		eraser.returnSavePoint();
		gamemap.returnSavePoint();
		CAudio::Instance()->Play(AUDIO_REBRITH, false);
		if (eraser.getNowLife() < 0) { //�ͩR�p��0�����C��
			nowTotalGem = 0;
			GotoGameState(GAME_STATE_OVER);
			CAudio::Instance()->Stop(AUDIO_BAKCGROUND);
		}
	}
}
}