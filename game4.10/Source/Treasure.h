namespace game_framework {
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
		bool isOpen();						// �O�_����
		void LoadBitmap();					// ���J�ϧ�
		void OnShow(CGameMap *m);			// �N�ϧζK��e��
		void SetXY(int nx, int ny);			// �]�w�_�c���y��
		void SetIsOpen(bool alive);			// �]�w�O�_���}
	protected:
		CMovingBitmap treasureBmp;			// �_�c����	
		int x, y;							// �_�c���y��
		bool is_Open;						// �O�_����
	private:
	};
}