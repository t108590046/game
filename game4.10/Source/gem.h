namespace game_framework {
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
		void setShowNumGem(bool flag);							//設定是否顯示寶石數量
		void getGem(int n);										//更新目前寶石數量
		void setShowStore(bool flag);							//顯示商店價格
		void updatePriceOfHeart(int n);							//更新價格
	protected:
		CMovingBitmap gem_bitmap;								// 寶石的圖	
		CMovingBitmap gemLeft;									//顯示寶石數量的圖
		CMovingBitmap gemNumber_digits[10];						//顯示數字
		int x, y;												// 寶石的座標
		bool is_alive;											// 是否活著
		bool isShowNumGem;										//是否顯示目前的寶石數量
		bool isShowStore;										//是否顯示商店的價格
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
		int showNumGemCounter;
		int totalGem;
		int priceOfHeart;										//換生命的寶石數量
	};
}