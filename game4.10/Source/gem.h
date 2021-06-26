namespace game_framework {
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
		void setShowNumGem(bool flag);							//�]�w�O�_����_�ۼƶq
		void getGem(int n);										//��s�ثe�_�ۼƶq
		void setShowStore(bool flag);							//��ܰө�����
		void updatePriceOfHeart(int n);							//��s����
	protected:
		CMovingBitmap gem_bitmap;								// �_�۪���	
		CMovingBitmap gemLeft;									//����_�ۼƶq����
		CMovingBitmap gemNumber_digits[10];						//��ܼƦr
		int x, y;												// �_�۪��y��
		bool is_alive;											// �O�_����
		bool isShowNumGem;										//�O�_��ܥثe���_�ۼƶq
		bool isShowStore;										//�O�_��ܰө�������
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
		int showNumGemCounter;
		int totalGem;
		int priceOfHeart;										//���ͩR���_�ۼƶq
	};
}