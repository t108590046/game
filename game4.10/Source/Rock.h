namespace game_framework {
	class CEraser;
	class CMovingBitmap;
	class CGameMap;
	class Bomb;
	class Rock
	{
	public:
		Rock();
		int GetX1();
		int GetX2();
		int GetY1();
		int GetY2();
		bool isOpenRock();
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void SetXY(int beWhichMap,int type,int nx, int ny);
		void setIsOpenRock(bool flag);
		void openRock(CGameMap *m);
		int returnType();		//回傳石頭的種類
	protected:
		CMovingBitmap rock[5];	//不同石頭的圖
		int x, y;
		int rockType;			//石頭的種類
		int WhichMap;			//被炸後要變成什麼地圖
		bool isOpen;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}