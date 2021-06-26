namespace game_framework {
	class CEraser;
	class CGameMap {
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
		void Initialize(int n);												//初始化地圖
		void OnMove(CEraser *c);											//視角的移動
		int	 ScreenX(int x);												//螢幕座標
		int  ScreenY(int y);
		bool IsEmpty(int x, int y);											//是否可以通過
		bool IsLittleMove_horizontal(int x, int y);							//是否在水平視角小移動
		bool IsLittleMove_updown(int x, int y);								//是否在垂直視角小移動
		bool ShowMovingDown();												//回傳視角移動
		bool ShowMovingUp();
		bool ShowMovingLeft();
		bool ShowMovingRight();
		void SetMovingDown(bool flag);										// 設定正在往下移動
		void SetMovingLeft(bool flag);										// 設定正在往左移動
		void SetMovingRight(bool flag);										// 設定正在往右移動
		void SetMovingUp(bool flag);										// 設定正在往上移動
		void SetMovingDownL(bool flag);										// 設定正在往下小移動
		void SetMovingLeftL(bool flag);										// 設定正在往左小移動
		void SetMovingRightL(bool flag);									// 設定正在往右小移動
		void SetMovingUpL(bool flag);										// 設定正在往上小移動
		bool touchThorn(int x, int y);										// 是否碰到尖刺陷阱
		bool IsChangeScreen_Diagonal_RD(int x, int y);						//視角移動(水平、垂直、右下、右上、左下、左上)
		bool IsChangeScreen_horizontal(int x, int y);
		bool IsChangeScreen_Diagonal_RDandLU(int x, int y);
		bool IsChangeScreen_Diagonal_RUandLD(int x, int y);
		bool IsChangeScreen_UpOrDown(int x, int y);
		bool IsStandingWood(int x, int y);									//是否站在可上不可下木頭
		bool IsStandingLittleWoodDoor(int x, int y);						//是否站在可下不可上的木頭
		int  IsPipe(int x, int y, CEraser *c);								//是否在水管
		bool IsLittleDown(int x, int y);									
		bool IsScreenStopMoving(int x, int y);								//視角是否停止移動
		bool IsChangeHeartMap(int x, int y);								//是否進入換生命圖
		bool ChangeHeart(int x, int y);										//是否換生命
		bool IsGoToNextMap(int x, int y);									//是否進入下一關
		bool checkScreenMoVing();											//是否視角正在移動
		void goToNextMap(int n);											//進入下一關
		void beAir(int x, int y, int x2, int y2);							//將地圖變成空氣
		void beLittleMovingDown(int x, int y, int x2, int y2);				//將地圖變成視角小移動
		void beLittleMoving2(int x, int y, int x2, int y2);
		void returnSavePoint();												//回到記錄點
		void changeToHeartMap();											//換地圖到換生命圖
	protected:
		CMovingBitmap blue, green,yellow,stage1,stage2,stage3,changeHeartMap;//載入地圖
		int map[250][225];
		const int MW, MH;													//地圖每格長寬
		int	 sx, sy;														//視角座標
		int nowMap;															//目前的地圖
		bool isGoToChangeHeartMap;
		int savePointSx, savePointSy;										//紀錄點
		bool isMovingDown;													// 是否正在往下移動
		bool isMovingLeft;													// 是否正在往左移動
		bool isMovingRight;													// 是否正在往右移動
		bool isMovingUp;													// 是否正在往上移動
		bool isMovingDownL;													// 是否正在往下小移動
		bool isMovingLeftL;													// 是否正在往左小移動
		bool isMovingRightL;												// 是否正在往右小移動
		bool isMovingUpL;													// 是否正在往上小移動
		bool canChangeHeart;												// 是否可以換生命
		int Stop_x, Stop_y;													// 視角停止的範圍
		int Screen_Height, Screen_Width;									//解晰度的長寬
	};
}