namespace game_framework {
	class CGameMap;
	class Bomb;
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					//�p�����W�� x �y��
		int  GetY1();					//�p�����W�� y �y��
		int  GetX2();					//�p���k�U�� x �y��
		int  GetY2();					//�p���k�U�� y �y��
		void Initialize(int n);			//�]�w��l��
		void LoadBitmap();				//���J�ϧ�
		void OnMove(CGameMap *m,Bomb *bomb);					
		void OnShow(CGameMap *m);					
		void SetBombing(bool flag);		//�]�w���b�U���u
		void SetMovingLeft(bool flag);	//�]�w���b��������
		void SetMovingRight(bool flag); //�]�w���b���k����
		void SetMovingUp(bool flag);	//�]�w���b���W����
		void SetPressDown(bool flag);	//�]�w���U
		void SetXY(int nx, int ny);		//�]�w�p�����W���y��
		void SetLanding(bool flag);		//�]�w�p���Y��
		void SetStepOnBomb(bool flag);	//�]�w�p����b���u�W
		bool check_MovingLeft();		//�p���O�_��������
		bool check_MovingRight();		//�p���O�_���k����
		bool check_IsBombing();			//�p���O�_�b�񬵼u����
		bool check_inPipe();			//�p���O�_�b���޸�
		bool checkCanPutBomb();			//�p���O�_�i�H�񬵼u
		bool checkOnFloor();			//�p���O�_��b�a�O�W
		bool checkOnBomb();				//�p���O�_�b���u�W
		void setShowHeart(bool flag);	//��ܥͩR
		void stopMoving();				//���p�������
		void minusNowLife();			//���@���R
		void addNowLife();				//�[�@���R
		int  getNowLife();				//���o�ثe�ͩR
		void returnSavePoint();			//�^������I
		void setHurt(bool flag);		//�]�w�p�����˪����A
		void healHeart();				//�p���ɺ���
		void setChickenJumping(bool flag); //�]�w�p�����b��
		bool getNowIsPipeGoToUp();		//�p���ثe�O�_�q���ީ��W
		bool getNowIsPipeGoToDown();	//�p���ثe�O�_�q���ީ��U
	protected:
		CAnimation animation;		//�����ʵe
		CAnimation goToLeft;		//���V��
		CAnimation goToRight;		//���V�k
		CAnimation cantputBomb;		//���񬵼u����
		CMovingBitmap heart,emptyHeart;
		int x, y;					//���l���W���y��
		int savePointX, savePointY;
		bool isBombing;			    //�O�_���b�U���u
		bool isMovingLeft;			//�O�_���b��������
		bool isMovingRight;			//�O�_���b���k����
		bool isMovingUp;			//�O�_���b���W����
		bool isPressDown;			//�O�_���U
		bool is_landing;			//�O�_���b�U��
		bool isStepOnBomb;			//�O�_���b���u�W
		bool isInPipeGoToUp;		//�O�_�q���ީ��W
		bool isInPipeGoToDown;		//�O�_�q���ީ��U
		bool isShowHeart;			//�O�_��ܥͩR
		bool isCanPutBomb;			//�O�_�i�H�񬵼u
		bool isHurt;				//�O�_����
		bool isJumping;				//�O�_���b��
		int life_Max;				//�ͩR�W��
		int nowLife;				//�ثe�ͩR
		int showHeartCounter;       //��ܥͩR�p�ɾ�
		int jumpCounter;			//���D�p�ɾ�
		int hurtCounter;			//���˭p�ɾ�
	};
}