/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "Bomb.h"
#include "CBouncingBall.h"
#include "gameMap.h"
#include "gem.h"
#include "doorButton.h"
#include "door.h"
#include "woodDoor.h"
#include "Treasure.h"
#include "Rock.h"
#include "Enemy.h"
#include "Hammer.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_init,				// 0
		AUDIO_BAKCGROUND,       // 1
		AUDIO_PUTBOMB,          // 2
   		AUDIO_BOMBING,          // 3
		AUDIO_PUSHBOMB,         // 4
		AUDIO_REBRITH,          // 5
		AUDIO_GAMEOVER,         // 6
		AUDIO_PASS,				// 7
		AUDIO_KILLENEMY,		// 8
		AUDIO_MENU, 		    // 9
		AUDIO_OPENTREASURE,     //10
		AUDIO_GETGEM,           //11
		AUDIO_BUTTONDOOR,       //12
		AUDIO_OPENWOODDOOR      //13
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		//CMovingBitmap logo;								// csie的logo
		CMovingBitmap start[7];
		int current;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void ReBrith();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		bool			CHEAT_MODE;	//無敵的狀態
		bool			IS_IN_CHANGE_HEART_MAP; //進入換生命關的狀態
		const int		NUMBOMBS;	// 炸彈的總數
		int				NUMGEM;		// 寶石的總數
		int				NUMBTN;
		int				NUM_WOOD_DOOR;
		int				NUMTREASURE;
		int				NUMROCK;
		int				NUMENEMY;
		int				NUMHAMMER;
		CMovingBitmap	menu[3][3];
		Gem				*gem;			//寶石的陣列
		CEraser			eraser;			// 小雞
		CGameMap		gamemap;		//地圖
		Hammer			*hammer;		//槌子
		Bomb			*bomb;			//炸彈
		Button			*btn;			//按鈕
		Door			*door;			//門
		Rock			*rock;			//石頭
		Enemy			*enemy;			//敵人
		woodDoor		*wooddoor;		//木門
		Treasure		*treasure;		//寶箱
		bool			isChange;		//交換生命的狀態(一次只能換一個)
		bool            isDie;		    //小雞的狀態
		bool            isInMenuState;  //切換menu
		int             menuState;      //menu目前顯示哪張圖
		int				tempNowMap;     //暫存目前第幾關
		int             reBrithCounter; //重生計數器
		int				numberBomb;	
		int				nowTotalGem;	//目前獲得寶石的數量
		int				nowMap;			//目前關卡
		//----------每個關卡的物件數量----------------
		int priceOfGemsEveryMap[3] = { 5 ,20,40};
		int numberOfGemEveryMap[3] = { 12 ,10,13};
		int numberOfBtnEveryMap[3] = { 3 ,3, 2};
		int numberOfWoodDoorEveryMap[3] = { 2,0,0 };
		int numberOfTreasureEveryMap[3] = { 1,1,0};
		int numberOfRockEveryMap[3] = { 2 ,41,17};
		int numberOfEnemyEveryMap[3] = {6,4,20};
		int numberOfHammerEveryMap[3] = { 0,15,0};
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;									// 倒數之計數器
		CMovingBitmap gameOver;
	};

}