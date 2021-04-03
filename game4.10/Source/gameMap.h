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
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
	protected:
		CMovingBitmap blue, green,yellow;
		int map[15][25];
		const int MW, MH;
		int	 sx, sy;
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};














}