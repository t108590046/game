namespace game_framework {
	class CEraser;
	class CMovingBitmap;
	class CGameMap;
	class Door
	{
	public:
		Door();
		bool touchDoor(CEraser *eraser);
		bool isOpenDoor();
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void SetXY(int type, int nx, int ny);
		void setIsOpenDoor(bool flag);
		void openDoor(CGameMap *m);
	protected:
		CMovingBitmap door[2];
		int x, y;
		int doorType; //門的種類
		bool isOpen;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}