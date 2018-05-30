//Matthew Prelich
//The Classic "Frogger" Arcade Game 



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"




void DrawCircle(int cx, int cy, int rad, int fill)
{
	const double YS_PI = 3.1415927;

	if (0 != fill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}

	int i;
	for (i = 0; i<64; i++)
	{
		double angle = (double)i*YS_PI / 32.0;
		double x = (double)cx + cos(angle)*(double)rad;
		double y = (double)cy + sin(angle)*(double)rad;
		glVertex2d(x, y);
	}

	glEnd();
}

void DrawRect(int x1, int y1, int x2, int y2, int fill)
{
	if (0 != fill)
	{
		glBegin(GL_QUADS);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}

	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);

	glEnd();
}

void DrawSemiCircle(int cx, int cy, int rad, int way) //way=0 means concave up versus way= anything else makes concave down
{
	if (way = 0) {
		glBegin(GL_POLYGON);
		const double YS_PI = 3.1415927;
		int i;
		for (i = 0; i < 32; i++) //creating semicircles
		{
			double angle = (double)i*YS_PI / 32.0;
			double x = (double)cx + cos(angle)*(double)rad;
			double y = (double)cy + sin(angle)*(double)rad;
			glVertex2d(x, y);
		}
	}
	else {
		glBegin(GL_POLYGON);
		const double YS_PI = 3.1415927;
		int i;
		for (i = 32; i < 64; i++) //creating semicircles
		{
			double angle = ((double)i*YS_PI / 32.0) + YS_PI;
			double x = (double)cx + cos(angle)*(double)rad;
			double y = (double)cy + sin(angle)*(double)rad;
			glVertex2d(x, y);
		}
		//for (i = 0; i < 32; i++) //creating semicircles
		//{
		//	double angle = (double)i*YS_PI / 32.0;
		//	double x = (double)cx + cos(angle)*(double)rad;
		//	double y = (double)cy + sin(angle)*(double)rad;
		//	glColor3ub(0, 0, 0);
		//	glVertex2d(x, y);
		//}

	}
	glEnd();

}

void DrawSnake(int cx, int cy, int rad)
{
	glColor3ub(50, 150, 55);
	DrawSemiCircle(cx, cy, rad, 0);
	glColor3ub(0, 0, 0);
	DrawSemiCircle(cx, cy, rad - 10, 0);

	glColor3ub(50, 150, 55);
	DrawSemiCircle(cx - (rad * 2 - 7), cy - 5, rad, 1);
	glColor3ub(0, 0, 0);
	DrawSemiCircle(cx - (rad * 2 - 7), cy - 5, rad - 10, 0);

}

void DrawTurtle(int cx, int cy)
{
	glColor3ub(150, 67, 55);
	DrawCircle(cx - 40 / 1.8, cy - 25 / 1.8, 3, 1);
	DrawCircle(cx - 25 / 1.8, cy - 8 / 1.8, 3, 1);
	DrawCircle(cx - 25 / 1.8, cy - 40 / 1.8, 3, 1);
	DrawCircle(cx + 30 / 1.8, cy - 11 / 1.8, 3, 1);
	DrawCircle(cx + 30 / 1.8, cy - 35 / 1.8, 3, 1);


	glBegin(GL_POLYGON);
	glColor3ub(50, 150, 55);

	glVertex2i(cx, cy);
	glVertex2i(cx - 7 / 1.8, cy - 1.5 / 1.8);
	glVertex2i(cx - 14 / 1.8, cy - 4 / 1.8);
	glVertex2i(cx - 20 / 1.8, cy - 7 / 1.8);
	glVertex2i(cx - 30 / 1.8, cy - 11 / 1.8);
	glVertex2i(cx - 36 / 1.8, cy - 17 / 1.8);
	glVertex2i(cx - 36 / 1.8, cy - 24 / 1.8);

	glVertex2i(cx - 37 / 1.8, cy - 26 / 1.8);
	glVertex2i(cx - 33 / 1.8, cy - 30 / 1.8);
	glVertex2i(cx - 30 / 1.8, cy - 34 / 1.8);
	glVertex2i(cx - 22 / 1.8, cy - 38 / 1.8);
	glVertex2i(cx - 14 / 1.8, cy - 41.5 / 1.8);
	glVertex2i(cx - 8 / 1.8, cy - 44 / 1.8);
	glVertex2i(cx, cy - 45 / 1.8);

	glBegin(GL_POLYGON);
	glVertex2i(cx, cy);
	glVertex2i(cx + 7 / 1.8, cy - 1.5 / 1.8);
	glVertex2i(cx + 14 / 1.8, cy - 4 / 1.8);
	glVertex2i(cx + 20 / 1.8, cy - 7 / 1.8);
	glVertex2i(cx + 30 / 1.8, cy - 11 / 1.8);
	glVertex2i(cx + 36 / 1.8, cy - 17 / 1.8);
	glVertex2i(cx + 40 / 1.8, cy - 24 / 1.8);

	glVertex2i(cx + 40 / 1.8, cy - 26 / 1.8);
	glVertex2i(cx + 33 / 1.8, cy - 30 / 1.8);
	glVertex2i(cx + 30 / 1.8, cy - 34 / 1.8);
	glVertex2i(cx + 22 / 1.8, cy - 38 / 1.8);
	glVertex2i(cx + 14 / 1.8, cy - 43 / 1.8);
	glVertex2i(cx + 8 / 1.8, cy - 46 / 1.8);
	glVertex2i(cx, cy - 47 / 1.8);




	/*glVertex2i(cx, cy);
	glVertex2i(cx-1, cy-.25);
	glVertex2i(cx-2, cy-.5);
	glVertex2i(cx-3, cy-.75);
	glVertex2i(cx - 4, cy - 1);
	glVertex2i(cx - 5, cy - 1.25);
	glVertex2i(cx - 6, cy - 1.5);*/

	glEnd();
}

void DrawLeg1(float scale, int cx, int cy)
{
	char pattern[] =
	{

		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111......"
		"......1111......"
		"......1111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"......1111......"
		"......1111......"
		"......1111......"
		"......1111......"
		"................"
		/*
		"...1........1..."
		"...11......11..."
		"...1........1..."
		"...1........1..."
		"...1........1..."
		"..1..1111....1.."
		"..1..........1.."
		"..111111111111.."
		".1............1."
		".1............1."
		"1..............1"
		"1..............1"
		".1............1."
		".1............1."
		"................"
		"................"*/
	};
	const int width = 16;
	const int height = 16;

	int i, j;
	for (i = 0; i<width; i++) //for all rows
	{
		for (j = 0; j<height; j++) //for all columns
		{
			if (pattern[j * width + i] == '1')
			{
				glColor3ub(50, 150, 55);
				glBegin(GL_QUADS);
				glVertex2d(cx + i * scale*width, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height + scale*width);
				glVertex2d(cx + i * scale*width, cy + j * scale*height + scale*width);
			}
		}
	}
	glEnd();

}

void DrawLeg2(float scale, int cx, int cy)
{
	char pattern[] =
	{

		"1111111111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"......1111......"
		"......1111......"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111......"
		"......1111......"
		"......1111......"
		"......1111......"
		"................"
		/*
		"...1........1..."
		"...11......11..."
		"...1........1..."
		"...1........1..."
		"...1........1..."
		"..1..1111....1.."
		"..1..........1.."
		"..111111111111.."
		".1............1."
		".1............1."
		"1..............1"
		"1..............1"
		".1............1."
		".1............1."
		"................"
		"................"*/
	};
	const int width = 16;
	const int height = 16;

	int i, j;
	for (i = 0; i<width; i++) //for all rows
	{
		for (j = 0; j<height; j++) //for all columns
		{
			if (pattern[j * width + i] == '1')
			{
				glColor3ub(50, 150, 55);
				glBegin(GL_QUADS);
				glVertex2d(cx + i * scale*width, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height + scale*width);
				glVertex2d(cx + i * scale*width, cy + j * scale*height + scale*width);
			}
		}
	}
	glEnd();

}

void DrawLeg3(float scale, int cx, int cy)
{
	char pattern[] =
	{

		"......1111......"
		"......1111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"......1111......"
		"......1111......"
		"......1111......"
		"......1111......"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"................"
		/*
		"...1........1..."
		"...11......11..."
		"...1........1..."
		"...1........1..."
		"...1........1..."
		"..1..1111....1.."
		"..1..........1.."
		"..111111111111.."
		".1............1."
		".1............1."
		"1..............1"
		"1..............1"
		".1............1."
		".1............1."
		"................"
		"................"*/
	};
	const int width = 16;
	const int height = 16;

	int i, j;
	for (i = 0; i<width; i++) //for all rows
	{
		for (j = 0; j<height; j++) //for all columns
		{
			if (pattern[j * width + i] == '1')
			{
				glColor3ub(50, 150, 55);
				glBegin(GL_QUADS);
				glVertex2d(cx + i * scale*width, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height + scale*width);
				glVertex2d(cx + i * scale*width, cy + j * scale*height + scale*width);
			}
		}
	}
	glEnd();

}
void DrawLeg4(float scale, int cx, int cy)
{
	char pattern[] =
	{

		"......1111......"
		"......1111......"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111111111"
		"......1111......"
		"......1111......"
		"......1111......"
		"......1111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"1111111111......"
		"................"
		/*
		"...1........1..."
		"...11......11..."
		"...1........1..."
		"...1........1..."
		"...1........1..."
		"..1..1111....1.."
		"..1..........1.."
		"..111111111111.."
		".1............1."
		".1............1."
		"1..............1"
		"1..............1"
		".1............1."
		".1............1."
		"................"
		"................"*/
	};
	const int width = 16;
	const int height = 16;

	int i, j;
	for (i = 0; i<width; i++) //for all rows
	{
		for (j = 0; j<height; j++) //for all columns
		{
			if (pattern[j * width + i] == '1')
			{
				glColor3ub(50, 150, 55);
				glBegin(GL_QUADS);
				glVertex2d(cx + i * scale*width, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height + scale*width);
				glVertex2d(cx + i * scale*width, cy + j * scale*height + scale*width);
			}
		}
	}
	glEnd();

}

void DrawSkelton(float scale, int cx, int cy)
{
	char pattern[] =
	{

		"..................................."
		"............111111111.............."
		"..........1..........1............."
		"........1..............1..........."
		"......1..................1........."
		".....1.....................1......."
		"....1.....1.........1.......1......"
		"...1....1...1.....1...1.....1......"
		"....1.....1.........1......1......."
		".....1...................1........."
		".......1...............1..........."
		".....1...................1........."
		"....1.....................1........"
		"...1.......................1......."
		"...1.......................1......."
		"....111111............11111........"
		"..........1..........1............."
		"...........1.......1..............."
		".............111111................"
		"..................................."
		"..11111...................11......."
		".11....1................1....1....."
		"...1.....1............1......1....."
		".....1......1.......1.......1......"
		".......1......1...1.......1........"
		".........1......1.......1.........."
		"...........1......1...1............"
		"............1.1.......1............"
		"..........1.....1.......1.........."
		"........1....1....1......1........."
		"......1.....1........1......1......"
		"....1.....1............1......1...."
		"..1....11................1.....1...."
		"..1111....................1111....."
		"..................................."

	};
	const int width = 35;
	const int height = 35;

	int i, j;
	for (i = 0; i<width; i++) //for all rows
	{
		for (j = 0; j<height; j++) //for all columns
		{
			if (pattern[j * width + i] == '1')
			{
				glColor3ub(139, 0, 0);
				glBegin(GL_QUADS);
				glVertex2d(cx + i * scale*width, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height);
				glVertex2d(cx + i * scale*width + scale*height, cy + j * scale*height + scale*width);
				glVertex2d(cx + i * scale*width, cy + j * scale*height + scale*width);
			}
		}
	}
	glEnd();

}

void DrawFrog(int cx, int cy)
{

	glBegin(GL_POLYGON);
	glColor3ub(50, 150, 55);

	glVertex2i(cx, cy);
	glVertex2i(cx - 3 / 1.4, cy - 5 / 1.4);
	glVertex2i(cx - 7 / 1.4, cy - 10 / 1.4);
	glVertex2i(cx - 12 / 1.4, cy - 7 / 1.4);
	glVertex2i(cx - 15 / 1.4, cy - 11 / 1.4);
	glVertex2i(cx - 18 / 1.4, cy - 17 / 1.4);
	glVertex2i(cx - 22 / 1.4, cy - 24 / 1.4);

	glVertex2i(cx - 22 / 1.4, cy - 25 / 1.4);
	glVertex2i(cx - 20 / 1.4, cy - 30 / 1.4);
	glVertex2i(cx - 17 / 1.4, cy - 34 / 1.4);
	glVertex2i(cx - 13 / 1.4, cy - 37 / 1.4);
	glVertex2i(cx - 11 / 1.4, cy - 40 / 1.4);
	glVertex2i(cx - 8 / 1.4, cy - 44 / 1.4);
	glVertex2i(cx - 4 / 1.4, cy - 46 / 1.4);
	glVertex2i(cx, cy - 48 / 1.4);

	glBegin(GL_POLYGON);
	glColor3ub(50, 150, 55);

	glVertex2i(cx, cy);
	glVertex2i(cx + 3 / 1.4, cy - 5 / 1.4);
	glVertex2i(cx + 7 / 1.4, cy - 10 / 1.4);
	glVertex2i(cx + 12 / 1.4, cy - 7 / 1.4);
	glVertex2i(cx + 15 / 1.4, cy - 11 / 1.4);
	glVertex2i(cx + 18 / 1.4, cy - 17 / 1.4);
	glVertex2i(cx + 22 / 1.4, cy - 24 / 1.4);

	glVertex2i(cx + 22 / 1.4, cy - 25 / 1.4);
	glVertex2i(cx + 20 / 1.4, cy - 30 / 1.4);
	glVertex2i(cx + 17 / 1.4, cy - 34 / 1.4);
	glVertex2i(cx + 13 / 1.4, cy - 37 / 1.4);
	glVertex2i(cx + 11 / 1.4, cy - 40 / 1.4);
	glVertex2i(cx + 8 / 1.4, cy - 44 / 1.4);
	glVertex2i(cx + 4 / 1.4, cy - 46 / 1.4);
	glVertex2i(cx, cy - 48 / 1.4);
	glEnd();

	DrawLeg1(.05, cx - 30 / 1.4, cy - 15 / 1.4);
	DrawLeg2(.05, cx + 12 / 1.4, cy - 15 / 1.4);
	DrawLeg3(.05, cx - 32 / 1.4, cy - 46 / 1.4);
	DrawLeg4(.05, cx + 12 / 1.4, cy - 46 / 1.4);

	glColor3ub(128, 0, 128);
	DrawCircle(cx - 8, cy - 20, 2.5, 1);
	DrawCircle(cx + 8, cy - 20, 2.5, 1);




	//don't include glEnd() since we only need it once and our main() has it already. 
}




void DrawLog(int cx, int cy, int height, int width)
{

	glColor3ub(155, 45, 19);
	DrawCircle(cx - height / 10, cy - height / 1.95, height / 1.6, 1);
	glColor3ub(139, 69, 19);
	DrawRect(cx, cy, (cx + width), (cy - height), 1);

}

void DrawLilipad(int cx, int cy)
{

	glColor3ub(0, 255, 0);
	DrawCircle(cx, cy, 25, 1);  //outer radius=25
	glColor3ub(55, 200, 0);
	DrawCircle(cx, cy, 15, 1);  //inner radious=15
								//later in program I make it such that if part of frog touches inner circle, then it is "on" the lilipad
								//if frog is not touching inner circle, then it is considered "off" the lilipad and thus dies :( 
}

void DrawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);

	glVertex2i(x1, y1);
	glVertex2i(x2, y2);

	glEnd();
}

void DrawRandomCurrents(void)
{
	int cx, cy, rad;
	int r, g, b;
	cx = rand() % 800;
	cy = 60 + rand() % 240;
	rad = rand() % 3;
	r = 100;
	g = rand() % 255;
	b = 255;

	glColor3ub(r, g, b);
	DrawCircle(cx, cy, rad, 1);
}

void DrawScene(void)
{
	glColor3ub(139, 69, 19);
	DrawRect(0, 600, 800, 540, 1);

	glColor3ub(255, 255, 0);
	DrawLine(0, 540, 800, 540);
	DrawLine(0, 480, 800, 480);
	DrawLine(0, 420, 800, 420);
	DrawLine(0, 360, 800, 360);
	DrawLine(0, 300, 800, 300);

	for (int i = 10; i < 801; i += 20)
	{
		DrawLine(i - 10, 510, i, 510);
		DrawLine(i - 10, 450, i, 450);
		DrawLine(i - 10, 390, i, 390);
		DrawLine(i - 10, 330, i, 330);
		DrawLine(i - 10, 270, i, 270);
	}


	glColor3ub(70, 155, 30);
	DrawRect(0, 0, 100, 60, 1);
	DrawRect(160, 0, 260, 60, 1);
	DrawRect(320, 0, 420, 60, 1);
	DrawRect(480, 0, 580, 60, 1);
	DrawRect(640, 0, 800, 60, 1);

	glColor3ub(0, 0, 205);  //water 
	DrawRect(100, 0, 160, 60, 1);
	DrawRect(260, 0, 320, 60, 1);
	DrawRect(420, 0, 480, 60, 1);
	DrawRect(580, 0, 640, 60, 1);
	//DrawRect(740, 0, 800, 60, 1);

	DrawRect(0, 60, 800, 300, 1);




}

//-----------------------------------------------------Class Definitions--------------------------

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

void Frog::ResetLocation(void)
{
	x = 450;
	y = 580;
}

void Frog::Draw(void)
{
	DrawFrog(x, y);
}

void Frog::Dead(int time1) //calculates score as well. 
{
	gametime = time(NULL) - time1;
	//score += 10*(120 - gametime);  //10 points per unused seconds (given 2 minutes) 
	alive = false;
	DrawSkelton(.25, 250, 100);
	//printf("Game Over. Your Score was %d \n", score);
}

void Frog::Winner(int time1) //calculates score as well. 
{
	gametime = time(NULL) - time1;
	score += 10 * (120 - gametime);  //10 points per unused seconds (given 2 minutes) 
	alive = false;  //He's still alive though actually! Just for convenience
	//printf("You won! Congratulations! Your time was %d seconds, and your Score was %d   \n", gametime, score);
}

bool Frog::CheckAlive(bool truck, bool car1, bool car2, bool occupied, bool missed)
{
	if (x > 800 || x < 0) {
		return false;
	}


	if (truck == false || car1 == false || car2 == false || occupied == true || missed == true) {
		return false;
	}
	else {
		return true;
	}

}

//void Move(void)
//{
//	x+=50
//
//
//}
//

//int Frog::IsHitByWater(Water & water)
//{
//	int relativeX, relativeY;
//	relativeX = ball.x - x;
//	relativeY = ball.y - y;
//	if (0 <= relativeX && relativeX<w && 0 <= relativeY && relativeY<h)
//	{
//		alive = false; 
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//
//int Frog::OffScreen(void) //check if frog goes offscreen or hits green part of pond (Non-lilipad) which kills it. 
//{
//	if (y<100.0 && checkLilipadState !=)
//	{
//		vy = -vy;
//	}
//
//	if (x<-39.0 && vx<0.0)
//	{
//		vx = -vx;
//	}
//	else if (x>39.0 && vx>0.0)
//	{
//		vx = -vx;
//	}
//	int relativeX, relativeY;
//	relativeX = ball.x - x;
//	relativeY = ball.y - y;
//	if (0 <= relativeX && relativeX<w && 0 <= relativeY && relativeY<h)
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//------------------------------------Truck Class---------------
class Truck
{
public:
	int x1, x2, y, w, h, v;
	void Initialize(void);
	void Draw(void);
	void Move(void);
	bool IsHitByFrog(Frog & frog);
};

void Truck::Initialize(void) //make sure to call outside the loop
{
	srand(time(NULL));
	x1 = 200 + rand() % 600;
	srand(time(NULL));  //Need this srand() here or else doesn't randomize it. 
	x2 = x1 + 100 + rand() % 400;
	h = 35;
	w = 70;
	y = 465;
	v = 10 + rand() % 10; //velocity in pixels per frame
}

void Truck::Draw(void)
{
	if ((x1 + w) <800) {
		glColor3ub(0, 0, 255);
		DrawRect(x1, y, x1 + w, y - h, 1);
	}
	else {
		x1 = 0;
		glColor3ub(0, 0, 255);
		DrawRect(x1, y, x1 + w, y - h, 1);
	}
	if ((x2 + w) <800) {
		glColor3ub(0, 0, 255);
		DrawRect(x2, y, x2 + w, y - h, 1);
	}
	else {
		x2 = 0;
		glColor3ub(0, 0, 255);
		DrawRect(x2, y, x2 + w, y - h, 1);
	}

}

void Truck::Move(void)
{
	x1 = x1 + v;
	x2 = x2 + v;
}

bool Truck::IsHitByFrog(Frog &frog)
{
	int relativeX1, relativeX2, relativeY;
	relativeX1 = frog.x - x1;
	relativeX2 = frog.x - x2;
	relativeY = frog.y - y;

	//if (frog.CheckAlive(trucks.IsHitByFrog(frog), aaa, aaaa) == false) {
	//	frog.Dead();
	//}

	if ((-frog.w <= relativeX1 && relativeX1<(w + .5*frog.w) && frog.y<480 && frog.y>420) || (-frog.w <= relativeX2 && relativeX2<(w + .5*frog.w) && frog.y<480 && frog.y>420))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//--------------------------------------------------------------------------------Car Class---------------------------------------------------------
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

void Car::Draw(int y, int R, int G, int B)
{
	if ((x1 + w) <800) {
		glColor3ub(R, G, B);
		DrawRect(x1, y, x1 + w, y - h, 1);
	}
	else {
		x1 = 0;
		glColor3ub(R, G, B);
		DrawRect(x1, y, x1 + w, y - h, 1);
	}
	if ((x2 + w) <800) {
		glColor3ub(R, G, B);
		DrawRect(x2, y, x2 + w, y - h, 1);
	}
	else {
		x2 = 0;
		glColor3ub(R, G, B);
		DrawRect(x2, y, x2 + w, y - h, 1);
	}
	if ((x3 + w) <800) {
		glColor3ub(R, G, B);
		DrawRect(x3, y, x3 + w, y - h, 1);
	}
	else {
		x3 = 0;
		glColor3ub(R, G, B);
		DrawRect(x3, y, x3 + w, y - h, 1);
	}

}

void Car::Move(int velocitycar)
{
	v = velocitycar;
	x1 = x1 + v;
	x2 = x2 + v;
	x3 = x3 + v;
}

bool Car::IsHitByFrog(Frog &frog, int argy)
{
	int relativeX1, relativeX2, relativeX3, relativeY;
	relativeX1 = frog.x - x1;
	relativeX2 = frog.x - x2;
	relativeX3 = frog.x - x3;

	//if (frog.CheckAlive(trucks.IsHitByFrog(frog), aaa, aaaa) == false) {
	//	frog.Dead();
	//}

	if ((-frog.w <= relativeX1 && relativeX1<(w + .5*frog.w) && frog.y<argy && frog.y>(argy - 60)) || (-frog.w <= relativeX2 && relativeX2<(w + .5*frog.w) && frog.y<argy && frog.y>(argy - 60)) || (-frog.w <= relativeX3 && relativeX3<(w + .5*frog.w) && frog.y<argy && frog.y>(argy - 60)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

////----------------------------------------------------------------------------------------Turtle Class-------------------------------------------

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

void Turtle::Draw(int y)
{
	if (((x1 + w) <800)) {

		DrawTurtle(x1, y);
		DrawTurtle(x1 + 50, y);
		DrawTurtle(x1 + 100, y);
	}
	else {
		x1 = 0;
		DrawTurtle(x1, y);
		DrawTurtle(x1 + 50, y);
		DrawTurtle(x1 + 100, y);
	}
	if ((x2 + w) <800) {
		DrawTurtle(x2, y);
		DrawTurtle(x2 + 50, y);
		DrawTurtle(x2 + 100, y);
	}
	else {
		x2 = 0;
		DrawTurtle(x2, y);
		DrawTurtle(x2 + 50, y);
		DrawTurtle(x2 + 100, y);
	}
	if ((x3 + w) <800) {
		DrawTurtle(x3, y);
		DrawTurtle(x3 + 50, y);
		DrawTurtle(x3 + 100, y);
	}
	else {
		x3 = 0;
		DrawTurtle(x3, y);
		DrawTurtle(x3 + 50, y);
		DrawTurtle(x3 + 100, y);
	}

}

void Turtle::Move(void)
{
	x1 = x1 + v;
	x2 = x2 + v;
	x3 = x3 + v;
}

bool Turtle::IsUnderFrog(Frog &frog, int argy)
{
	int relativeX1, relativeX2, relativeX3, relativeY;
	relativeX1 = frog.x - x1;
	relativeX2 = frog.x - x2;
	relativeX3 = frog.x - x3;

	//if (frog.CheckAlive(trucks.IsHitByFrog(frog), aaa, aaaa) == false) {
	//	frog.Dead();
	//}

	//printf("@ %d %d %d\n", frog.x, frog.y, frog.w);
	//printf("%d %d\n", w,v);
	//printf("%d %d %d\n", x1, x2, x3);
	//printf("%d %d %d\n", relativeX1, relativeX2, relativeX3);
	//printf("%d %d\n", argy, argy - 60);

	if ((-frog.w <= relativeX1 && relativeX1<(w + frog.w) && frog.y<argy && frog.y>(argy - 60)) ||
		(-frog.w <= relativeX2 && relativeX2<(w + frog.w) && frog.y<argy && frog.y>(argy - 60)) ||
		(-frog.w <= relativeX3 && relativeX3<(w + frog.w) && frog.y<argy && frog.y>(argy - 60)))
	{
		return true;
	}
	else
	{
		return false;
	}

	/*if ((-15<= relativeX1 && relativeX1<(100) && frog.y<argy && frog.y>(argy - 60)) || (-15<= relativeX2 && relativeX2<(100) && frog.y<argy && frog.y>(argy - 60)) || (-15 <= relativeX3 && relativeX3<(100) && frog.y<argy && frog.y>(argy - 60)))
	{
	return true;
	}
	else
	{
	return false;
	}*/
}


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
//void DrawLog(int cx, int cy, int width)

void Log::Draw(int y, int w)
{
	if (((x1 + w) >0)) {

		DrawLog(x1, y, h, w);
	}
	else {
		x1 = 800;
		DrawLog(x1, y, h, w);
	}
	if (((x2 + w) >0)) {
		DrawLog(x2, y, h, w);
	}
	else {
		x2 = 800;
		DrawLog(x2, y, h, w);
	}
	if (((x3 + w) >0)) {
		DrawLog(x3, y, h, w);
	}
	else {
		x3 = 800;
		DrawLog(x3, y, h, w);
	}

}

void Log::Move(int velocity)
{
	v = velocity;
	x1 = x1 - v;
	x2 = x2 - v;
	x3 = x3 - v;
}



bool Log::IsUnderFrog(Frog &frog, int argy, int w)
{
	int relativeX1, relativeX2, relativeX3;
	relativeX1 = (frog.x - x1);
	relativeX2 = (frog.x - x2);
	relativeX3 = (frog.x - x3);


	/*if ((-frog.w <= relativeX1 && relativeX1<(w + .5*frog.w) && frog.y<argy && frog.y>(argy - 60)) || (-frog.w <= relativeX2 && relativeX2<(w + .5*frog.w) && frog.y<argy && frog.y>(argy - 60)) || (-frog.w <= relativeX3 && relativeX3<(w + .5*frog.w) && frog.y<argy && frog.y>(argy - 60)))
	{
	return true;
	}
	else
	{
	return false;
	}*/

	////printf("@L %d %d %d\n", frog.x, frog.y, frog.w); //Debugging 
	//printf("%d %d\n", w,v);
	//printf("%d %d %d\n", x1, x2, x3);
	//printf("%d %d %d\n", relativeX1, relativeX2, relativeX3);
	//printf("%d %d\n", argy, argy - 60);

	if ((-frog.w <= relativeX1 && relativeX1<(w + frog.w) && frog.y<argy && frog.y>(argy - 60)) ||
		(-frog.w <= relativeX2 && relativeX2<(w + frog.w) && frog.y<argy && frog.y>(argy - 60)) ||
		(-frog.w <= relativeX3 && relativeX3<(w + frog.w) && frog.y<argy && frog.y>(argy - 60)))
	{
		return true;
	}
	else
	{
		return false;
	}
}




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
//void DrawLog(int cx, int cy, int width)

void Lilipad::Draw()
{
	DrawLilipad(x, y);

}

void Lilipad::IsUnderFrog(Frog &frog)
{
	//I make it such that if part of frog touches inner circle, then it is "on" the lilipad
	//if frog is not touching inner circle, then it is considered "off" the lilipad and thus dies :( 
	//int relativeX,relativeY; //local variable
	//relativeX= (frog.x - x);
	//relativeY = (frog.y - y);


	if ((abs(frog.x - x)) <= (frog.w + 15) && (abs(frog.y - y) <= (frog.h + 15)))
	{

		occupied = true;
		frog.ResetLocation();
		frog.score += 50;

		//return true; //returns "true" if called 
	}
	//else
	//{
	//	occupied = false; 
	//	//return false;
	//}
}
bool Lilipad::boolIsUnderFrog(Frog &frog) //return true if the frog has jumped onto current lilipad 
{
	if ((abs(frog.x - x)) <= (frog.w + 15) && (abs(frog.y - y) <= (frog.h + 15)))
	{
		return true;
	}
	else {
		return false;
	}

}

int Frog::PlayFrogger(void) //to play Frogger
{
	const int nLilipads = 4;
	Lilipad lili[nLilipads];
	Truck trucks;
	Car bluecars;
	Car redcars;
	Turtle lowturtles;
	Turtle highturtles;
	Log lowlog;
	Log highlog;
	Frog frog;



	for (int i = 0; i < nLilipads; i++)
	{
		switch (i)
		{
		case 0:
			/*int xcoor = (i + 1) * 130;*/
			lili[i].x = (i + 1) * 130;
			break;
		case 1:

			lili[i].x = 130 + i * 160;
			break;
		case 2:
			lili[i].x = 130 + i * 160;
			break;
		case 3:

			lili[i].x = 130 + i * 160;
			break;
		case 4:
			lili[i].x = 130 + i * 160;
			break;
		case 5:

			lili[i].x = 130 + i * 160;
			break;
		case 6:
			lili[i].x = 130 + i * 160;
			break;
		case 7:

			lili[i].x = 130 + i * 160;
			break;
		case 8:
			lili[i].x = 130 + i * 160;
			break;
		}
	}


	trucks.Initialize();
	srand(time(NULL));

	lowturtles.v = 5 + rand() % 8;
	//lowturtles.x1 = 200 + rand() % 600;
	int velocitylowlog = 3 + rand() % 6;
	int velocityhighlog = 5 + rand() % 8;
	int widthlowlog = 50 + rand() % 150;  //REPLACE WITH THIS AT THE END ********************************************************
	int widthhighlog = 50 + rand() % 100;
	int velocitybluecar = 5 + rand() % 17; //velocity in pixels per frame
	int velocityredcar = 5 + rand() % 17; //velocity in pixels per frame
	bluecars.x1 = 200 + rand() % 600;


	FsPollDevice();

	int time1 = time(NULL); //time at start


	while (frog.alive == true)
	{
		FsPollDevice();
		int key = FsInkey();

		switch (key)
		{

		case FSKEY_UP:
			frog.y -= 60;
			break;
		case FSKEY_DOWN:
			frog.y += 60;
			break;
		case FSKEY_LEFT:
			frog.x -= 30;
			break;
		case FSKEY_RIGHT:
			frog.x += 30;
			break;
		case FSKEY_ESC:
			frog.alive = false;
			break;
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //makes background black
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


		DrawScene();
		DrawRandomCurrents();
		redcars.Draw(520, 255, 0, 0);
		redcars.Move(velocityredcar);
		bluecars.Draw(400, 0, 0, 255);
		bluecars.Move(velocitybluecar);
		trucks.Draw();
		trucks.Move();
		highturtles.v = 10 + rand() % 5;
		highturtles.Draw(150);
		highturtles.Move();
		lowturtles.Draw(270);
		lowturtles.Move();

		//printf("Must match %d %d\n", lowlog.w, widthlowlog);

		lowlog.Draw(210, widthlowlog);
		lowlog.Move(velocitylowlog);
		highlog.Draw(90, widthhighlog);
		highlog.Move(velocityhighlog);
		//DrawFrog(400, 590);
		for (int j = 0; j < nLilipads; j++)
		{
			lili[j].Draw();
		}
		frog.Draw();
		//printf("&&\n");
		if (frog.y > 60 && frog.y < 120) {
			if (true == highlog.IsUnderFrog(frog, 120, widthhighlog)) {
				//printf("BPA\n");
				frog.x -= highlog.v;
			}
			else {
				//printf("BPB\n");
				frog.Dead(time1);
			}
		}
		if (frog.y > 180 && frog.y < 240) {
			if (true == lowlog.IsUnderFrog(frog, 240, widthlowlog)) {
				//printf("BPC\n");
				frog.x -= lowlog.v;
			}
			else if (false == lowlog.IsUnderFrog(frog, 240, widthlowlog)) {
				//printf("BPD\n");
				frog.Dead(time1);  //kills it
			}
		}


		if (frog.y > 240 && frog.y < 300) {
			if (true == lowturtles.IsUnderFrog(frog, 300)) {
				//printf("BPE\n");
				frog.x += lowturtles.v;
			}
			else if (false == lowturtles.IsUnderFrog(frog, 300)) { //changed
																   //printf("BPF\n");
				frog.Dead(time1);
			}
		}
		if (frog.y > 120 && frog.y < 180) {
			if (true == highturtles.IsUnderFrog(frog, 180)) {
				//printf("BPG\n"); //only print if condition is true
				frog.x += highturtles.v;
			}
			else {
				//printf("BPH\n");
				frog.Dead(time1);
			}
		}

		//Lilipad lili[nLilipads];

		bool lilipadoccupied; //bolean that says whether lilipad is occupied or not. 

		for (int i = 0; i < nLilipads; i++) //this loop checks if frog landed on already occupied lilypad 
		{
			if (lili[i].occupied == true) //before we reassign at "IsUnderFrog", we need to do this first. This extra line is critical
										  //the if statement makes sure we're only concerned with if it's close IF the lilipad is already occupied (otherwise we don't care if it's close)
			{
				if ((abs(frog.x - lili[i].x)) <= (frog.w + 15) && (abs(frog.y - lili[i].y) <= (frog.h + 15)))
				{
					lilipadoccupied = true;
					break;
				}
			}
		}
		bool missed[nLilipads];
		bool miss = false;
		bool sumbool = 0;
		for (int i = 0; i < nLilipads; i++)
		{
			missed[i] = lili[i].boolIsUnderFrog(frog);  //missed stores whether a lilipad is occupied or not
		}

		for (int i = 0; i < nLilipads; i++)
		{
			sumbool += missed[i];
		}

		if (frog.y <= 60 && sumbool == false) //Condition=all four lilipads are empty and y<=60
		{
			miss = true;
			//we need the condition to be IF ALL FOUR LILIPADS ARE EMPTY AND y<=60, THEN Stop program
			break;
		}

		for (int i = 0; i < nLilipads; i++) //this loop sees if lilipad is under frog, if so, then it makes it occupied, and calls frog.ResetLocation()
		{
			//don't need Classname in argument in main() (only needed when definining before main())...just input the object
			lili[i].IsUnderFrog(frog);
		}

		for (int i = 0; i < nLilipads; i++) //this loop draws the frog since we want a picture of frog to stay there to show it is occupied.
		{
			if (lili[i].occupied == true)
			{
				DrawFrog(lili[i].x, (lili[i].y + (.5*frog.h)));
				//lilipadoccupied = true; 
				//break; 
			}
		}

		bool occupiedarray[nLilipads];
		//bool alloccupied = true;
		int sumoccupied = 0;  //INTEGER OBVIOUSLY!!!!
		for (int i = 0; i < nLilipads; i++)
		{
			occupiedarray[i] = lili[i].occupied;
		}

		for (int i = 0; i < nLilipads; i++)
		{
			//printf(" %d \n ", occupiedarray[i]);
			sumoccupied += occupiedarray[i];
		}

		//printf(" %d %d %d %d ---- \n ", occupiedarray[0], occupiedarray[1], occupiedarray[2], occupiedarray[3]);


		if (sumoccupied == nLilipads)
		{
			frog.Winner(time1);
		}
		//printf("------------------------------- %d ---- \n", sumoccupied);

		//DrawPic(.3); 



		bool aa, aaa, aaaa;
		aaa = false, aaaa = true;
		if (frog.CheckAlive(trucks.IsHitByFrog(frog), bluecars.IsHitByFrog(frog, 420), redcars.IsHitByFrog(frog, 540), lilipadoccupied, miss) == false) {
			//printf("BPI\n");
			frog.Dead(time1);
		}

		glColor3ub(128, 128, 0);


		FsSwapBuffers();

		FsSleep(25);
	}



	//getchar(); //this caused it to not escape but was used for debugging 
	//Putting getchar() at end of program can be used for debugging because 
	//instead of it escaping as we programmed game to do, it keeps up the last picture so we can see very last frame. 
	unsigned long endtime = FsSubSecondTimer();
	while(FsSubSecondTimer() - endtime < 2000){
	}
	return frog.score; //return score 
	
}









