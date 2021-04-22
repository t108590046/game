namespace game_framework {
	class CGameMap {
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		int	 ScreenX(int x);
		int  ScreenY(int y);
		bool IsEmpty(int x, int y);
		bool IsLittleMove_horizontal(int x, int y);
		bool IsLittleMove_updown(int x, int y);

		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetMovingDownL(bool flag);	// �]�w�O�_���b���U�p����
		void SetMovingLeftL(bool flag);	// �]�w�O�_���b�����p����
		void SetMovingRightL(bool flag); // �]�w�O�_���b���k�p����
		void SetMovingUpL(bool flag);	// �]�w�O�_���b���W�p����
		bool IsChangeScreen_horizontal(int x, int y);
		bool IsChangeScreen_Diagonal(int x, int y);
	protected:
		CMovingBitmap blue, green,yellow,stage1;
		int map[20][30];
		const int MW, MH;
		int	 sx, sy;
		int NowShowStage;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isMovingDownL;			// �O�_���b���U�p����
		bool isMovingLeftL;			// �O�_���b�����p����
		bool isMovingRightL;		// �O�_���b���k�p����
		bool isMovingUpL;			// �O�_���b���W�p����

	};














}