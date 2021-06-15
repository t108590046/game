/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	//logo.LoadBitmap(IDB_BACKGROUND);
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
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
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	//logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	*/
	start[current].SetTopLeft(0, 0);
	start[current].ShowBitmap();
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
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
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	gameOver.SetTopLeft(0, 0);
	gameOver.ShowBitmap();
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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
	//所有的寶石的座標
	int allGemXY[12][2] = {{1100,580},{1585,560}, {1718,528},{2045,460},{2320,430},{2320,330},{2320,230},{2930,665},{2930,615},{2665,335},{2690,335},{2715,335} };
	for (int i = 0; i < NUMGEM; i++) {
		gem[i].SetXY(allGemXY[i][0], allGemXY[i][1]);
		gem[i].updatePriceOfHeart(priceOfGemsEveryMap[nowMap]);
	}
	//所有的按鈕的座標{方向,x,y}
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
	//所有木門的座標
	int allWoodDoor[2][2] = { {955,445},
							  {1290,515} };
	for (int i = 0; i < NUM_WOOD_DOOR; i++)
	{
		wooddoor[i].SetXY(allWoodDoor[i][0], allWoodDoor[i][1]);
	}
	//所有寶藏的座標
	int allTreasure[1][2] = { {1880,695} };
	for (int i = 0; i < NUMTREASURE; i++) {
		treasure[i].SetXY(allTreasure[i][0], allTreasure[i][1]);
	}
	//所有石頭的座標
	int allRock[2][2] = { {2155,665},{2155,598} };
	for (int i = 0; i < NUMROCK; i++) {
		rock[i].SetXY(allRock[i][0], allRock[i][1]);
	}
	//所有敵人的座標
	int allEnemy[2][6][3] = { {{0,2000,672},{1,2525,685},{2,2220,830},{3,2500,870},{4,2810,597},{2,2690,190}},
	                          {{4,145,250}}
	};
	for (int i = 0; i < NUMENEMY; i++) {
		enemy[i].SetXY(allEnemy[nowMap][i][0], allEnemy[nowMap][i][1], allEnemy[nowMap][i][2]);
		enemy[i].setIsAlive(true);
	}

	eraser.Initialize(nowMap);
	gamemap.Initialize();
	/*background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
	*/

}


void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
				//bomb[i].OnMove(&eraser, &gamemap);
			//CAudio::Instance()->Play(AUDIO_DING);
			//hits_left.Add(-1);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			//if (hits_left.GetInteger() <= 0) {
			//	CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
			//	CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
			//	GotoGameState(GAME_STATE_OVER);
	// 移動背景圖的座標
	//

	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// 移動球
	//
	//int i;
	//for (i=0; i < NUMBALLS; i++)
		//ball[i].OnMove();
	//
	
	//
	//判斷雞是否碰到寶石
	
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
	// 敵人碰到小雞
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
	// 判斷炸彈是否碰到雞
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
		if (bomb[i].IsAlive() && bomb[i].chickenPushBomb(&eraser)) //推炸彈
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
				door[j].setIsOpenDoor(true); //把門打開
				door[j].openDoor(&gamemap);
			}
		}
		for (int j = 0; j < NUM_WOOD_DOOR; j++) { // 木門被炸彈炸開
			if (!wooddoor[j].isOpenDoor() && bomb[i].beBombed(&wooddoor[j]))
			{
				wooddoor[j].setIsOpenDoor(true);
				wooddoor[j].openDoor(&gamemap);
			}
		}
		for (int j = 0; j < NUMROCK; j++) { // 石頭被炸彈炸開
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
			door[j].setIsOpenDoor(true); //把門打開
			door[j].openDoor(&gamemap);
		}
	}
	gamemap.OnMove(&eraser);
	//扣血死掉結束
	/*
*/
	//
	// 移動彈跳的球
	//
	//bball.OnMove();
}

void CGameStateRun::OnInit()  // 遊戲的初值及圖形設定
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
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	int i;
	for (i = 0; i < NUMBOMBS; i++)
		ball[i].LoadBitmap();								// 載入第i個球的圖形
	eraser.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	//bball.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_SPACE = 0x20;// keyboard空白鍵
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
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_SPACE = 0x20;// keyboard空白鍵

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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	//background.ShowBitmap();			// 貼上背景圖
	//help.ShowBitmap();					// 貼上說明圖
	//hits_left.ShowBitmap();
	//for (int i=0; i < NUMBALLS; i++)
		//ball[i].OnShow();				// 貼上第i號球
	//bball.OnShow();						// 貼上彈跳的球
	
	
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
	eraser.OnShow(&gamemap);// 貼上擦子			
	for (int i = 0; i < NUMBOMBS; i++)
	{
		bomb[i].OnShow(&gamemap);
	}
	for (int i = 0; i < NUMENEMY; i++) {
		enemy[i].OnShow(&gamemap);
	}
	//
	//  貼上左上及右下角落的圖
	//
	//corner.SetTopLeft(0,0);
	//corner.ShowBitmap();
	//corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	//corner.ShowBitmap();
}
}