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
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetMovingDownL(bool flag);	// 設定是否正在往下小移動
		void SetMovingLeftL(bool flag);	// 設定是否正在往左小移動
		void SetMovingRightL(bool flag); // 設定是否正在往右小移動
		void SetMovingUpL(bool flag);	// 設定是否正在往上小移動
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
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isMovingDownL;			// 是否正在往下小移動
		bool isMovingLeftL;			// 是否正在往左小移動
		bool isMovingRightL;		// 是否正在往右小移動
		bool isMovingUpL;			// 是否正在往上小移動
		int Stop_x, Stop_y;
		int Screen_Height, Screen_Width;
	};














}