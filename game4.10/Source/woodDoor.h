namespace game_framework {
	class CEraser;
	class CMovingBitmap;
	class CGameMap;
	class woodDoor
	{
	public:
		woodDoor();
		int GetX1();
		int GetX2();
		int GetY1();
		int GetY2();
		bool touchDoor(Bomb *bomb);
		bool isOpenDoor();
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void SetXY(int nx, int ny);
		void setIsOpenDoor(bool flag);
		void openDoor(CGameMap *m);
	protected:
		CMovingBitmap door;
		int x, y;
		bool isOpen;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}