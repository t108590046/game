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
		bool touchRock(Bomb *bomb);
		bool isOpenRock();
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void SetXY(int nx, int ny);
		void setIsOpenRock(bool flag);
		void openRock(CGameMap *m);
	protected:
		CMovingBitmap rock;
		int x, y;
		bool isOpen;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}