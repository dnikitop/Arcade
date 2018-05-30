#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "galaga.h"
#include "Asteroids.h"
#include "centipede.h"
#include "Tetris.hpp"
#include "Tron.h"
#include "yspng.h"
#include "pacman.h"
#include <ctype.h>
#include "FroggerFinalVersionDone.h"
#include "ysglfontdata.h"
#include "ysglmaketextbitmap.h"
#include <string>


const double YsPi=3.1415927;
GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[4] = { .4f, 0.0f, 0.0f, .1f };
GLfloat mat_ambient2[4] = { 1.0f, 1.0f, 1.0f, .1f };
GLfloat mat_ambient_color[4] = { 0.8f, 0.8f, 0.2f, .3f };
GLfloat mat_diffuse[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat no_shininess[1] = { 0.0f };
GLfloat low_shininess[1] = { 5.0f };
GLfloat high_shininess[1] = { 100.0f };
GLfloat mat_emission[4] = {0.3f, 0.2f, 0.2f, 0.0f};


GLfloat cubemat_ambient[4] = { 0.0f, 0.0f, .40f, 1.0f };
GLfloat cubemat_diffuse[4] = { 0.0f, 0.0f, .40f, 1.0f };
GLfloat cubemat_specular[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat cubemat_emission[4] = {0.0f, .0f, 0.0f, .2f};

GLfloat supmat_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat supmat_diffuse[4] = { 0.0f, 0.0f, .00f, 1.0f };
GLfloat supmat_specular[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat supmat_emission[4] =  {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat gridmat_ambient[4] = { .0f, .2f, 0.8f, .3f };
GLfloat gridmat_diffuse[4] = { .0f, 0.2f, 0.8f, 1.0f };
GLfloat gridmat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat gridmat_emission[4] = {0.0f, 1.0f, 1.0f, .5f};

GLfloat linemat_ambient[4] = { .0f, .2f, 0.8f, .3f };
GLfloat linemat_diffuse[4] = { .0f, 0.2f, 0.8f, 1.0f };
GLfloat linemat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat linemat_emission[4] = {1.0f, 0.0f, .7f, .5f};

GLfloat wallmat_ambient[4] = { 0.1f, 0.0f, 0.1f, 1.0f };
GLfloat wallmat_diffuse[4] = { 0.1f, 0.0f, 0.1f, 1.0f };
GLfloat wallmat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat wallmat_emission[4] = {0.0f, 0.0f, 0.0f, .5f};

GLfloat scoremat_ambient[4] = { 0.0f,0.0f, 0.0f, 1.0f };
GLfloat scoremat_diffuse[4] = { .0f, 0.0f, 0.0f, 1.0f };
GLfloat scoremat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat scoremat_emission[4] = {00.0f, 0.0f, 0.0f, .5f};

GLfloat textmat_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat textmat_diffuse[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat textmat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat textmat_emission[4] = {0.0f, 0.0f, 0.0f, .5f};

GLfloat floormat_ambient[4] = { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat floormat_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat floormat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat floormat_emission[4] = {0.0f, 0.0f, 0.0f, 1.0f};


GLfloat light_positionglobal[] = {0.0f, 5.0f, 0.0f,1.0f};
GLfloat light_ambient[] = { .1f, .1f, .1f, 1.0f};
GLfloat light_diffuse[] = { .5f, 0.5f, 0.5f, 1.0f};
GLfloat light_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat light_direction[] = { 0.0f, -1.0f, 0.0f};
GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };

double dropoff = .0007;
double pushin = 1.05;
double pushup = 3.1;
const int stations = 7;

int roomx = 30;
int roomz = 45;
int roomy = 20;
const int numLights = 5;
const int scoreSize = 12000;
unsigned char asteroidsScore [scoreSize];
unsigned char centipedeScore [scoreSize];
unsigned char froggerScore [scoreSize];
unsigned char galagaScore [scoreSize];
unsigned char pacmanScore [scoreSize];
unsigned char tetrisScore [scoreSize];
unsigned char tronScore [scoreSize];

int scores [] = {0,0,0,0,0,0,0};


void makeAsteroidScore(int score, GLuint texts []){
	for (int i = 3; i < scoreSize; i++){
		asteroidsScore[i] = 0;
	}
	std::string score1 = std::to_string(score);
    char * input = new char[score1.length()+1];
    std::strcpy(input,score1.c_str());
	YsGlWriteStringToRGBA8Bitmap(input,1,255,0,255, asteroidsScore, 100,30,0,0,YsFont8x12,8,12);
	delete[] input;
	glGenTextures(1, &texts[3]);
	glBindTexture(GL_TEXTURE_2D, texts[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			100,        30,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE	,  // Source component type
			asteroidsScore);
}
void makeCentipedeScore(int score, GLuint texts []){
	for (int i = 3; i < scoreSize; i++){
		centipedeScore[i] = 0;
	}
	std::string score1 = std::to_string(score);
    char * input = new char[score1.length()+1];
    std::strcpy(input,score1.c_str());
	YsGlWriteStringToRGBA8Bitmap(input,1,255,0,255, centipedeScore, 100,30,0,0,YsFont8x12,8,12);
	delete[] input;
	glGenTextures(1,&texts[4]);
	glBindTexture(GL_TEXTURE_2D, texts[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			100,        30,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE	,  // Source component type
			centipedeScore);
}
void makeFroggerScore(int score, GLuint texts []){
	for (int i = 3; i < scoreSize; i++){
		froggerScore[i] = 0;
	}
	std::string score1 = std::to_string(score);
    char * input = new char[score1.length()+1];
    std::strcpy(input,score1.c_str());
	YsGlWriteStringToRGBA8Bitmap(input,1,255,0,255, froggerScore, 100,30,0,0,YsFont8x12,8,12);
	delete[] input;
	glGenTextures(1,&texts[5]);
	glBindTexture(GL_TEXTURE_2D, texts[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			100,        30,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE	,  // Source component type
			froggerScore);
}
void makeGalagaScore(int score, GLuint texts []){
	for (int i = 3; i < scoreSize; i++){
		galagaScore[i] = 0;
	}
	std::string score1 = std::to_string(score);
    char * input = new char[score1.length()+1];
    std::strcpy(input,score1.c_str());
	YsGlWriteStringToRGBA8Bitmap(input,1,255,0,255, galagaScore, 100,30,0,0,YsFont8x12,8,12);
	delete[] input;
	glGenTextures(1,&texts[6]);
	glBindTexture(GL_TEXTURE_2D, texts[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			100,        30,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE	,  // Source component type
			galagaScore);

}
void makePacmanScore(int score, GLuint texts []){
	for (int i = 3; i < scoreSize; i++){
		pacmanScore[i] = 0;
	}
	std::string score1 = std::to_string(score);
    char * input = new char[score1.length()+1];
    std::strcpy(input,score1.c_str());
	YsGlWriteStringToRGBA8Bitmap(input,1,255,0,255, pacmanScore, 100,30,0,0,YsFont8x12,8,12);
	delete[] input;
	glGenTextures(1,&texts[7]);
	glBindTexture(GL_TEXTURE_2D, texts[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			100,        30,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE	,  // Source component type
			pacmanScore);
}
void makeTetrisScore(int score, GLuint texts []){
	for (int i = 3; i < scoreSize; i++){
		tetrisScore[i] = 0;
	}
	std::string score1 = std::to_string(score);
    char * input = new char[score1.length()+1];
    std::strcpy(input,score1.c_str());
	YsGlWriteStringToRGBA8Bitmap(input,1,255,0,255, tetrisScore, 100,30,0,0,YsFont8x12,8,12);
	delete[] input;
	glGenTextures(1,&texts[8]);
	glBindTexture(GL_TEXTURE_2D, texts[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			100,        30,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE	,  // Source component type
			tetrisScore);
}
void makeTronScore(int score, GLuint texts []){
	for (int i = 3; i < scoreSize; i++){
		tronScore[i] = 0;
	}
	std::string score1 = std::to_string(score);
    char * input = new char[score1.length()+1];
    std::strcpy(input,score1.c_str());
	YsGlWriteStringToRGBA8Bitmap(input,1,255,0,255, tronScore, 100,30,0,0,YsFont8x12,8,12);
	delete[] input;
	glGenTextures(1,&texts[9]);
	glBindTexture(GL_TEXTURE_2D, texts[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			100,        30,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE	,  // Source component type
			tronScore);
}

void returnNormal(double temp3 [], double point1 [], double point2 [], double point3 []){
	double temp1[3];
	double temp2[3];
	for (int i = 0; i < 3; i++){
		temp1[i] = point2[i] - point1[i];
		temp2[i] = point3[i] - point1[i];
	}

	temp3[0] = temp1[1]*temp2[2] - temp1[2]*temp2[1];
	temp3[1] = temp1[2]*temp2[0] - temp1[0]*temp2[2];
	temp3[2] = temp1[0]*temp2[1] - temp1[1]*temp2[0];
}

class Walls{
public:
	double frontleftbot[3];
	double frontrightbot[3];	
	double frontlefttop[3];
	double frontrighttop[3];
	double backleftbot[3];
	double backrightbot[3];
	double backlefttop[3];
	double backrighttop[3];

	void Init();
	void DrawWalls(GLuint texts[]);
};

void Walls::Init(){
	double roomx1 = (double)roomx;
	double roomy1 = (double)roomy;
	double roomz1 = (double)roomz;
	double temp0 [] = {-1*roomx1,0,-1*roomz1};
	double temp1 [] = {-1*roomx1,0,1*roomz1};
	double temp2 [] = {-1*roomx1,roomy1,-1*roomz1};
	double temp3 [] = {-1*roomx1,roomy1, 1*roomz1};
	double temp4 [] = {1*roomx1,0,-1*roomz1};
	double temp5 [] = {1*roomx1,0,1*roomz1};
	double temp6 [] = {1*roomx1,roomy1,-1*roomz1};
	double temp7 [] = {1*roomx1,roomy1,1*roomz1};
	for(int i =0; i<3;i++){
		frontleftbot[i] = temp0[i];
		frontrightbot[i] = temp1[i];
		frontlefttop[i] = temp2[i];
		frontrighttop[i] = temp3[i];
		backleftbot[i] = temp4[i];
		backrightbot[i] = temp5[i];
		backlefttop[i] = temp6[i];
		backrighttop[i] = temp7[i];

	}
}

void Walls::DrawWalls(GLuint texts []){
	glMaterialfv(GL_FRONT, GL_AMBIENT, wallmat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wallmat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wallmat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, wallmat_emission);
	//left
	double temp [3];

	glBegin(GL_QUADS);
	returnNormal(temp, frontrightbot,frontleftbot,frontlefttop);
	glNormal3dv(temp);
	glVertex3dv(frontrightbot);
	glVertex3dv(frontleftbot);
	glVertex3dv(frontlefttop);
	glVertex3dv(frontrighttop);
	glEnd();

	glBegin(GL_QUADS);
	returnNormal(temp, frontleftbot,backleftbot,backlefttop);
	glNormal3dv(temp);
	glVertex3dv(frontleftbot);
	glVertex3dv(backleftbot);
	glVertex3dv(backlefttop);
	glVertex3dv(frontlefttop);
	glEnd();

	glBegin(GL_QUADS);
	returnNormal(temp, frontrightbot,frontrighttop,backrighttop);
	glNormal3dv(temp);
	glVertex3dv(frontrightbot);
	glVertex3dv(frontrighttop);
	glVertex3dv(backrighttop);
	glVertex3dv(backrightbot);
	glEnd();

	glBegin(GL_QUADS);
	returnNormal(temp, backlefttop,backleftbot,backrightbot);
	glNormal3dv(temp);
	glVertex3dv(backlefttop);
	glVertex3dv(backleftbot);
	glVertex3dv(backrightbot);
	glVertex3dv(backrighttop);
	glEnd();

	glBegin(GL_QUADS);
	returnNormal(temp, backlefttop,backrighttop,frontrighttop);
	glNormal3dv(temp);
	glVertex3dv(backlefttop);
	glVertex3dv(backrighttop);
	glVertex3dv(frontrighttop);
	glVertex3dv(frontlefttop);
	glEnd();

	glMaterialfv(GL_FRONT, GL_AMBIENT, linemat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, linemat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, linemat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, linemat_emission);
    for (int i = 0; i < 5; i++){
		glBegin(GL_LINES);
		glVertex3d(-roomx,3+3*i,-roomz);
		glVertex3d(roomx,3+3*i,-roomz);
		glVertex3d(roomx,3+3*i,-roomz);	
		glVertex3d(roomx,3+3*i,roomz);
		glVertex3d(roomx,3+3*i,roomz);
		glVertex3d(-roomx,3+3*i,roomz);
		glVertex3d(-roomx,3+3*i,roomz);
		glVertex3d(-roomx,3+3*i,-roomz);
		glEnd();
}


}

class HighScore{
public:
	double scores [7];

	void changeScore(int game, int score);
	void DrawScores(GLuint texts [], int textnumber);
	void Init();
};

void HighScore::Init(){
	for (int i = 0; i < 7; i++){
		scores[i] = 0;
	}
}

void HighScore::DrawScores(GLuint texts [], int textnumber){
	glMaterialfv(GL_FRONT, GL_AMBIENT, scoremat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, scoremat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, scoremat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, scoremat_emission);
	glColor4d(1.0,1.0,1.0,1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, supmat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, supmat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, supmat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, supmat_emission);

	glBindTexture(GL_TEXTURE_2D,texts[textnumber]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glNormal3d(-1,0,0);
	glTexCoord2d(0.0,1.0);
	glVertex3f(roomx-.1,0,-5);
	glTexCoord2d(1.0,1.0);
	glVertex3f(roomx-.1,0,2.5);
	glTexCoord2d(1.0,0.0);
	glVertex3f(roomx-.1,15,2.5);
	glTexCoord2d(0.0,0.0);
	glVertex3f(roomx-.1,15,-5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT, GL_AMBIENT, scoremat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, scoremat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, scoremat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, scoremat_emission);
	glColor3ub(0,0,0);
   	glBegin(GL_QUADS);
   	glNormal3d(-1,0,0);
	glVertex3f(roomx-.1,0,2.5);
	glVertex3f(roomx-.1,0,5);
	glVertex3f(roomx-.1,15,5);
	glVertex3f(roomx-.1,15,2.5);
	glEnd();
	glMaterialfv(GL_FRONT, GL_AMBIENT, supmat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, supmat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, supmat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, supmat_emission);
	glColor4d(1.0,1.0,1.0,1.0);
   	for(int i = 0; i < 7; i ++){
		glBindTexture(GL_TEXTURE_2D,texts[textnumber+2+(6-i)]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glNormal3d(-1,0,0);
		glTexCoord2d(0.0,0.0);
		glVertex3f(roomx-.2,1.1 + ((double)i)*1.8,2.5);
		glTexCoord2d(1.0,0.0);
		glVertex3f(roomx-.2,1.1 + ((double)i)*1.8,8);
		glTexCoord2d(1.0,1.0);
		glVertex3f(roomx-.2,2.5 + ((double)i)*1.8,8);
		glTexCoord2d(0.0,1.0);
		glVertex3f(roomx-.2,2.5 + ((double)i)*1.8,2.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}



class Cube
{
public:
	double centerx, centerz, width, length, height,colorr, colorg, colorb, rotation;
	double backbotleft[3];
	double backbotright[3];
	double frontbotleft[3];
	double frontbotright[3];
	double backtopleft[3];
	double backtopright[3];
	double fronttopleft[3];
	double fronttopright[3];

	double backtallleft[3];
	double backtallright[3];
	double fronttallleft[3];
	double fronttallright[3];
	double pastunderleft[3];
	double pastunderright[3];
	double frontunderleft[3];
	double frontunderright[3];
	double midtopleft[3];
	double midtopright[3];
	double temp0[3];
	double normx = 0;
	double normz = 0;

	double screentopleft[3];
	double screentopright[3];
	double screenbotleft[3];
	double screenbotright[3];
	int textnum = 1;
	int mode;
	double bot = 0;
    

	void Init(double centerx1, double centerz1, double length1, double width1, double height1, double colorr1, double colorg1, double colorb1,double rotation1,int mode1);
	void DrawCube(int mode1, GLuint texts []);
	double rotatex(double x, double y, double z);
	double rotatez(double x, double y, double z);
};

void Cube::Init(double centerx1, double centerz1, double length1, double width1, double height1, double colorr1, double colorg1, double colorb1,double rotation1,int mode1){
	centerx = centerx1;
	centerz = centerz1;
	length = length1;
	width = width1;
	height = height1;
	colorr = colorr1;
	colorg = colorg1;
	colorb = colorb1;
	rotation = rotation1;
	mode = mode1;
	normx = cos(rotation);
	normz = sin(rotation);
	double front = -1*length / 2;
	double back = 1*length / 2;
	double top = height;
	double left = -1*width/2;
	double right = 1*width/2;
	double tall = height*2.25;
	double under = height*2;
	double past = length/4;
	double mid = 0;
	/*double screenleft = -1*width/2.5;
	double screenright = 1*width/2.5;
	double screenback = .19776*length;
	double screenfront = .05242*length;
	double screentop = .79104*height+height;
	double screenbot = .20896*height+height;
	*/
	double screenleft = -1*width/2.5;
	double screenright = 1*width/2.5;
	double screenback = .18776*length;
	double screenfront = .04242*length;
	double screentop = .80104*height+height;
	double screenbot = .21896*height+height;
	double temp00 [] = {centerx + rotatex(front + pushin, top, mid), top, centerz + rotatez(front + pushin, top, mid)};
	double temp1 [] = {centerx + rotatex(back, bot, left), bot, centerz + rotatez(back, bot, left)};
	double temp2 [] = {centerx + rotatex(back, bot, right), bot, centerz + rotatez(back, bot, right)};
	double temp3 [] = {centerx + rotatex(front, bot, left), bot, centerz + rotatez(front, bot, left)};
	double temp4 [] = {centerx + rotatex(front, bot, right), bot, centerz + rotatez(front, bot, right)};
	double temp5 [] = {centerx + rotatex(back, top, left), top , centerz + rotatez(back, top, left)};
	double temp6 [] = {centerx + rotatex(back, top, right), top ,centerz + rotatez(back, top, right)};
	double temp7 [] = {centerx + rotatex(front, top, left), top , centerz + rotatez(front, top, left)};
	double temp8 [] = {centerx + rotatex(front, top, right), top , centerz + rotatez(front, top, right)};


	double temp9 [] = {centerx + rotatex(back, tall, left), tall, centerz + rotatez(back, tall, left)};	
	double temp10 [] = {centerx + rotatex(back, tall, right), tall, centerz + rotatez(back, tall, right)};
	double temp11 [] = {centerx + rotatex(front, tall, left), tall, centerz + rotatez(front, tall, left)};
	double temp12 [] = {centerx + rotatex(front, tall, right), tall, centerz + rotatez(front, tall, right)};
	double temp13 [] = {centerx + rotatex(past, under, left), under, centerz + rotatez(past, under, left)};
	double temp14 [] = {centerx + rotatex(past, under, right), under, centerz + rotatez(past, under, right)};
	double temp15 [] = {centerx + rotatex(front, under, left), under, centerz + rotatez(front, under, left)};
	double temp16 [] = {centerx + rotatex(front, under, right), under, centerz + rotatez(front, under, right)};

	double temp17 [] = {centerx + rotatex(mid, top, left), top, centerz + rotatez(mid, top, left)};
	double temp18 [] = {centerx + rotatex(mid, top, right), top, centerz + rotatez(mid, top, right)};

	double temp19 [] = {centerx + rotatex(screenback,screentop,screenleft),screentop,centerz+rotatez(screenback,screentop,screenleft)};
	double temp20 [] = {centerx + rotatex(screenback,screentop,screenright),screentop,centerz+rotatez(screenback,screentop,screenright)};
	double temp21 [] = {centerx + rotatex(screenfront,screenbot,screenright),screenbot,centerz+rotatez(screenfront,screenbot,screenright)};
	double temp22 [] = {centerx + rotatex(screenfront,screenbot,screenleft),screenbot,centerz+rotatez(screenfront,screenbot,screenleft)};

	for (int i = 0; i < 3; i++){
	backbotleft[i] = temp1[i];
	backbotright[i] = temp2[i];
	frontbotleft[i] = temp3[i];
	frontbotright[i] = temp4[i];
	backtopleft[i] = temp5[i];
	backtopright[i] = temp6[i];
	fronttopleft[i] = temp7[i];
	fronttopright[i] = temp8[i];
	backtallleft[i] = temp9[i];
	backtallright[i] = temp10[i];
	fronttallleft[i] = temp11[i];
	fronttallright[i] = temp12[i];
	pastunderleft[i] = temp13[i];
	pastunderright[i] = temp14[i];
	frontunderleft[i] = temp15[i];
	frontunderright[i] = temp16[i];
	midtopleft[i] = temp17[i];
	midtopright[i] = temp18[i];
	temp0[i] = temp00[i];
	screentopleft[i] = temp19[i];
	screentopright[i] = temp20[i];
	screenbotright[i] = temp21[i];
	screenbotleft[i] = temp22[i];
	}


}

double Cube::rotatex(double x, double y, double z){
	return 1*sin(rotation)*z + cos(rotation)*x;
}
double Cube::rotatez(double x, double y, double z){
	return -1*sin(rotation)*x + cos(rotation)*z;
}



void Cube::DrawCube(int mode1, GLuint texts [])
{	if(mode1){
	    glMaterialfv(GL_FRONT, GL_AMBIENT, cubemat_ambient);
    	glMaterialfv(GL_FRONT, GL_DIFFUSE, cubemat_diffuse);
    	glMaterialfv(GL_FRONT, GL_SPECULAR, cubemat_specular);
    	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    	glMaterialfv(GL_FRONT, GL_EMISSION, cubemat_emission);
	}
	
	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
	glColor3d(colorr, colorg, colorb);

	double temp [3];
	
	//bot
	returnNormal(temp, backbotleft,backbotright,frontbotright);
	glNormal3dv(temp);
	glVertex3dv(backbotleft);
	glVertex3dv(backbotright);
	glVertex3dv(frontbotright);
	glVertex3dv(frontbotleft);
	glEnd();
	//top
	glBegin(GL_QUADS);
	returnNormal(temp, backtopleft,fronttopleft,fronttopright);
	glNormal3dv(temp);
	glVertex3dv(backtopleft);
	glVertex3dv(fronttopleft);
	glVertex3dv(fronttopright);
	glVertex3dv(backtopright);
	glEnd();

	//back
	glBegin(GL_QUADS);
	returnNormal(temp, backbotleft,backtopleft,backtopright);
	glNormal3dv(temp);
	glVertex3dv(backbotleft);
	glVertex3dv(backtopleft);
	glVertex3dv(backtopright);
	glVertex3dv(backbotright);
	
	
	glEnd();

	//front
	glBegin(GL_QUADS);
	returnNormal(temp, frontbotleft,frontbotright,fronttopright);
	glNormal3dv(temp);
	glVertex3dv(frontbotleft);
	glVertex3dv(frontbotright);
	glVertex3dv(fronttopright);
	glVertex3dv(fronttopleft);
	glEnd();
	
	//left
	glBegin(GL_QUADS);
	returnNormal(temp, frontbotleft,fronttopleft,backtopleft);
	glNormal3dv(temp);
	glVertex3dv(frontbotleft);
	glVertex3dv(fronttopleft);
	glVertex3dv(backtopleft);
	glVertex3dv(backbotleft);
	glEnd();
	
	//right
	glBegin(GL_QUADS);
	returnNormal(temp, frontbotright,backbotright,backtopright);
	glNormal3dv(temp);
	glVertex3dv(frontbotright);
	glVertex3dv(backbotright);
	glVertex3dv(backtopright);
	glVertex3dv(fronttopright);
	glEnd();


	//screen
	glBegin(GL_QUADS);
	returnNormal(temp, midtopleft,midtopright,pastunderright);
	glNormal3dv(temp);
	glVertex3dv(midtopleft);
	glVertex3dv(midtopright);
	glVertex3dv(pastunderright);
	glVertex3dv(pastunderleft);
	glEnd();

	//left panel
	glBegin(GL_QUADS);
	returnNormal(temp, midtopleft,pastunderleft,backtallleft);
	glNormal3dv(temp);
	glVertex3dv(midtopleft);
	glVertex3dv(pastunderleft);
	glVertex3dv(backtallleft);
	glVertex3dv(backtopleft);
	glEnd();

	//right panel
	glBegin(GL_QUADS);
	returnNormal(temp, midtopright,backtopright,backtallright);
	glNormal3dv(temp);
	glVertex3dv(midtopright);
	glVertex3dv(backtopright);
	glVertex3dv(backtallright);
	glVertex3dv(pastunderright);
	glEnd();


	//upperback
	glBegin(GL_QUADS);
	returnNormal(temp, backtopleft,backtallleft,backtallright);
	glNormal3dv(temp);
	glVertex3dv(backtopleft);
	glVertex3dv(backtallleft);
	glVertex3dv(backtallright);
	glVertex3dv(backtopright);
	glEnd();

	//under
	glBegin(GL_QUADS);
	returnNormal(temp, frontunderleft,frontunderright,pastunderright);
	glNormal3dv(temp);
	glVertex3dv(frontunderleft);
	glVertex3dv(frontunderright);
	glVertex3dv(pastunderright);
	glVertex3dv(pastunderleft);
	glEnd();

	//topleftpanel
	glBegin(GL_QUADS);
	returnNormal(temp, frontunderleft,fronttallleft,backtallleft);
	glNormal3dv(temp);
	glVertex3dv(frontunderleft);
	glVertex3dv(fronttallleft);
	glVertex3dv(backtallleft);
	glVertex3dv(pastunderleft);
	glEnd();

	//toprightpanel
	glBegin(GL_QUADS);
	returnNormal(temp, backtallright,fronttallright,frontunderright);
	glNormal3dv(temp);
	glVertex3dv(backtallright);
	glVertex3dv(fronttallright);
	glVertex3dv(frontunderright);
	glVertex3dv(pastunderright);
	glEnd();

	//tiptop
	glBegin(GL_QUADS);
	returnNormal(temp, backtallleft,fronttallleft,fronttallright);
	glNormal3dv(temp);
	glVertex3dv(backtallleft);
	glVertex3dv(fronttallleft);
	glVertex3dv(fronttallright);
	glVertex3dv(backtallright);
	glEnd();

	//topfront

	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor4d(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D,texts[textnum + 7]);
		// Select the current texture.
	glMaterialfv(GL_FRONT, GL_AMBIENT, supmat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, supmat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, supmat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, supmat_emission);

    glBegin(GL_QUADS);
    returnNormal(temp, fronttallleft,frontunderleft,frontunderright);
    glNormal3dv(temp);
    glTexCoord2d(0.0,0.0);  // For each vertex, assign texture coordinate before vertex coordinate.
    glVertex3dv(fronttallleft);
	glTexCoord2d(1.0,0.0);
    glVertex3dv(fronttallright);
    glTexCoord2d(1.0,1.0);
    glVertex3dv(frontunderright);
    glTexCoord2d(0.0,1.0); 
    glVertex3dv(frontunderleft);
    glEnd();

    glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texts[textnum]);	// Select the current texture.
    glBegin(GL_QUADS);
    returnNormal(temp, screentopleft,screentopright,screenbotright);
	glNormal3dv(temp);
    glTexCoord2d(0.0,0.0);  // For each vertex, assign texture coordinate before vertex coordinate.
    glVertex3dv(screentopleft);
	glTexCoord2d(1.0,0.0);
    glVertex3dv(screentopright);
    glTexCoord2d(1.0,1.0);
    glVertex3dv(screenbotright);

    glTexCoord2d(0.0,1.0); 
    glVertex3dv(screenbotleft);
    glEnd();
    glDisable(GL_TEXTURE_2D);


}



void DrawGroundLattice(GLuint texts [])
{	glMaterialfv(GL_FRONT, GL_AMBIENT, gridmat_ambient);
   	glMaterialfv(GL_FRONT, GL_DIFFUSE, gridmat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gridmat_specular);
   	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, gridmat_emission);
	glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_LINES);
	for(int x=-1*roomx; x<=roomx; x+=15)
	{	for(int y = -1*roomz; y <=roomz; y+=15){
			glNormal3d(0,1,0);
			glVertex3i(x,19,y);
			glVertex3i(x,19, y+15);
			glVertex3i(x,19,y);
			glVertex3i(x+15,19, y);
		}
	}
	glEnd();
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, floormat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, floormat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, floormat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, floormat_emission);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor4d(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
    for(int x =-1*roomx; x<=roomx; x+=15)
    	{	for(int y = -1*roomz; y <= roomz; y+=15){
			
			glBindTexture(GL_TEXTURE_2D,texts[0]);	// Select the current texture.
			glNormal3d(0,1,0);
    		glBegin(GL_QUADS);
    		
			glTexCoord2d(0.0,0.0);   // For each vertex, assign texture coordinate before vertex coordinate.
    		glVertex3d(x,0,y);

    		glTexCoord2d(1.0,0.0);
    		glVertex3d(x,0,y+15);

    		glTexCoord2d(1.0,1.0);
    		glVertex3d(x+15,0,y+15);

    		glTexCoord2d(0.0,1.0);
    		glVertex3d(x+15,0,y);
    	}
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);

}

class CameraObject
{
public:
    double x,y,z;
    double h,p,b;

    double fov,nearZ,farZ;

    CameraObject();
    void Initialize(void);
    void SetUpCameraProjection(void);
    void SetUpCameraTransformation(void);

    void GetForwardVector(double &vx,double &vy,double &vz);
};

CameraObject::CameraObject()
{
    Initialize();
}

void CameraObject::Initialize(void)
{
    x=0;
    y=0;
    z=0;
    h=1.57;
    p=0;
    b=0;

    fov=2*YsPi*70/360;  // 30 degree
    nearZ=0.1;
    farZ=200.0;
}

void CameraObject::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)wid/(double)hei;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis
    glRotated(-p*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis
    glRotated(-h*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis
    glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}


class Lights
{
	public:
	GLfloat alight_position[4];
	GLfloat alight_ambient[4];
	GLfloat alight_diffuse[4];
	GLfloat alight_specular[4];
	GLfloat alight_direction[3];
	int lightnum = 0;
	//Lights();
	void Init(int lighter, GLfloat pos[], GLfloat amb[], GLfloat diffuse[], GLfloat spec[], GLfloat dir[]);
	void StartLight();
	void updateLightPosit();
	void ChangeLightPos(double x, double y, double z);
};

void Lights::Init(int lighter, GLfloat pos[], GLfloat amb[], GLfloat diffuse[], GLfloat spec[], GLfloat dir[]){
	lightnum = lighter;
	for(int i = 0; i < 4; i++){
		alight_position[i] = pos[i];
		alight_ambient[i] = amb[i];
		alight_diffuse[i] = diffuse[i];
		alight_specular[i] = spec[i];

	}
	for(int i = 0; i < 3; i++){
		light_direction[i] = dir[i];
	}
}

void Lights::StartLight(){
	glEnable(GL_LIGHT0+lightnum);
	glLightfv(GL_LIGHT0+lightnum, GL_AMBIENT, alight_ambient);
	glLightfv(GL_LIGHT0+lightnum, GL_DIFFUSE, alight_diffuse);
	glLightfv(GL_LIGHT0+lightnum, GL_SPECULAR, alight_specular);
	glLightfv(GL_LIGHT0+lightnum, GL_POSITION, alight_position);
	glLightf(GL_LIGHT0 + lightnum, GL_QUADRATIC_ATTENUATION, dropoff);
	

}
void Lights::ChangeLightPos(double x, double y, double z){
	alight_position[0] = (GLfloat)(x);
	alight_position[1] = (GLfloat)(y);
	alight_position[2] = (GLfloat)(z);
}

void Lights::updateLightPosit(){
	glLightfv(GL_LIGHT0+lightnum, GL_POSITION, alight_position);
}

void init(CameraObject &camera)
{	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}

void moveCamera(double point1 [], double angle, CameraObject &camera, int counter){
	int totals = 500;
	camera.h = fmod(camera.h,YsPi*2);
	double cammovex = (point1[0] - camera.x)*sin(counter*YsPi/totals);
	double cammovey = (point1[1] - camera.y)*sin(counter*YsPi/totals);
	double cammovez = (point1[2] - camera.z)*sin(counter*YsPi/totals);
	double cammovh = 0;
	double cammovp = 0;
	camera.x = camera.x + cammovex;
	camera.y = camera.y + cammovey;
	camera.z = camera.z + cammovez;
	if (fabs(point1[0] - camera.x) < .05){
		camera.x = point1[0];
		//printf("goodx\n");
	}
	if (fabs(point1[1] - camera.y) < .05){
		camera.y = point1[1];
		//printf("goody\n");
	}
	if (fabs(point1[2] - camera.z) < .05){
		camera.z = point1[2];
		//printf("goodz\n");
	}
	double difangle = 0;
	if(camera.h < angle) {
		if(fabs(angle - camera.h) <= YsPi){
			difangle = angle - camera.h;
			cammovh = difangle*sin(counter*YsPi/totals);
			
		}
		else{
			difangle = angle - camera.h - YsPi*2; 
			cammovh = difangle*sin(counter*YsPi/totals);
		}
	}
	else{
		if(fabs(angle - camera.h) <= YsPi){
			difangle = angle - camera.h;
			cammovh = difangle*sin(counter*YsPi/totals);
		}
		else{
			difangle = angle - camera.h + YsPi*2;
			cammovh = difangle*sin(counter*YsPi/totals);
			
		}
	}
	camera.h = camera.h + cammovh;
	if(fabs(camera.h - angle) < .01){//} || fabs(camera.h - angle) > 2*YsPi){
		camera.h = angle;
	}
	if(camera.h < 0){
		camera.h = camera.h + YsPi*2;
	}
	double wantedp = -.244;
	double difanglep = 0;
	if(camera.p > wantedp){
		difanglep = wantedp - camera.p;
		cammovp = difanglep*sin(counter*YsPi/totals);
	}
	camera.p = camera.p + cammovp;
	if(fabs(camera.p - wantedp) < .01){
		camera.p = wantedp;
	}

	

}

bool checkCollision(double xdir, double zdir, double time, CameraObject &camera, Cube cubes []){
	if(camera.x + xdir*time*30 > roomx || camera.x + xdir*time*30 < -1*roomx){
		return false;
	
	}
	if(camera.z + zdir*time*30 > roomz || camera.z + zdir*time*30 < -1*roomz){
		return false;
	}
	for(int i = 0; i < stations;  i++){
		double tempx1 = camera.x + xdir*time*30 - cubes[i].centerx;
		double tempz1 = camera.z + zdir*time*30 - cubes[i].centerz;
		double tempx = tempx1*cos(1*cubes[i].rotation) - tempz1*sin(1*cubes[i].rotation);
		double tempz = tempx1*sin(1*cubes[i].rotation) + tempz1*cos(1*cubes[i].rotation);
		if((tempx > -1*cubes[i].width/2 && tempx < 1*cubes[i].width/2)){
			if((tempz > -1*cubes[i].width/2 && tempz < 1*cubes[i].width/2)){
				//printf("           %f %f %d %f %f %f %f %f %f\n", xdir, zdir, i, time, cubes[i].centerx, cubes[i].centerz,camera.x, camera.z, cubes[i].rotation);
				return false;
			}
		}
	}
	return true;
}

void checkAndMove(int direction, double dt, CameraObject &camera, Cube  cubes []){
	if(direction == 1){
		double vx,vy,vz;
		camera.GetForwardVector(vx,vy,vz);
		if(checkCollision(vx, vz, dt, camera, cubes)){
			camera.x+=vx*dt*30.0;
			camera.z+=vz*dt*30.0;
		}
	}
	if(direction == 2){
		double vx,vy,vz;
		camera.GetForwardVector(vx,vy,vz);
		if(checkCollision(-1*vx, -1*vz, dt, camera, cubes)){
			camera.x-=vx*dt*30.0;
			camera.z-=vz*dt*30.0;
		}
	}
	if(direction == 3){
		double vx,vy,vz;
		camera.GetForwardVector(vx,vy,vz);
		if(checkCollision(vz, -1*vx, dt, camera, cubes)){
			camera.z-=vx*dt*30.0;
			camera.x+=vz*dt*30.0;
		}
	}
	if(direction == 4){
		double vx,vy,vz;
		camera.GetForwardVector(vx,vy,vz);
		if(checkCollision(-1*vz, vx, dt, camera, cubes)){
			camera.z+=vx*dt*30.0;
			camera.x-=vz*dt*30.0;
		}
	}

}

void playGame(int num, GLuint texts []){
	int newscore = 0;
	switch(num)
	{
		
		case 0:
		{
			AsteroidsGame game0;
			newscore = (int)game0.play();
			if(newscore > scores[0]){
				scores[0] = newscore;
				makeAsteroidScore(newscore,texts);
			}
			break;
		}
		case 1:
		{
			CentipedeGame game1;
			newscore = (int)game1.Play();
			if(newscore > scores[1]){
				scores[1] = newscore;
				makeCentipedeScore(newscore,texts);
			}
			break;
		}
		case 2:
		{
			Frog game2;
			newscore = (int)game2.PlayFrogger();
			if(newscore > scores[2]){
				scores[2] = newscore;
				makeFroggerScore(newscore,texts);
			}
			break;
		}
		case 3:
		{	Galaga game3;
			newscore = (int)game3.play();
			if(newscore > scores[3]){
				scores[3] = newscore;
				makeGalagaScore(newscore,texts);
			}
			break;
		}
		case 4:
		{
			CharBitmap game4;
			newscore = (int)game4.play();
			if(newscore > scores[4]){
				scores[4] = newscore;
				makePacmanScore(newscore,texts);
			}
			break;
		}
		case 5:
		{
			Tetris game5;
			newscore = (int)game5.Play();
			if(newscore > scores[5]){
				scores[5] = newscore;
				makeTetrisScore(newscore,texts);
			}
			break;
		}
		case 6:
		{
			Tron game6;
			game6.play();
			break;
		}	
	}
	
}

int main(void)
{
    int terminate=0;
    CameraObject camera;
    camera.z=0.0;
    camera.y=7.0;
    camera.x = 0;
	camera.h = 1.57;
	Cube cubes[stations];
	int radius = 40;
	/**
	for (double i = 0; i < stations; i++){
		cubes[(int)i].Init(radius*cos(2*i*3.14/((double)stations)), -1*radius*sin(2*i*3.14/((double)stations)), 5, 5, 5, 0, 0, 255,2*i*3.14/((double)stations),(int)i%2);
		if(i < 3){
			cubes[(int)i].textnum = i;
		}
	}
	*/
	for(int i = 0 ; i < stations; i++){
		int newx = 55 + -80*cos((-30.0+10*i)*YsPi/180);
		int newy = 0+-80*sin((-30.0+10*i)*YsPi/180);
		cubes[i].Init(newx, newy,5,5,5, 255, 255, 0 ,(30+180+-10*i)*YsPi/180, 0);
		cubes[(int)i].textnum = i ;
	}



	FsOpenWindow(16,16,800,600,1);
	const int numTexts  = 15;
	YsRawPngDecoder png[numTexts];
	png[0].Decode("asteroids.png");
	png[1].Decode("CentipedeMenu.png");
	png[2].Decode("FroggerGame.png");
	png[3].Decode("GalagaSprite/GalagaScreen.png");
	png[4].Decode("Menu.png");
	png[5].Decode("TetrisScreen.png");
	png[6].Decode("FinalTron.png");
	png[7].Decode("Asteroids_header.png");
	png[8].Decode("CentipedeBanner.png");
	png[9].Decode("froggerBanner.png");
	png[10].Decode("galagabanner.png");
	png[11].Decode("BannerPacman.png");
	png[12].Decode("TetrisSign.png");
	png[13].Decode("TronBanner.png");
	png[14].Decode("mainmenu.png");

    GLuint texId[numTexts];
	for(int i = 0; i < numTexts; i++){
		glGenTextures(1, &texId[i]);
		glBindTexture(GL_TEXTURE_2D, texId[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			png[i].wid,         png[i].hei,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE,  // Source component type
			png[i].rgba);
	}
	YsRawPngDecoder others[10];
	GLuint othertexId[numTexts];
	others[0].Decode("floor.png");
	others[1].Decode("HighScores.png");
	for(int i = 0; i < 2; i++){
		glGenTextures(1, &othertexId[i]);
		glBindTexture(GL_TEXTURE_2D, othertexId[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Specifying parameters    
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);   
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0,    // Level of detail
			GL_RGBA,  // Internal data type.
			others[i].wid,         others[i].hei,         0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,  // Source data type
			GL_UNSIGNED_BYTE,  // Source component type
			others[i].rgba);
	}
	makeAsteroidScore(0,othertexId);
	makeCentipedeScore(0,othertexId);
	makeFroggerScore(0,othertexId);
	makeGalagaScore(0,othertexId);
	makePacmanScore(0,othertexId);
	makeTetrisScore(0,othertexId);
	makeTronScore(0,othertexId);

	Walls SomeWalls;
	SomeWalls.Init();
	HighScore table;
	table.Init();
  	init(camera);
	Lights someLights[numLights];
	for(int i = 0; i < numLights; i++){
		someLights[i].Init(i,light_positionglobal,light_ambient,light_diffuse,light_specular,light_direction);
		someLights[i].StartLight();
		//someLights[i].ChangeLightPos(-60 +i*60,5,0);
	}
	double corner = 70;
	someLights[0].ChangeLightPos(-1*25,10,-1*40);
	someLights[1].ChangeLightPos(-1*25,10,40);
	someLights[2].ChangeLightPos(25,10,40);
	someLights[3].ChangeLightPos(25,10,-1*40);
	someLights[4].ChangeLightPos(0,5,0);
	
	FsPassedTime();
	int mode = 0;
	double angle = 0;
	double point [3];
	int best = stations;
	int counter =0 ;
	int total = 0;
	long int timer = FsSubSecondTimer();
	long int cubetimer = FsSubSecondTimer();
	int lit = 0;
	int loop = 1000;
	double oldx = 0;
	double oldz = 0;
	double oldh = 0;

	png[14].Flip();
	for(;;) {
        FsPollDevice();
        auto key=FsInkey();
        int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glRasterPos2d(0.0,(double)(winHei-1));
        glDrawPixels(png[14].wid,png[14].hei,GL_RGBA,GL_UNSIGNED_BYTE,png[14].rgba);
        FsSwapBuffers();
        FsSleep(100);
        if(FSKEY_ESC == key) {
            break;
        }
        if(FSKEY_ENTER == key) {
            break;
        }
    }



    while(0==terminate)
    {
        FsPollDevice();
        double dt=(double)FsPassedTime()/1000.0;

        int wid,hei;
        FsGetWindowSize(wid,hei);

        int key=FsInkey();
        if(mode == 0)
        {
        	switch(key)
        	{
        	case FSKEY_ESC:
            	terminate=1;
            	break;
        	}
			//printf(" %f, %f, %f\n", camera.x, camera.z, camera.y);
			if(0!=FsGetKeyState(FSKEY_W))
			{
				checkAndMove(1,dt,camera,cubes);
			}
			if(0!=FsGetKeyState(FSKEY_SPACE)){
				camera.x = 0;
				camera.z =0;
			}
			if (0 != FsGetKeyState(FSKEY_S))
			{checkAndMove(2,dt,camera,cubes);
			}
			if(0!=FsGetKeyState(FSKEY_A))
			{
				checkAndMove(3,dt,camera,cubes);
			}
			if(0!=FsGetKeyState(FSKEY_D))
			{
				checkAndMove(4,dt,camera,cubes);
			}

			if (0 != FsGetKeyState(FSKEY_RIGHT))
			{
				camera.h -= dt*YsPi;
			}
			if (0 != FsGetKeyState(FSKEY_LEFT))
			{
				camera.h += dt*YsPi;
			}
			if (0 != FsGetKeyState(FSKEY_P))
			{
				mode = 1;
				double distance = 1000;
				for(int i = 0; i < stations; i ++){
					double temp = sqrt(pow((camera.x - cubes[i].temp0[0]),2) + pow((camera.z - cubes[i].temp0[2]),2));
					if(temp < distance){
						best = i;
						
						distance = temp;
					}
				}
				printf("%d \n", best);
				angle = cubes[best].rotation - 1.57;
				if(angle < 0){
					angle = angle + 2*YsPi;
				}
				oldx = camera.x;
				oldz= camera.z;
				oldh = camera.h;
				for(int i = 0; i < 3; i++){
					point[i] = cubes[best].temp0[i];
				}
				//point[0] += 3*cubes[best].normx;
				point[1] += pushup;
				//point[2] += 3*cubes[best].normz;	
			}
		}
		else{
			if(camera.h != angle || point[0] != camera.x || camera.y != point[1] || camera.z != point[2]){
				moveCamera(point, angle, camera, counter);
				counter++;
			}
			else{
				glDisable(GL_LIGHTING);
				glClearColor(1, 1, 1, 1);
				playGame(best,othertexId);
				mode = 0;
				counter = 0;
				total = 0;
				glEnable(GL_LIGHTING);
				glClearColor(0, 0, 0, 0);
				camera.x = oldx;
				camera.z = oldz;
				camera.h = oldh;
				camera.p = 0;
			}
		}

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        glViewport(0,0,wid,hei);
        // Set up 3D drawing
        camera.SetUpCameraProjection();
        camera.SetUpCameraTransformation();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_FILL);
        for(int i = 0; i<numLights; i++){
        	someLights[i].updateLightPosit();
        }
        //printf("%f  %f\n",camera.x, camera.z);
        glPolygonOffset(1,1);

        // 3D drawing from here
		for (int i = 0; i < stations; i++){
			cubes[i].DrawCube(1, texId);
		}/*
		for (int i = 0; i < stations; i++){
			cubes[i].DrawCube(1);
		}*/
		DrawGroundLattice(othertexId);
		SomeWalls.DrawWalls(texId);
		table.DrawScores(othertexId,1);
        // Set up 2D drawing
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);

        // 2D drawing from here


        FsSwapBuffers();
        FsSleep(30);
        //printf("FramerateL %f\n",1/dt);
    }

    return 0;
}


