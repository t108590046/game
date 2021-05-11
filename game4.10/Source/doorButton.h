namespace game_framework {
	class CEraser;
	class CMovingBitmap;
	class CGameMap;
	class Button
	{
	public:
		Button();
		bool touchButton(CEraser *eraser);						
		bool IsTouched();										
		void LoadBitmap();										
		void OnShow(CGameMap *m);								
		void SetXY(int direction,int nx, int ny);
		void SetIsTouched(bool touched);						
	protected:
		CMovingBitmap button[4];
		int x, y;
		int btnDirection; //«ö¶sªº¤è¦V
		bool isTouched;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	
	};
}