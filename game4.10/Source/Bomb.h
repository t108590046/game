namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class Bomb
	{
	public:
		Bomb();
		Bomb(int x,int y);
		bool HitBomb(CEraser *eraser);							// 是否碰到擦子
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void chickenPushBomb(CEraser *eraser);
		void OnMove(CEraser *eraser, CGameMap *m);				// 移動
		void OnShow(CGameMap *m);								// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		//void SetDelay(int d);									// 設定旋轉的速度
		void SetBomb(bool flag);	// 設定是否正在下炸彈
		void setBombAnimation();
	protected:
		CAnimation bmp;				// 球的圖
		CMovingBitmap bmp_center;	// 圓心的圖
		int x, y;					// 圓心的座標
		//int dx, dy;				// 球距離圓心的位移量
		//int index;				// 球的「角度」，0-17表示0-360度
		//int delay_counter;		// 調整旋轉速度的計數器
		//int delay;				// 旋轉的速度
		bool is_alive;				// 是否活著
		bool is_putBomb;			//是否放炸彈
		bool is_bePushed;			//是否被推
		clock_t start, finish;			
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形


	};
}