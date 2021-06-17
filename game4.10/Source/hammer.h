namespace game_framework {
	class CEraser;
	class CMovingBitmap;
	class CGameMap;
	class Bomb;
	class Hammer
	{
	public:
		Hammer();
		int GetX1();
		int GetX2();
		int GetY1();
		int GetY2();
		bool pressChicken(CEraser *eraser);
		void touchChicken(CEraser *eraser);
		bool hammerTouchBomb(Bomb *bomb);
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void OnMove();
		void SetXY(int nx, int ny);
		void setDelay(int n);
	protected:
		CAnimation hammer;
		int x, y,delay;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}
