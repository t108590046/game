namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CEraser;
	class woodDoor;
	class Treasure;
	class Rock;
	class Enemy;
	class Bomb
	{
	public:
		Bomb();
		int  GetX1();					
		int  GetY1();					
		int  GetX2();					
		int  GetY2();
		int  GetHeight();
		bool isMoving();
		bool HitBomb(CEraser *eraser);
		bool HitBomb(Bomb *bomb);// �O�_�I�����l
		bool IsBombing();
		void setIsOnBomb(bool flag);
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		bool beBombed(woodDoor *door);							//�O�_�Q����
		bool beBombed(Bomb *bomb);								
		bool beBombed(Treasure *treasure);						
		bool beBombed(Rock *rock);								
		bool beBombed(CEraser *eraser);
		bool beBombed(Enemy *enemy);
		bool beEnemyTouched(Enemy *enemy);
		bool movingBombTouch(Enemy *enemy);
		bool chickenPushBomb(CEraser *eraser);
		bool checkOnBomb(Bomb *bomb);
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
		void OnMove(CEraser *eraser, CGameMap *m);				// ����
		void OnShow(CGameMap *m);								// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		//void SetDelay(int d);									// �]�w���઺�t��
		void SetBomb(bool flag);	// �]�w�O�_���b�U���u
		void setBombAnimation();
		void setMovingRight(bool flag);
		void setMovingLeft(bool flag);
		void setIsBombing(bool flag);
	protected:
		CAnimation bmp;				// �y����
		CAnimation bmpBombing;
		CMovingBitmap bmp_center;	// ��ߪ���
		int x, y;					// ��ߪ��y��
		//int dx, dy;				// �y�Z����ߪ��첾�q
		//int index;				// �y���u���סv�A0-17���0-360��
		//int delay_counter;		// �վ����t�ת��p�ƾ�
		//int delay;				// ���઺�t��
		bool is_alive;				// �O�_����
		bool is_putBomb;			//�O�_�񬵼u
		bool isMovingRight;
		bool isMovingLeft;
		bool isBombing;
		bool isLanding;
		bool isOnBomb;
	private:
		int bombTimeCounter,bombingTimeCounter;

	};
}