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