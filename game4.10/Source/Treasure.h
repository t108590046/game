namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class CMovingBitmap;
	class Treasure
	{
	public:
		Treasure();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		bool touchTreasure(CEraser *eraser);					// 是否碰到小雞
		bool isOpen();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnShow(CGameMap *m);								// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定寶石的座標
		void SetIsOpen(bool alive);								// 設定是否活著
	protected:
		CMovingBitmap treasureBmp;			// 球的圖	
		int x, y;				// 寶石的座標
		bool is_Open;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}