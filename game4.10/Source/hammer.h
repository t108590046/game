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
		bool pressChicken(CEraser *eraser);	//槌子壓到小雞
		void touchChicken(CEraser *eraser);	//小雞碰到槌子
		bool hammerTouchBomb(Bomb *bomb);	//槌子碰到炸彈
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void OnMove();
		void SetXY(int inputdelay,int nx, int ny);
	protected:
		CAnimation hammer;
		int x, y;
		int	delay;							//槌子的延遲
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}
