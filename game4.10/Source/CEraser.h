namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap;
	class Bomb;
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize(int n);				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove(CGameMap *m,Bomb *bomb);					// 移動擦子
		void OnShow(CGameMap *m);					// 將擦子圖形貼到畫面
		void SetBombing(bool flag);	// 設定是否正在下炸彈
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetPressDown(bool flag);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void SetLanding(bool flag);
		void SetStepOnBomb(bool flag);
		bool check_MovingLeft();
		bool check_MovingRight();
		bool check_IsBombing();
		bool check_inPipe();
		bool checkCanPutBomb();
		bool checkOnFloor();
		bool checkOnBomb();
		void setShowHeart(bool flag);
		void stopMoving();
		void minusNowLife();
		void addNowLife();
		int getNowLife();
		void returnSavePoint();
		void setHurt(bool flag);
		void healHeart();
		void setChickenJumping(bool flag);
		bool getNowIsPipeGoToUp();
		bool getNowIsPipeGoToDown();
	protected:
		CAnimation animation;		// 擦子的動畫
		CAnimation goToLeft;		//雞向左
		CAnimation goToRight;		//雞向右
		CAnimation cantputBomb;	   //雞放炸彈撞牆
		CMovingBitmap heart,emptyHeart;
		int x, y;					// 擦子左上角座標
		int savePointX, savePointY;
		bool isBombing;			    // 是否正在下炸彈
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isPressDown;			
		bool is_landing;			//正在下降
		bool isStepOnBomb;
		bool isInPipeGoToUp;
		bool isInPipeGoToDown;
		bool isShowHeart; 
		bool isCanPutBomb;
		bool isHurt;
		bool isJumping;
		int life_Max; //生命上限
		int nowLife; // 目前生命
		int showHeartCounter;
		int jumpCounter;
		int hurtCounter;
	};
}