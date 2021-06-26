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
		bool pressChicken(CEraser *eraser);	//�l�l����p��
		void touchChicken(CEraser *eraser);	//�p���I��l�l
		bool hammerTouchBomb(Bomb *bomb);	//�l�l�I�쬵�u
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void OnMove();
		void SetXY(int inputdelay,int nx, int ny);
	protected:
		CAnimation hammer;
		int x, y;
		int	delay;							//�l�l������
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}
