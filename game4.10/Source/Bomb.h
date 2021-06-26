namespace game_framework {
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
		bool HitBomb(CEraser *eraser);							//�p���O�_��b���u�W
		bool HitBomb(Bomb *bomb);								//���u�O�_�I�쬵�u
		bool IsBombing();										//�O�_���b�z��
		void setIsOnBomb(bool flag);							//�]�w�O�_�|�b���u�W
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		bool beBombed(woodDoor *door);							//�O�_�Q����
		bool beBombed(Bomb *bomb);								
		bool beBombed(Treasure *treasure);						
		bool beBombed(Rock *rock);								
		bool beBombed(CEraser *eraser);
		bool beBombed(Enemy *enemy);
		bool beEnemyTouched(Enemy *enemy);						//�O�_�Q�ĤH�I��
		bool movingBombTouch(Enemy *enemy);						//�O�_�Q�ĤH�I��
		bool chickenPushBomb(CEraser *eraser);					//�p���O�_���쬵�u
		bool checkOnBomb(Bomb *bomb);							//�O�_�|�b���u�W
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
		void OnMove(CEraser *eraser, CGameMap *m);				// ����
		void OnShow(CGameMap *m);								// �N�ϧζK��e��
		void SetXY(int nx, int ny);								
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetBomb(bool flag);								// �]�w�O�_���b�U���u
		void setBombAnimation();								//���s���u�ʵe
		void setMovingRight(bool flag);
		void setMovingLeft(bool flag);
		void setIsBombing(bool flag);
	protected:
		CAnimation bmp;				
		CAnimation bmpBombing;
		int x, y;					
		bool is_alive;											// �O�_����
		bool is_putBomb;										//�O�_�񬵼u
		bool isMovingRight;
		bool isMovingLeft;
		bool isBombing;
		bool isLanding;
		bool isOnBomb;
	private:
		int bombTimeCounter,bombingTimeCounter;					//���u�P�z���p�ɾ�
	};
}