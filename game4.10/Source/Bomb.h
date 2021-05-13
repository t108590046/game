namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class woodDoor;
	class Treasure;
	class Rock;
	class Bomb
	{
	public:
		Bomb();
		int  GetX1();					
		int  GetY1();					
		int  GetX2();					
		int  GetY2();
		bool isMoving();
		bool HitBomb(CEraser *eraser);
		bool HitBomb(Bomb *bomb);// 是否碰到擦子
		bool IsBombing();
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		bool beBombed(woodDoor *door);							//是否被炸到
		bool beBombed(Bomb *bomb);								//是否被炸到
		bool beBombed(Treasure *treasure);						//是否被炸到
		bool beBombed(Rock *rock);								//是否被炸到
		bool beBombed(CEraser *eraser);								//是否被炸到
		bool chickenPushBomb(CEraser *eraser);
		void OnMove(CEraser *eraser, CGameMap *m);				// 移動
		void OnShow(CGameMap *m);								// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		//void SetDelay(int d);									// 設定旋轉的速度
		void SetBomb(bool flag);	// 設定是否正在下炸彈
		void setBombAnimation();
		void setMovingRight(bool flag);
		void setMovingLeft(bool flag);
		void setIsBombing(bool flag);
	protected:
		CAnimation bmp;				// 球的圖
		CAnimation bmpBombing;
		CMovingBitmap bmp_center;	// 圓心的圖
		int x, y;					// 圓心的座標
		//int dx, dy;				// 球距離圓心的位移量
		//int index;				// 球的「角度」，0-17表示0-360度
		//int delay_counter;		// 調整旋轉速度的計數器
		//int delay;				// 旋轉的速度
		bool is_alive;				// 是否活著
		bool is_putBomb;			//是否放炸彈
		bool isMovingRight;
		bool isMovingLeft;
		bool isBombing;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
		int bombTimeCounter,bombingTimeCounter;

	};
}