#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <string.h>
#include "Asteroids.h"


int hkp_barycentr(double ax, double ay, double bx, double by, double cx, double cy,double mx, double my)
{
	int decision;
	double areatr = (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
	double areamr1= (bx - mx)*(cy - my) - (by - my)*(cx - mx);
	double areamr2 = (ax - mx)*(cy - my) - (ay - my)*(cx - mx);
	double areamr3 = (bx - mx)*(ay - my) - (by - my)*(ax - mx);
	double a1 = fabs(areamr1 / areatr);
	double a2 = fabs(areamr2 / areatr);
	double a3 = fabs(areamr3 / areatr);
	//printf("a1=%lf  a2=%lf a3= %lf\n", a1, a2, a3);
	if (a1 < 1.0 && a2 < 1.0 && a3 < 1.0)
	{
		decision = 1;
	}
	else
	{
		decision = 0;
	}
	return decision;
}
bool CheckCollision_astmsl(int tx,int ty,int tw,int th,int mx,int my)
{
	double x1 = tx;
	double y1 = ty - th;
	double x2 = tx + tw / 8.0;
	double y2 = ty - th / 2.0;
	double x3 = tx + tw;
	double y3 = ty;
	double x4 = tx + tw / 2.0;
	double y4 = ty + th / 4.0;
	double x5 = tx;
	double y5 = ty+th;
	double x6 = tx - tw / 2.0;
	double y6=ty + th / 8.0;
	double x7 = tx - tw;
	double y7 = ty;
	double x8 = tx - tw / 4.0;
	double y8 = ty - th / 2.0;

	int d1 = hkp_barycentr(x1, y1, x2, y2, x3, y3, mx, my);
	int d2= hkp_barycentr(x1, y1, x3, y3, x4,y4,mx, my);
	int d3 = hkp_barycentr(x1, y1, x4, y4, x5, y5, mx, my);
	int d4 = hkp_barycentr(x1, y1, x5, y5, x6, y6, mx, my);
	int d5 = hkp_barycentr(x1, y1, x6, y6, x7, y7, mx, my);
	int d6 = hkp_barycentr(x1, y1, x7, y7, x8, y8, mx, my);
	if (d1 == 1 || d2 == 1 || d3 == 1 || d4 == 1 || d5 == 1 || d6 == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool checkplayercollision_astply(double px, double py, double tx, double ty, double tw, double th)
{
	double r = 10.0;
    double x1 = px + r;
	double y1 = py;
	double x2 = px - r;
	double y2 = py + r / 2;
	double x3 = px - r;
	double y3 = py - r / 2;
	bool d1 = CheckCollision_astmsl(tx, ty, tw, th, x1, y1);
	bool d2 = CheckCollision_astmsl(tx, ty, tw, th, x2, y2);
	bool d3 = CheckCollision_astmsl(tx, ty, tw, th, x3, y3);
	if (d1 == true || d2 == true || d3 == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
GameObject::GameObject()
{
	x = 0;
	y = 0;
}
GameObject::GameObject(const GameObject &incoming)
{
	x = incoming.x;
	y = incoming.y;
}
GameObject &GameObject::operator=(const GameObject &incoming)
{
	CleanUp();
	x = incoming.x;
	y = incoming.y;
	return *this;
}
GameObject::~GameObject()
{
	CleanUp();
}
void GameObject::CleanUp(void)
{
	x = 0;
	y = 0;
}

GameObjectWithState::GameObjectWithState()
{
	x = 0;
	y = 0;
	state = 0;
}
GameObjectWithState::GameObjectWithState(const GameObjectWithState &incoming)
{
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
}
GameObjectWithState &GameObjectWithState::operator=(const GameObjectWithState &incoming)
{
	CleanUp();
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
	return *this;
}
GameObjectWithState::~GameObjectWithState()
{
	CleanUp();
}
void GameObjectWithState::CleanUp(void)
{
	x = 0;
	y = 0;
	state = 0;
}

Missile::Missile()
{
	x = 0;
	y = 0;
	state = 0;
	angle = 0;
	vx = 0;
	vy = 0;
}
Missile::Missile(const Missile &incoming)
{
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
	angle = incoming.angle;
	vx = incoming.vx;
	vy = incoming.vy;
}
Missile &Missile::operator=(const Missile &incoming)
{
	CleanUp();
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
	angle = incoming.angle;
	vx = incoming.vx;
	vy = incoming.vy;
	return *this;
}
Missile::~Missile()
{
	CleanUp();
}
void Missile::CleanUp(void)
{
	x = 0;
	y = 0;
	state = 0;
	angle = 0;
	vx = 0;
	vy = 0;
}
double Missile::Getx(void) const
{
	return x;
}
double Missile::Gety(void) const
{
	return y;
}
int Missile::Getstate(void) const
{
	return state;
}
void Missile::Initialize(void)
{
	x=0;
	y=0;
	state=0;
}

void Missile::Fire(double sx,double sy, double sangle)
{
	state=1;
	x=sx;
	y=sy;
	angle = sangle;
}

void Missile::Move(double v)
{
	
	vx = cos(angle) * v;   //set x velocity
	vy = sin(angle) * v;  //set y velocity
	x += vx;
	y += vy;
	if (800<x)
	{
		state = 0;
	}
	if (0>x)
	{
		state=0;
	}

	if (600<y)
	{
		state=0;
	}
	if (0>y)
	{
		state=0;
	}
}

void Missile::Steer(void)
{
	if(0!=FsGetKeyState(FSKEY_Z))
	{
		x-=2*cos(angle);
		y -= 2 * sin(angle);
	}
	if(0!=FsGetKeyState(FSKEY_X))
	{
	x += 2 * cos(angle);
	y += 2 * sin(angle);
	}
}

void Missile::Draw(void)
{
	Getx();
	Gety();
	Getstate();
	if (0 != state)
	{
		double mx = x + 7.5*cos(angle);
		double my = y + 7.5*sin(angle);
		//printf("%lf %lf %lf %lf \n", x, y, mx, my);
		glShadeModel(GL_SMOOTH);

		glBegin(GL_LINES);
		glColor3ub(255, 255, 0);
		glVertex2d(x, y);
		glColor3ub(255, 150, 0);
		glVertex2d(mx, my);
		glEnd();
	}
}

bool Missile::CheckCollision(class Target &t)
{
	return ::CheckCollision_astmsl(t.x, t.y, t.w, t.h, x, y);
}




Target::Target()
{
	x = 0;
	y = 0;
	state = 0;
	w = 0;
	h = 0;
	vx = 0;
	vy = 0;
}
Target::Target(const Target &incoming)
{
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
	w = incoming.w;
	h = incoming.h;
	vx = incoming.vx;
	vy = incoming.vy;
}
Target &Target::operator=(const Target &incoming)
{
	CleanUp();
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
	w = incoming.w;
	h = incoming.h;
	vx = incoming.vx;
	vy = incoming.vy;
	return *this;
}
Target::~Target()
{
	CleanUp();
}
void Target::CleanUp(void)
{
	x = 0;
	y = 0;
	state = 0;
	w = 0;
	h = 0;
	vx = 0;
	vy = 0;
}
double Target::Getx(void) const
{
	return x;
}
double Target::Gety(void) const
{
	return y;
}
int Target::Getstate(void) const
{
	return state;
}

void Target::Initialize(class Player &p)
{
	state = 1;
	x = rand() % 800;
	y = rand() % 600;
	if (fabs(x - p.x) + fabs(y - p.y)  <= 120.0)
	{
		x = rand() % 800;
		y = rand() % 600;
		if (fabs(x - p.x) + fabs(y - p.y) <= 120.0)
		{
			x = rand() % 800;
			y = rand() % 600;
		}
	}
	w = 15 + rand() % 5;
	h = 10 + rand() % 10;
	vx = 1 + rand() % 2;
	vy = rand() %1 - 2;
}

void Target::drawasteroids(double w, double h) const
{
	glShadeModel(GL_SMOOTH);
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(255, 255, 0);
	glVertex2d(x, y - h);
	glVertex2d(x + w / 8.0, y - h / 2.0);
	glColor3ub(255, 120, 0);
	glVertex2d(x + w, y);
	glVertex2d(x + w / 2.0, y + h / 4.0);
	glVertex2d(x, y + h);
	glColor3ub(175, 50, 0);
	glVertex2d(x - w / 2.0, y + h / 8.0);
	glColor3ub(170, 30, 0);
	glVertex2d(x - w, y);
	glVertex2d(x - w / 4.0, y - h / 2.0);
	glEnd();
}

void Target::Move(void)
{
	x+=vx;
	y += vy;
	if(800<x)
	{
		x=0;
	}
	if (0>x)
	{
		x=800;
	}
	
	if (600<y)
	{
		y = 0;
	}
	if (0>y)
	{
		y = 600;
	}
}



void Target::Draw(void)
{
	if(0!=state)
	{
		drawasteroids(w, h);
	}
}


Player::Player()
{
	x = 0;
	y = 0;
	state = 0;
	angle = 0;
	vx = 0;
	vy = 0;
}
Player::Player(const Player &incoming)
{
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
	angle = incoming.angle;
	vx = incoming.vx;  
	vy = incoming.vy;
}
Player &Player::operator=(const Player &incoming)
{
	CleanUp();
	x = incoming.x;
	y = incoming.y;
	state = incoming.state;
	angle = incoming.angle;
	vx = incoming.vx;
	vy = incoming.vy;
	return *this;
}
Player::~Player()
{
	CleanUp();
}
void Player::CleanUp(void)
{
	x = 0;
	y = 0;
	state = 0;
	angle = 0;
	vx = 0;
	vy = 0;
}
double Player::Getx(void) const
{
	return x;
}
double Player::Gety(void) const
{
	return y;
}
int Player::Getstate(void) const
{
	return state;
}

void Player::Initialize(double sx,double sy, double sangle)
{
	x=sx;
	y=sy;
	angle = sangle;
}

double Player::rotateplayerx(double x1, double y1) const
{
	double xn = (x1 - x)*cos(angle) - (y1 - y)*sin(angle) + x;
	return xn;
}
double Player::rotateplayery(double x1, double y1) const
{
	double yn = (x1 - x)*sin(angle) + (y1 - y)*cos(angle) + y;
	return yn;
}
void Player::DrawPlayer(void) const
{
	double r = 15.0;

	double x1 = x + r;
	double y1 = y;
	double x2 = x - r;
	double y2 = y + r / 2;
	double x3 = x - r;
	double y3 = y - r / 2;
	double x4 = x - 1.5*r;
	//printf("Beforerot: x1=%lf y1=%lf x2=%lf y2=%lf x3=%lfy3=%lf \n", x1, y1, x2, y2, x3, y3);
	double x1n = rotateplayerx(x1, y1);
	double y1n = rotateplayery(x1, y1);
	double x2n = rotateplayerx(x2, y2);
	double y2n = rotateplayery(x2, y2);
	double x3n = rotateplayerx(x3, y3);
	double y3n = rotateplayery(x3, y3);
	double x4n = rotateplayery(x4, y2);
	double x5n = rotateplayery(x4, y3);
	//printf("Aftertrans: x1=%lf y1=%lf x2=%lf y2=%lf x3=%lfy3=%lf \n", x1n, y1n, x2n, y2n, x3n, y3n);
	
	glShadeModel(GL_SMOOTH); 
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(0, 150, 255);
	glVertex2d(x1n, y1n);
	glColor3ub(0, 255, 255);
	glVertex2d(x2n, y2n);
	glColor3ub(0, 255, 255);
	glVertex2d(x3n, y3n);


	glEnd();
}

void Player::DrawFire(void) const
{	
		double rf = 15.0;

		double x1 = x - 1.2*rf;
		double y1 = y-rf/2;
		double x2 = x - 2.0*rf;
		double y2 = y - rf / 2.0;
		double x3 = x - 1.2*rf;
		double y3 = y;
		double x4 = x - 2.0*rf;
		double y4 = y + rf / 2.0;
		double x5 = x - 1.2*rf;
		double y5 = y + rf / 2.0;
		//printf("Beforerot: x1=%lf y1=%lf x2=%lf y2=%lf x3=%lfy3=%lf \n", x1, y1, x2, y2, x3, y3);
		double x1n = rotateplayerx(x1, y1);
		double y1n = rotateplayery(x1, y1);
		double x2n = rotateplayerx(x2, y2);
		double y2n = rotateplayery(x2, y2);
		double x3n = rotateplayerx(x3, y3);
		double y3n = rotateplayery(x3, y3);
		double x4n = rotateplayerx(x4, y4);
		double y4n = rotateplayery(x4, y4);
		double x5n = rotateplayerx(x5, y5);
		double y5n = rotateplayery(x5, y5);
		//printf("Aftertrans: x1=%lf y1=%lf x2=%lf y2=%lf x3=%lfy3=%lf \n", x1n, y1n, x2n, y2n, x3n, y3n);
		
		glBegin(GL_LINE_LOOP);

		glVertex2d(x1n, y1n);
		glVertex2d(x2n, y2n);
		glVertex2d(x3n, y3n);
		glVertex2d(x4n, y4n);
		glVertex2d(x5n, y5n);
		glEnd();
	
}
void Player::Move(void)
{
	if (800<x)
	{
		x = 0;
	}
	if (0>x)
	{
		x = 800;
	}

	if (600<y)
	{
		y = 0;
	}
	if (0>y)
	{
		y = 600;
	}
}
void Player::steer(void)
{
	if (0 != FsGetKeyState(FSKEY_Z))
	{
		vx = -2 * cos(angle);
		vy = -2 * sin(angle);
		
	}
	if (0 != FsGetKeyState(FSKEY_X))
	{
		vx = 2 * cos(angle);
		vy = 2 * sin(angle);
	}
}
void Player::Draw(void) const
{
	//printf("xini=%lf yini= %lf\n", x, y);
	DrawPlayer();
	//DrawFire();
	//printf("xini=%lf yini= %lf\n", x, y);
}
void Player::DrawPlayerBOOMast(void) const
{
	double w = 25;
	double h = 20;
	double w1 = 30;
	double h1 = 25;
	glColor3ub(255, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(x, y - h);
	glVertex2d(x + w / 8.0, y - h / 2.0);
	glVertex2d(x + w, y);
	glVertex2d(x + w / 2.0, y + h / 4.0);
	glVertex2d(x, y + h);
	glVertex2d(x - w / 2.0, y + h / 8.0);
	glVertex2d(x - w, y);
	glVertex2d(x - w / 4.0, y - h / 2.0);
	glEnd();

	glColor3ub(255, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x, y - h);
	glVertex2d(x + w1 / 8.0, y - h1 / 2.0);
	glVertex2d(x + w1, y);
	glVertex2d(x + w1 / 2.0, y + h1 / 4.0);
	glVertex2d(x, y + h);
	glVertex2d(x - w1 / 2.0, y + h1 / 8.0);
	glVertex2d(x - w1, y);
	glVertex2d(x - w1 / 4.0, y - h1 / 2.0);
	glEnd();
	glColor3ub(255, 255, 0);
	glRasterPos2d(x - w, y);
	YsGlDrawFontBitmap16x20("CRASH");
}
void Player::DrawBOOM(void) const
{	
	DrawPlayerBOOMast();
}
bool Player::CheckCollision(class Target &t)
{
	return ::checkplayercollision_astply(x,y,t.x, t.y, t.w, t.h);
}
void AsteroidsGame::RunGameMenu(int keyM)
{
	if (keyM == 0 || keyM==2 || keyM == 3 || keyM == 4 || keyM == 5)
	{
		return;
	}
	int x = 0;
	int XMAX = 800;
	int YMAX = 600;
	int y = 0;


	glColor3ub(255, 255, 255);
	glRasterPos2d(x + 10, y + 20);
	YsGlDrawFontBitmap10x14("Game Instructions:");
	glColor3ub(255, 255, 255); 
	glRasterPos2d(x + 10, y + 40);
	YsGlDrawFontBitmap10x14("Shoot at Asteroids to score points");
	glRasterPos2d(x + 10, y + 60);
	YsGlDrawFontBitmap10x14("Once you shoot all Asteroids, new set of asteroids will be created");
	glRasterPos2d(x + 10, y + 80);
	YsGlDrawFontBitmap10x14("The speed of the Asteroids will increase when you level-up in the game");
	glRasterPos2d(x + 10, y + 100);
	YsGlDrawFontBitmap10x14("If Asteroids hits the player, player will lose 1 life.");
	glRasterPos2d(x + 10, y + 120);
	YsGlDrawFontBitmap10x14("The Player has 3 lives in total");
	glRasterPos2d(x + 10, y + 160);
	YsGlDrawFontBitmap10x14("Game Commands:");
	glRasterPos2d(x + 10, y + 180);
	YsGlDrawFontBitmap10x14("To Move Player forward: Press UP");
	glRasterPos2d(x + 10, y + 200);
	YsGlDrawFontBitmap10x14("To Move Player Backward: Press DOWN");
	glRasterPos2d(x + 10, y + 220);
	YsGlDrawFontBitmap10x14("To Rotate Player clockwise: Press RIGHT");
	glRasterPos2d(x + 10, y + 240);
	YsGlDrawFontBitmap10x14("To Rotate Player counterclockwise: Press LEFT");
	glRasterPos2d(x + 10, y + 260);
	YsGlDrawFontBitmap10x14("To Shoot Missile: Press SPACE");
	glRasterPos2d(x + 10, y + 280);
	YsGlDrawFontBitmap10x14("To increse speed of Missile: Press X");
	glRasterPos2d(x + 10, y + 300);
	YsGlDrawFontBitmap10x14("To reduce the speed of Missile: Press Z");


	glRasterPos2d(x + 10, y + 320);
	YsGlDrawFontBitmap10x14("To Resume Game: Press R");
	glRasterPos2d(x + 10, y + 360);
	YsGlDrawFontBitmap10x14("Scoring Rubric:");
	glRasterPos2d(x + 10, y + 380);
	YsGlDrawFontBitmap10x14("Every succcessful shoot will earn 10 points");
	glRasterPos2d(x + 10, y + 400);
	YsGlDrawFontBitmap10x14("After level-up, score will increase by 10 x level#");
	glRasterPos2d(x + 10, y + 420);
	YsGlDrawFontBitmap10x14("You win the game when you complete level 5.");

	glRasterPos2d(x + 10, y + 460);
	YsGlDrawFontBitmap10x14("Press R to go back to game.");
	glRasterPos2d(x + 10, y + 480);
	YsGlDrawFontBitmap10x14("Press ESC to Exit.");

	return;
}
void AsteroidsGame::DrawLevel(int keyM,int ncount)
{
	if (keyM == 0 || keyM == 1 || keyM==3 || keyM == 4 || keyM == 5)
	{
		return;
	}
	char buff[100];
	sprintf(buff, "%d", ncount);
	glColor3ub(255, 255, 255);
	//char nc = itoa(ncount);
	glRasterPos2d(100, 290);
	YsGlDrawFontBitmap16x20("Level-");
	glRasterPos2d(200, 290);
	YsGlDrawFontBitmap16x20(buff);
	glRasterPos2d(100, 340);
	YsGlDrawFontBitmap16x20("Press R to continue");
	
	
}

void AsteroidsGame::Drawplayerdestructor(int keyM, int nPAlive)
{
	if (keyM == 0 || keyM == 1 || keyM == 2 || keyM == 4 || keyM == 5)
	{
		return;
	}
	
	char buff[100];
	sprintf(buff, "%d", nPAlive);
	
	glColor3ub(255, 255, 255);
	//char nc = itoa(ncount);
	glRasterPos2d(100, 240);
	YsGlDrawFontBitmap16x20("Crashed with an Asteroid!");
	glRasterPos2d(100, 290);
	YsGlDrawFontBitmap16x20("You have");
	glRasterPos2d(250, 290);
	YsGlDrawFontBitmap16x20(buff);
	glRasterPos2d(280, 290);
	YsGlDrawFontBitmap16x20("more live(s) in this game");
	glRasterPos2d(100, 340);
	YsGlDrawFontBitmap16x20("Press R to continue");
}
void AsteroidsGame::waitasec(void)
{
	//printf("Start timer.\n");
	unsigned int t0 = time(NULL);
	while (time(NULL) - t0<2)
	{
	}
	
	//printf("End timer.\n");
}
void AsteroidsGame::DrawEnd(int KeyM, int Score)
{
	if (keyM == 0 || keyM == 1 || keyM == 2 || keyM == 3 || keyM == 5)
	{
		return;
	}
	char buff[100];
	sprintf(buff, "%d", Score);
	glColor3ub(255, 255, 255);
	glRasterPos2d(100, 240);
	YsGlDrawFontBitmap16x20("Crashed with an Asteroid!");
	glRasterPos2d(100, 290);
	YsGlDrawFontBitmap16x20("The Game Ends");

	glRasterPos2d(100, 340);
	YsGlDrawFontBitmap16x20("Your Score is:");
	glRasterPos2d(400, 340);
	YsGlDrawFontBitmap16x20(buff);
	glRasterPos2d(100, 390);
	YsGlDrawFontBitmap16x20("Press ESC to exit");
	
	
}

void AsteroidsGame::DrawWin(int KeyM, int Score)
{
	if (keyM == 0 || keyM == 1 || keyM == 2 || keyM == 3 || keyM == 5)
	{
		return;
	}
	char buff[100];
	sprintf(buff, "%d", Score);
	glColor3ub(255, 255, 255);
	glRasterPos2d(100, 240);
	YsGlDrawFontBitmap16x20("You Won!");
	glRasterPos2d(100, 290);
	YsGlDrawFontBitmap16x20("The Game Ends");

	glRasterPos2d(100, 340);
	YsGlDrawFontBitmap16x20("Your Score is:");
	glRasterPos2d(400, 340);
	YsGlDrawFontBitmap16x20(buff);
	glRasterPos2d(100, 390);
	YsGlDrawFontBitmap16x20("Press ESC to exit");


}


void AsteroidsGame::Drawinitial(int KeyM, class Player &p)
{
	if (keyM == 0 || keyM == 1 || keyM == 2 || keyM == 3 || keyM == 4)
	{
		return;
	}
	
	p.Draw();
	
	
	glColor3ub(255, 255, 255);
	glRasterPos2d(250, 250);
	YsGlDrawFontBitmap32x48("Asteroids");
	glRasterPos2d(250, 350);
	YsGlDrawFontBitmap16x20("Press R to begin");


}

int AsteroidsGame::play(void)
{
	
	const double HP_PI = 3.14;
	const double v = 10.0;
	double sx = 400.0;
	double sy = 300.0;
	double sangle = 0.0;

	int nPAlive = 3;
	
	int keyM = 5;
	
	const int nT=7;
	const int nM = 10;

	Missile msl[nM];
	Player player;
	Target tgt[nT];


	int ncount = 1;
	int terminate = 0;
	int score = 0;


	for(auto &m : msl)
	{
		m.Initialize();
	}

	player.Initialize(sx,sy,sangle);

	for(auto &t : tgt)
	{
		t.Initialize(player);
	}

	while (terminate == 0)
	{
		FsPollDevice();
		auto key = FsInkey();

		if (0 != FsGetKeyState(FSKEY_ESC))
		{
			terminate = 1;
			break;
		}
		if (FSKEY_H == key)
		{
			if (keyM == 0)
			{
				keyM = 1;
				
			}
			
		}
		if (FSKEY_R == key) // exit the help menu and resume the game
		{
			if (keyM == 1 || keyM==2 || keyM==3 || keyM == 5)
				keyM = 0;
			
		}
		if (0 != FsGetKeyState(FSKEY_LEFT) && keyM == 0)
		{
			player.angle -= HP_PI / 45.0;
		}
		if (0 != FsGetKeyState(FSKEY_RIGHT) && keyM == 0)
		{
			player.angle += HP_PI / 45.0;
		}
		if (0 != FsGetKeyState(FSKEY_DOWN) && keyM == 0)
		{
			player.x -= v*cos(player.angle);
			player.y -= v*sin(player.angle);
			player.Move();
		}
		if (0 != FsGetKeyState(FSKEY_UP) && keyM == 0)
		{

			player.x += v*cos(player.angle);
			player.y += v*sin(player.angle);
			player.Move();

		}
		if (FSKEY_SPACE == key&& keyM == 0)
		{
			for (auto &m : msl)
			{
				if (0 == m.state)
				{
					m.Fire(player.x, player.y, player.angle);
					break;
				}
			}
		}
		int wid, hei;
		FsGetWindowSize(wid, hei);
		//glViewport(0, 0, wid, hei);



		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		/*
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, wid, hei, 0, -1, 1);
		*/
		if (keyM == 5)
		{
			Drawinitial(keyM,player);
			for (auto t : tgt)
			{
				t.Draw();
			}
		}
		if (keyM == 0)
		{
			if (0 != FsGetKeyState(FSKEY_UP))
			{
				glColor3ub(255, 105, 0);
				player.DrawFire();

			}
			if (0 != FsGetKeyState(FSKEY_DOWN))
			{
				glColor3ub(128, 128, 128);
				player.DrawFire();

			}
			for (int i = 0; i < nT; ++i)
			{
				if (0 != tgt[i].state &&
					true == player.CheckCollision(tgt[i]))
				{
					player.state = 0;
					player.DrawBOOM();
					tgt[i].state = 0;
					nPAlive -= 1;
					//printf("No of players alive = %d\n", nPAlive);
					
					keyM = 3;
					break;

				}
			}
			if (0 == nPAlive)
			{
				keyM = 4;
			}
			for (int m = 0; m < nM; ++m)
			{
				if (0 != msl[m].state)
				{
					msl[m].Move(v);
					msl[m].Steer();
					for (int i = 0; i < nT; ++i)
					{
						if (0 != tgt[i].state &&
							true == msl[m].CheckCollision(tgt[i]))
						{
							score=score+ncount*10;
							tgt[i].state = 0;
							msl[m].state = 0;
							//printf("Hit!\n");
							break;
						}
					}
				}
			}

			int nAlive = 0;
			for (auto t : tgt)
			{
				nAlive += t.state;
			}

			if (0 == nAlive)
			{
				if (keyM != 3 && keyM != 4)
				{
					for (int kk = 0; kk < nM; ++kk)
					{
						msl[kk].state = 0;
					}
					++ncount;
					if (ncount > 5)
					{
						keyM = 4;
					}
					else
					{
						keyM = 2;


						//printf("Number of targets chassed= %d\n", ncount);
						for (auto &t : tgt)
						{

							t.Initialize(player);
							t.vx = (double)(0.75)*ncount*t.vx;
							t.vy = (double)(0.75)*ncount*t.vy;
							//printf("t.vx=%lf, t.vy=%lf\n", t.vx, t.vy);
						}
					}
				}
			}
		

			for (auto &t : tgt)
			{
				t.Move();
			}
			player.Draw();

			for (auto t : tgt)
			{
				t.Draw();
			}

			for (auto m : msl)
			{
				m.Draw();
			}
		}
		else if (keyM==1)
		{
			RunGameMenu(keyM);
		}
		
		else if (keyM == 3)
		{
			Drawplayerdestructor(keyM,nPAlive);
			//waitasec();
		}

		else if (keyM == 2)
		{
			DrawLevel(keyM, ncount);
		}
		else if (keyM == 4 && nPAlive==0)
		{
			DrawEnd(keyM,score);
			//waitasec();
			if (0 != FsGetKeyState(FSKEY_ESC))
			{
				break;
			}
		}
		else if (keyM == 4 && nPAlive >0)
		{
			DrawWin(keyM, score);
			//waitasec();
			if (0 != FsGetKeyState(FSKEY_ESC))
			{
				break;
			}
		}
		FsSwapBuffers();
		FsSleep(25);
		
}	
	return score;
}
