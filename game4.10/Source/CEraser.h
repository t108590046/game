namespace game_framework {
	class CGameMap;
	class Bomb;
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					//小雞左上角 x 座標
		int  GetY1();					//小雞左上角 y 座標
		int  GetX2();					//小雞右下角 x 座標
		int  GetY2();					//小雞右下角 y 座標
		void Initialize(int n);			//設定初始值
		void LoadBitmap();				//載入圖形
		void OnMove(CGameMap *m,Bomb *bomb);					
		void OnShow(CGameMap *m);					
		void SetBombing(bool flag);		//設定正在下炸彈
		void SetMovingLeft(bool flag);	//設定正在往左移動
		void SetMovingRight(bool flag); //設定正在往右移動
		void SetMovingUp(bool flag);	//設定正在往上移動
		void SetPressDown(bool flag);	//設定按下
		void SetXY(int nx, int ny);		//設定小雞左上角座標
		void SetLanding(bool flag);		//設定小雞墜落
		void SetStepOnBomb(bool flag);	//設定小雞踩在炸彈上
		bool check_MovingLeft();		//小雞是否往左移動
		bool check_MovingRight();		//小雞是否往右移動
		bool check_IsBombing();			//小雞是否在放炸彈移動
		bool check_inPipe();			//小雞是否在水管裡
		bool checkCanPutBomb();			//小雞是否可以放炸彈
		bool checkOnFloor();			//小雞是否踩在地板上
		bool checkOnBomb();				//小雞是否在炸彈上
		void setShowHeart(bool flag);	//顯示生命
		void stopMoving();				//讓小雞停止移動
		void minusNowLife();			//扣一條命
		void addNowLife();				//加一條命
		int  getNowLife();				//取得目前生命
		void returnSavePoint();			//回到紀錄點
		void setHurt(bool flag);		//設定小雞受傷的狀態
		void healHeart();				//小雞補滿血
		void setChickenJumping(bool flag); //設定小雞正在跳
		bool getNowIsPipeGoToUp();		//小雞目前是否從水管往上
		bool getNowIsPipeGoToDown();	//小雞目前是否從水管往下
	protected:
		CAnimation animation;		//雞的動畫
		CAnimation goToLeft;		//雞向左
		CAnimation goToRight;		//雞向右
		CAnimation cantputBomb;		//雞放炸彈撞牆
		CMovingBitmap heart,emptyHeart;
		int x, y;					//擦子左上角座標
		int savePointX, savePointY;
		bool isBombing;			    //是否正在下炸彈
		bool isMovingLeft;			//是否正在往左移動
		bool isMovingRight;			//是否正在往右移動
		bool isMovingUp;			//是否正在往上移動
		bool isPressDown;			//是否按下
		bool is_landing;			//是否正在下降
		bool isStepOnBomb;			//是否站在炸彈上
		bool isInPipeGoToUp;		//是否從水管往上
		bool isInPipeGoToDown;		//是否從水管往下
		bool isShowHeart;			//是否顯示生命
		bool isCanPutBomb;			//是否可以放炸彈
		bool isHurt;				//是否受傷
		bool isJumping;				//是否正在跳
		int life_Max;				//生命上限
		int nowLife;				//目前生命
		int showHeartCounter;       //顯示生命計時器
		int jumpCounter;			//跳躍計時器
		int hurtCounter;			//受傷計時器
	};
}