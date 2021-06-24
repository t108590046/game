/*
 * mygame.h: ���ɮ��x�C��������class��interface
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

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
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
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		//CMovingBitmap logo;								// csie��logo
		CMovingBitmap start[7];
		int current;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void ReBrith();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		bool			CHEAT_MODE;	//�L�Ī����A
		bool			IS_IN_CHANGE_HEART_MAP; //�i�J���ͩR�������A
		const int		NUMBOMBS;	// ���u���`��
		int				NUMGEM;		// �_�۪��`��
		int				NUMBTN;
		int				NUM_WOOD_DOOR;
		int				NUMTREASURE;
		int				NUMROCK;
		int				NUMENEMY;
		int				NUMHAMMER;
		CMovingBitmap	menu[3][3];
		Gem				*gem;			//�_�۪��}�C
		CEraser			eraser;			// �p��
		CGameMap		gamemap;		//�a��
		Hammer			*hammer;		//�l�l
		Bomb			*bomb;			//���u
		Button			*btn;			//���s
		Door			*door;			//��
		Rock			*rock;			//���Y
		Enemy			*enemy;			//�ĤH
		woodDoor		*wooddoor;		//���
		Treasure		*treasure;		//�_�c
		bool			isChange;		//�洫�ͩR�����A(�@���u�ഫ�@��)
		bool            isDie;		    //�p�������A
		bool            isInMenuState;  //����menu
		int             menuState;      //menu�ثe��ܭ��i��
		int				tempNowMap;     //�Ȧs�ثe�ĴX��
		int             reBrithCounter; //���ͭp�ƾ�
		int				numberBomb;	
		int				nowTotalGem;	//�ثe��o�_�۪��ƶq
		int				nowMap;			//�ثe���d
		//----------�C�����d������ƶq----------------
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
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;									// �˼Ƥ��p�ƾ�
		CMovingBitmap gameOver;
	};

}