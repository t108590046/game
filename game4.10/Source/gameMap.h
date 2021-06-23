namespace game_framework {
	class CEraser;
	class CGameMap {
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
		void Initialize(int n);
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
		bool touchThorn(int x, int y);
		bool IsChangeScreen_Diagonal_RD(int x, int y);
		bool IsChangeScreen_horizontal(int x, int y);
		bool IsChangeScreen_Diagonal_RDandLU(int x, int y);
		bool IsChangeScreen_Diagonal_RUandLD(int x, int y);
		bool IsChangeScreen_UpOrDown(int x, int y);
		bool IsStandingWood(int x, int y);
		bool IsStandingLittleWoodDoor(int x, int y);
		int  IsPipe(int x, int y, CEraser *c);
		bool IsLittleDown(int x, int y);
		bool IsScreenStopMoving(int x, int y);
		bool IsChangeHeartMap(int x, int y);
		bool ChangeHeart(int x, int y);
		bool IsGoToNextMap(int x, int y);
		bool checkScreenMoVing();
		void goToNextMap(int n);
		void beAir(int x, int y, int x2, int y2);
		void beLittleMovingDown(int x, int y, int x2, int y2);
		void beLittleMoving2(int x, int y, int x2, int y2);
		void returnSavePoint();
		void changeToHeartMap();
	protected:
		CMovingBitmap blue, green,yellow,stage1,stage2,stage3,changeHeartMap;
		int map[250][225];
		const int MW, MH;
		int	 sx, sy;
		int nowMap;
		bool isGoToChangeHeartMap;
		int savePointSx, savePointSy;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isMovingDownL;			// 是否正在往下小移動
		bool isMovingLeftL;			// 是否正在往左小移動
		bool isMovingRightL;		// 是否正在往右小移動
		bool isMovingUpL;			// 是否正在往上小移動
		bool canChangeHeart;
		int Stop_x, Stop_y;
		int Screen_Height, Screen_Width;
	};














}