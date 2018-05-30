//Michael Goodspeed
//Engineering Computation
//Centipede game
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

//Class for the player that can move around
class Player
{
public:
	int state, x, y, lives;

	void Initialize(void);
};
void Player::Initialize(void)
{
	state = 1;
	x = 396;
	y = 544;
}

//Class for the missle
class Missle
{
public:
	int x, y, state;
	void Initialize(void);
	void MoveMissle(void);
};
void Missle::Initialize(void)
{
	state = 0;
	x = 0;
	y = 0;
}
void Missle::MoveMissle(void)
{
	y -= 10;
	//Checks hitting the top of the screen
	if (y - 10 < 0)
	{
		state = 0;
	}

}

//Class for the mushrooms
class Mushroom
{
public:
	int state, x, y;

	void Initialize(int coordinates[], int icount);
};
void Mushroom::Initialize(int coordinates[], int icount)
{
	x = coordinates[icount] % 50;
	y = coordinates[icount] / 50;
	state = 4;

}
//Creates random location for mushrooms to start with no overlap
void SwapInt(int &a, int &b)
{
	int c;
	c = a;
	a = b;
	b = c;
}
void RandomShroom(int shroom[50*36])
{
	int i;
	for (i = 0; i<(50*33); i++)
	{
		shroom[i] = i;
	}

	for (i = 0; i<(50*33); i++)
	{
		int r = rand() % (50*33);
		SwapInt(shroom[i], shroom[r]);
	}
}

//Class for the Centipede
class Centipede
{
public:
	int x, y, state, vx, vy, xhist[9], yhist[9], hitdetect, bottomdetect, draweyes;
	void Initialize(int centspeed, int xstart);
};
void Centipede::Initialize(int centspeed, int xstart)
{
	x = xstart;
	y = 0;
	state = 1;
	vx = centspeed;
	vy = 0;
	hitdetect = 0;
	bottomdetect = 0;
	draweyes = 0;
	for (int i = 0; i < 9; i++)
	{
		xhist[i] = 0;
		yhist[i] = 0;
	}
}

//Class for Spider (22 wide)
class Spider
{
public:
	int state, move;
	double x, y;
	void Initialize(void);
	void MoveSpider(int px, int py, double sx, double sy, int movecounter, int level);
};
void Spider::Initialize(void)
{
	state = 1;
	x = 0;
	y = 400;
	move = 0;
}
void Spider::MoveSpider(int px, int py, double sx, double sy, int movecounter, int level)
{

	int multiplier;
	if (level == 1 || level == 2)
	{
		multiplier = 2;
	}
	else
	{
		multiplier = 3;
	}
	double xdifference = sx - px;
	double ydifference = sy - py;
	//Player is to the right and below
	if (xdifference<0 && ydifference<0 && y+16<=560 && x+22 <=800)
	{
		if (px > 800 - 18 && x >= 800 - 26)
		{
			y += multiplier;
			if (y >= py)
			{
				move = 0;
				movecounter = 0;
			}
		}
		else
		{
			double theta = atan((double)xdifference / (double)ydifference);
			x += multiplier * sin(theta);
			y += multiplier * cos(theta);
			if (x >= px && y >= py)
			{
				move = 0;
				movecounter = 0;
			}
		}

	}
	//Player is to the right and above
	if (xdifference<0 && ydifference>0 && y >=400 && x + 22 <=800)
	{
		if (px > 800 - 18 && x >= 800 - 26)
		{
			y -= multiplier;
			if (y <= py)
			{
				move = 0;
				movecounter = 0;
			}
		}
		else
		{
			double theta = atan((double)ydifference / (double)xdifference);
			x += multiplier * cos(theta);
			y += multiplier * sin(theta);
			if (x >= px && y <= py)
			{
				move = 0;
				movecounter = 0;
			}
		}
	}
	//Player is to the left and below
	if (xdifference>0 && ydifference<0 && y + 16<=560 && x>=0)
	{
		double theta = atan((double)xdifference / (double)ydifference);
		x += multiplier * sin(theta);
		y += multiplier * cos(theta);
		if (x <= px && y >= py)
		{
			move = 0;
			movecounter = 0;
		}
	}
	//Player is to the left and above
	if (xdifference>0 && ydifference>0 && y >=400 && x>=0)
	{
		double theta = atan((double)ydifference / (double)xdifference);
		x -= multiplier * cos(theta);
		y -= multiplier * sin(theta);
		if (x <= px && y <= py)
		{
			move = 0;
			movecounter = 0;
		}
	}
	//Player is to the right
	if (xdifference<0 && ydifference==0 && x+22<= 800)
	{
		x += multiplier;
		if (x >= px)
		{
			move = 0;
			movecounter = 0;
		}
	}
	//Player is to the left
	if (xdifference>0 && ydifference == 0 && x>=0)
	{
		x -= multiplier;
		if (x <= px)
		{
			move = 0;
			movecounter = 0;
		}
	}
	//Player is above
	if (xdifference==0 && ydifference >=0 && y>=400)
	{
		y -= multiplier;
		if (y <= py)
		{
			move = 0;
			movecounter = 0;
		}
	}
	//Player is below
	if (xdifference == 0 && ydifference <=0 && y+16<=560)
	{
		y += multiplier;
		if (y >= py)
		{
			move = 0;
			movecounter = 0;
		}
	}

	if (x < 0)
	{
		x = 0;
		move = 0;
		movecounter = 0;
	}
	if (x + 22 > 800)
	{
		x= 800-22;
		move = 0;
		movecounter = 0;
	}
	if (y < 400)
	{
		y = 400;
		move = 0;
		movecounter = 0;
	}
	if (y + 16 > 560)
	{
		y = 560 - 16;
		move = 0;
		movecounter = 0;
	}


}

//Check missile collision with mushroom
int CentipedeCheckShroomCollision(int mx, int my, int mstate, int sx, int sy, int sstate, int &score)
{
	if (mstate == 1 && sstate != 0 && (mx + 9) >= sx*16 && (mx + 7) <= (sx*16 + 16) && (my-10)<((sy+1)*16) &&(my-10)>((sy+1)*16-15))
	{
		score += 5;
		return 1;
	}
	else
	{
		return 0;
	}
}
//Check missile collision with centipede
int CentipedeCheckCentCollision(int mx, int my, int mstate, int cx, int cy, int cstate, int &score)
{
	if (mstate == 1 && cstate != 0 && (mx + 9) >= cx && (mx + 7) <= (cx + 16) && (my - 10)<(cy+16) && (my - 10)>cy)
	{
		score += 25;
		return 1;
	}
	else
	{
		return 0;
	}
}
//Check centipede collision with player
int CentipedeCheckCentPlyrCollision(int px, int py, int pstate, int cx, int cy, int cstate, int &score)
{
	//Left side
	if (pstate == 1 && cstate != 0 && (px + 14) >= cx && (px + 7) <= (cx + 16) && (py+16)>(cy) && (py)<(cy+16))
	{
		score -= 500;
		return 1;
	}
	//Right side
	if (pstate == 1 && cstate != 0 && (px) <= (cx+14) && (px) >= (cx + 7) && (py + 16)>(cy) && (py)<(cy + 16))
	{
		score -= 500;
		return 1;
	}
	//Top side
	if (pstate == 1 && cstate != 0 && (py+14) >= (cy) && (py+7) <= (cy) && (px + 16)>(cx) && (px)<(cx + 16))
	{
		score -= 500;
		return 1;
	}
	//Bottom side
	if (pstate == 1 && cstate != 0 && (py) <= (cy+14) && (py) >= (cy+7) && (px + 16)>(cx) && (px)<(cx + 16))
	{
		score -= 500;
		return 1;
	}
	return 0;
}
//Check missile collision with spider
int CentipedeCheckSpiderCollision(int mx, int my, int mstate, int sx, int sy, int sstate, int &score)
{
	if (mstate == 1 && sstate != 0 && (mx + 9) >= sx && (mx + 7) <= (sx + 22) && (my - 10)<(sy + 16) && (my - 10)>sy)
	{
		score += 250;
		return 1;
	}
	else
	{
		return 0;
	}
}
//Check spider collision with player
int CentipedeCheckSpdrPlyrCollision(int px, int py, int pstate, int sx, int sy, int sstate, int &score)
{
	//Left side
	if (pstate == 1 && sstate != 0 && (px + 14) >= sx && (px + 7) <= (sx + 22) && (py + 16)>(sy) && (py)<(sy + 16))
	{
		score -= 500;
		return 1;
	}
	//Right side
	if (pstate == 1 && sstate != 0 && (px) <= (sx + 20) && (px) >= (sx + 7) && (py + 16)>(sy) && (py)<(sy + 16))
	{
		score -= 500;
		return 1;
	}
	//Top side
	if (pstate == 1 && sstate != 0 && (py + 14) >= (sy) && (py + 7) <= (sy) && (px + 16)>(sx) && (px)<(sx + 22))
	{
		score -= 500;
		return 1;
	}
	//Bottom side
	if (pstate == 1 && sstate != 0 && (py) <= (sy + 14) && (py) >= (sy + 7) && (px + 16)>(sx) && (px)<(sx + 22))
	{
		score -= 500;
		return 1;
	}
	return 0;
}

//Draws the background
void CentipedeBackgroundColor(void)
{
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 600);
	glVertex2i(0, 600);
	glEnd();

	glColor3ub(25, 25, 25);
	glBegin(GL_QUADS);
	glVertex2i(0, 560);
	glVertex2i(800, 560);
	glVertex2i(800, 600);
	glVertex2i(0, 600);
	glEnd();

}
//Draws the player
void CentipedeDrawPlayer(int x, int y, int level)
{
	
	if (level == 1)
	{
		glColor3ub(210, 180, 140);
	}
	else if(level == 2)
	{
		glColor3ub(255, 255, 0);
	}
	else
	{
		glColor3ub(0, 255, 255);
	}
	glBegin(GL_QUADS);
	glVertex2i(x+5, y+2);
	glVertex2i(x+11, y+2);
	glVertex2i(x+11, y+16);
	glVertex2i(x+5, y+16);

	glVertex2i(x, y + 6);
	glVertex2i(x + 16, y + 6);
	glVertex2i(x + 16, y + 10);
	glVertex2i(x, y + 10);

	glVertex2i(x+2, y + 4);
	glVertex2i(x + 14, y + 4);
	glVertex2i(x + 14, y + 12);
	glVertex2i(x+2, y + 12);


	if (level == 1)
	{
		glColor3ub(255, 0, 0);
	}
	else if (level == 2)
	{
		glColor3ub(0, 255, 0);
	}
	else
	{
		glColor3ub(255, 255, 0);
	}
	glVertex2i(x + 2, y + 4);
	glVertex2i(x + 6, y + 4);
	glVertex2i(x + 6, y + 8);
	glVertex2i(x + 2, y + 8);

	glVertex2i(x + 10, y + 4);
	glVertex2i(x + 14, y + 4);
	glVertex2i(x + 14, y + 8);
	glVertex2i(x + 10, y + 8);

	glVertex2i(x + 7, y + 2);
	glVertex2i(x + 9, y + 2);
	glVertex2i(x + 9, y);
	glVertex2i(x + 7, y);

	
	if (level == 1)
	{
		glColor3ub(0, 255, 0);
	}
	else if (level == 2)
	{
		glColor3ub(0, 0, 255);
	}
	else
	{
		glColor3ub(255, 0, 0);
	}
	glVertex2i(x +7, y + 2);
	glVertex2i(x + 9, y + 2);
	glVertex2i(x + 9, y + 8);
	glVertex2i(x + 7, y + 8);

	glEnd();
}
//Draws the missle
void CentipedeDrawMissle(int x, int y, int state, int level)
{
	if (level == 1)
	{
		glColor3ub(255, 0, 0);
	}
	else if (level == 2)
	{
		glColor3ub(0, 255, 255);
	}
	else
	{
		glColor3ub(255, 255, 0);
	}
	glBegin(GL_QUADS);
	glVertex2i(x+7, y);
	glVertex2i(x+9, y);
	glVertex2i(x+9, y-10);
	glVertex2i(x+7, y-10);
	glEnd();
}
//Draws the mushrooms
void CentipedeDrawMushroom(int x, int y, int state, int level)
{
	if (state == 4)
	{
		//Exterior
		if (level == 1)
		{
			glColor3ub(255, 0, 0);
		}
		else if (level == 2)
		{
			glColor3ub(0, 255, 255);
		}
		else
		{
			glColor3ub(255, 255, 0);
		}
		glBegin(GL_QUADS);
		glVertex2i(x * 16+4, (y+1) * 16);
		glVertex2i(x * 16 + 12, (y+1) * 16);
		glVertex2i(x * 16 + 12, (y+1) * 16 + 16);
		glVertex2i(x * 16+4, (y+1) * 16 + 16);

		glVertex2i(x * 16, (y + 1) * 16+10);
		glVertex2i(x * 16 + 2, (y + 1) * 16+10);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);
		glVertex2i(x * 16, (y + 1) * 16 + 4);

		glVertex2i(x * 16+2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);
		glVertex2i(x * 16+2, (y + 1) * 16 + 2);

		glVertex2i(x * 16+14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 4);
		glVertex2i(x * 16+14, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		//Interior

		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x * 16 + 6, (y + 1) * 16+2);
		glVertex2i(x * 16 + 10, (y + 1) * 16+2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);

		glVertex2i(x * 16 + 6, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 14);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 14);

		glVertex2i(x * 16+2, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 4);
		glVertex2i(x * 16+2, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glEnd();
	}
	if (state == 3)
	{
		//Exterior
		if (level == 1)
		{
			glColor3ub(255, 0, 0);
		}
		else if (level == 2)
		{
			glColor3ub(0, 255, 255);
		}
		else
		{
			glColor3ub(255, 255, 0);
		}
		glBegin(GL_QUADS);
		glVertex2i(x * 16 + 4, (y + 1) * 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 16);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 16);

		glVertex2i(x * 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);
		glVertex2i(x * 16, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		//Interior
		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);

		glVertex2i(x * 16 + 6, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 14);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 14);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glEnd();
		//Holes
		glColor3ub(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2i(x * 16+6, (y + 1) * 16+12);
		glVertex2i(x * 16 + 8, (y + 1) * 16+12);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 14);
		glVertex2i(x * 16+6, (y + 1) * 16 + 14);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);

		glVertex2i(x * 16 + 4, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glEnd();

	}
	if (state == 2)
	{
		if (level == 1)
		{
			glColor3ub(255, 0, 0);
		}
		else if (level == 2)
		{
			glColor3ub(0, 255, 255);
		}
		else
		{
			glColor3ub(255, 255, 0);
		}
		glBegin(GL_QUADS);
		glVertex2i(x * 16 + 4, (y + 1) * 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 16);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 16);

		glVertex2i(x * 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);
		glVertex2i(x * 16, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		//Interior
		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);

		glVertex2i(x * 16 + 6, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 14);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 14);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glEnd();
		//Holes
		glColor3ub(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 12);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 12);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 14);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 14);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);

		glVertex2i(x * 16 + 4, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 12);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 12);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);
		glEnd();
	}
	if (state == 1)
	{
		if (level == 1)
		{
			glColor3ub(255, 0, 0);
		}
		else if (level == 2)
		{
			glColor3ub(0, 255, 255);
		}
		else
		{
			glColor3ub(255, 255, 0);
		}
		glBegin(GL_QUADS);
		glVertex2i(x * 16 + 4, (y + 1) * 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 16);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 16);

		glVertex2i(x * 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);
		glVertex2i(x * 16, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		//Interior
		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);

		glVertex2i(x * 16 + 6, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 14);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 14);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glEnd();
		//Holes
		glColor3ub(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 12);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 12);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 14);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 14);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 10);

		glVertex2i(x * 16 + 4, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 12);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 12);

		glVertex2i(x * 16 + 14, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 16, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 14, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 6, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 6, (y + 1) * 16 + 4);

		glVertex2i(x * 16 + 8, (y + 1) * 16 + 0);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 0);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 2);
		glVertex2i(x * 16 + 8, (y + 1) * 16 + 2);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 16);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 14);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 14);

		glVertex2i(x * 16 + 2, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 10);
		glVertex2i(x * 16 + 4, (y + 1) * 16 + 8);
		glVertex2i(x * 16 + 2, (y + 1) * 16 + 8);

		glVertex2i(x * 16 + 10, (y + 1) * 16 + 4);
		glVertex2i(x * 16 +12, (y + 1) * 16 + 4);
		glVertex2i(x * 16 + 12, (y + 1) * 16 + 6);
		glVertex2i(x * 16 + 10, (y + 1) * 16 + 6);
		glEnd();
	}
}
//Draws the centipide
void CentipedeDrawCentipede(int x, int y, int state, int draweyes, int drawlegs, int vx, int vy, int level)
{

	glBegin(GL_QUADS);
	if (vx > 0 && vy == 0)
	{
		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x+2, y + 4);
		glVertex2i(x + 16, y + 4);
		glVertex2i(x + 16, y + 12);
		glVertex2i(x+2, y + 12);

		glVertex2i(x + 4, y + 2);
		glVertex2i(x + 14, y + 2);
		glVertex2i(x + 14, y + 14);
		glVertex2i(x + 4, y + 14);

		glVertex2i(x + 2, y + 6);
		glVertex2i(x + 1, y + 6);
		glVertex2i(x + 1, y + 10);
		glVertex2i(x + 2, y + 10);

		if (draweyes == 1)
		{
			if (level == 1)
			{
				glColor3ub(255, 0, 0);
			}
			else if (level == 2)
			{
				glColor3ub(0, 255, 255);
			}
			else
			{
				glColor3ub(255,255, 0);
			}
			glVertex2i(x + 10, y + 2);
			glVertex2i(x + 14, y + 2);
			glVertex2i(x + 14, y + 6);
			glVertex2i(x + 10, y + 6);

			glVertex2i(x + 10, y + 10);
			glVertex2i(x + 14, y + 10);
			glVertex2i(x + 14, y + 14);
			glVertex2i(x + 10, y + 14);
		}

		if (drawlegs>0)
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 10, y + 2);
			glVertex2i(x + 8, y + 2);
			glVertex2i(x + 8, y + 0);
			glVertex2i(x + 10, y + 0);

			glVertex2i(x + 10, y + 14);
			glVertex2i(x + 8, y + 14);
			glVertex2i(x + 8, y + 16);
			glVertex2i(x + 10, y + 16);
		}
		else
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 4, y + 2);
			glVertex2i(x + 6, y + 2);
			glVertex2i(x + 6, y + 0);
			glVertex2i(x + 4, y + 0);

			glVertex2i(x + 4, y + 14);
			glVertex2i(x + 6, y + 14);
			glVertex2i(x + 6, y + 16);
			glVertex2i(x + 4, y + 16);
		}

	}
	if (vx < 0 && vy == 0)
	{
		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x, y + 4);
		glVertex2i(x + 14, y + 4);
		glVertex2i(x + 14, y + 12);
		glVertex2i(x, y + 12);

		glVertex2i(x+2, y + 2);
		glVertex2i(x + 12, y + 2);
		glVertex2i(x + 12, y + 14);
		glVertex2i(x+2, y + 14);

		glVertex2i(x + 14, y + 6);
		glVertex2i(x + 15, y + 6);
		glVertex2i(x + 15, y + 10);
		glVertex2i(x + 14, y + 10);

		if (draweyes == 1)
		{
			if (level == 1)
			{
				glColor3ub(255, 0, 0);
			}
			else if (level == 2)
			{
				glColor3ub(0, 255, 255);
			}
			else
			{
				glColor3ub(255, 255, 0);
			}
			glVertex2i(x + 6, y + 2);
			glVertex2i(x + 2, y + 2);
			glVertex2i(x + 2, y + 6);
			glVertex2i(x + 6, y + 6);

			glVertex2i(x + 6, y + 10);
			glVertex2i(x + 2, y + 10);
			glVertex2i(x + 2, y + 14);
			glVertex2i(x + 6, y + 14);
		}
		if (drawlegs>0)
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 6, y + 2);
			glVertex2i(x + 8, y + 2);
			glVertex2i(x + 8, y + 0);
			glVertex2i(x + 6, y + 0);

			glVertex2i(x + 6, y + 14);
			glVertex2i(x + 8, y + 14);
			glVertex2i(x + 8, y + 16);
			glVertex2i(x + 6, y + 16);
		}
		else
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 12, y + 2);
			glVertex2i(x + 10, y + 2);
			glVertex2i(x + 10, y + 0);
			glVertex2i(x + 12, y + 0);

			glVertex2i(x + 12, y + 14);
			glVertex2i(x + 10, y + 14);
			glVertex2i(x + 10, y + 16);
			glVertex2i(x + 12, y + 16);
		}
	}
	if (vy > 0)
	{
		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x + 4, y + 2);
		glVertex2i(x + 12, y + 2);
		glVertex2i(x + 12, y + 16);
		glVertex2i(x + 4, y + 16);

		glVertex2i(x + 2, y + 4);
		glVertex2i(x + 14, y + 4);
		glVertex2i(x + 14, y + 14);
		glVertex2i(x + 2, y + 14);

		glVertex2i(x + 6, y + 2);
		glVertex2i(x + 10, y + 2);
		glVertex2i(x + 10, y + 1);
		glVertex2i(x + 6, y + 1);

		if (draweyes == 1)
		{
			if (level == 1)
			{
				glColor3ub(255, 0, 0);
			}
			else if (level == 2)
			{
				glColor3ub(0, 255, 255);
			}
			else
			{
				glColor3ub(255, 255, 0);
			}
			glVertex2i(x + 2, y + 10);
			glVertex2i(x + 6, y + 10);
			glVertex2i(x + 6, y + 14);
			glVertex2i(x + 2, y + 14);

			glVertex2i(x + 10, y + 10);
			glVertex2i(x + 14, y + 10);
			glVertex2i(x + 14, y + 14);
			glVertex2i(x + 10, y + 14);
		}

		if (drawlegs > 0)
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 0, y + 10);
			glVertex2i(x + 2, y + 10);
			glVertex2i(x + 2, y + 8);
			glVertex2i(x + 0, y + 8);

			glVertex2i(x + 14, y + 8);
			glVertex2i(x + 16, y + 8);
			glVertex2i(x + 16, y + 10);
			glVertex2i(x + 14, y + 10);
		}
		else
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 0, y + 4);
			glVertex2i(x + 2, y + 4);
			glVertex2i(x + 2, y + 6);
			glVertex2i(x + 0, y + 6);

			glVertex2i(x + 14, y + 4);
			glVertex2i(x + 16, y + 4);
			glVertex2i(x + 16, y + 6);
			glVertex2i(x + 14, y + 6);
		}
	}
	if (vy < 0)
	{
		if (level == 1)
		{
			glColor3ub(0, 255, 0);
		}
		else if (level == 2)
		{
			glColor3ub(219, 73, 172);
		}
		else
		{
			glColor3ub(255, 0, 0);
		}
		glVertex2i(x + 4, y + 14);
		glVertex2i(x + 12, y + 14);
		glVertex2i(x + 12, y + 0);
		glVertex2i(x + 4, y + 0);

		glVertex2i(x + 2, y + 12);
		glVertex2i(x + 14, y + 12);
		glVertex2i(x + 14, y + 2);
		glVertex2i(x + 2, y + 2);

		glVertex2i(x + 6, y + 14);
		glVertex2i(x + 10, y + 14);
		glVertex2i(x + 10, y + 15);
		glVertex2i(x + 6, y + 15);

		if (draweyes == 1)
		{
			if (level == 1)
			{
				glColor3ub(255, 0, 0);
			}
			else if (level == 2)
			{
				glColor3ub(0, 255, 255);
			}
			else
			{
				glColor3ub(255, 255, 0);
			}
			glVertex2i(x + 2, y + 6);
			glVertex2i(x + 6, y + 6);
			glVertex2i(x + 6, y + 2);
			glVertex2i(x + 2, y + 2);

			glVertex2i(x + 10, y + 6);
			glVertex2i(x + 14, y + 6);
			glVertex2i(x + 14, y + 2);
			glVertex2i(x + 10, y + 2);
		}

		if (drawlegs > 0)
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 0, y + 6);
			glVertex2i(x + 2, y + 6);
			glVertex2i(x + 2, y + 8);
			glVertex2i(x + 0, y + 8);

			glVertex2i(x + 14, y + 8);
			glVertex2i(x + 16, y + 8);
			glVertex2i(x + 16, y + 6);
			glVertex2i(x + 14, y + 6);
		}
		else
		{
			glColor3ub(210, 180, 140);
			glVertex2i(x + 0, y +12);
			glVertex2i(x + 2, y + 12);
			glVertex2i(x + 2, y + 10);
			glVertex2i(x + 0, y + 10);

			glVertex2i(x + 14, y + 12);
			glVertex2i(x + 16, y + 12);
			glVertex2i(x + 16, y + 10);
			glVertex2i(x + 14, y + 10);
		}
	}

	glEnd();
}
//Draws the spider
void CentipedeDrawSpider(int x, int y, int drawlegs, int level)
{
	if (level == 1)
	{
		glColor3ub(0, 255, 0);
	}
	else if (level == 2)
	{
		glColor3ub(219, 73, 172);
	}
	else
	{
		glColor3ub(255, 0, 0);
	}
	glBegin(GL_QUADS);
	glVertex2i(x + 6, y + 4);
	glVertex2i(x + 16, y + 4);
	glVertex2i(x + 16, y + 14);
	glVertex2i(x + 6, y + 14);

	glVertex2i(x + 8, y + 14);
	glVertex2i(x + 14, y + 14);
	glVertex2i(x + 14, y + 16);
	glVertex2i(x + 8, y + 16);

	glVertex2i(x + 10, y + 2);
	glVertex2i(x + 12, y + 2);
	glVertex2i(x + 12, y + 4);
	glVertex2i(x + 10, y + 4);

	if (level == 1)
	{
		glColor3ub(255, 0, 0);
	}
	else if (level == 2)
	{
		glColor3ub(0, 255, 255);
	}
	else
	{
		glColor3ub(255, 255, 0);
	}
	glVertex2i(x + 10, y + 12);
	glVertex2i(x + 12, y + 12);
	glVertex2i(x + 12, y + 16);
	glVertex2i(x + 10, y + 16);

	glVertex2i(x + 8, y + 12);
	glVertex2i(x + 14, y + 12);
	glVertex2i(x + 14, y + 14);
	glVertex2i(x + 8, y + 14);

	glVertex2i(x + 6, y + 4);
	glVertex2i(x + 10, y + 4);
	glVertex2i(x + 10, y + 8);
	glVertex2i(x + 6, y + 8);

	glVertex2i(x + 12, y + 4);
	glVertex2i(x + 16, y + 4);
	glVertex2i(x + 16, y + 8);
	glVertex2i(x + 12, y + 8);

	glColor3ub(210, 180, 140);
	glVertex2i(x + 6, y + 4);
	glVertex2i(x + 8, y + 4);
	glVertex2i(x + 6, y + 6);
	glVertex2i(x + 8, y + 6);

	glVertex2i(x + 16, y + 4);
	glVertex2i(x + 14, y + 4);
	glVertex2i(x + 14, y + 6);
	glVertex2i(x + 16, y + 6);

	if (drawlegs > 0)
	{
		glVertex2i(x + 6, y + 4);
		glVertex2i(x + 4, y + 4);
		glVertex2i(x + 4, y + 6);
		glVertex2i(x + 6, y + 6);

		glVertex2i(x + 2, y + 4);
		glVertex2i(x + 4, y + 4);
		glVertex2i(x + 4, y + 2);
		glVertex2i(x + 2, y + 2);

		glVertex2i(x + 2, y + 4);
		glVertex2i(x , y + 4);
		glVertex2i(x , y + 2);
		glVertex2i(x + 2, y + 2);

		glVertex2i(x + 16, y + 4);
		glVertex2i(x + 18, y + 4);
		glVertex2i(x + 18, y + 6);
		glVertex2i(x + 16, y + 6);

		glVertex2i(x + 18, y + 4);
		glVertex2i(x + 20, y + 4);
		glVertex2i(x + 20, y + 2);
		glVertex2i(x + 18, y + 2);

		glVertex2i(x + 20, y + 4);
		glVertex2i(x+22, y + 4);
		glVertex2i(x+22, y + 2);
		glVertex2i(x + 20, y + 2);

		glVertex2i(x + 6, y + 10);
		glVertex2i(x + 4, y + 10);
		glVertex2i(x + 4, y + 12);
		glVertex2i(x + 6, y + 12);

		glVertex2i(x + 2, y + 10);
		glVertex2i(x + 4, y + 10);
		glVertex2i(x + 4, y + 8);
		glVertex2i(x + 2, y + 8);

		glVertex2i(x + 2, y + 10);
		glVertex2i(x, y + 10);
		glVertex2i(x, y + 8);
		glVertex2i(x + 2, y + 8);

		glVertex2i(x + 16, y + 10);
		glVertex2i(x + 18, y + 10);
		glVertex2i(x + 18, y + 12);
		glVertex2i(x + 16, y + 12);

		glVertex2i(x + 18, y + 10);
		glVertex2i(x + 20, y + 10);
		glVertex2i(x + 20, y + 8);
		glVertex2i(x + 18, y + 8);

		glVertex2i(x + 20, y + 10);
		glVertex2i(x + 22, y + 10);
		glVertex2i(x + 22, y + 8);
		glVertex2i(x + 20, y + 8);
	}
	else
	{
		glVertex2i(x + 6, y + 4);
		glVertex2i(x + 4, y + 4);
		glVertex2i(x + 4, y + 6);
		glVertex2i(x + 6, y + 6);

		glVertex2i(x + 2, y + 4);
		glVertex2i(x + 4, y + 4);
		glVertex2i(x + 4, y + 6);
		glVertex2i(x + 2, y + 6);

		glVertex2i(x + 2, y + 6);
		glVertex2i(x, y + 6);
		glVertex2i(x, y + 8);
		glVertex2i(x + 2, y + 8);

		glVertex2i(x + 16, y + 4);
		glVertex2i(x + 18, y + 4);
		glVertex2i(x + 18, y + 6);
		glVertex2i(x + 16, y + 6);

		glVertex2i(x + 18, y + 4);
		glVertex2i(x + 20, y + 4);
		glVertex2i(x + 20, y + 6);
		glVertex2i(x + 18, y + 6);

		glVertex2i(x + 20, y + 6);
		glVertex2i(x + 22, y + 6);
		glVertex2i(x + 22, y + 8);
		glVertex2i(x + 20, y + 8);

		glVertex2i(x + 6, y + 10);
		glVertex2i(x + 4, y + 10);
		glVertex2i(x + 4, y + 12);
		glVertex2i(x + 6, y + 12);

		glVertex2i(x + 2, y + 10);
		glVertex2i(x + 4, y + 10);
		glVertex2i(x + 4, y + 12);
		glVertex2i(x + 2, y + 12);

		glVertex2i(x + 2, y + 14);
		glVertex2i(x, y + 14);
		glVertex2i(x, y + 12);
		glVertex2i(x + 2, y + 12);

		glVertex2i(x + 16, y + 10);
		glVertex2i(x + 18, y + 10);
		glVertex2i(x + 18, y + 12);
		glVertex2i(x + 16, y + 12);

		glVertex2i(x + 18, y + 10);
		glVertex2i(x + 20, y + 10);
		glVertex2i(x + 20, y + 12);
		glVertex2i(x + 18, y + 12);

		glVertex2i(x + 20, y + 12);
		glVertex2i(x + 22, y + 12);
		glVertex2i(x + 22, y + 14);
		glVertex2i(x + 20, y + 14);
	}
	glEnd();
}
//Draws the footer life, score, and info
void CentipedeDrawFooter(int lives, int score)
{
	char clives[32];
	sprintf(clives, "Lives: %d", lives);
	glColor3ub(255, 255, 255);
	glRasterPos2i(25, 585);
	YsGlDrawFontBitmap10x14(clives);

	char cscore[256];
	sprintf(cscore, "Score: %d", score);
	glColor3ub(255, 255, 255);
	glRasterPos2i(650, 585);
	YsGlDrawFontBitmap10x14(cscore);

	glColor3ub(255, 255, 255);
	glRasterPos2i(300, 585);
	YsGlDrawFontBitmap10x14("Press H for Help");
}
//Draw help screen
void CentipedeDrawHelp(int menumove, int gameover, int score)
{
	if (gameover == 0)
	{
		glColor3ub(25, 25, 25);
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(800, 0);
		glVertex2i(800, 600);
		glVertex2i(0, 600);
		glEnd();
		glColor3ub(255, 255, 255);
		glRasterPos2i(320, 20);
		YsGlDrawFontBitmap10x14("CENTIPEDE");
		glBegin(GL_LINES);
		glVertex2i(200, 25);
		glVertex2i(535, 25);
		glEnd();
		glRasterPos2i(310, 50);
		YsGlDrawFontBitmap10x14("Help Screen");
		glRasterPos2i(237, 70);
		YsGlDrawFontBitmap10x14("Press R to Return / Start");
		glRasterPos2i(675, 25);
		YsGlDrawFontBitmap10x14("ESC to EXIT");
		glRasterPos2i(25, 110);
		YsGlDrawFontBitmap10x14("Controls: ");
		glRasterPos2i(125, 110);
		YsGlDrawFontBitmap10x14("UP - Move Player Up");
		glRasterPos2i(125, 130);
		YsGlDrawFontBitmap10x14("DOWN - Move Player Down");
		glRasterPos2i(125, 150);
		YsGlDrawFontBitmap10x14("LEFT - Move Player Left");
		glRasterPos2i(125, 170);
		YsGlDrawFontBitmap10x14("RIGHT - Move Player Right");
		if (menumove / 10 < 1)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 130 + 2);
			glVertex2i(500 + 11, 130 + 2);
			glVertex2i(500 + 11, 130 + 16);
			glVertex2i(500 + 5, 130 + 16);

			glVertex2i(500, 130 + 6);
			glVertex2i(500 + 16, 130 + 6);
			glVertex2i(500 + 16, 130 + 10);
			glVertex2i(500, 130 + 10);

			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 12);
			glVertex2i(500 + 2, 130 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 6, 130 + 4);
			glVertex2i(500 + 6, 130 + 8);
			glVertex2i(500 + 2, 130 + 8);

			glVertex2i(500 + 10, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 8);
			glVertex2i(500 + 10, 130 + 8);

			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130);
			glVertex2i(500 + 7, 130);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130 + 8);
			glVertex2i(500 + 7, 130 + 8);
			glEnd();
		}
		if (menumove / 10 >= 1 && menumove / 10<2)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 130 + 2 - 20);
			glVertex2i(500 + 11, 130 + 2 - 20);
			glVertex2i(500 + 11, 130 + 16 - 20);
			glVertex2i(500 + 5, 130 + 16 - 20);

			glVertex2i(500, 130 + 6 - 20);
			glVertex2i(500 + 16, 130 + 6 - 20);
			glVertex2i(500 + 16, 130 + 10 - 20);
			glVertex2i(500, 130 + 10 - 20);

			glVertex2i(500 + 2, 130 + 4 - 20);
			glVertex2i(500 + 14, 130 + 4 - 20);
			glVertex2i(500 + 14, 130 + 12 - 20);
			glVertex2i(500 + 2, 130 + 12 - 20);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2, 130 + 4 - 20);
			glVertex2i(500 + 6, 130 + 4 - 20);
			glVertex2i(500 + 6, 130 + 8 - 20);
			glVertex2i(500 + 2, 130 + 8 - 20);

			glVertex2i(500 + 10, 130 + 4 - 20);
			glVertex2i(500 + 14, 130 + 4 - 20);
			glVertex2i(500 + 14, 130 + 8 - 20);
			glVertex2i(500 + 10, 130 + 8 - 20);

			glVertex2i(500 + 7, 130 + 2 - 20);
			glVertex2i(500 + 9, 130 + 2 - 20);
			glVertex2i(500 + 9, 130 - 20);
			glVertex2i(500 + 7, 130 - 20);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 130 + 2 - 20);
			glVertex2i(500 + 9, 130 + 2 - 20);
			glVertex2i(500 + 9, 130 + 8 - 20);
			glVertex2i(500 + 7, 130 + 8 - 20);
			glEnd();
		}
		if (menumove / 10 >= 2 && menumove / 10<3)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 130 + 2);
			glVertex2i(500 + 11, 130 + 2);
			glVertex2i(500 + 11, 130 + 16);
			glVertex2i(500 + 5, 130 + 16);

			glVertex2i(500, 130 + 6);
			glVertex2i(500 + 16, 130 + 6);
			glVertex2i(500 + 16, 130 + 10);
			glVertex2i(500, 130 + 10);

			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 12);
			glVertex2i(500 + 2, 130 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 6, 130 + 4);
			glVertex2i(500 + 6, 130 + 8);
			glVertex2i(500 + 2, 130 + 8);

			glVertex2i(500 + 10, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 8);
			glVertex2i(500 + 10, 130 + 8);

			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130);
			glVertex2i(500 + 7, 130);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130 + 8);
			glVertex2i(500 + 7, 130 + 8);
			glEnd();
		}
		if (menumove / 10 >= 3 && menumove / 10<4)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 130 + 2 + 20);
			glVertex2i(500 + 11, 130 + 2 + 20);
			glVertex2i(500 + 11, 130 + 16 + 20);
			glVertex2i(500 + 5, 130 + 16 + 20);

			glVertex2i(500, 130 + 6 + 20);
			glVertex2i(500 + 16, 130 + 6 + 20);
			glVertex2i(500 + 16, 130 + 10 + 20);
			glVertex2i(500, 130 + 10 + 20);

			glVertex2i(500 + 2, 130 + 4 + 20);
			glVertex2i(500 + 14, 130 + 4 + 20);
			glVertex2i(500 + 14, 130 + 12 + 20);
			glVertex2i(500 + 2, 130 + 12 + 20);

			glColor3ub(255, 0, 0 + 20);
			glVertex2i(500 + 2, 130 + 4 + 20);
			glVertex2i(500 + 6, 130 + 4 + 20);
			glVertex2i(500 + 6, 130 + 8 + 20);
			glVertex2i(500 + 2, 130 + 8 + 20);

			glVertex2i(500 + 10, 130 + 4 + 20);
			glVertex2i(500 + 14, 130 + 4 + 20);
			glVertex2i(500 + 14, 130 + 8 + 20);
			glVertex2i(500 + 10, 130 + 8 + 20);

			glVertex2i(500 + 7, 130 + 2 + 20);
			glVertex2i(500 + 9, 130 + 2 + 20);
			glVertex2i(500 + 9, 130 + 20);
			glVertex2i(500 + 7, 130 + 20);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 130 + 2 + 20);
			glVertex2i(500 + 9, 130 + 2 + 20);
			glVertex2i(500 + 9, 130 + 8 + 20);
			glVertex2i(500 + 7, 130 + 8 + 20);
			glEnd();
		}
		if (menumove / 10 >= 4 && menumove / 10<5)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 130 + 2);
			glVertex2i(500 + 11, 130 + 2);
			glVertex2i(500 + 11, 130 + 16);
			glVertex2i(500 + 5, 130 + 16);

			glVertex2i(500, 130 + 6);
			glVertex2i(500 + 16, 130 + 6);
			glVertex2i(500 + 16, 130 + 10);
			glVertex2i(500, 130 + 10);

			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 12);
			glVertex2i(500 + 2, 130 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 6, 130 + 4);
			glVertex2i(500 + 6, 130 + 8);
			glVertex2i(500 + 2, 130 + 8);

			glVertex2i(500 + 10, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 8);
			glVertex2i(500 + 10, 130 + 8);

			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130);
			glVertex2i(500 + 7, 130);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130 + 8);
			glVertex2i(500 + 7, 130 + 8);
			glEnd();
		}
		if (menumove / 10 >= 5 && menumove / 10<6)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5 - 20, 130 + 2);
			glVertex2i(500 + 11 - 20, 130 + 2);
			glVertex2i(500 + 11 - 20, 130 + 16);
			glVertex2i(500 + 5 - 20, 130 + 16);

			glVertex2i(500 - 20, 130 + 6);
			glVertex2i(500 + 16 - 20, 130 + 6);
			glVertex2i(500 + 16 - 20, 130 + 10);
			glVertex2i(500 - 20, 130 + 10);

			glVertex2i(500 + 2 - 20, 130 + 4);
			glVertex2i(500 + 14 - 20, 130 + 4);
			glVertex2i(500 + 14 - 20, 130 + 12);
			glVertex2i(500 + 2 - 20, 130 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2 - 20, 130 + 4);
			glVertex2i(500 + 6 - 20, 130 + 4);
			glVertex2i(500 + 6 - 20, 130 + 8);
			glVertex2i(500 + 2 - 20, 130 + 8);

			glVertex2i(500 + 10 - 20, 130 + 4);
			glVertex2i(500 + 14 - 20, 130 + 4);
			glVertex2i(500 + 14 - 20, 130 + 8);
			glVertex2i(500 + 10 - 20, 130 + 8);

			glVertex2i(500 + 7 - 20, 130 + 2);
			glVertex2i(500 + 9 - 20, 130 + 2);
			glVertex2i(500 + 9 - 20, 130);
			glVertex2i(500 + 7 - 20, 130);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7 - 20, 130 + 2);
			glVertex2i(500 + 9 - 20, 130 + 2);
			glVertex2i(500 + 9 - 20, 130 + 8);
			glVertex2i(500 + 7 - 20, 130 + 8);
			glEnd();
		}
		if (menumove / 10 >= 6 && menumove / 10<7)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 130 + 2);
			glVertex2i(500 + 11, 130 + 2);
			glVertex2i(500 + 11, 130 + 16);
			glVertex2i(500 + 5, 130 + 16);

			glVertex2i(500, 130 + 6);
			glVertex2i(500 + 16, 130 + 6);
			glVertex2i(500 + 16, 130 + 10);
			glVertex2i(500, 130 + 10);

			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 12);
			glVertex2i(500 + 2, 130 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2, 130 + 4);
			glVertex2i(500 + 6, 130 + 4);
			glVertex2i(500 + 6, 130 + 8);
			glVertex2i(500 + 2, 130 + 8);

			glVertex2i(500 + 10, 130 + 4);
			glVertex2i(500 + 14, 130 + 4);
			glVertex2i(500 + 14, 130 + 8);
			glVertex2i(500 + 10, 130 + 8);

			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130);
			glVertex2i(500 + 7, 130);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 130 + 2);
			glVertex2i(500 + 9, 130 + 2);
			glVertex2i(500 + 9, 130 + 8);
			glVertex2i(500 + 7, 130 + 8);
			glEnd();
		}
		if (menumove / 10 >= 7 && menumove / 10<8)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5 + 20, 130 + 2);
			glVertex2i(500 + 11 + 20, 130 + 2);
			glVertex2i(500 + 11 + 20, 130 + 16);
			glVertex2i(500 + 5 + 20, 130 + 16);

			glVertex2i(500 + 20, 130 + 6);
			glVertex2i(500 + 16 + 20, 130 + 6);
			glVertex2i(500 + 16 + 20, 130 + 10);
			glVertex2i(500 + 20, 130 + 10);

			glVertex2i(500 + 2 + 20, 130 + 4);
			glVertex2i(500 + 14 + 20, 130 + 4);
			glVertex2i(500 + 14 + 20, 130 + 12);
			glVertex2i(500 + 2 + 20, 130 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2 + 20, 130 + 4);
			glVertex2i(500 + 6 + 20, 130 + 4);
			glVertex2i(500 + 6 + 20, 130 + 8);
			glVertex2i(500 + 2 + 20, 130 + 8);

			glVertex2i(500 + 10 + 20, 130 + 4);
			glVertex2i(500 + 14 + 20, 130 + 4);
			glVertex2i(500 + 14 + 20, 130 + 8);
			glVertex2i(500 + 10 + 20, 130 + 8);

			glVertex2i(500 + 7 + 20, 130 + 2);
			glVertex2i(500 + 9 + 20, 130 + 2);
			glVertex2i(500 + 9 + 20, 130);
			glVertex2i(500 + 7 + 20, 130);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7 + 20, 130 + 2);
			glVertex2i(500 + 9 + 20, 130 + 2);
			glVertex2i(500 + 9 + 20, 130 + 8);
			glVertex2i(500 + 7 + 20, 130 + 8);
			glEnd();
		}
		glColor3ub(255, 255, 255);
		glRasterPos2i(125, 210);
		YsGlDrawFontBitmap10x14("SPACE - Shoot");
		if (menumove / 40 < 1)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 197 + 2);
			glVertex2i(500 + 11, 197 + 2);
			glVertex2i(500 + 11, 197 + 16);
			glVertex2i(500 + 5, 197 + 16);

			glVertex2i(500, 197 + 6);
			glVertex2i(500 + 16, 197 + 6);
			glVertex2i(500 + 16, 197 + 10);
			glVertex2i(500, 197 + 10);

			glVertex2i(500 + 2, 197 + 4);
			glVertex2i(500 + 14, 197 + 4);
			glVertex2i(500 + 14, 197 + 12);
			glVertex2i(500 + 2, 197 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2, 197 + 4);
			glVertex2i(500 + 6, 197 + 4);
			glVertex2i(500 + 6, 197 + 8);
			glVertex2i(500 + 2, 197 + 8);

			glVertex2i(500 + 10, 197 + 4);
			glVertex2i(500 + 14, 197 + 4);
			glVertex2i(500 + 14, 197 + 8);
			glVertex2i(500 + 10, 197 + 8);

			glVertex2i(500 + 7, 197 + 2);
			glVertex2i(500 + 9, 197 + 2);
			glVertex2i(500 + 9, 197);
			glVertex2i(500 + 7, 197);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 197 + 2);
			glVertex2i(500 + 9, 197 + 2);
			glVertex2i(500 + 9, 197 + 8);
			glVertex2i(500 + 7, 197 + 8);
			glEnd();
		}
		if (menumove / 40 >= 1)
		{
			glColor3ub(210, 180, 140);
			glBegin(GL_QUADS);
			glVertex2i(500 + 5, 197 + 2);
			glVertex2i(500 + 11, 197 + 2);
			glVertex2i(500 + 11, 197 + 16);
			glVertex2i(500 + 5, 197 + 16);

			glVertex2i(500, 197 + 6);
			glVertex2i(500 + 16, 197 + 6);
			glVertex2i(500 + 16, 197 + 10);
			glVertex2i(500, 197 + 10);

			glVertex2i(500 + 2, 197 + 4);
			glVertex2i(500 + 14, 197 + 4);
			glVertex2i(500 + 14, 197 + 12);
			glVertex2i(500 + 2, 197 + 12);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 2, 197 + 4);
			glVertex2i(500 + 6, 197 + 4);
			glVertex2i(500 + 6, 197 + 8);
			glVertex2i(500 + 2, 197 + 8);

			glVertex2i(500 + 10, 197 + 4);
			glVertex2i(500 + 14, 197 + 4);
			glVertex2i(500 + 14, 197 + 8);
			glVertex2i(500 + 10, 197 + 8);

			glVertex2i(500 + 7, 197 + 2);
			glVertex2i(500 + 9, 197 + 2);
			glVertex2i(500 + 9, 197);
			glVertex2i(500 + 7, 197);

			glColor3ub(0, 255, 0);
			glVertex2i(500 + 7, 197 + 2);
			glVertex2i(500 + 9, 197 + 2);
			glVertex2i(500 + 9, 197 + 8);
			glVertex2i(500 + 7, 197 + 8);

			glColor3ub(255, 0, 0);
			glVertex2i(500 + 7, 197);
			glVertex2i(500 + 9, 197);
			glVertex2i(500 + 9, 197 - 10);
			glVertex2i(500 + 7, 197 - 10);
			glEnd();
		}

		glColor3ub(255, 255, 255);
		glRasterPos2i(60, 250);
		YsGlDrawFontBitmap10x14("Goal: The game is pretty simple:");
		glRasterPos2i(122, 270);
		YsGlDrawFontBitmap10x14("Destroy all the centipede segments to advance to the next level");
		glRasterPos2i(122, 290);
		YsGlDrawFontBitmap10x14("Complete three levels to win");
		glRasterPos2i(51, 330);
		YsGlDrawFontBitmap10x14("Score: Get points by hitting mushroooms, centipedes, and spiders");
		glRasterPos2i(30, 450);
		YsGlDrawFontBitmap10x14("Caution: Avoid touching the spider or the centipede.");
		glRasterPos2i(118, 470);
		YsGlDrawFontBitmap10x14("You will lose a life and points");

		//Draw centipede
		glColor3ub(210, 180, 140);
		glBegin(GL_QUADS);
		glColor3ub(0, 255, 0);
		glVertex2i(495 + 2, 340 + 4);
		glVertex2i(495 + 16, 340 + 4);
		glVertex2i(495 + 16, 340 + 12);
		glVertex2i(495 + 2, 340 + 12);

		glVertex2i(495 + 4, 340 + 2);
		glVertex2i(495 + 14, 340 + 2);
		glVertex2i(495 + 14, 340 + 14);
		glVertex2i(495 + 4, 340 + 14);

		glVertex2i(495 + 2, 340 + 6);
		glVertex2i(495 + 1, 340 + 6);
		glVertex2i(495 + 1, 340 + 10);
		glVertex2i(495 + 2, 340 + 10);

		glColor3ub(255, 0, 0);
		glVertex2i(495 + 10, 340 + 2);
		glVertex2i(495 + 14, 340 + 2);
		glVertex2i(495 + 14, 340 + 6);
		glVertex2i(495 + 10, 340 + 6);

		glVertex2i(495 + 10, 340 + 10);
		glVertex2i(495 + 14, 340 + 10);
		glVertex2i(495 + 14, 340 + 14);
		glVertex2i(495 + 10, 340 + 14);

		if (menumove / 40 < 1)
		{
			glColor3ub(210, 180, 140);
			glVertex2i(495 + 10, 340 + 2);
			glVertex2i(495 + 8, 340 + 2);
			glVertex2i(495 + 8, 340 + 0);
			glVertex2i(495 + 10, 340 + 0);

			glVertex2i(495 + 10, 340 + 14);
			glVertex2i(495 + 8, 340 + 14);
			glVertex2i(495 + 8, 340 + 16);
			glVertex2i(495 + 10, 340 + 16);
		}
		if (menumove / 40 >= 1)
		{
			glColor3ub(210, 180, 140);
			glVertex2i(495 + 4, 340 + 2);
			glVertex2i(495 + 6, 340 + 2);
			glVertex2i(495 + 6, 340 + 0);
			glVertex2i(495 + 4, 340 + 0);

			glVertex2i(495 + 4, 340 + 14);
			glVertex2i(495 + 6, 340 + 14);
			glVertex2i(495 + 6, 340 + 16);
			glVertex2i(495 + 4, 340 + 16);
		}
		glEnd();

		//Draw mushroom Exterior
		glColor3ub(255, 0, 0);
		glBegin(GL_QUADS);
		glVertex2i(380 + 4, 340);
		glVertex2i(380 + 12, 340);
		glVertex2i(380 + 12, 340 + 16);
		glVertex2i(380 + 4, 340 + 16);

		glVertex2i(380, 340 + 10);
		glVertex2i(380 + 2, 340 + 10);
		glVertex2i(380 + 2, 340 + 4);
		glVertex2i(380, 340 + 4);

		glVertex2i(380 + 2, 340 + 10);
		glVertex2i(380 + 4, 340 + 10);
		glVertex2i(380 + 4, 340 + 2);
		glVertex2i(380 + 2, 340 + 2);

		glVertex2i(380 + 14, 340 + 10);
		glVertex2i(380 + 16, 340 + 10);
		glVertex2i(380 + 16, 340 + 4);
		glVertex2i(380 + 14, 340 + 4);

		glVertex2i(380 + 12, 340 + 10);
		glVertex2i(380 + 14, 340 + 10);
		glVertex2i(380 + 14, 340 + 2);
		glVertex2i(380 + 12, 340 + 2);
		//Interior
		glColor3ub(0, 255, 0);
		glVertex2i(380 + 6, 340 + 2);
		glVertex2i(380 + 10, 340 + 2);
		glVertex2i(380 + 10, 340 + 8);
		glVertex2i(380 + 6, 340 + 8);

		glVertex2i(380 + 6, 340 + 10);
		glVertex2i(380 + 10, 340 + 10);
		glVertex2i(380 + 10, 340 + 14);
		glVertex2i(380 + 6, 340 + 14);

		glVertex2i(380 + 2, 340 + 8);
		glVertex2i(380 + 4, 340 + 8);
		glVertex2i(380 + 4, 340 + 4);
		glVertex2i(380 + 2, 340 + 4);

		glVertex2i(380 + 4, 340 + 8);
		glVertex2i(380 + 6, 340 + 8);
		glVertex2i(380 + 6, 340 + 2);
		glVertex2i(380 + 4, 340 + 2);

		glVertex2i(380 + 12, 340 + 8);
		glVertex2i(380 + 14, 340 + 8);
		glVertex2i(380 + 14, 340 + 4);
		glVertex2i(380 + 12, 340 + 4);

		glVertex2i(380 + 10, 340 + 8);
		glVertex2i(380 + 12, 340 + 8);
		glVertex2i(380 + 12, 340 + 2);
		glVertex2i(380 + 10, 340 + 2);
		glEnd();

		//Draws Spider
		glColor3ub(0, 255, 0);
		glBegin(GL_QUADS);
		glVertex2i(635 + 6, 340 + 4);
		glVertex2i(635 + 16, 340 + 4);
		glVertex2i(635 + 16, 340 + 14);
		glVertex2i(635 + 6, 340 + 14);

		glVertex2i(635 + 8, 340 + 14);
		glVertex2i(635 + 14, 340 + 14);
		glVertex2i(635 + 14, 340 + 16);
		glVertex2i(635 + 8, 340 + 16);

		glVertex2i(635 + 10, 340 + 2);
		glVertex2i(635 + 12, 340 + 2);
		glVertex2i(635 + 12, 340 + 4);
		glVertex2i(635 + 10, 340 + 4);

		glColor3ub(255, 0, 0);
		glVertex2i(635 + 10, 340 + 12);
		glVertex2i(635 + 12, 340 + 12);
		glVertex2i(635 + 12, 340 + 16);
		glVertex2i(635 + 10, 340 + 16);

		glVertex2i(635 + 8, 340 + 12);
		glVertex2i(635 + 14, 340 + 12);
		glVertex2i(635 + 14, 340 + 14);
		glVertex2i(635 + 8, 340 + 14);

		glVertex2i(635 + 6, 340 + 4);
		glVertex2i(635 + 10, 340 + 4);
		glVertex2i(635 + 10, 340 + 8);
		glVertex2i(635 + 6, 340 + 8);

		glVertex2i(635 + 12, 340 + 4);
		glVertex2i(635 + 16, 340 + 4);
		glVertex2i(635 + 16, 340 + 8);
		glVertex2i(635 + 12, 340 + 8);

		glColor3ub(210, 180, 140);
		glVertex2i(635 + 6, 340 + 4);
		glVertex2i(635 + 8, 340 + 4);
		glVertex2i(635 + 6, 340 + 6);
		glVertex2i(635 + 8, 340 + 6);

		glVertex2i(635 + 16, 340 + 4);
		glVertex2i(635 + 14, 340 + 4);
		glVertex2i(635 + 14, 340 + 6);
		glVertex2i(635 + 16, 340 + 6);

		if (menumove / 40 < 1)
		{
			glVertex2i(635 + 6, 340 + 4);
			glVertex2i(635 + 4, 340 + 4);
			glVertex2i(635 + 4, 340 + 6);
			glVertex2i(635 + 6, 340 + 6);

			glVertex2i(635 + 2, 340 + 4);
			glVertex2i(635 + 4, 340 + 4);
			glVertex2i(635 + 4, 340 + 2);
			glVertex2i(635 + 2, 340 + 2);

			glVertex2i(635 + 2, 340 + 4);
			glVertex2i(635, 340 + 4);
			glVertex2i(635, 340 + 2);
			glVertex2i(635 + 2, 340 + 2);

			glVertex2i(635 + 16, 340 + 4);
			glVertex2i(635 + 18, 340 + 4);
			glVertex2i(635 + 18, 340 + 6);
			glVertex2i(635 + 16, 340 + 6);

			glVertex2i(635 + 18, 340 + 4);
			glVertex2i(635 + 20, 340 + 4);
			glVertex2i(635 + 20, 340 + 2);
			glVertex2i(635 + 18, 340 + 2);

			glVertex2i(635 + 20, 340 + 4);
			glVertex2i(635 + 22, 340 + 4);
			glVertex2i(635 + 22, 340 + 2);
			glVertex2i(635 + 20, 340 + 2);

			glVertex2i(635 + 6, 340 + 10);
			glVertex2i(635 + 4, 340 + 10);
			glVertex2i(635 + 4, 340 + 12);
			glVertex2i(635 + 6, 340 + 12);

			glVertex2i(635 + 2, 340 + 10);
			glVertex2i(635 + 4, 340 + 10);
			glVertex2i(635 + 4, 340 + 8);
			glVertex2i(635 + 2, 340 + 8);

			glVertex2i(635 + 2, 340 + 10);
			glVertex2i(635, 340 + 10);
			glVertex2i(635, 340 + 8);
			glVertex2i(635 + 2, 340 + 8);

			glVertex2i(635 + 16, 340 + 10);
			glVertex2i(635 + 18, 340 + 10);
			glVertex2i(635 + 18, 340 + 12);
			glVertex2i(635 + 16, 340 + 12);

			glVertex2i(635 + 18, 340 + 10);
			glVertex2i(635 + 20, 340 + 10);
			glVertex2i(635 + 20, 340 + 8);
			glVertex2i(635 + 18, 340 + 8);

			glVertex2i(635 + 20, 340 + 10);
			glVertex2i(635 + 22, 340 + 10);
			glVertex2i(635 + 22, 340 + 8);
			glVertex2i(635 + 20, 340 + 8);
		}
		if (menumove / 40 >= 1)
		{
			glVertex2i(635 + 6, 340 + 4);
			glVertex2i(635 + 4, 340 + 4);
			glVertex2i(635 + 4, 340 + 6);
			glVertex2i(635 + 6, 340 + 6);

			glVertex2i(635 + 2, 340 + 4);
			glVertex2i(635 + 4, 340 + 4);
			glVertex2i(635 + 4, 340 + 6);
			glVertex2i(635 + 2, 340 + 6);

			glVertex2i(635 + 2, 340 + 6);
			glVertex2i(635, 340 + 6);
			glVertex2i(635, 340 + 8);
			glVertex2i(635 + 2, 340 + 8);

			glVertex2i(635 + 16, 340 + 4);
			glVertex2i(635 + 18, 340 + 4);
			glVertex2i(635 + 18, 340 + 6);
			glVertex2i(635 + 16, 340 + 6);

			glVertex2i(635 + 18, 340 + 4);
			glVertex2i(635 + 20, 340 + 4);
			glVertex2i(635 + 20, 340 + 6);
			glVertex2i(635 + 18, 340 + 6);

			glVertex2i(635 + 20, 340 + 6);
			glVertex2i(635 + 22, 340 + 6);
			glVertex2i(635 + 22, 340 + 8);
			glVertex2i(635 + 20, 340 + 8);

			glVertex2i(635 + 6, 340 + 10);
			glVertex2i(635 + 4, 340 + 10);
			glVertex2i(635 + 4, 340 + 12);
			glVertex2i(635 + 6, 340 + 12);

			glVertex2i(635 + 2, 340 + 10);
			glVertex2i(635 + 4, 340 + 10);
			glVertex2i(635 + 4, 340 + 12);
			glVertex2i(635 + 2, 340 + 12);

			glVertex2i(635 + 2, 340 + 14);
			glVertex2i(635, 340 + 14);
			glVertex2i(635, 340 + 12);
			glVertex2i(635 + 2, 340 + 12);

			glVertex2i(635 + 16, 340 + 10);
			glVertex2i(635 + 18, 340 + 10);
			glVertex2i(635 + 18, 340 + 12);
			glVertex2i(635 + 16, 340 + 12);

			glVertex2i(635 + 18, 340 + 10);
			glVertex2i(635 + 20, 340 + 10);
			glVertex2i(635 + 20, 340 + 12);
			glVertex2i(635 + 18, 340 + 12);

			glVertex2i(635 + 20, 340 + 12);
			glVertex2i(635 + 22, 340 + 12);
			glVertex2i(635 + 22, 340 + 14);
			glVertex2i(635 + 20, 340 + 14);
		}
		glEnd();
	}
	else
	{
		glColor3ub(25, 25, 25);
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(800, 0);
		glVertex2i(800, 600);
		glVertex2i(0, 600);
		glEnd();
		glColor3ub(255, 255, 255);
		glRasterPos2i(340, 250);
		YsGlDrawFontBitmap10x14("Game Over");
		char cscore[256];
		sprintf(cscore, "Score: %d", score);
		glColor3ub(255, 255, 255);
		glRasterPos2i(340, 270);
		YsGlDrawFontBitmap10x14(cscore);
	}
	
}

//Class to run the game
class CentipedeGame
{
public:
	int score;
	int Play(void);
	
};
int CentipedeGame::Play(void)
{
	//Sets initial level
	int level = 1;
	int initiation = 1;
	int gameover = 0;
	int gameover2 = 0;

	//Variable to end Menu loop
	int menuclose = -1;
	int menumove = 0;

	//Creates player object and initializes
	Player plyr;
	plyr.Initialize();
	score = 0;
	plyr.lives = 3;
	int livescount = 0;

	//Creates missile object and initializes
	Missle msl;
	msl.Initialize();

	//Creates spider object and initializes
	Spider spdr;
	spdr.Initialize();
	int oldplayerx, oldplayery, oldspiderx, oldspidery;
	int movecounter = 0;
	int centcount = 0;
	int centcount2 = 0;

	//Used for mushrooms
	int t0 = time(NULL);
	srand(t0);
	const int numshroom = 150;
	Mushroom shrm[numshroom];

	//Used for centipede
	const int centlength = 60;
	int centspeed = 2;
	int xstart = -16;
	int legstatecounter = 0;
	int drawlegs = 1;
	int centsshot = 0;
	//Centipede cent[centlength];
	Centipede cent[centlength];

	//FsOpenWindow(0, 0, 800, 600, 1);
	for (;;)
	{
		//Generates random mushrooms and initiates the centipede after each level
		int coordinates[50 * 36];
		int icount = 0;
		if (initiation == 1)
		{
			if (level == 1)
			{
				RandomShroom(coordinates);
				for (auto &s : shrm)
				{
					s.Initialize(coordinates, icount);
					icount++;
				}
				for (int i = 0; i < 100; i++)
				{
					shrm[i].state = 0;
				}
				for (int i = 0; i < centlength; i++)
				{
					cent[i].Initialize(centspeed, xstart);
					xstart -= 16;
				}		
				for (int i = 20; i < centlength; i++)
				{
					cent[i].state = 0;
				}
				initiation = 0;
				xstart = -16;
			}
			else if (level == 2)
			{
				RandomShroom(coordinates);
				for (auto &s : shrm)
				{
					s.Initialize(coordinates, icount);
					icount++;
				}
				for (int i = 0; i < 50; i++)
				{
					shrm[i].state = 0;
				}
				for (int i = 0; i < centlength; i++)
				{
					cent[i].Initialize(centspeed, xstart);
					xstart -= 16;
				}
				for (int i = 40; i < centlength; i++)
				{
					cent[i].state = 0;
				}
				initiation = 0;
				xstart = -16;
			}
			else 
			{
				RandomShroom(coordinates);
				for (auto &s : shrm)
				{
					s.Initialize(coordinates, icount);
					icount++;
				}
				for (int i = 0; i < centlength; i++)
				{
					cent[i].Initialize(centspeed, xstart);
					xstart -= 16;
				}
				initiation = 0;
				xstart = -16;
			}
			
		}

		FsPollDevice();
		auto key = FsInkey();
		switch (key)
		{
		case FSKEY_ESC:
			goto label;
		case FSKEY_H:
			menuclose = -1;
			break;
		case FSKEY_R:
			menuclose = 1;
			break;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (menuclose > 0)
		{
			//Input to the player object
			if (0 != FsGetKeyState(FSKEY_UP) && plyr.y > 400)
			{
				plyr.y -= 4;
			}
			if (0 != FsGetKeyState(FSKEY_DOWN) && plyr.y + 16 < 560)
			{
				plyr.y += 4;
			}
			if (0 != FsGetKeyState(FSKEY_LEFT) && plyr.x>1)
			{
				plyr.x -= 4;
			}
			if (0 != FsGetKeyState(FSKEY_RIGHT) && plyr.x + 16< 800)
			{
				plyr.x += 4;
			}
			if (0 != FsGetKeyState(FSKEY_SPACE))
			{
				if (msl.state == 0 && plyr.state ==1)
				{
					msl.x = plyr.x;
					msl.y = plyr.y;
					msl.state = 1;
				}
			}
			//Defines leg state by odd or odd number
			legstatecounter += 1;
			if (legstatecounter == 100)
			{
				legstatecounter = 0;
			}
			if (legstatecounter % 25 == 0)
			{
				drawlegs = drawlegs*-1;
			}
			
			//Moves the centipede head and body
			int j = 0;
			for (int i = 0; i < centlength; i++)
			{
				//Defines whether eyes need to be drawn for the head
				if ((i == 0) || (cent[i - 1].state == 0))
				{
					cent[i].draweyes = 1;
				}
				//Moving the head
				//If it hits a mushroom
				for (int k = 0; k < numshroom; k++)
				{
					//Left side of mushroom
					if (cent[i].x + 16 == shrm[k].x * 16 && cent[i].y == (shrm[k].y + 1) * 16 && cent[i].vx>0 && shrm[k].state!=0)
					{
						cent[i].hitdetect = 1;
					}
					//Right side of mushroom
					if (cent[i].x == shrm[k].x * 16 + 16 && cent[i].y == (shrm[k].y + 1) * 16 && cent[i].vx<0 && shrm[k].state != 0)
					{
						cent[i].hitdetect = 1;
					}
				}
				//Checks if hits the bottom
				if (cent[i].y + 16 == 560)
				{
					cent[i].bottomdetect = 1;
				}
				if (cent[i].y <= 400)
				{
					cent[i].bottomdetect = 0;
				}
				//If head hits the right edge
				if (cent[i].x + 16 == 800 && cent[i].vx>0 && cent[i].hitdetect == 0)
				{
					cent[i].xhist[0] = cent[i].x;
					cent[i].yhist[0] = cent[i].y;
					if ((i == 0) || (cent[i - 1].state == 0))
					{
						if (cent[i].bottomdetect == 1)
						{
							cent[i].vy = -centspeed;
							cent[i].y += cent[i].vy;
						}
						else
						{
							cent[i].vy = centspeed;
							cent[i].y += cent[i].vy;
						}
					}
					if (cent[i].xhist[0] == cent[i].xhist[7] && cent[i].y % 16 == 0)
					{
						cent[i].vx = cent[i].vx*-1;
						cent[i].vy = 0;
					}
				}
				//If head hits the left edge
				else if (cent[i].x == 0 && cent[i].vx < 0 && cent[i].hitdetect == 0)
				{
					cent[i].xhist[0] = cent[i].x;
					cent[i].yhist[0] = cent[i].y;
					if ((i == 0) || (cent[i - 1].state == 0))
					{
						if (cent[i].bottomdetect == 1)
						{
							cent[i].vy = -centspeed;
							cent[i].y += cent[i].vy;
						}
						else
						{
							cent[i].vy = centspeed;
							cent[i].y += cent[i].vy;
						}
					}
					if (cent[i].xhist[0] == cent[i].xhist[7] && cent[i].y % 16 == 0)
					{
						cent[i].vx = cent[i].vx*-1;
						cent[i].vy = 0;
					}
				}
				//Hits mushroom
				else if (cent[i].hitdetect != 0)
				{
					cent[i].hitdetect += 1;
					cent[i].xhist[0] = cent[i].x;
					cent[i].yhist[0] = cent[i].y;
					if ((i == 0) || (cent[i - 1].state == 0))
					{
						if (cent[i].bottomdetect == 1)
						{
							cent[i].vy = -centspeed;
							cent[i].y += cent[i].vy;
						}
						else
						{
							cent[i].vy = centspeed;
							cent[i].y += cent[i].vy;
						}
					}
					if (cent[i].hitdetect > 7 && cent[i].x == 0 && cent[i].y % 16 == 0) 
					{
						cent[i].vx = cent[i].vx*-1;
						cent[i].hitdetect = 0;
						cent[i].vy = 0;
					}
					if (cent[i].hitdetect >7 && cent[i].x == 800 - 16 && cent[i].y % 16 == 0)
					{
						cent[i].vx = cent[i].vx*-1;
						cent[i].hitdetect = 0;
						cent[i].vy = 0;
					}
					if (cent[i].hitdetect >8 && cent[i].y % 16 == 0) 
					{
						cent[i].vx = cent[i].vx*-1;
						cent[i].hitdetect = 0;
						cent[i].vy = 0;
					}
				}
				else
				{
					cent[i].xhist[0] = cent[i].x;
					cent[i].yhist[0] = cent[i].y;
					if ((i == 0) || (cent[i - 1].state == 0))
					{
						if (cent[i].hitdetect == 0)
						{
							cent[i].x += cent[i].vx;
							cent[i].hitdetect = 0;
						}
					}
				}
				if (cent[i].x < 0)
				{
					cent[i].x = 0;
				}
				for (int k = 8; k>0; k--) 
				{
					cent[i].xhist[k] = cent[i].xhist[k - 1];
					cent[i].yhist[k] = cent[i].yhist[k - 1];
				}

				//Moving the body
				if (cent[j - 1].state == 1)
				{
					cent[j].x = cent[j - 1].xhist[8];  
					cent[j].y = cent[j - 1].yhist[8];  
				}
				j++;
			}

			//Checks collisions of the missile on the mushroom
			for (int i = 0; i < numshroom; ++i)
			{
				int mushcollision = CentipedeCheckShroomCollision(msl.x, msl.y, msl.state, shrm[i].x, shrm[i].y, shrm[i].state, score);
				if (mushcollision == 1)
				{
					shrm[i].state -= 1;
					msl.state = 0;
				}
			}

			//Checks collision of missile on centipede and centipede on player
			for (int i = 0; i < centlength; ++i)
			{
				int centcollision = CentipedeCheckCentCollision(msl.x, msl.y, msl.state, cent[i].x, cent[i].y, cent[i].state, score);
				if (centcollision == 1 && cent[i].x>=0)
				{
					cent[i].state = 0;
					msl.state = 0;
					cent[i + 1].hitdetect = 1;
					centsshot += 1;
				}
				
				int centplyr = CentipedeCheckCentPlyrCollision(plyr.x, plyr.y, plyr.state, cent[i].x, cent[i].y, cent[i].state, score);
				if (centplyr == 1)
				{
					plyr.state = 0;
					plyr.lives -= 1;
				}
			}

			//Checks collision of missile on the spider
			int spdrcollision = CentipedeCheckSpiderCollision(msl.x, msl.y, msl.state, spdr.x, spdr.y, spdr.state, score);
			if (spdrcollision == 1)
			{
				spdr.state = 0;
				msl.state = 0;
				spdr.move = 0;
			}

			//Checks for collision of spider on player
			int spdrplyr = CentipedeCheckSpdrPlyrCollision(plyr.x, plyr.y, plyr.state, spdr.x, spdr.y, spdr.state, score);
			if (spdrplyr == 1)
			{
				plyr.state = 0;
				plyr.lives -= 1;
				spdr.move = 1;
			}

			//Defines whether the spider should move and where
			if (spdr.move == 0 && plyr.state==1)
			{
				oldplayerx = plyr.x;
				oldplayery = plyr.y;
				oldspiderx = spdr.x;
				oldspidery = spdr.y;
			}
			if (plyr.state == 0)
			{
				oldplayery = 400;
				oldplayerx = plyr.x;
				oldspiderx = spdr.x;
				oldspidery = spdr.y;
			}

			//Move is turned on after so many cycles without it on
			if (spdr.move == 0)
			{
				movecounter +=1;
			}
			if (movecounter >= 75)
			{
				spdr.move = 1;
				movecounter = 0;
			}

			//Defines if the spider should turn on
			if (spdr.state == 1)
			{
				centcount2 = 0;
			}
			else
			{
				centcount = 0;
			}
			for (int i = 0; i<centlength; i++)
			{
				if (cent[i].state == 0 && spdr.state==0)
				{
					centcount++;
				}
				if (cent[i].state == 0 && spdr.state == 1)
				{
					centcount2++;
				}
			}

			//Spider turns on
			if (level == 1)
			{
				if (centcount - centcount2 == 5 && centcount != 0 && spdr.state == 0)
				{
					if (plyr.x > 392)
					{
						spdr.state = 1;
						spdr.x = 0;
						spdr.y = 400;
						oldspiderx = 0;
						oldspidery = 400;
						spdr.move = 1;
					}
					else
					{
						spdr.state = 1;
						spdr.x = 800 - 22;
						spdr.y = 400;
						oldspiderx = 800 - 22;
						oldspidery = 400;
						spdr.move = 1;
					}
					centcount = 0;
					centcount2 = 0;
				}
			}
			else if (level == 2)
			{
				if (centcount - centcount2 == 3 && centcount != 0 && spdr.state == 0)
				{
					if (plyr.x > 392)
					{
						spdr.state = 1;
						spdr.x = 0;
						spdr.y = 400;
						oldspiderx = 0;
						oldspidery = 400;
						spdr.move = 1;
					}
					else
					{
						spdr.state = 1;
						spdr.x = 800 - 22;
						spdr.y = 400;
						oldspiderx = 800 - 22;
						oldspidery = 400;
						spdr.move = 1;
					}
					centcount = 0;
					centcount2 = 0;
				}
			}
			else
			{
				if (centcount != 0 && spdr.state == 0)
				{
					if (plyr.x > 392)
					{
						spdr.state = 1;
						spdr.x = 0;
						spdr.y = 400;
						oldspiderx = 0;
						oldspidery = 400;
						spdr.move = 1;
					}
					else
					{
						spdr.state = 1;
						spdr.x = 800 - 22;
						spdr.y = 400;
						oldspiderx = 800 - 22;
						oldspidery = 400;
						spdr.move = 1;
					}
					centcount = 0;
					centcount2 = 0;
				}
			}

			//Respawns the player after being hit
			if (plyr.state == 0 && plyr.lives != 0)
			{

				livescount++;
				int safe = 0;
				for (int i = 0; i < centlength; i++)
				{
					if (cent[i].x > 250 && cent[i].x < 550 && cent[i].y>520 && cent[i].state == 1)
					{
						safe++;
					}
					else if (spdr.y > 500 && spdr.x < 550 && spdr.x>250)
					{
						safe++;
					}
				}
				if (livescount > 100 && safe ==0)
				{
					plyr.state = 1;
					plyr.x = 396;
					plyr.y = 544;
					livescount = 0;
				}
			}

			//Defines if the end of the level has occurred
			int levelover = 0;
			for (int i=0; i<centlength; i++)
			{
				if (cent[i].state != 0)
				{
					levelover++;
				}
			}
			if (levelover == 0)
			{
				level += 1;
				initiation = 1;
			}
			//Closes if complete level 3
			if (level == 4 || plyr.lives ==0)
			{
				menuclose = 0;
				gameover = 1;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		//Draw menu
		if (menuclose < 1)
		{
			CentipedeDrawHelp(menumove, gameover, score);
			menumove++;
			if (menumove >= 80)
			{
				menumove = 0;
			}
			if (gameover == 1)
			{
				gameover2++;
				if (gameover2 > 200)
				{
					goto label;
				}
			}

		}
		else
		{
			//Holds screen for a few seconds after end of level
			if (initiation == 1)
			{
				unsigned int t0 = time(NULL);
				while (time(NULL) - t0<1)
				{
					FsSwapBuffers();
					FsSleep(10);
				}
				spdr.Initialize();
				plyr.Initialize();
			}
			CentipedeBackgroundColor();
			CentipedeDrawFooter(plyr.lives, score);
			//Draws the missle and then moves it
			if (msl.state == 1)
			{
				CentipedeDrawMissle(msl.x, msl.y, msl.state, level);
				msl.MoveMissle();
			}
			//Draws the random mushrooms
			for (auto s : shrm)
			{
				if (0 != s.state)
				{
					CentipedeDrawMushroom(s.x, s.y, s.state, level);
				}
			}
			
			if (plyr.state == 1)
			{
				CentipedeDrawPlayer(plyr.x, plyr.y, level);
			}

			//Draws the centipede and provides indicator on when the spider should turn on
			for (int i = 0; i<centlength; i++)
			{
				if (cent[i].state == 1) //& i!=0
				{
					CentipedeDrawCentipede(cent[i].x, cent[i].y, cent[i].state, cent[i].draweyes, drawlegs, cent[i].vx, cent[i].vy, level);
				}
			}

			//Draws the spider
			if (spdr.state == 1)
			{
				if (spdr.move == 1)
				{
					spdr.MoveSpider(oldplayerx, oldplayery, oldspiderx, oldspidery, movecounter, level);
				}
				CentipedeDrawSpider(spdr.x, spdr.y, drawlegs, level);
			}
			
		}

		FsSwapBuffers();
		FsSleep(10);
	}
label:
	return score;
}

//int main(void)
//{
//	Game game;
//	game.Play();
//	return 0;
//}