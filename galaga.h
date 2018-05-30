

class Shooter{
public:
	int x = 400;
	int y = 60;
	void Draw();
	void Move(int direction);
	int mode = 3;
		
};

class Missle{
public:
	Missle(int inputx, int inputy);
	void Draw();
	int Move();
	int x;
	int y;
};

class Galaga{
public:
	int play(void);
};