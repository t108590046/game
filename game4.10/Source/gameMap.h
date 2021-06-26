namespace game_framework {
	class CEraser;
	class CGameMap {
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
		void Initialize(int n);												//��l�Ʀa��
		void OnMove(CEraser *c);											//����������
		int	 ScreenX(int x);												//�ù��y��
		int  ScreenY(int y);
		bool IsEmpty(int x, int y);											//�O�_�i�H�q�L
		bool IsLittleMove_horizontal(int x, int y);							//�O�_�b���������p����
		bool IsLittleMove_updown(int x, int y);								//�O�_�b���������p����
		bool ShowMovingDown();												//�^�ǵ�������
		bool ShowMovingUp();
		bool ShowMovingLeft();
		bool ShowMovingRight();
		void SetMovingDown(bool flag);										// �]�w���b���U����
		void SetMovingLeft(bool flag);										// �]�w���b��������
		void SetMovingRight(bool flag);										// �]�w���b���k����
		void SetMovingUp(bool flag);										// �]�w���b���W����
		void SetMovingDownL(bool flag);										// �]�w���b���U�p����
		void SetMovingLeftL(bool flag);										// �]�w���b�����p����
		void SetMovingRightL(bool flag);									// �]�w���b���k�p����
		void SetMovingUpL(bool flag);										// �]�w���b���W�p����
		bool touchThorn(int x, int y);										// �O�_�I��y�보��
		bool IsChangeScreen_Diagonal_RD(int x, int y);						//��������(�����B�����B�k�U�B�k�W�B���U�B���W)
		bool IsChangeScreen_horizontal(int x, int y);
		bool IsChangeScreen_Diagonal_RDandLU(int x, int y);
		bool IsChangeScreen_Diagonal_RUandLD(int x, int y);
		bool IsChangeScreen_UpOrDown(int x, int y);
		bool IsStandingWood(int x, int y);									//�O�_���b�i�W���i�U���Y
		bool IsStandingLittleWoodDoor(int x, int y);						//�O�_���b�i�U���i�W�����Y
		int  IsPipe(int x, int y, CEraser *c);								//�O�_�b����
		bool IsLittleDown(int x, int y);									
		bool IsScreenStopMoving(int x, int y);								//�����O�_�����
		bool IsChangeHeartMap(int x, int y);								//�O�_�i�J���ͩR��
		bool ChangeHeart(int x, int y);										//�O�_���ͩR
		bool IsGoToNextMap(int x, int y);									//�O�_�i�J�U�@��
		bool checkScreenMoVing();											//�O�_�������b����
		void goToNextMap(int n);											//�i�J�U�@��
		void beAir(int x, int y, int x2, int y2);							//�N�a���ܦ��Ů�
		void beLittleMovingDown(int x, int y, int x2, int y2);				//�N�a���ܦ������p����
		void beLittleMoving2(int x, int y, int x2, int y2);
		void returnSavePoint();												//�^��O���I
		void changeToHeartMap();											//���a�Ϩ촫�ͩR��
	protected:
		CMovingBitmap blue, green,yellow,stage1,stage2,stage3,changeHeartMap;//���J�a��
		int map[250][225];
		const int MW, MH;													//�a�ϨC����e
		int	 sx, sy;														//�����y��
		int nowMap;															//�ثe���a��
		bool isGoToChangeHeartMap;
		int savePointSx, savePointSy;										//�����I
		bool isMovingDown;													// �O�_���b���U����
		bool isMovingLeft;													// �O�_���b��������
		bool isMovingRight;													// �O�_���b���k����
		bool isMovingUp;													// �O�_���b���W����
		bool isMovingDownL;													// �O�_���b���U�p����
		bool isMovingLeftL;													// �O�_���b�����p����
		bool isMovingRightL;												// �O�_���b���k�p����
		bool isMovingUpL;													// �O�_���b���W�p����
		bool canChangeHeart;												// �O�_�i�H���ͩR
		int Stop_x, Stop_y;													// ��������d��
		int Screen_Height, Screen_Width;									//�Ѵ��ת����e
	};
}