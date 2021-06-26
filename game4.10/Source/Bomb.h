namespace game_framework {
	class CEraser;
	class woodDoor;
	class Treasure;
	class Rock;
	class Enemy;
	class Bomb
	{
	public:
		Bomb();
		int  GetX1();					
		int  GetY1();					
		int  GetX2();					
		int  GetY2();
		int  GetHeight();
		bool isMoving();
		bool HitBomb(CEraser *eraser);							//小雞是否踩在炸彈上
		bool HitBomb(Bomb *bomb);								//炸彈是否碰到炸彈
		bool IsBombing();										//是否正在爆炸
		void setIsOnBomb(bool flag);							//設定是否疊在炸彈上
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		bool beBombed(woodDoor *door);							//是否被炸到
		bool beBombed(Bomb *bomb);								
		bool beBombed(Treasure *treasure);						
		bool beBombed(Rock *rock);								
		bool beBombed(CEraser *eraser);
		bool beBombed(Enemy *enemy);
		bool beEnemyTouched(Enemy *enemy);						//是否被敵人碰到
		bool movingBombTouch(Enemy *enemy);						//是否被敵人碰到
		bool chickenPushBomb(CEraser *eraser);					//小雞是否推到炸彈
		bool checkOnBomb(Bomb *bomb);							//是否疊在炸彈上
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
		void OnMove(CEraser *eraser, CGameMap *m);				// 移動
		void OnShow(CGameMap *m);								// 將圖形貼到畫面
		void SetXY(int nx, int ny);								
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetBomb(bool flag);								// 設定是否正在下炸彈
		void setBombAnimation();								//重製炸彈動畫
		void setMovingRight(bool flag);
		void setMovingLeft(bool flag);
		void setIsBombing(bool flag);
	protected:
		CAnimation bmp;				
		CAnimation bmpBombing;
		int x, y;					
		bool is_alive;											// 是否活著
		bool is_putBomb;										//是否放炸彈
		bool isMovingRight;
		bool isMovingLeft;
		bool isBombing;
		bool isLanding;
		bool isOnBomb;
	private:
		int bombTimeCounter,bombingTimeCounter;					//炸彈與爆炸計時器
	};
}