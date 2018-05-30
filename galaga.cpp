#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include <array>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "ysglfontdata.h"
#include <string>

const double PI=3.1415927;
const int height = 600;
const int width = 800;
const int scale = 2;
const int shipbit [] = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
				  0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
				  0,0,0,2,0,0,1,1,1,0,0,2,0,0,0,
				  0,0,0,2,0,0,1,1,1,0,0,2,0,0,0,
				  0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,
				  2,0,0,1,3,1,1,2,1,1,3,1,0,0,2,
				  2,0,0,3,1,1,2,2,2,1,1,3,0,0,2,
				  1,0,0,1,1,1,2,1,2,1,1,1,0,0,1,
				  1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,
				  1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,
				  1,1,1,0,2,2,1,1,1,2,2,0,1,1,1,
				  1,1,0,0,2,2,0,1,0,2,2,0,0,1,1,
				  1,0,0,0,0,0,0,1,0,0,0,0,0,0,1};

const int misslebit [] = {0,0,3,0,0,
						  0,0,3,0,0,
						  3,3,3,3,3,
						  3,3,1,3,3,
						  0,0,2,0,0,
						  0,0,2,0,0,
						  0,0,2,0,0,
						  0,0,2,0,0,
						  0,0,2,0,0};

const int emisslebit[] = {0,0,1,0,0,
						  0,0,1,0,0,
						  0,0,1,0,0,
						  0,0,1,0,0,
						  0,0,1,0,0,
						  2,2,0,2,2,
						  2,2,2,2,2,
						  0,0,2,0,0,
						  0,0,2,0,0};

const int flybit [] = {0,3,3,0,0,0,4,0,0,0,3,3,0,
					  0,0,3,3,4,2,4,2,4,3,3,0,0,
					  0,0,0,3,2,2,4,2,2,3,0,0,0,
					  0,0,0,0,4,4,4,4,4,0,0,0,0,
					  0,0,3,3,3,2,2,2,3,3,3,0,0,
					  0,3,3,3,0,2,2,2,0,3,3,3,0,
					  3,3,3,3,0,4,4,4,0,3,3,3,3,
					  3,3,3,3,0,2,2,2,0,3,3,3,3,
					  3,3,3,0,0,0,2,0,0,0,3,3,3};

const int edata [] = {0,13,9,1,13,10,2,14,15};

void DrawRect(int xval, int yval, int xval1, int yval1){
	glVertex2d(xval, yval);
	glVertex2d(xval1, yval);
	glVertex2d(xval1, yval1);
	glVertex2d(xval, yval1);
}
void DrawShape(int shipHeight, int shipWidth, const int bitmap [], int startx, int starty){
	for(int i = 0; i < shipHeight; i++){
		for (int j = 0; j < shipWidth; j++){
			glBegin(GL_QUADS);
			int x1 = startx + j*scale;
			int x2 = startx + (j+1)*scale;
			int y1 = height - starty + i*scale;
			int y2 = height - starty + (i+1)*scale;
			if(bitmap[i*shipWidth + j] == 1){
				glColor3f(1, 1, 1);
				DrawRect(x1, y1, x2, y2);
			}
			else if(bitmap[i*shipWidth + j] == 2){
				glColor3f(1, 0, 0);
				DrawRect(x1, y1, x2, y2);
			}
			else if(bitmap[i*shipWidth + j] == 3){
				glColor3f(0, 0, 1);
				DrawRect(x1, y1, x2, y2);
			}
			else if(bitmap[i*shipWidth + j] == 4){
				glColor3f(1, 1, 0);
				DrawRect(x1, y1, x2, y2);
			}
			
		}
	}
}


class Shooter{
public:
	int x = 400;
	int y = 60;
	void Draw();
	void Move(int direction);
	int mode = 1;
		
};

void Shooter::Draw(){
	DrawShape(16,15,shipbit,x,y);
	if(mode == 2 || mode == 3){
		DrawShape(16,15,shipbit,x+15*scale,y);
	}
	if(mode == 3){
		DrawShape(16,15,shipbit,x+15*2*scale,y);
	}
	glEnd();
}
void Shooter::Move(int direction){
	if(direction == 1){
		x = x - 10;
	}
	else if(direction == 2){
		x = x + 10;
	}
	if(x <0){
		x = 0;
	}
	if(x >785){
		x = 784;
	}
}
void Bezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, double u, double &x, double &y){
	double u2 = u*u;
	double u3 = u*u*u;	
	double valx1 = (-1*u3 + 3*u2 + -3*u + 1)*((int)x1);
	double valx2 = (3*u3 + -6*u2 + 3*u)*((int)x2);
	double valx3 = (-3*u3 + 3*u2)*((int)x3);
	double valx4 = (u3)*((int)x4);
	double valy1 = (-1*u3 + 3*u2 + -3*u + 1)*((int)y1);
	double valy2 = (3*u3 + -6*u2 + 3*u)*((int)y2);
	double valy3 = (-3*u3 + 3*u2)*((int)y3);
	double valy4 = (u3)*((int)y4);
	double valx = valx1 + valx2 + valx3 + valx4;
	double valy = valy1 + valy2 + valy3 + valy4;
	
	x = valx;
	y = valy;
}

class Enemy{
public:
	Enemy(int inputx, int inputym, int thetype, YsRawPngDecoder * pointer);
	double x;
	double y;
	double ew;
	double eh;
	double u = 0;
	void Draw();
	void Move(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	void init(int state1, double rando1);
	int type = 1;
	YsRawPngDecoder * epointer;
	int state;
	double rando;
		
};

/**
[-1 3 -3 1
  3 -6 3 0 
 -3 3 0 0 
  1 0 0 0 ]
*/

void drawPng(int wid, int hei, int startx, int starty, unsigned char * inputmap){
	for(int i = 0; i < hei; i++){
		for (int j = 0; j < wid; j++){
			glBegin(GL_QUADS);
			int x1 = startx + j*scale;
			int x2 = startx + (j+1)*scale;
			int y1 = height - starty + i*scale;
			int y2 = height - starty + (i+1)*scale;
			glColor3ub(inputmap[i*4*wid + j*4], inputmap[i*4*wid + j*4 + 1], inputmap[i*4*wid + j*4 + 2]);
			if(inputmap[i*4*wid + j*4] == 0 && inputmap[i*4*wid + j*4 + 1] == 0 && inputmap[i*4*wid + j*4 + 2] == 0){

			}
			else{
			DrawRect(x1, y1, x2, y2);
		}
			
		}
	}
}



Enemy::Enemy(int inputx, int inputy, int thetype, YsRawPngDecoder * pointer){
	x = inputx, y = inputy;
	type = thetype;
	ew = edata[type*3 + 1];
	eh = edata[type*3 + 1];
	epointer = pointer;
}

void Enemy::init(int state1, double rando1){
	state = state1;
	rando = rando1;
}

void Enemy::Move(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
	Bezier(x1,y1,x2,y2,x3,y3,x4,y4,u, x, y);

}
void Enemy::Draw(){	
	//glRasterPos2d(x,height - y);
	//glDrawPixels(epointer->wid,epointer->hei,GL_RGBA,GL_UNSIGNED_BYTE,epointer->rgba);
	//DrawShape(9,13,flybit,x,y);
	drawPng(epointer->wid,epointer->hei,x,y,epointer->rgba);
	glEnd();
}

class eMissle{
public:
	eMissle(int inputx, int inputy, double invx, double invy);
	void Draw();
	int Move();
	int collide(Shooter aship);
	int x;
	int y;
	int vx;
	int vy;
	
};

eMissle::eMissle(int inputx, int inputy, double invx, double invy){
	x = inputx;
	y = inputy;
	vx = invx;
	vy = invy;
	
}

int eMissle::collide(Shooter aship){
	if(x < aship.x + 15 && x + 5 > aship.x){
			if(y > aship.y - 16 && y < aship.y){
        		return true;
			}
	}
	return false;
}

int eMissle::Move(){
	if(x > 800 || x < 0 || y > 600 || y < 0){
		return 1;
	}
	else{
		x = x + vx;
		y = y + vy;
	}
	return 0;
}

void eMissle::Draw(){
	DrawShape(9,5,emisslebit,x,y);
	glEnd();

}


class Missle{
public:
	Missle(int inputx, int inputy);
	void Draw();
	int Move();
	int x;
	int y;
};

Missle::Missle(int inputx, int inputy){
	x = inputx, y = inputy;
}

int Missle::Move(){
	if(x > 800 || x < 0 || y > 600){
		return 1;
	}
	else{
		y = y + 30;
	}
	return 0;
}

void Missle::Draw(){
	DrawShape(9,5,misslebit,x,y);
	glEnd();
}


bool checkCollision(int &tempx, int &tempy,std::vector<Enemy> &es, Missle ms){
	
	for(int i = 0; i < es.size(); i++){
		
		if(ms.x < es[i].x + es[i].ew && ms.x + 5 > es[i].x){
			if(ms.y > es[i].y - es[i].eh && ms.y < es[i].y+es[i].eh*2){
				if(es[i].type == 1){
				}
				tempx = es[i].x;
				tempy = es[i].y;
				
				es.erase(es.begin()+i);
        		i--;
        		return true;
			}
		}
	}
	return false;
	
}

class Explosion{
public:
	int x,y;
	Explosion(int tx, int ty, YsRawPngDecoder * pointer);
	int timer = 0;
	void Explode(YsRawPngDecoder * pointer);
	YsRawPngDecoder * epointer;
};

Explosion::Explosion(int tx, int ty ,YsRawPngDecoder * pointer){
	x = tx;
	y = ty;
	epointer = pointer;
}

void Explosion::Explode(YsRawPngDecoder * pointer){
	drawPng(epointer->wid,epointer->hei,x-(epointer->wid)*scale/2,y + (epointer->hei)*scale/2,epointer->rgba);
	timer++;
	epointer = pointer;
}


class Galaga{
public:
	int play(void);
};

int Galaga::play(){
	int score = 0;
	srand(time(NULL));
	const int numPics = 9;
	YsRawPngDecoder png[numPics];

	png[0].Decode("GalagaSprite/Explosion1.png");
	png[1].Decode("GalagaSprite/Explosion2.png");
	png[2].Decode("GalagaSprite/Explosion3.png");
	png[3].Decode("GalagaSprite/Explosion4.png");
	png[4].Decode("GalagaSprite/Explosion5.png");
	png[5].Decode("GalagaSprite/Enemy0.png");
	png[6].Decode("GalagaSprite/Enemy1.png");
	png[7].Decode("GalagaSprite/Enemy3.png");
	png[8].Decode("GalagaSprite/GalagaScreen.png");
	png[8].Flip();

	int terminate=0;
    Shooter ship;
	std::vector<Missle> missles;
	std::vector<Enemy> enemies;
	std::vector<Explosion> booms;
	std::vector<eMissle> emissles;

    //FsOpenWindow(16,16,width,height,1);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    FsSwapBuffers();
	FsPassedTime();
	
	int exit = 0;
	int help = 0;
	for(;;) {
	   	FsPollDevice();
    	auto key=FsInkey();
        int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glRasterPos2d(0.0,(double)(winHei-1));
        glDrawPixels(png[8].wid,png[8].hei,GL_RGBA,GL_UNSIGNED_BYTE,png[8].rgba);
        FsSwapBuffers();
        FsSleep(100);
        if(FSKEY_ESC == key) {
		          break;
        }	
        if(FSKEY_ENTER == key) {
		          break;
        }
    }

	long long mTimer = FsSubSecondTimer();
	long long newTimer = FsSubSecondTimer();
	long long eTimer = FsSubSecondTimer();
	long long eTimer2 = FsSubSecondTimer();
	long long eTimer3 = FsSubSecondTimer();
    while(0==terminate)
    {
        FsPollDevice();
        double dt=(double)FsPassedTime()/1000.0;

        int key=FsInkey();
        	switch(key)
        	{
        	case FSKEY_ESC:
            	terminate=1;
            	break;
        	}
			if(0!=FsGetKeyState(FSKEY_W))
			{
				
			}

			if (0 != FsGetKeyState(FSKEY_S))
			{
			}
			if(0!=FsGetKeyState(FSKEY_LEFT))
			{
				ship.Move(1); 
				
			}
			if(0!=FsGetKeyState(FSKEY_RIGHT))
			{
				ship.Move(2);
			}
			if(0!= FsGetKeyState(FSKEY_P)){
				help = 1;
				
			}

			if (0 != FsGetKeyState(FSKEY_SPACE))
			{	if(FsSubSecondTimer() - mTimer> 100){
					missles.push_back( Missle(ship.x + 5*scale, ship.y));
					if(ship.mode == 2){
						missles.push_back(Missle(ship.x + 5*scale + 15*scale, ship.y));
					}
					if(ship.mode == 3){
						missles.push_back(Missle(ship.x + 5*scale + 15*scale, ship.y));
						missles.push_back(Missle(ship.x + 5*scale + 15*scale*2, ship.y));
					}
					mTimer = FsSubSecondTimer();
			    }
			}
		if(FsSubSecondTimer() - newTimer > 0){
			if(FsSubSecondTimer() - eTimer > 1000){
				int t1 = rand() % 25;
				double t2 = double((rand()%100)) /100;
				enemies.push_back(Enemy(800,300,0,&png[5]));
				(enemies.back()).init(t1,t2);
				eTimer = FsSubSecondTimer();
			}
		}
		if(FsSubSecondTimer() - newTimer > 1500){
			if(FsSubSecondTimer() - eTimer2 > 500){
				int t1 = rand() % 25;
				double t2 = double((rand()%100)) /100;
				enemies.push_back(Enemy(0,300,1,&png[6]));
				(enemies.back()).init(t1,t2);
				eTimer2 = FsSubSecondTimer();
			}
		}
		if(FsSubSecondTimer() - newTimer > 3000){
			if(FsSubSecondTimer() - eTimer3 > 400){
				int t1 = rand() % 25;
				double t2 = double((rand()%100)) /100;
				enemies.push_back(Enemy(0,600,2,&png[7]));
				(enemies.back()).init(t1,t2);
				eTimer3 = FsSubSecondTimer();
			}
		}

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        for (int i =0; i < booms.size();i++){
        	booms[i].Explode(&png[(int)(booms[i].timer/8)]);
        	if(booms[i].timer > 39){
        		booms.erase(booms.begin() + i);
        		i--;
        	}
        }
        int j = missles.size();
        for(int i = 0; i < j; i++){
      		if(missles[i].Move()){
      			missles.erase(missles.begin() + i);
      			i--;
      		}
      		else{
        		missles[i].Draw();
       		}
        	j = missles.size();
        }
        int z = enemies.size();
        for(int i =0; i < z; i++){
        	if(enemies[i].u > 1){
        		enemies.erase(enemies.begin()+i);
        		i--;
        	}
        	else{
        		if(enemies[i].type == 0){
        			enemies[i].Move(800,300,600,300,600,600,800,600);
        		}
        		else if (enemies[i].type == 1){
        			enemies[i].Move(0,300,400,400,500,500,800,600);
        		}
        		else if (enemies[i].type == 2){
        			enemies[i].Move(0,600,500,200,600,500,300,600);
        		}


        		enemies[i].u = enemies[i].u + .01;
        		
        		if(enemies[i].state > 0){
        			if(enemies[i].rando < enemies[i].u){
        				double tempvx = -1*enemies[i].x + ship.x;
        				double tempvy = -1*enemies[i].y + ship.y;
        				double another = sqrt(tempvx*tempvx + tempvy*tempvy);
        				double speed = FsSubSecondTimer() - newTimer;
        				speed = sqrt(speed)/20;
        				if(speed<5){
        					speed = 5;
        				}
        				tempvx = speed*tempvx/another;
        				tempvy = speed*tempvy/another;
        				enemies[i].state = 0;
        				emissles.push_back(eMissle(enemies[i].x,enemies[i].y,tempvx,tempvy));
        			}
        		}
        		enemies[i].Draw();
        	}
        	z = enemies.size();
        }
        for (int i = 0; i< missles.size(); i++){
        	int tempx;
        	int tempy;
        	if(checkCollision(tempx,tempy,enemies,missles[i])){
        		missles.erase(missles.begin() + i);
        		score = score + 10;
        		i--;
        		booms.push_back(Explosion(tempx,tempy,&png[0]));
        	}
        }
        for (int i = 0; i<emissles.size(); i++){
        	if(emissles[i].collide(ship)){
        		exit = 1;
        	}
        	else{
        		emissles[i].Draw();
        		if(emissles[i].Move()){
        			emissles.erase(emissles.begin() +i);
        			i--;
        		}
        		
        	}
        }
        glRasterPos2d(720,50);
        glColor3ub(255,0,0);
        std::string score1 = std::to_string(score);
        char * ttt = new char[score1.length()+1];
        std::strcpy(ttt,score1.c_str());
        YsGlDrawFontBitmap20x32(ttt);
        delete[] ttt;
        ship.Draw();
        FsSwapBuffers();
        FsSleep(10);
        if(exit == 1){
        	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        	glRasterPos2d(180,300);
        	glColor3ub(255,0,0);
        	std::string score1 = "You lose. Final Score: " + std::to_string(score);
        	char * ttt = new char[score1.length()+1];
        	std::strcpy(ttt,score1.c_str());
        	YsGlDrawFontBitmap20x32(ttt);
        	delete[] ttt;
        	FsSwapBuffers();
        	newTimer = FsSubSecondTimer();
        	while(FsSubSecondTimer() - newTimer < 2000){

        	}
        	break;
        }
        if(help == 1){
        	
			for(;;) {
	        	FsPollDevice();
        		auto key=FsInkey();
        		int winWid,winHei;
        		FsGetWindowSize(winWid,winHei);
        		glRasterPos2d(0.0,(double)(winHei-1));
        		glDrawPixels(png[8].wid,png[8].hei,GL_RGBA,GL_UNSIGNED_BYTE,png[8].rgba);
        		FsSwapBuffers();
        		FsSleep(100);
        		if(FSKEY_ESC == key) {
        			help = 0;
		            break;
        		}	
        		if(FSKEY_ENTER == key) {
        			help = 0;
		            break;
        		}
    		}
        }
    }
	return score;
}

/*
void main(){
	FsOpenWindow(16,16,800,600,1);
	Galaga game;
	game.play();
}
*/



