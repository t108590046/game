namespace game_framework {
	class CEraser;
	class CMovingBitmap;
	class CGameMap;
	class Bomb;
	class Enemy
	{
	public:
		Enemy();
		int GetX1();
		int GetX2();
		int GetY1();
		int GetY2();
		bool touchChicken(CEraser *eraser);
		bool isAlive();
		void LoadBitmap();
		void OnShow(CGameMap *m);
		void OnMove(CGameMap *m);
		void SetXY(int type,int nx, int ny);
		void setIsAlive(bool flag);
	protected:
		CAnimation enemy[2][2];
		int x, y;
		bool is_alive;
		int typeEnemy;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}