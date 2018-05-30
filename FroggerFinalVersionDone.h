

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include "fssimplewindow.h"



class Frog
{
public:
	int x, y, w, h, gametime, score;
	bool alive;
	void Draw(void);
	void ResetLocation(void);
	void Dead(int time1);
	void Winner(int time1);
	//void Reset(bool dead);
	bool CheckAlive(bool truck, bool car1, bool car2, bool occupied, bool missed);
	int PlayFrogger(void);
	//void Move(void);
	//int IsHitByBall(CannonBall & ball);

	//Default constructor
	Frog() {
		x = 450;
		y = 580;
		h = 35; //change later
		w = 16;
		score = 0;
		gametime = 0;
		alive = true;
	}
};


class Truck
{
public:
	int x1, x2, y, w, h, v;
	void Initialize(void);
	void Draw(void);
	void Move(void);
	bool IsHitByFrog(Frog & frog);
};

class Car
{
public:
	int x1, x2, x3, y, w, h, v;
	void Draw(int y, int R, int G, int B);
	void Move(int velocitycar);
	bool IsHitByFrog(Frog & frog, int y);
	//Default constructor
	Car() {
		srand(time(NULL));
		x1 = 200 + rand() % 600;
		srand(time(NULL));  //Need this srand() here or else doesn't randomize it. 
		x2 = x1 + 100 + rand() % 400;
		srand(time(NULL));
		x3 = x2 + 200;
		h = 30;
		w = 35;
		srand(time(NULL));


	}

};

class Turtle
{
public:
	int x1, x2, x3, y, w, h, v;
	void Draw(int y);
	void Move(void);
	bool IsUnderFrog(Frog &frog, int argy);
	/*int IsHitByFrog(Frog & frog);*/
	//Default constructor
	Turtle() {
		srand(time(NULL));
		x1 = rand() % 150;
		srand(time(NULL));  //Need this srand() here or else doesn't randomize it. 
		x2 = (x1 + 100 + rand() % 200);
		srand(time(NULL));
		x3 = x2 + 100 + rand() % 200;
		h = 20;
		w = 98;
		srand(time(NULL));
		v = 8 + rand() % 8; //velocity in pixels per frame
	}

};

class Log
{
public:
	int x1, x2, x3, y, h, v;
	void Draw(int y, int w);
	void Move(int velocity);
	bool IsUnderFrog(Frog &frog, int argy, int w);
	/*int IsHitByFrog(Frog & frog);*/
	//Default constructor
	Log() {
		srand(time(NULL));
		x1 = 300 + (rand() % 800);
		x2 = x1 + 300 + rand() % 200;
		srand(time(NULL));
		x3 = x1 + 400;
		h = 20;
		/*w = 100;*/ //changes anyways
	}

};

class Lilipad
{
public:
	int x, y;
	bool occupied;
	void Draw(void);
	void IsUnderFrog(Frog &frog);
	bool boolIsUnderFrog(Frog &frog);
	//Default constructor
	Lilipad() {
		y = 30;
		occupied = false;
	}

};

