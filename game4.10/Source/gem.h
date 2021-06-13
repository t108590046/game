namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class CMovingBitmap;
	class Gem
	{
	public:
		Gem();
		void Initialize();
		bool HitChicken(CEraser *eraser);						// 是否碰到小雞
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnShow(CGameMap *m);								// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定寶石的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		void setShowNumGem(bool flag);
		void getGem(int n);
		void setShowStore(bool flag);
		void updatePriceOfHeart(int n);
	protected:
		CMovingBitmap gem_bitmap;			// 球的圖	
		CMovingBitmap gemLeft;
		CMovingBitmap gemNumber_digits[10];
		int x, y;				// 寶石的座標
		bool is_alive;				// 是否活著
		bool isShowNumGem;
		bool isShowStore;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
		int showNumGemCounter;
		int totalGem;
		int priceOfHeart;
	};
}