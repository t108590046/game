namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap;
	class Bomb;
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize(int n);				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(CGameMap *m,Bomb *bomb);					// �������l
		void OnShow(CGameMap *m);					// �N���l�ϧζK��e��
		void SetBombing(bool flag);	// �]�w�O�_���b�U���u
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetPressDown(bool flag);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetLanding(bool flag);
		void SetStepOnBomb(bool flag);
		bool check_MovingLeft();
		bool check_MovingRight();
		bool check_IsBombing();
		bool check_inPipe();
		bool checkCanPutBomb();
		bool checkOnFloor();
		bool checkOnBomb();
		void setShowHeart(bool flag);
		void stopMoving();
		void minusNowLife();
		void addNowLife();
		int getNowLife();
		void returnSavePoint();
		void setHurt(bool flag);
		void healHeart();
		void setChickenJumping(bool flag);
		bool getNowIsPipeGoToUp();
		bool getNowIsPipeGoToDown();
	protected:
		CAnimation animation;		// ���l���ʵe
		CAnimation goToLeft;		//���V��
		CAnimation goToRight;		//���V�k
		CAnimation cantputBomb;	   //���񬵼u����
		CMovingBitmap heart,emptyHeart;
		int x, y;					// ���l���W���y��
		int savePointX, savePointY;
		bool isBombing;			    // �O�_���b�U���u
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isPressDown;			
		bool is_landing;			//���b�U��
		bool isStepOnBomb;
		bool isInPipeGoToUp;
		bool isInPipeGoToDown;
		bool isShowHeart; 
		bool isCanPutBomb;
		bool isHurt;
		bool isJumping;
		int life_Max; //�ͩR�W��
		int nowLife; // �ثe�ͩR
		int showHeartCounter;
		int jumpCounter;
		int hurtCounter;
	};
}