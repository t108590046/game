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
		bool IsLittleMove(int x, int y);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetMovingDownL(bool flag);	// 設定是否正在往下小移動
		void SetMovingLeftL(bool flag);	// 設定是否正在往左小移動
		void SetMovingRightL(bool flag); // 設定是否正在往右小移動
		void SetMovingUpL(bool flag);	// 設定是否正在往上小移動

	protected:
		CMovingBitmap blue, green,yellow,stage1[2];
		int map[20][80];
		const int MW, MH;
		int	 sx, sy;
		int	 NowShowStage;			//紀錄現在show的畫面
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isMovingDownL;			// 是否正在往下小移動
		bool isMovingLeftL;			// 是否正在往左小移動
		bool isMovingRightL;		// 是否正在往右小移動
		bool isMovingUpL;			// 是否正在往上小移動

	};














}