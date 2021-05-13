namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class CMovingBitmap;
	class Treasure
	{
	public:
		Treasure();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		bool touchTreasure(CEraser *eraser);					// �O�_�I��p��
		bool isOpen();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnShow(CGameMap *m);								// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w�_�۪��y��
		void SetIsOpen(bool alive);								// �]�w�O�_����
	protected:
		CMovingBitmap treasureBmp;			// �y����	
		int x, y;				// �_�۪��y��
		bool is_Open;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}