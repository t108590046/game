namespace game_framework {
	class CEraser;
	class CGameMap {
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
		void OnMove(CEraser *c);
		int	 ScreenX(int x);
		int  ScreenY(int y);
		bool IsEmpty(int x, int y);
		bool IsLittleMove_horizontal(int x, int y);
		bool IsLittleMove_updown(int x, int y);
		bool ShowMovingDown();
		bool ShowMovingUp();
		bool ShowMovingLeft();
		bool ShowMovingRight();
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetMovingDownL(bool flag);	// �]�w�O�_���b���U�p����
		void SetMovingLeftL(bool flag);	// �]�w�O�_���b�����p����
		void SetMovingRightL(bool flag); // �]�w�O�_���b���k�p����
		void SetMovingUpL(bool flag);	// �]�w�O�_���b���W�p����
		bool IsChangeScreen_horizontal(int x, int y);
		bool IsChangeScreen_Diagonal_RDandLU(int x, int y);
		bool IsChangeScreen_Diagonal_RUandLD(int x, int y);
		bool IsChangeScreen_UpOrDown(int x, int y);
		bool IsStandingWood(int x, int y);
		bool IsPipe(int x, int y);
		bool IsScreenStopMoving(int x, int y);
		void ScreenStopMoving();
		void beAir(int x, int y, int x2, int y2);
	protected:
		CMovingBitmap blue, green,yellow,stage1;
		int map[250][220];
		const int MW, MH;
		int	 sx, sy;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isMovingDownL;			// �O�_���b���U�p����
		bool isMovingLeftL;			// �O�_���b�����p����
		bool isMovingRightL;		// �O�_���b���k�p����
		bool isMovingUpL;			// �O�_���b���W�p����
		int Stop_x, Stop_y;
		int Screen_Height, Screen_Width;
	};














}