#ifndef SHOOT_CLASS_IS_INCLUDED
#define SHOOT_CLASS_IS_INCLUDED


class GameObject
{
public:
	double x,y;
	GameObject();
	~GameObject();
	void CleanUp(void);
	// Add copy constructor and copy-assignment operator
	GameObject(const GameObject &incoming);
	GameObject &operator=(const GameObject &incoming);
	
};
class GameObjectWithState : public GameObject
{
public:
	int state;
	GameObjectWithState();
	~GameObjectWithState();
	void CleanUp(void);
	// Add copy constructor and copy-assignment operator
	GameObjectWithState(const GameObjectWithState &incoming);
	GameObjectWithState &operator=(const GameObjectWithState &incoming);
};



class Missile : public GameObjectWithState
{
public:
	double vx,vy,angle;
	Missile();
	~Missile();
	void CleanUp(void);
	// Add copy constructor and copy-assignment operator
	Missile(const Missile &incoming);
	Missile &operator=(const Missile &incoming);
	double Getx(void) const;
	double Gety(void) const;
	int Getstate(void) const;
	
	void Initialize(void);
	void Fire(double sx,double sy, double angle);
	void Move(double v);
	bool CheckCollision(class Target &t);
	
	void Steer(void);
	void Draw(void);
};

class Target : public GameObjectWithState
{
public:

	double w,h,vx,vy;
	void Initialize(class Player &p);
	
	Target();
	~Target();
	void CleanUp(void);
	// Add copy constructor and copy-assignment operator
	Target(const Target &incoming);
	Target &operator=(const Target &incoming);
	double Getx(void) const;
	double Gety(void) const;
	int Getstate(void) const;
	void drawasteroids(double w, double h) const;

	
	void Move(void);
	
	void Draw(void);
};

class Player : public GameObjectWithState
{
public:
	double vx, vy, angle;
	int life;
	Player();
	~Player();
	void CleanUp(void);
	// Add copy constructor and copy-assignment operator
	Player(const Player &incoming);
	Player &operator=(const Player &incoming);
	double Getx(void) const;
	double Gety(void) const;
	int Getstate(void) const;
	void Initialize(double sx,double sy, double angle);

	double rotateplayerx(double xs, double ys) const;
	double rotateplayery(double xs, double ys) const;
	void DrawPlayer(void) const;
	void DrawFire(void) const;
	void DrawPlayerBOOMast(void) const;
	void Move(void);
	void steer(void);
	void Draw(void) const;
	void DrawBOOM(void) const;
	bool CheckCollision(class Target &t);
};


class AsteroidsGame
{
public:
	int keyM;
	void DrawLevel(int keyM, int ncount);
	void Drawinitial(int KeyM, class Player &p);
	void Drawplayerdestructor(int keyM, int nPAlive);
	void waitasec(void);
	void RunGameMenu(int keyM);
	void DrawEnd(int KeyM, int Score);
	void DrawWin(int KeyM, int Score);
	int play(void);
	
};

#endif
