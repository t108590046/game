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
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(CGameMap *m);					// �������l
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
		void setShowHeart(bool flag);
		void stopMoving();
	protected:
		CAnimation animation;		// ���l���ʵe
		CAnimation goToLeft;		//���V��
		CAnimation goToRight;		//���V�k
		CAnimation putBomb;			//���񬵼u
		CMovingBitmap heart[20];
		int x, y;					// ���l���W���y��
		bool isBombing;			// �O�_���b�U���u
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isPressDown;			
		bool is_landing;			//���b�U��
		bool isStepOnBomb;
		bool isInPipeGoToUp;
		bool isInPipeGoToDown;
		bool isShowHeart; 
		int life_Max; //�ͩR�W��
		int nowLife; // �ثe�ͩR
		int showHeartCounter;
	};
}