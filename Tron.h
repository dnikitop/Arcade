
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

