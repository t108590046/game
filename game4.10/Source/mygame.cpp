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
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
	current = 0;
	start[0].LoadBitmap(IDB_start0, RGB(0, 0, 0));
	start[1].LoadBitmap(IDB_start1, RGB(0, 0, 0));
	start[2].LoadBitmap(IDB_start2, RGB(0, 0, 0));
	start[3].LoadBitmap(IDB_start3, RGB(0, 0, 0));
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	const char KEY_ESC = 27; 
	const char KEY_ENTER = 13;
	const char KEY_UpArrow = 38;
	const char KEY_DownArrow = 40;
	if (nChar >= 0 && current == 0) {
		current = 1;
	}
	else if(current == 1 && nChar == KEY_ENTER)
	{
		GotoGameState(GAME_STATE_RUN);
	}
	else if (current == 3 && nChar == KEY_ENTER)
	{
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}
	if(nChar == KEY_UpArrow)
	{
		if (current == 1) {
			current = 3;
		}
		else if (current == 2) {
			current = 1;
		}
		else if (current == 3) {
			current = 2;
		}
	}
	if (nChar == KEY_DownArrow)
	{
		if (current == 1) {
			current = 2;
		}
		else if (current == 2) {
			current = 3;
		}
		else if (current == 3) {
			current = 1;
		}
	}

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	//logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	*/
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
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	gameOver.LoadBitmap(IDB_GAMEOVER);
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
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
	: CGameState(g), NUMBOMBS(10), NUMGEM(30), NUMBTN(10), NUM_WOOD_DOOR(10), NUMTREASURE(10),NUMROCK(10),NUMENEMY(10)
{
	nowMap = 1;
	numberBomb = 0;
	ball = new CBall [NUMBOMBS];
	bomb = new Bomb[NUMBOMBS];
	gem = new Gem[NUMGEM];
	btn = new Button[NUMBTN];
	door = new Door[NUMBTN];
	wooddoor = new woodDoor[NUM_WOOD_DOOR];
	treasure = new Treasure[NUMTREASURE];
	rock = new Rock[NUMROCK];
	enemy = new Enemy[NUMENEMY];
	nowTotalGem = 5;
	CHEAT_MODE = IS_IN_CHANGE_HEART_MAP = isChange =false;
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
	delete [] bomb;
	delete[] gem;
	delete[] btn;
	delete[] door;
	delete[] wooddoor;
	delete[] treasure;
	delete[] rock;
	delete[] enemy;
}

void CGameStateRun::OnBeginState()
{
	NUMGEM = numberOfGemEveryMap[nowMap];
	NUMBTN = numberOfBtnEveryMap[nowMap];
	NUM_WOOD_DOOR = numberOfWoodDoorEveryMap[nowMap];
	NUMTREASURE = numberOfTreasureEveryMap[nowMap];
	NUMROCK = numberOfRockEveryMap[nowMap];
	NUMENEMY = numberOfEnemyEveryMap[nowMap];
	//�Ҧ����_�۪��y��
	int allGemXY[12][2] = {{1100,580},{1585,560}, {1718,528},{2045,460},{2320,430},{2320,330},{2320,230},{2930,665},{2930,615},{2665,335},{2690,335},{2715,335} };
	for (int i = 0; i < NUMGEM; i++) {
		gem[i].SetXY(allGemXY[i][0], allGemXY[i][1]);
		gem[i].updatePriceOfHeart(priceOfGemsEveryMap[nowMap]);
	}
	//�Ҧ������s���y��{��V,x,y}
	int allBtnXY[3][3] = { {0,50,545},
						   {1,2605,670},
	                       {3,2670,95} };
	for (int i = 0; i < NUMBTN; i++) {
		btn[i].SetXY(allBtnXY[i][0],allBtnXY[i][1], allBtnXY[i][2]);
	}
	int allDoorXY[3][3] = { {0,565,450},{0,2625,840},{1,2672,266} };
	for (int i = 0; i < NUMBTN; i++) {
		door[i].SetXY(allDoorXY[i][0], allDoorXY[i][1], allDoorXY[i][2]);
	}
	//�Ҧ�������y��
	int allWoodDoor[2][2] = { {955,445},
							  {1290,515} };
	for (int i = 0; i < NUM_WOOD_DOOR; i++)
	{
		wooddoor[i].SetXY(allWoodDoor[i][0], allWoodDoor[i][1]);
	}
	//�Ҧ��_�ê��y��
	int allTreasure[1][2] = { {1880,695} };
	for (int i = 0; i < NUMTREASURE; i++) {
		treasure[i].SetXY(allTreasure[i][0], allTreasure[i][1]);
	}
	//�Ҧ����Y���y��
	int allRock[2][2] = { {2155,665},{2155,598} };
	for (int i = 0; i < NUMROCK; i++) {
		rock[i].SetXY(allRock[i][0], allRock[i][1]);
	}
	//�Ҧ��ĤH���y��
	int allEnemy[2][6][3] = { {{0,2000,672},{1,2525,685},{2,2220,830},{3,2500,870},{4,2810,597},{2,2690,190}},
	                          {{4,145,250}}
	};
	for (int i = 0; i < NUMENEMY; i++) {
		enemy[i].SetXY(allEnemy[nowMap][i][0], allEnemy[nowMap][i][1], allEnemy[nowMap][i][2]);
		enemy[i].setIsAlive(true);
	}

	eraser.Initialize(nowMap);
	gamemap.Initialize();
	/*background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
	*/

}


void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
				//bomb[i].OnMove(&eraser, &gamemap);
			//CAudio::Instance()->Play(AUDIO_DING);
			//hits_left.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			//if (hits_left.GetInteger() <= 0) {
			//	CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
			//	CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
			//	GotoGameState(GAME_STATE_OVER);
	// ���ʭI���Ϫ��y��
	//

	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// ���ʲy
	//
	//int i;
	//for (i=0; i < NUMBALLS; i++)
		//ball[i].OnMove();
	//
	
	//
	//�P�_���O�_�I���_��
	
	for (int i = 0; i < NUMGEM; i++)
	{
		if (gem[i].IsAlive() && gem[i].HitChicken(&eraser))
		{
			gem[i].SetIsAlive(false);
			gem[i].setShowNumGem(true);
			nowTotalGem++;
			eraser.setShowHeart(true);
		}
		gem[i].getGem(nowTotalGem);
	}
	// �ĤH�I��p��
	for (int i = 0; i < NUMENEMY; i++) {
		enemy[i].OnMove(&gamemap);
		if (enemy[i].isAlive() && enemy[i].checkOnEnemy(&eraser)) {
			enemy[i].setIsAlive(false);
			eraser.setChickenJumping(true);
		}
		if (enemy[i].isAlive()&&enemy[i].touchChicken(&eraser)) {
			eraser.setShowHeart(true);
			gem[0].setShowNumGem(true);
			if (!CHEAT_MODE) {
				eraser.setHurt(true);
				eraser.minusNowLife();
				eraser.returnSavePoint();
				gamemap.returnSavePoint();
				if (eraser.getNowLife() < 0) {
					GotoGameState(GAME_STATE_RUN);
				}
			}
		}
	}
	// �P�_���u�O�_�I����
	//
	for (int i = 0; i < NUMBOMBS; i++) {
		if (bomb[i].IsAlive()) {
			if (!bomb[i].HitBomb(&eraser)) {
				eraser.SetStepOnBomb(false);
			}
		}
	}
	for (int i=0; i < NUMBOMBS; i++)
	{
		if (bomb[i].IsAlive()) {
			 if (bomb[i].HitBomb(&eraser)) {
				eraser.SetStepOnBomb(true);
			}
		}
		if (bomb[i].IsAlive() && bomb[i].chickenPushBomb(&eraser)) //�����u
		{
			if (eraser.check_MovingLeft()) 
				bomb[i].setMovingLeft(true);
			if(eraser.check_MovingRight())
				bomb[i].setMovingRight(true);
		}
		
		for (int j = 0; j < NUMBOMBS; j++) {
			if (i != j) {
				if ( bomb[j].IsAlive()  && (bomb[i].beBombed(&bomb[j]))) {
					bomb[j].SetIsAlive(false);
					bomb[j].setIsBombing(true);
				}
				if (bomb[j].IsAlive() && bomb[i].IsAlive() && bomb[i].isMoving() && bomb[i].HitBomb(&bomb[j])) {
					bomb[j].SetIsAlive(false);
					bomb[j].setIsBombing(true);
				}
				if (bomb[j].IsAlive() && bomb[i].IsAlive()) {
					if (bomb[i].checkOnBomb(&bomb[j])) {
						bomb[j].setIsOnBomb(true);
						TRACE("j:%d\n", j);

					}
					else
						bomb[j].setIsOnBomb(false);
				}
			}
		}
		if ( bomb[i].beBombed(&eraser)) {
			bomb[i].setIsBombing(false);
			eraser.SetStepOnBomb(false);
			eraser.setShowHeart(true);
			gem[0].setShowNumGem(true);
			if (!CHEAT_MODE) {
				eraser.minusNowLife();
				eraser.returnSavePoint();
				gamemap.returnSavePoint();
				if (eraser.getNowLife() < 0) {
					GotoGameState(GAME_STATE_OVER);
				}
			}
		}
		for (int j = 0; j < NUMBTN; j++)
		{
			if (!btn[j].IsTouched() && btn[j].touchButton(&bomb[i])) {
				btn[j].SetIsTouched(true);
				door[j].setIsOpenDoor(true); //������}
				door[j].openDoor(&gamemap);
			}
		}
		for (int j = 0; j < NUM_WOOD_DOOR; j++) { // ����Q���u���}
			if (!wooddoor[j].isOpenDoor() && bomb[i].beBombed(&wooddoor[j]))
			{
				wooddoor[j].setIsOpenDoor(true);
				wooddoor[j].openDoor(&gamemap);
			}
		}
		for (int j = 0; j < NUMROCK; j++) { // ���Y�Q���u���}
			if (!rock[j].isOpenRock() && bomb[i].beBombed(&rock[j]))
			{
				rock[j].setIsOpenRock(true);
				rock[j].openRock(&gamemap);
			}
		}
		for (int j = 0; j < NUMTREASURE; j++) {
			if (!treasure[j].isOpen() && bomb[i].beBombed(&treasure[j])) {
				treasure[j].SetIsOpen(true);
				nowTotalGem += 5;
				gem[0].setShowNumGem(true);
				eraser.setShowHeart(true);
			}
		}
		for (int j = 0; j < NUMENEMY; j++) {
			if (enemy[j].isAlive() && bomb[i].beBombed(&enemy[j])) {
				enemy[j].setIsAlive(false);
			}
			if (bomb[i].IsAlive() && bomb[i].beEnemyTouched(&enemy[j])) {
				enemy[j].enemyTouchBomb();
				
			}
			if (bomb[i].IsAlive() && bomb[i].isMoving() && enemy[j].isAlive() && bomb[i].movingBombTouch(&enemy[j])) {
				bomb[i].SetIsAlive(false);
				bomb[i].setIsBombing(true);
			}
		}
		bomb[i].OnMove(&eraser, &gamemap);
	}
	eraser.OnMove(&gamemap, bomb);

	if (gamemap.IsChangeHeartMap(eraser.GetX1(), eraser.GetY1())) {
		gamemap.changeToHeartMap();
		eraser.SetXY(30, 300);
		eraser.healHeart();
		IS_IN_CHANGE_HEART_MAP = true;
		CHEAT_MODE = true;
	}
	if (IS_IN_CHANGE_HEART_MAP) {
		eraser.setShowHeart(true);
		gem[0].setShowNumGem(true);
		gem[0].setShowStore(true);
		if (!isChange && eraser.check_IsBombing() && gamemap.ChangeHeart(eraser.GetX1(), eraser.GetY2()) && nowTotalGem>= priceOfGemsEveryMap[nowMap]) {
			eraser.addNowLife();
			nowTotalGem -= priceOfGemsEveryMap[nowMap];
			isChange = true;
		}
		if (gamemap.IsGoToNextMap(eraser.GetX1(), eraser.GetY1())) {
			nowMap++;
			gamemap.goToNextMap(nowMap);
			GotoGameState(GAME_STATE_RUN);
			IS_IN_CHANGE_HEART_MAP = false;
			CHEAT_MODE = false;
		}
	}
	for (int j = 0; j < NUMBTN; j++)
	{
		if (!btn[j].IsTouched() && btn[j].touchButton(&eraser)) {
			btn[j].SetIsTouched(true);
			door[j].setIsOpenDoor(true); //������}
			door[j].openDoor(&gamemap);
		}
	}
	gamemap.OnMove(&eraser);
	//���妺������
	/*
*/
	//
	// ���ʼu�����y
	//
	//bball.OnMove();
}

void CGameStateRun::OnInit()  // �C������Ȥιϧγ]�w
{
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
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	int i;
	for (i = 0; i < NUMBOMBS; i++)
		ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	eraser.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	//bball.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
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
	if (!gamemap.checkScreenMoVing()) {
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
		if (nChar == KEY_SPACE)
		{
			eraser.SetBombing(true);
			if (eraser.checkCanPutBomb() && eraser.checkOnFloor()) {
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
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	//background.ShowBitmap();			// �K�W�I����
	//help.ShowBitmap();					// �K�W������
	//hits_left.ShowBitmap();
	//for (int i=0; i < NUMBALLS; i++)
		//ball[i].OnShow();				// �K�W��i���y
	//bball.OnShow();						// �K�W�u�����y
	
	
	gamemap.OnShow();
	for (int i = 0; i < NUMBTN; i++)
	{
		btn[i].OnShow(&gamemap);
		door[i].OnShow(&gamemap);
	}
	for (int i = 0; i < NUMGEM; i++)
	{
		gem[i].OnShow(&gamemap);
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
	eraser.OnShow(&gamemap);// �K�W���l			
	for (int i = 0; i < NUMBOMBS; i++)
	{
		bomb[i].OnShow(&gamemap);
	}
	for (int i = 0; i < NUMENEMY; i++) {
		enemy[i].OnShow(&gamemap);
	}
	//
	//  �K�W���W�Υk�U��������
	//
	//corner.SetTopLeft(0,0);
	//corner.ShowBitmap();
	//corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	//corner.ShowBitmap();
}
}