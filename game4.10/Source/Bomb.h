namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class Bomb
	{
	public:
		Bomb();
		Bomb(int x,int y);
		bool HitBomb(CEraser *eraser);							// �O�_�I�����l
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void chickenPushBomb(CEraser *eraser);
		void OnMove(CEraser *eraser, CGameMap *m);				// ����
		void OnShow(CGameMap *m);								// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		//void SetDelay(int d);									// �]�w���઺�t��
		void SetBomb(bool flag);	// �]�w�O�_���b�U���u
		void setBombAnimation();
	protected:
		CAnimation bmp;				// �y����
		CMovingBitmap bmp_center;	// ��ߪ���
		int x, y;					// ��ߪ��y��
		//int dx, dy;				// �y�Z����ߪ��첾�q
		//int index;				// �y���u���סv�A0-17���0-360��
		//int delay_counter;		// �վ����t�ת��p�ƾ�
		//int delay;				// ���઺�t��
		bool is_alive;				// �O�_����
		bool is_putBomb;			//�O�_�񬵼u
		bool is_bePushed;			//�O�_�Q��
		clock_t start, finish;			
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��


	};
}