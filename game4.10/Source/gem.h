namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class CMovingBitmap;
	class Gem
	{
	public:
		Gem();
		void Initialize();
		bool HitChicken(CEraser *eraser);						// �O�_�I��p��
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnShow(CGameMap *m);								// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w�_�۪��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void setShowNumGem(bool flag);
		void getGem(int n);
		void setShowStore(bool flag);
		void updatePriceOfHeart(int n);
	protected:
		CMovingBitmap gem_bitmap;			// �y����	
		CMovingBitmap gemLeft;
		CMovingBitmap gemNumber_digits[10];
		int x, y;				// �_�۪��y��
		bool is_alive;				// �O�_����
		bool isShowNumGem;
		bool isShowStore;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
		int showNumGemCounter;
		int totalGem;
		int priceOfHeart;
	};
}