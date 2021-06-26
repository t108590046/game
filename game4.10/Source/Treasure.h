namespace game_framework {
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
		bool isOpen();						// 是否活著
		void LoadBitmap();					// 載入圖形
		void OnShow(CGameMap *m);			// 將圖形貼到畫面
		void SetXY(int nx, int ny);			// 設定寶箱的座標
		void SetIsOpen(bool alive);			// 設定是否打開
	protected:
		CMovingBitmap treasureBmp;			// 寶箱的圖	
		int x, y;							// 寶箱的座標
		bool is_Open;						// 是否活著
	private:
	};
}