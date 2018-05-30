#include <stdio.h>
#include "fssimplewindow.h"
#include <math.h>
#include <list>
#include <vector>
#include <ctime>
#include "ysglfontdata.h"
#include "yspng.h"
#include <string>
#include "pacman.h"

int numx = 25;
int numy = 22;
int sizex = 800;
int sizey = 600;
bool moveleft = false;
bool moveright = false;
bool moveup = false;
bool movedown = false;
unsigned int passed = FsPassedTime();
unsigned int oldpassed = 0;
unsigned int oldpassed2 = 0;
double duration;
int delay = 240;
int score = 0;

int amount = 0;
int val = 0;
int openclose = 1;
int mov = 0;
int redtar = 18;
int pinktar = 1;
int pinkdir = 0;
int tealdir = 0;
int orangedir = 0;
int tealtar = 27;
int j = 0;
long strt = FsSubSecondTimer();
int num = 0;

void Drawboundaries(int x1,int y1,int x2,int y2,int fill)
{
    glColor3ub(0,0,0);
    if(0!=fill)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    
    glVertex2i(x1,y1);
    glVertex2i(x2,y1);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);
    
    glEnd();
}

void DrawCircle(int cx,int cy,int r)
{
    glColor3ub(0,0,255);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<=64; ++i)
    {
        const double pi=3.14159265;
        double angle=(double)i*pi/32.0;
        double c=cos(angle);
        double s=sin(angle);
        glVertex2d((double)cx+c*r,(double)cy+s*r);
    }
    glEnd();
}

void pacman::drawright() {
    int r=sizey/numy/2;
    glColor3ub(204,204,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x,y);
    for(int i=30; i<=330; ++i)
    {
        const double pi=3.14159265;
        double angle=(double)i*pi/180;
        double c=cos(angle);
        double s=sin(angle);
        glVertex2d((double)x+c*r,(double)y+s*r);
    }
    
    glEnd();
}

void pacman::drawleft() {
    int r=sizey/numy/2;
    glColor3ub(204,204,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x,y);
    for(int i=210; i<=510; ++i)
    {
        const double pi=3.14159265;
        double angle=(double)i*pi/180;
        double c=cos(angle);
        double s=sin(angle);
        glVertex2d((double)x+c*r,(double)y+s*r);
    }
    
    glEnd();
}

void pacman::drawdown() {
    int r=sizey/numy/2;
    glColor3ub(204,204,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x,y);
    for(int i=120; i<=420; ++i)
    {
        const double pi=3.14159265;
        double angle=(double)i*pi/180;
        double c=cos(angle);
        double s=sin(angle);
        glVertex2d((double)x+c*r,(double)y+s*r);
    }
    
    glEnd();
}

void pacman::drawup() {
    int r=sizey/numy/2;
    glColor3ub(204,204,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x,y);
    for(int i=300; i<=600; ++i)
    {
        const double pi=3.14159265;
        double angle=(double)i*pi/180;
        double c=cos(angle);
        double s=sin(angle);
        glVertex2d((double)x+c*r,(double)y+s*r);
    }
    
    glEnd();
}

void pacman::drawvoid() {
    int r=sizey/numy/2;
    glColor3ub(204,204,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x,y);
    for(int i=0; i<=360; ++i)
    {
        const double pi=3.14159265;
        double angle=(double)i*pi/180;
        double c=cos(angle);
        double s=sin(angle);
        glVertex2d((double)x+c*r,(double)y+s*r);
    }
    
    glEnd();
}

void coins::draw() {
    DrawCircle(x,y,sizey/numy/6);
}

void coins::SetCoins(int x0, int y0) {
    state = 1;
    x = x0;
    y = y0;
}




ghost::ghost(double initx, double inity){
    x = initx;
    y = inity;
    i = (x/sizex)*numx;
    j = (y/sizey)*numy;
}

void ghost::draw(int red,int green, int blue) {
    double r=sizey/numy/2;
    glColor3ub(red,green,blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x,y);
    for(int i=180; i<=360; ++i)
    {
        const double pi=3.14159265;
        double angle=(double)i*pi/180;
        double c=cos(angle);
        double s=sin(angle);
        glVertex2d((double)x+c*r,(double)y+s*r);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(x-r,y);
    glVertex2d(x-r,y+r);
    glVertex2d(x-(3*r/4),y+(2*r/3));
    glVertex2d(x-(2*r/4),y+r);
    glVertex2d(x-(1*r/4),y+(2*r/3));
    glVertex2d(x,y+r);
    glVertex2d(x+(1*r/4),y+(2*r/3));
    glVertex2d(x+(2*r/4),y+r);
    glVertex2d(x+(3*r/4),y+(2*r/3));
    glVertex2d(x+r,y+r);
    glVertex2d(x+r,y);
    glVertex2d(x-r,y);
    glEnd();
}

int CharBitmap::dir(int i,int j, int itar, int jtar) {
    int dest = ((jtar*numx) + itar);
    int pos = (j*numx)+i;
    int visited[1000];
    for(int q = 0;q<(numx*numy);q++){
        visited[q] = 0;
        if(dat[q]== '1' || dat[q]== ',' || dat[q]== '3') {
            visited[q] = -1;
        }
    }
    std::list<int> queue;
    queue.push_back(pos);
    std::vector<int> path[1000];
    
    while(queue.size() != 0) {
        if(pos == dest) {
            return pos;
        }
        pos = queue.front();
        queue.pop_front();
        path[pos].push_back(pos);
        if(dat[pos+1] == '2' || dat[pos+1] == '.') {
            if(visited[pos + 1] == 0) {
                queue.push_back(pos + 1);
                visited[pos+1] = pos;
                for(int i = 0; i < path[pos].size();i++) {
                    path[pos+1].push_back(path[pos].at(i));
                }
            }
        }
        if(dat[pos-1] == '2' || dat[pos-1] == '.') {
            if(visited[pos-1] == 0) {
                queue.push_back(pos - 1);
                visited[pos-1] = pos;
                for(int i = 0; i < path[pos].size();i++) {
                    path[pos-1].push_back(path[pos].at(i));
                }
            }
        }
        if(dat[pos + numx] == '2' || dat[pos + numx] == '.') {
            if(visited[pos+numx] == 0) {
                queue.push_back(pos + numx);
                visited[pos+numx] = pos;
                for(int i = 0; i < path[pos].size();i++) {
                    path[pos+numx].push_back(path[pos].at(i));
                }
            }
        }
        if(dat[pos - numx] == '2' || dat[pos - numx] == '.') {
            if(visited[pos-numx] == 0) {
                queue.push_back(pos - numx);
                visited[pos-numx] = pos;
                for(int i = 0; i < path[pos].size();i++) {
                    path[pos-numx].push_back(path[pos].at(i));
                }
            }
        }
        if(pos == dest) {
            break;
        }
    }
    
    if(path[pos].size()>0) {
    return path[pos].at(1);
    } else {
        return pos;
    }
}

int CharBitmap::move(int retval, int key) {
    val = retval;
    pac.i = (pac.x/sizex)*numx;
    pac.j = (pac.y/sizey)*numy;
    int pos = (pac.j*numx)+pac.i;
    FsPollDevice();
    passed = FsPassedTime();
    oldpassed += passed;
    oldpassed2 += passed;
    int direction = 0;
    if(duration <= 14000) {
        pinkdir = pinkghostInit();
        if (pinkdir == 0) {
            pinkdir = dir(pinkGH.i,pinkGH.j,pinktar,1);
        }
        //scatter for 7
        direction = dir(redGH.i,redGH.j,redtar,1);
        if(redtar == 24) {
            redtar = 18;
        }
        if(pinktar == 6) {
            pinktar = 1;
        }
    }
    else if(duration > 14000 && duration <= 34000 ) {
        //chase for 20
        direction = dir(redGH.i,redGH.j,pac.i,pac.j);
        int increm = 0;
        if(moveright == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm++;
            }
            if((pac.j)*numx+pac.i+4+increm > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i+4+increm,pac.j);
        }
        else if(moveleft == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j)*numx+pac.i-4+increm > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i-4+increm,pac.j);
        }
        else if(movedown == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm--;
            }
            if((pac.j+4+increm*numx)+pac.i > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j+4+increm);
        }
        else if(moveup == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j-4+increm*numx)+pac.i > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j-4+increm);
        }
        else {
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j);
        }
    }
    else if(duration > 34000 && duration <= 44000 ) {
        //scatter for 7
        direction = dir(redGH.i,redGH.j,redtar,1);
        pinkdir = dir(pinkGH.i,pinkGH.j,pinktar,1);
        if(mov % 10 == 0) {
            redtar++;
        }
        if(redtar == 24) {
            redtar = 18;
        }
        if(pinktar == 6) {
            pinktar = 1;
        }
    }
    else if(duration > 44000 && duration <= 64000 ) {
        //chase for 20
        direction = dir(redGH.i,redGH.j,pac.i,pac.j);
        int increm = 0;
        if(moveright == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm++;
            }
            if((pac.j)*numx+pac.i+4+increm > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i+4+increm,pac.j);
        }
        else if(moveleft == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j)*numx+pac.i-4+increm > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i-4+increm,pac.j);
        }
        else if(movedown == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm--;
            }
            if((pac.j+4+increm*numx)+pac.i > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j+4+increm);
        }
        else if(moveup == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j-4+increm*numx)+pac.i > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j-4+increm);
        }
        else {
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j);
        }
    }
    else if(duration > 64000 && duration <= 70000 ) {
        //scatter for 5
        direction = dir(redGH.i,redGH.j,redtar,1);
        pinkdir = dir(pinkGH.i,pinkGH.j,pinktar,1);
        if(mov % 10 == 0) {
            redtar++;
        }
        if(redtar == 24) {
            redtar = 18;
        }
        if(pinktar == 6) {
            pinktar = 1;
        }
    }
    else if(duration > 70000 && duration <= 90000 ) {
        //chase for 20
        direction = dir(redGH.i,redGH.j,pac.i,pac.j);
        int increm = 0;
        if(moveright == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm++;
            }
            if((pac.j)*numx+pac.i+4+increm > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i+4+increm,pac.j);
        }
        else if(moveleft == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j)*numx+pac.i-4+increm > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i-4+increm,pac.j);
        }
        else if(movedown == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm--;
            }
            if((pac.j+4+increm*numx)+pac.i > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j+4+increm);
        }
        else if(moveup == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j-4+increm*numx)+pac.i > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j-4+increm);
        }
        else {
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j);
        }
    }
    else if(duration > 90000 && duration <= 95000 ) {
        //scatter for 5
        direction = dir(redGH.i,redGH.j,redtar,1);
        pinkdir = dir(pinkGH.i,pinkGH.j,pinktar,1);
        if(mov % 10 == 0) {
            redtar++;
        }
        if(redtar == 24) {
            redtar = 18;
        }
        if(pinktar == 6) {
            pinktar = 1;
        }
    }
    else {
        //chase
        direction = dir(redGH.i,redGH.j,pac.i,pac.j);
        int increm = 0;
        if(moveright == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm++;
            }
            if((pac.j)*numx+pac.i+4+increm > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i+4+increm,pac.j);
        }
        else if(moveleft == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j)*numx+pac.i-4+increm > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i-4+increm,pac.j);
        }
        else if(movedown == true) {
            while(dat[(pac.j*numx)+pac.i+4+increm] == ',' || dat[(pac.j*numx)+pac.i+4+increm] == '1' || dat[(pac.j*numx)+pac.i+4+increm] == '3') {
                increm--;
            }
            if((pac.j+4+increm*numx)+pac.i > numx*numy) {
                increm = -4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j+4+increm);
        }
        else if(moveup == true) {
            while(dat[(pac.j*numx)+pac.i-4+increm] == ',' || dat[(pac.j*numx)+pac.i-4+increm] == '1' || dat[(pac.j*numx)+pac.i-4+increm] == '3') {
                increm--;
            }
            if((pac.j-4+increm*numx)+pac.i > numx*numy) {
                increm = +4;
            }
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j-4+increm);
        }
        else {
            pinkdir = dir(pinkGH.i,pinkGH.j,pac.i,pac.j);
        }
    }
    if(findnum() < 250) {
        int potdir = tealghostInit();
        if (potdir != 0) {
            tealdir = potdir;
        } else {
            int found = 0;
            if(tealtar == (tealGH.j*numx+tealGH.i)) {
                for(int i = j+1;i < wid*hei;i++) {
                    if(dat[i] == '.' || dat[i] == '2') {
                        if(found == 0) {
                            tealtar = i;
                            found = i;
                            j++;
                        }
                    }
                }
            }
            potdir = tealtar;
            int tealGHnextI = potdir % numx;
            int tealGHnextJ = (potdir - (potdir % numx)) / numx;
            tealdir = dir(tealGH.i,tealGH.j,tealGHnextI,tealGHnextJ);
            if(j >= (wid*hei) - 30) {
                j = 0;
            }
        }
    }
    
    if(findnum() < 100) {
        int potdir = orangeghostInit();
        if (potdir != 0) {
            orangedir = potdir;
        } else {
            orangedir = dir(orangeGH.i,orangeGH.j,pac.i,pac.j);
        }
    }
    
    int tealGHnextI = tealdir % numx;
    int tealGHnextJ = (tealdir - (tealdir % numx)) / numx;
    int tealGHnextx = ((double) sizex/numx)*tealGHnextI + (sizex/numx)/2;
    int tealGHnexty = ((double) sizey/numy)*tealGHnextJ + (sizey/numy)/2;
    
    int pinkGHnextI = pinkdir % numx;
    int pinkGHnextJ = (pinkdir - (pinkdir % numx)) / numx;
    int pinkGHnextx = ((double) sizex/numx)*pinkGHnextI + (sizex/numx)/2;
    int pinkGHnexty = ((double) sizey/numy)*pinkGHnextJ + (sizey/numy)/2;
    
    int redGHnextI = direction % numx;
    int redGHnextJ = (direction - (direction % numx)) / numx;
    int redGHnextx = ((double) sizex/numx)*redGHnextI + (sizex/numx)/2;
    int redGHnexty = ((double) sizey/numy)*redGHnextJ + (sizey/numy)/2;
    
    int orangeGHnextI = orangedir % numx;
    int orangeGHnextJ = (orangedir - (orangedir % numx)) / numx;
    int orangeGHnextx = ((double) sizex/numx)*orangeGHnextI + (sizex/numx)/2;
    int orangeGHnexty = ((double) sizey/numy)*orangeGHnextJ + (sizey/numy)/2;
    
    if(oldpassed2 > delay) {
        oldpassed2 = 0;
        mov++;
        if(mov % 3 == 0) {
            redtar++;
            pinktar++;
            redGH.x = redGHnextx;
            redGH.y = redGHnexty;
            redGH.i = redGHnextI;
            redGH.j = redGHnextJ;
            pinkGH.x = pinkGHnextx;
            pinkGH.y = pinkGHnexty;
            pinkGH.i = pinkGHnextI;
            pinkGH.j = pinkGHnextJ;
        }
        if(findnum() < 250) {
            tealGH.x = tealGHnextx;
            tealGH.y = tealGHnexty;
            tealGH.i = tealGHnextI;
            tealGH.j = tealGHnextJ;
        }
        if(mov % 4 == 0) {
            if(findnum() < 100) {
                orangeGH.x = orangeGHnextx;
                orangeGH.y = orangeGHnexty;
                orangeGH.i = orangeGHnextI;
                orangeGH.j = orangeGHnextJ;
            }
        }
    }
    if(moveleft == true && oldpassed > delay) {
        oldpassed = 0;
        if(pac.i == 0) {
            pac.x = (sizex + ((sizex/numx)/2));
            pac.i = (pac.x/sizex)*numx;
            pac.j = (pac.y/sizey)*numy;
        }
        if(dat[(pac.j*numx)+pac.i - 1] == '1' || dat[(pac.j*numx)+pac.i - 1] == ',' || dat[(pac.j*numx)+pac.i - 1] == '3') {
            moveleft = false;
        }
        if(moveleft== true) {
            amount++;
            if(dat[pos] != '1') {
                dat[pos] = '2';
            }
            if(amount % 2 != 0) {
                pac.x -= (sizex/numx);
            }
        }
        if(amount % 2 != 0) {
            val = 2;
        } else {
            val = 1;
        }
    }
    if(moveright == true && oldpassed > delay) {
        oldpassed = 0;
        if(pac.i == numx - 1) {
            pac.x = (-(sizex/numx)/2 );
            pac.i = (pac.x/sizex)*numx;
            pac.j = (pac.y/sizey)*numy;
            int pos = (pac.j*numx)+pac.i;
            dat[pos] = '2';
        }
        if(dat[(pac.j*numx)+pac.i + 1 ] == '1' || dat[(pac.j*numx)+pac.i + 1] == ',' || dat[(pac.j*numx)+pac.i + 1 ] == '3') {
            moveright = false;
        }
        if(moveright== true) {
            amount++;
            dat[pos] = '2';
            if(amount % 2 != 0){
                pac.x += (sizex/numx);
            }
        }
        if(amount % 2 != 0) {
            val = 0;
        } else {
            val = 1;
        }
    }
    if(moveup == true && oldpassed > delay) {
        oldpassed = 0;
        if(dat[(pac.j*numx)+pac.i - numx] == '1' || dat[(pac.j*numx)+pac.i - numx] == ',' || dat[(pac.j*numx)+pac.i - numx] == '3') {
            moveup = false;
        }
        if(moveup== true) {
            amount++;
            dat[pos] = '2';
            if(amount % 2 != 0) {
                pac.y -= (sizey/numy);
            }
        }
        if(amount % 2 != 0) {
            val = 3;
        } else {
            val = 1;
        }
    }
    if(movedown == true && oldpassed > delay) {
        oldpassed = 0;
        if(dat[(pac.j*numx)+pac.i + numx] == '1' || dat[(pac.j*numx)+pac.i + numx] == ',' || dat[(pac.j*numx)+pac.i + numx] == '3') {
            movedown = false;
        }
        if(movedown== true) {
            amount++;
            dat[pos] = '2';
            if(amount % 2 != 0){
                pac.y += (sizey/numy);
            }
        }
        if(amount % 2 != 0) {
            val = 4;
        } else {
            val = 1;
        }
    }
    if(FSKEY_LEFT==key)
    {
        
        if(dat[(pac.j*numx)+pac.i - 1] != '1' && dat[(pac.j*numx)+pac.i - 1] != ',' && dat[(pac.j*numx)+pac.i - 1] != '3' && pac.i < numx && pac.i > 0) {
            moveright = false;
            moveup = false;
            movedown = false;
            moveleft = true;
        }
    }
    if(FSKEY_RIGHT==key)
    {
        if(dat[(pac.j*numx)+pac.i + 1 ] != '1' && dat[(pac.j*numx)+pac.i + 1] != ',' && dat[(pac.j*numx)+pac.i + 1 ] != '3' && pac.i < numx && pac.i > 0) {
            moveleft = false;
            moveup = false;
            movedown = false;
            moveright = true;
        }
    }
    if(FSKEY_UP==key)
    {
        if(dat[(pac.j*numx)+pac.i - numx] != '1' && dat[(pac.j*numx)+pac.i - numx] != ',' && dat[(pac.j*numx)+pac.i - numx] != '3') {
            moveleft = false;
            moveright = false;
            movedown = false;
            moveup = true;
        }
    }
    if(FSKEY_DOWN==key)
    {
        if(dat[(pac.j*numx)+pac.i + numx] != '1' && dat[(pac.j*numx)+pac.i + numx] != ',' && dat[(pac.j*numx)+pac.i + numx] != '3') {
            moveleft = false;
            moveright = false;
            moveup = false;
            movedown = true;
        }
    }
    return val;
}
int CharBitmap::pinkghostInit() {
    if(dat[(pinkGH.j*numx)+pinkGH.i] == ',') {
        if(oldpassed2 > delay && mov % 3 == 0){
            pinkGH.y -= (sizey/numy);
            pinkGH.j = (pinkGH.y/sizey)*numy;
        }
        return (pinkGH.j*numx)+pinkGH.i;
    }
    return 0;
}

int CharBitmap::tealghostInit() {
    if(dat[(tealGH.j*numx)+tealGH.i] == ',') {
        if(oldpassed2 > delay){
            if(tealGH.i == 11) {
                tealGH.x += (sizex/numx);
                tealGH.i = (tealGH.x/sizex)*numx;
            } else {
                tealGH.y -= (sizey/numy);
                tealGH.j = (tealGH.y/sizey)*numy;
            }
        }
        return (tealGH.j*numx)+tealGH.i;
    }
    return 0;
}

int CharBitmap::orangeghostInit() {
    if(dat[(orangeGH.j*numx)+orangeGH.i] == ',') {
        if(oldpassed2 > delay && mov % 3 == 0){
            if(orangeGH.i == 13) {
                orangeGH.x -= (sizex/numx);
                orangeGH.i = (orangeGH.x/sizex)*numx;
            } else {
                orangeGH.y -= (sizey/numy);
                orangeGH.j = (orangeGH.y/sizey)*numy;
            }
        }
        return (orangeGH.j*numx)+orangeGH.i;
    }
    return 0;
}

CharBitmap::CharBitmap() :
redGH((double)sizex/2,(double) (sizey/numy)*8 + (sizey/numy)/2),
pinkGH((double)((sizex/2)),(double) (sizey/numy)*10 + (sizey/numy)/2),
tealGH((double) (sizex/numx)*11 + (sizex/numx)/2,(double) (sizey/numy)*10 + (sizey/numy)/2),
orangeGH((double) (sizex/numx)*13 + (sizex/numx)/2,(double) (sizey/numy)*10 + (sizey/numy)/2)
{
    dat = nullptr;
    wid = 0;
    hei = 0;
}
CharBitmap::~CharBitmap()
{
    CleanUp();
}
void CharBitmap::CleanUp(void)
{
    if(nullptr!=dat)
    {
        delete [] dat;
        dat=nullptr;
        wid=0;
        hei=0;
    }
}

void CharBitmap::SetBitmap(int bmpWid,int bmpHei,char bmp[])
{
    FsPassedTime();
    wid = bmpWid;
    hei = bmpHei;
    dat = new char [wid*hei];
    coin = new coins [wid*hei];
    for(int i = 0; i < hei; i++) {
        for(int j = 0; j < wid; j++) {
            int pos = (i*wid)+j;
            dat[pos] = bmp[pos];
        }
    }
}
void CharBitmap::SetPixel(int x,int y,char c)
{
    if(nullptr!=dat) {
        if(y > hei) {
            return;
        }
        if(x > wid) {
            return;
        }
        int pos = (y*wid)+x;
        dat[pos] = c;
    }
}
void CharBitmap::Print(void)
{
    int x,y;
    for(y=0; y<hei; y++)
    {
        for(x=0; x<wid; x++)
        {
            printf("%c",GetPixel(x,y));
        }
        printf("\n");
    }
}



void CharBitmap::Draw(int key)
{
    for(int i = 0; i < hei; i++) {
        for(int j = 0; j < wid; j++) {
            int pos = (i*wid)+j;
            double wid2 = wid*wid;
            double hei2 = hei*hei;
            if(dat[pos] == '1'){
                int x1 = ((j*wid)/wid2)*sizex;
                int y1 = ((i*hei)/hei2)*sizey;
                int x2 = (((j+1)*wid)/wid2)*sizex;
                int y2 = (((i+1)*hei)/hei2)*sizey;
                glColor3ub(0,0,0);
                glBegin(GL_QUADS);
                glVertex2i(x1,y1);
                glVertex2i(x2,y1);
                glVertex2i(x2,y2);
                glVertex2i(x1,y2);
                
                glEnd();
            }
            if(dat[pos] == '3'){
                int x1 = ((j*wid)/wid2)*sizex;
                int y1 = ((i*hei)/hei2)*sizey;
                int x2 = (((j+1)*wid)/wid2)*sizex;
                int y2 = (((i+1)*hei)/hei2)*sizey;
                glColor3ub(255,0,0);
                glBegin(GL_QUADS);
                glVertex2i(x1,y1);
                glVertex2i(x2,y1);
                glVertex2i(x2,y2);
                glVertex2i(x1,y2);
                
                glEnd();
            }
            if(dat[pos] == '.'){
                double incx = (sizex/numx)/2;
                double incy = (sizey/numy)/2;
                coin[pos].SetCoins((((j*wid)/wid2)*sizex + incx),(((i*hei)/hei2)*sizey)+ incy);
                coin[pos].draw();
            }
        }
    }
    int r = move(openclose,key);
    openclose = r;
    if (r == 0) {
        pac.drawright();
    } else if(r == 1) {
        pac.drawvoid();
    } else if(r == 2) {
        pac.drawleft();
    } else if(r == 3) {
        pac.drawup();
    } else if(r == 4) {
        pac.drawdown();
    }
    redGH.draw(255,0,0);
    pinkGH.draw(255,0,255);
    orangeGH.draw(255,128,0);
    tealGH.draw(0,255,255);
    glColor3ub(255,255,0);
    glRasterPos2d((sizex/numx)*1,(sizey/numy)*.75);
    score = (262 - findnum())*10;
    std::string s = std::to_string(score);
    char const *pchar = s.c_str();
    YsGlDrawFontBitmap12x16("score: ");
    glRasterPos2d((sizex/numx)*3.25,(sizey/numy)*.75);
    YsGlDrawFontBitmap12x16(pchar);
    glRasterPos2d((sizex/numx)*15.75,(sizey/numy)*.75);
    YsGlDrawFontBitmap12x16("press h for help/pause");
}

char CharBitmap::GetPixel(int x,int y)
{
    if(0<=x && x<wid && 0<=y && y<hei)
    {
        return dat[y*wid+x];
    }
    return 0;
}

const int CharBitmap::width(void) const
{
    return wid;
}

const int CharBitmap::height(void) const
{
    return hei;
}

const char *CharBitmap::data(void) const
{
    if(nullptr!=dat)
    {
        return dat;
    }
    return nullptr;
}

CharBitmap::CharBitmap(const CharBitmap &incoming) :
redGH((double)sizex/2,(double) (sizey/numy)*8 + (sizey/numy)/2),
pinkGH((double)((sizex/2)),(double) (sizey/numy)*10 + (sizey/numy)/2),
tealGH((double) (sizex/numx)*11 + (sizex/numx)/2,(double) (sizey/numy)*10 + (sizey/numy)/2),
orangeGH((double) (sizex/numx)*13 + (sizex/numx)/2,(double) (sizey/numy)*10 + (sizey/numy)/2)
{
    dat=nullptr;
    Set(incoming.data(),incoming.width(),incoming.height());
}

CharBitmap &CharBitmap::operator=(const CharBitmap &incoming)
{
    Set(incoming.data(),incoming.width(),incoming.height());
    return *this;
}

void CharBitmap::Set(const char *incoming,const int width,const int height) {
    if(incoming!=dat)
    {
        CleanUp();
        dat = new char [width*height];
        hei = height;
        wid = width;
        for(int i = 0; i < hei; i++) {
            for(int j = 0; j < wid; j++) {
                int pos = (i*wid)+j;
                dat[pos] = incoming[pos];
            }
        }
    }
}

int CharBitmap::findnum() {
    int num = 0;
    for(int i = 0;i<wid*hei;i++) {
        if(dat[i] == '.') {
            num++;
        }
    }
    return num;
}

int CharBitmap::play() {
    pac.x = sizex/2;
    pac.y = ((double) sizey/numy)*12 + (sizey/numy)/2;
    strt = FsSubSecondTimer();
    char pattern[]=
    {
        "1111111111111111111111111"
        "1......1.........1......1"
        "1.1111.1.1111111.1.1111.1"
        "1....1......1......1....1"
        "1111.1.1111.1.1111.1.1111"
        "1......1.........1......1"
        "1.1111.1.1111111.1.1111.1"
        "1.1111.1.1111111.1.1111.1"
        "1.......................1"
        "1111.111.333,333.111.1111"
        ".......1.3,,,,,3.1......."
        "1111.1.1.3333333.1.1.1111"
        "1....1.............1....1"
        "1.111111.1111111.111111.1"
        "1...........1...........1"
        "111111.1.11.1.11.1.111111"
        "1........11...11........1"
        "1.111111.11.1.11.111111.1"
        "1......1....1....1......1"
        "1.1111.1.1111111.1.1111.1"
        "1.......................1"
        "1111111111111111111111111"
    };
    
    SetBitmap(numx,numy,pattern);
    YsRawPngDecoder png;
    YsRawPngDecoder png2;
    if(YSOK==png.Decode("menu.png"))
    {
        png.Flip();
    }
    else
    {
        printf("Cannot open file.\n");
    }
    if(YSOK==png2.Decode("instructions.png"))
    {
        png2.Flip();
    }
    else
    {
        printf("Cannot open file.\n");
    }
    auto key=FsInkey();
    for(;;) {
        FsPollDevice();
        auto key=FsInkey();
        
        
        int winWid,winHei;
        FsGetWindowSize(winWid,winHei);
        glRasterPos2d(0.0,(double)(winHei-1));
        glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
        FsSwapBuffers();
        FsSleep(100);
        if(FSKEY_ESC == key) {
            goto loopout;
        }
        if(FSKEY_ENTER == key) {
            goto start;
        }
    }
    for(;;)
    {
    start:
        FsPollDevice();
        key=FsInkey();
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        Draw(key);
        
        if(FSKEY_H==key) {
            for(;;) {
                FsPollDevice();
                auto key=FsInkey();
                int winWid,winHei;
                FsGetWindowSize(winWid,winHei);
                glRasterPos2d(0.0,(double)(winHei-1));
                glDrawPixels(png2.wid,png2.hei,GL_RGBA,GL_UNSIGNED_BYTE,png2.rgba);
                FsSwapBuffers();
                FsSleep(100);
                if(FSKEY_R==key) {
                    goto endloop;
                }
                if(FSKEY_ESC == key) {
                    goto loopout;
                }
            }
        }
    endloop:
        if(findnum() == 0) {
            for(;;) {
                glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
                Draw(key);
                moveup = false;
                moveleft = false;
                movedown = false;
                moveright=  false;
                glColor3ub(0,0,0);
                glRasterPos2d(sizex/2 - ((sizex/numx)*2.5),sizey/2);
                YsGlDrawFontBitmap20x32("You Won!");
                FsSwapBuffers();
                FsSleep(100);
                passed = FsPassedTime();
                oldpassed += passed;
                if(oldpassed > 1000) {
                    goto loopout;
                }
            }
        }
        if((pac.i*wid) + pac.j == ((redGH.i*wid) + redGH.j) ||
           (pac.i*wid) + pac.j == ((pinkGH.i*wid) + pinkGH.j) ||
           (pac.i*wid) + pac.j == ((orangeGH.i*wid) + orangeGH.j) ||
           (pac.i*wid) + pac.j == ((tealGH.i*wid) + tealGH.j)) {
            for(;;) {
                glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
                Draw(key);
                moveup = false;
                moveleft = false;
                movedown = false;
                moveright=  false;
                glColor3ub(0,0,0);
                glRasterPos2d(sizex/2- ((sizex/numx)*2.5),sizey/2);
                YsGlDrawFontBitmap20x32("You Lost");
                FsSwapBuffers();
                FsSleep(100);
                passed = FsPassedTime();
                oldpassed += passed;
                if(oldpassed > 1000) {
                    goto loopout;
                }
            }
        }
        duration = FsSubSecondTimer() - strt;
        
        FsSwapBuffers();
        
        FsSleep(10);
        if(FSKEY_ESC==key) {
        loopout:
            break;
        }
    }
    return score;
}



