
#ifndef Tron_h
#define Tron_h

#endif /* Tron_h */

#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include <math.h>
#include <vector>
#include "ysglfontdata.h"
#include "yspng.h"
#include <string>
#include <time.h>

class Tron{
public:
    int helpMenuState=0;
    int PlayerState=0;
    int CompState=0;
    void Grid();
    void play();
    void helpMenu(int key);
    void startMenu();
    void gameOver();
    void win();
    
    class Bike{
    private:
        const double dt=0.3;
        
    public:
        int life=3;
        int complife=3;
        int bikeSize=5;
        int dummy=10;
        double bikeColor[3] = {0,0,0};
        double streakColor[3]={0,0,0};
        double bikex,bikey,bikevx,bikevy;
        double streakx, streaky;
        
        void initPlayer(int x, int y);
        void swap(int &a, int &b);
        void streak(double streakColor[]);
        void streakStructs(int x1, int y1, int x2, int y2, double streakColor[]);
        void bikeDraw(double bikeColor[]);
        void Move(int key, int &state, Bike &player);
        void MoveComp(int &state, Bike &comp, int &diff);
        void pickMove(bool choices[], Bike &player);
        bool collision(int x1, int y1, int x2, int y2, int &counter);
        void counter();
        void dispLives(Bike &player,int x, int y);
        
        
        std::vector<double> center;
        std::vector<int> collisioncounter;
        int length = (int)center.size();
        int lengthcol = (int)collisioncounter.size();
        
        
        
    };
    
    void DrawNCheck(Bike &player, Bike &comp);
    
};
void Tron::Grid(){
    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_LINES);
    for (int i=80;i<800;i+=80){
        glVertex2f(i, 0);
        glVertex2f(i, 600);
    }
    for (int i=60;i<600;i+=60){
        glVertex2f(0, i);
        glVertex2f(800, i);
    }
    glEnd();
}

void Tron::helpMenu(int key){
    
    
    if (key==FSKEY_H)
        for(;;){
            FsPollDevice();
            
            glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
            
            Grid();
            
            //background
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_QUADS);
            glVertex2f(100, 100);
            glVertex2f(700, 100);
            glVertex2f(700, 500);
            glVertex2f(100, 500);
            glEnd();
            
            //keypad
            int centerx=400, centery=300, padSize=12.5;
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_QUADS);
            
            //center
            glVertex2f(centerx-padSize, centery-padSize);
            glVertex2f(centerx+padSize, centery-padSize);
            glVertex2f(centerx+padSize, centery+padSize);
            glVertex2f(centerx-padSize, centery+padSize);
            
            //top
            glVertex2f(centerx-padSize, (centery-2*padSize)-padSize);
            glVertex2f(centerx+padSize, (centery-2*padSize)-padSize);
            glVertex2f(centerx+padSize, (centery-2*padSize)+padSize);
            glVertex2f(centerx-padSize, (centery-2*padSize)+padSize);
            
            //right
            glVertex2f((centerx+2*padSize)-padSize, centery-padSize);
            glVertex2f((centerx+2*padSize)+padSize, centery-padSize);
            glVertex2f((centerx+2*padSize)+padSize, centery+padSize);
            glVertex2f((centerx+2*padSize)-padSize, centery+padSize);
            
            //bottom
            glVertex2f(centerx-padSize, (centery+2*padSize)-padSize);
            glVertex2f(centerx+padSize, (centery+2*padSize)-padSize);
            glVertex2f(centerx+padSize, (centery+2*padSize)+padSize);
            glVertex2f(centerx-padSize, (centery+2*padSize)+padSize);
            
            //left
            glVertex2f((centerx-2*padSize)-padSize, centery-padSize);
            glVertex2f((centerx-2*padSize)+padSize, centery-padSize);
            glVertex2f((centerx-2*padSize)+padSize, centery+padSize);
            glVertex2f((centerx-2*padSize)-padSize, centery+padSize);
            
            glEnd();
            
            glColor3ub(255,255,255);
            glRasterPos2i(centerx-padSize+5,250);
            YsGlDrawFontBitmap12x16("UP");
            glRasterPos2i(centerx-padSize-10,365);
            YsGlDrawFontBitmap12x16("DOWN");
            glRasterPos2i(centerx-(8*padSize),310);
            YsGlDrawFontBitmap12x16("LEFT");
            glRasterPos2i(centerx+(4.2*padSize),310);
            YsGlDrawFontBitmap12x16("RIGHT");
            
            glRasterPos2i(105, 115);
            YsGlDrawFontBitmap8x12("H: Help Menu");
            glRasterPos2i(105, 135);
            YsGlDrawFontBitmap8x12("ESC: Quit Game");
            glRasterPos2i(105, 155);
            YsGlDrawFontBitmap8x12("R: Return to Game");
            
            glRasterPos2i(225, 425);
            YsGlDrawFontBitmap8x12("Avoid your streaks and computer's streaks");
            glRasterPos2i(225, 440);
            YsGlDrawFontBitmap8x12("to beat the game. Also avoid edges of screen");
            
            
            FsSwapBuffers();
            int newkey = FsInkey();
            
            if (newkey==FSKEY_R){
                helpMenuState=0;
                break;
            }
            if (newkey==FSKEY_ESC){
                helpMenuState=1;
                break;
            }
        }
    
    
}

void Tron::startMenu(){
    
    YsRawPngDecoder png;
    if(YSOK==png.Decode("FinalTron.png"))
    {
        png.Flip();
        printf("%dx%d\n",png.wid,png.hei);
    }
    else
    {
        printf("Cannot open file.\n");
    }
    
    for(;;){
        int key=FsInkey();
        FsPollDevice();
        
        if (key==FSKEY_S){
            break;
        }
        
        if (key==FSKEY_ESC){
            PlayerState=1;
            break;
        }
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        glRasterPos2i(50,400);
        glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        
        glColor3ub(255,255,255);
        glRasterPos2i(225, 425);
        YsGlDrawFontBitmap8x12("Press S to Start or ESC to quit");
        
        FsSwapBuffers();
        
        FsSleep(25);
    }
}

void Tron::gameOver(){
    
    for (;;){
        int key=FsInkey();
        FsPollDevice();
        
        if (key==FSKEY_ESC){
            break;
        }
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        glColor3ub(255,255,255);
        glRasterPos2i(260, 200);
        YsGlDrawFontBitmap32x48("GAME OVER");
        glRasterPos2i(310, 300);
        YsGlDrawFontBitmap8x12("PRESS ESC TO LEAVE GAME");
        
        FsSwapBuffers();
        
        FsSleep(25);
    }
}

void Tron::win(){
    
    for (;;){
        int key=FsInkey();
        FsPollDevice();
        
        if (key==FSKEY_ESC){
            break;
        }
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        glColor3ub(255,255,255);
        glRasterPos2i(300, 200);
        YsGlDrawFontBitmap32x48("YOU WIN!");
        glRasterPos2i(310, 300);
        YsGlDrawFontBitmap8x12("PRESS ESC TO LEAVE GAME");
        
        FsSwapBuffers();
        
        FsSleep(25);
    }
}

void Tron::Bike::swap(int &a, int &b){
    int c;
    c=a;
    a=b;
    b=c;
    
}

void Tron::Bike::bikeDraw(double bikeColor[]){
    glColor3f(bikeColor[0], bikeColor[1], bikeColor[2]);
    glBegin(GL_QUADS);
    glVertex2f(bikex-bikeSize, bikey-bikeSize);
    glVertex2f(bikex+bikeSize, bikey-bikeSize);
    glVertex2f(bikex+bikeSize, bikey+bikeSize);
    glVertex2f(bikex-bikeSize, bikey+bikeSize);
    glEnd();
}
void Tron::Bike::streak(double streakColor[]){
    glColor3f(streakColor[0], streakColor[1], streakColor[2]);
    glBegin(GL_QUADS);
    glVertex2f(streakx-bikeSize, streaky-bikeSize);
    glVertex2f(bikex+bikeSize, streaky-bikeSize);
    glVertex2f(bikex+bikeSize, bikey+bikeSize);
    glVertex2f(streakx-bikeSize, bikey+bikeSize);
    glEnd();
}

void Tron::Bike::streakStructs(int x1, int y1, int x2, int y2, double streakColor[]){
    glColor3f(streakColor[0], streakColor[1], streakColor[2]);
    glBegin(GL_QUADS);
    if (y2>y1){
        glVertex2f(x1-bikeSize, y1-bikeSize);
        glVertex2f(x2+bikeSize, y1-bikeSize);
        glVertex2f(x2+bikeSize, y2+bikeSize);
        glVertex2f(x1-bikeSize, y2+bikeSize);
    }
    else if (x2<x1){
        glVertex2f(x1+bikeSize, y1+bikeSize);
        glVertex2f(x2-bikeSize, y1+bikeSize);
        glVertex2f(x2-bikeSize, y2-bikeSize);
        glVertex2f(x1+bikeSize, y2-bikeSize);
        
    }
    else{
        glVertex2f(x1-bikeSize, y1+bikeSize);
        glVertex2f(x2+bikeSize, y1+bikeSize);
        glVertex2f(x2+bikeSize, y2-bikeSize);
        glVertex2f(x1-bikeSize, y2-bikeSize);
    }
    glEnd();
    
}

void Tron::Bike::Move(int key, int &State, Bike &player){
    
    bikex+=bikevx*dt;
    bikey+=bikevy*dt;
    
    if(player.life==0){
        State=1;
    }
    
    if (bikex+bikeSize>800){
        //        bikex=800-bikeSize;
        player.life--;
        player.initPlayer(400,300);
    }
    else if (bikex-bikeSize<0){
        //        bikex=bikeSize;
        player.life--;
        player.initPlayer(400,300);
    }
    if (bikey+bikeSize>600){
        //        bikey=600-bikeSize;
        player.life--;
        player.initPlayer(400,300);
        
    }
    else if (bikey-bikeSize<0){
        //        bikey=bikeSize;
        player.life--;
        player.initPlayer(400,300);
    }
    bool Up = bikevx==0 && bikevy==-10;
    bool Down = bikevx==0 && bikevy==10;
    bool Right = bikevx==10 && bikevy==0;
    bool Left = bikevx==-10 && bikevy==0;
    
    switch(key){
        case FSKEY_DOWN:
            if (!Down){
                bikevx=0;
                bikevy=10;
                streakx = bikex;
                streaky = bikey;
                
                center.insert(center.end(), {streakx,streaky});
                counter();
            }
            break;
            
        case FSKEY_UP:
            if(!Up){
                bikevx=0;
                bikevy=-10;
                streakx = bikex;
                streaky = bikey;
                
                center.insert(center.end(), {streakx,streaky});
                counter();
            }
            break;
            
        case FSKEY_LEFT:
            if(!Left){
                bikevy=0;
                bikevx=-10;
                streakx = bikex;
                streaky = bikey;
                
                center.insert(center.end(), {streakx,streaky});
                counter();
            }
            break;
            
        case FSKEY_RIGHT:
            if(!Right){
                bikevy=0;
                bikevx=10;
                streakx = bikex;
                streaky = bikey;
                
                center.insert(center.end(), {streakx,streaky});
                counter();
            }
            break;
            
    }
}

void Tron::Bike::MoveComp(int &State , Bike &player, int &diff){
    
    bikex+=bikevx*dt;
    bikey+=bikevy*dt;
    
    
    if (bikex+bikeSize>800){
        bikex=800-bikeSize;
    }
    else if (bikex-bikeSize<0){
        bikex=bikeSize;
    }
    if (bikey+bikeSize>600){
        bikey=600-bikeSize;
        
    }
    else if (bikey-bikeSize<0){
        bikey=bikeSize;
    }
    
    bool Up = bikevx==0 && bikevy==-10;
    bool Down = bikevx==0 && bikevy==10;
    bool Right = bikevx==10 && bikevy==0;
    bool Left = bikevx==-10 && bikevy==0;
    
    bool choices[4]={Up, Down, Right, Left};
    
    if (diff >= 700){ //time in milliseconds so 700 milliseconds
        pickMove(choices, player);
        diff=0;
    }
    
}

void Tron::Bike::pickMove(bool choices[], Bike &player){
    
//    double move = rand()%100;
    bool moveDown = bikey<player.bikey;//(bikex>800*0.6) || (bikex<800*0.2);//move>=0 && move<25;
    bool moveUp = bikey>player.bikey; //(bikex>800*0.8) || (bikex<800*0.4);//move>=25 && move<50;
    bool moveLeft = bikex>player.bikex;//(bikey>600*0.6) || (bikey<600*0.2);//move>=50 && move<75;
    bool moveRight = bikex<player.bikex;//(bikey>600*0.8) || (bikey<600*0.2);//move>=75 && move<99;
    
    
    //DOWN
    if (!choices[0] && moveDown && !choices[1]){
        bikevx=0;
        bikevy=10;
        streakx = bikex;
        streaky = bikey;
        
        center.insert(center.end(), {streakx,streaky});
        counter();
    }
    
    
    //UP:
    if (!choices[1] && moveUp && !choices[0]){
        bikevx=0;
        bikevy=-10;
        streakx = bikex;
        streaky = bikey;
        
        center.insert(center.end(), {streakx,streaky});
        counter();
    }
    
    
    //LEFT:
    if (!choices[2] && moveLeft && !choices[3]){
        bikevy=0;
        bikevx=-10;
        streakx = bikex;
        streaky = bikey;
        
        center.insert(center.end(), {streakx,streaky});
        counter();
    }
    
    
    //RIGHT:
    if (!choices[3] && moveRight && !choices[2]){
        bikevy=0;
        bikevx=10;
        streakx = bikex;
        streaky = bikey;
        
        center.insert(center.end(), {streakx,streaky});
        counter();
    }

    
}

bool Tron::Bike::collision(int x1, int y1, int x2, int y2, int &counter){
    
    if (y1>y2){
        swap(y1, y2);
    }
    if (x1>x2){
        swap(x1, x2);
    }
    // tolerance needed for y values because valuese of dt allow bikw to teleport or skip across streaks
    if (bikex<=x2 && bikex>=x1 && bikey<=y2+1 && bikey>=y1-1){
        if (counter<1){
            counter++;
        }
        else{
            return true;
        }
        
    }
    return false;
}

void Tron::Bike::counter(){
    collisioncounter.insert(collisioncounter.end(), {0,0});
}

void Tron::Bike::dispLives(Bike &player,int x, int y){
    
    
    std::string s = std::to_string(player.life);
    char const *pchar = s.c_str();
    char plystr[80] = "LIVES: ";
    strcat(plystr, pchar);
    
    glColor3ub(255,255,255);
    glRasterPos2i(x, y);
    YsGlDrawFontBitmap8x12(plystr);
}
void Tron::Bike::initPlayer(int x, int y){
    
    center.erase(center.begin(), center.end());
    collisioncounter.erase(collisioncounter.begin(), collisioncounter.end());
    
    bikex = x;
    bikey = y;
    
    streakx = bikex;
    streaky = bikey;
    
    bikevx = 10;
    bikevy = 0;
    
    center.insert(center.end(),
                  {streakx,
                      streaky});
}


void Tron::DrawNCheck(Bike &player, Bike &comp ){
    
    player.length = (int)player.center.size();
    player.lengthcol = (int)player.collisioncounter.size();
    if(player.length >= 4){
        
        for(int i=0; i< player.length-3; i+=2){
            player.streakStructs(player.center[i],
                                 player.center[i+1],
                                 player.center[i+2],
                                 player.center[i+3],
                                 player.streakColor);
            
            
            bool playerHitSelf=player.collision(player.center[i],
                                            player.center[i+1],
                                            player.center[i+2],
                                            player.center[i+3],
                                            player.collisioncounter[i]);
            
            
            
            if(player.life==0){
                PlayerState=1;
            }
            
            if (playerHitSelf){
                player.life--;
                player.initPlayer(400,300);
            }
            
        }
    }
    
    comp.length = (int)comp.center.size();
    comp.lengthcol = (int)comp.collisioncounter.size();
    if(comp.length >= 4){
        
        for(int i=0; i< comp.length-3; i+=2){
            
            comp.streakStructs(comp.center[i],
                               comp.center[i+1],
                               comp.center[i+2],
                               comp.center[i+3],
                               comp.streakColor);
            
            
            bool compHitSelf=comp.collision(comp.center[i],
                                        comp.center[i+1],
                                        comp.center[i+2],
                                        comp.center[i+3],
                                        comp.collisioncounter[i]);
            
            bool playerHitComp=player.collision(comp.center[i],
                                                comp.center[i+1],
                                                comp.center[i+2],
                                                comp.center[i+3],
                                                comp.collisioncounter[i]);
            
            if(comp.life==0){
                CompState=1;
            }
            
            if (playerHitComp){
                player.life--;
                player.initPlayer(400,300);

            }
            if(compHitSelf){
                comp.life--;
                comp.initPlayer(400,100);
            }
        }
    }
    
}

void initGridColor(){
    glClearColor(0.0,0.0,0.0,1.);
}


void Tron::play() {
    
//    time_t initial_time;
//    time_t end_time;
    srand((int)time(nullptr));
    
    initGridColor();
    Bike player1, comp1;
    
    player1.initPlayer(400,300);
    player1.streakColor[0]=1.0;player1.streakColor[1]=1.0;player1.streakColor[2]=1.0;
    player1.bikeColor[0]=1.0;player1.bikeColor[1]=0.0;player1.bikeColor[2]=0.0;
    comp1.initPlayer(400,100);
    comp1.streakColor[0]=0.0;comp1.streakColor[1]=1.0;comp1.streakColor[2]=1.0;
    comp1.bikeColor[0]=0.0;comp1.bikeColor[1]=1.0;comp1.bikeColor[2]=0.0;
    startMenu();
    
//    time(&initial_time);
    FsPassedTime();
    int diff = 0;
    for(;;)
    {
        
        FsPollDevice();
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        Grid();
        
        int key=FsInkey();
        
        if (key==FSKEY_ESC || helpMenuState==1 || PlayerState==1){
            gameOver();
            break;
        }
        
        if (CompState==1){
            win();
            break;
        }
        
        
        comp1.dispLives(comp1,20,50);
        comp1.streak(comp1.streakColor);
        comp1.bikeDraw(comp1.bikeColor);
        
        player1.dispLives(player1,650, 50);
        player1.streak(player1.streakColor);
        player1.bikeDraw(player1.bikeColor);
        player1.Move(key, PlayerState, player1);
        
        
        
        unsigned int passed=FsPassedTime();
        diff+=passed;
        comp1.MoveComp(CompState, player1 , diff);
        
        DrawNCheck(player1, comp1);
        
        helpMenu(key);
        
        FsSwapBuffers();
        
        FsSleep(10);
        
    }
    
}