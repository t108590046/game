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
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
	protected:
		CMovingBitmap blue, green,yellow;
		int map[15][25];
		const int MW, MH;
		int	 sx, sy;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
	};














}