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
		void SetXY(int type,int nx, int ny);
		void setIsOpenRock(bool flag);
		void openRock(CGameMap *m);
		int returnType();
	protected:
		CMovingBitmap rock[5];
		int x, y,rockType;
		bool isOpen;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}