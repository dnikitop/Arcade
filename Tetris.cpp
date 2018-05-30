//
//  Tetris.cpp
//  Tetris_2
//
//  Created by Rahul Raina on 11/19/17.
//  Copyright © 2017 CMU. All rights reserved.
//

#include "Tetris.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fssimplewindow.h"
#include <math.h>
#include "ysglfontdata.h"

#define Size_1 4
#define Size_2 9
#define Size_3 16
#define YMAX 600
#define XMAX 240
#define Box_W 560
#define STEP 20
#define X_START 100
#define Y_START -20

// Piece ---------------------------------------------------------

Piece::Piece()
{
    str = NULL;
    size = 0;
    xstart = X_START;
    ystart = Y_START;
    state = 1;
    xLeft = 0;
    xRight = 0;
}

Piece::Piece(int length)
{
    size = length;
    str = new char[size];
    xstart = XMAX / 2;
    ystart = 0;
    state = 1;
    xLeft = 0;
    xRight = 0;
    
}

void Piece::Set(int length)
{
    if(str != NULL)
    {
        Cleanup();
    }
    
    size = length;
    str = new char[size];
}

Piece::~Piece()
{
    Cleanup();
}

void Piece:: Cleanup()
{
    if(str != NULL)
    {
        delete [] str;
    }
    size = 0;
    xstart = 0;
    ystart = 0;
    state = 0;
    xLeft = 0;
    xRight = 0;
    
}

void Piece::DrawPiece(int x, int y,int r, int g, int b)
{
    glColor3ub(r,g,b);
    glBegin(GL_QUADS);
    glVertex2i(x,y);
    glVertex2i((x+STEP),y);
    glVertex2i((x+STEP),(y+STEP));
    glVertex2i(x,(y+STEP));
    glEnd();
    
    
    glColor3ub(0,0,0);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i((x+STEP),y);
    
    glBegin(GL_LINES);
    glVertex2i((x+STEP),y);
    glVertex2i((x+STEP),(y+STEP));
    
    glBegin(GL_LINES);
    glVertex2i((x+STEP),(y+STEP));
    glVertex2i(x,(y+STEP));
    
    glBegin(GL_LINES);
    glVertex2i(x,(y+STEP));
    glVertex2i(x,y);
    glEnd();
}

void Piece::Draw(int r, int g, int b)
{
    if(str == NULL)
        return;
    
    for(int i = 0; i < size; i++)
    {
        if(str[i] == '1')
        {
            int a = i % (int)sqrt((double)size);
            int b = i / (int)sqrt((double)size);
            int x = (a * STEP) + xstart;
            int y = (b * STEP) + ystart;
            
            DrawPiece(x,y,r,g,b);
            
        }
    }
}


void Piece::Create() // create a piece (1 of 5 options, chosen randomly).
{
    
    int number = rand()%5;
    
    switch(number)
    {
        case 0:
        {
            char Z[] =
            {
                "11."
                ".11"
                "..."
            };
            
            Set(Size_2);
            
            for(int i = 0; i < size; i++)
            {
                str[i] = Z[i];
            }
            
            break;
        }
        case 1:
        {
            char L[]=
            {
                "111"
                "..1"
                "..."
            };
            Set(Size_2);
            
            for(int i = 0; i < size; i++)
            {
                str[i] = L[i];
            }
            
            break;
            
        }
        case 2:
        {
            char T[]=
            {
                "111"
                ".1."
                "..."
            };
            Set(Size_2);
            
            for(int i = 0; i < size; i++)
            {
                str[i] = T[i];
            }
            
            break;
            
        }
        case 3:
        {
            char Sq[]=
            {
                "11"
                "11"
            };
            
            Set(Size_1);
            
            for(int i = 0; i < size; i++)
            {
                str[i] = Sq[i];
            }
            
            break;
            
        }
        case 4:
        {
            char Line[]=
            {
                "1..."
                "1..."
                "1..."
                "1..."
            };
            
            Set(Size_3);
            
            for(int i = 0; i < size; i++)
            {
                str[i] = Line[i];
            }
            
            break;
            
        }
            
    }
    
    return;
    
}

int Piece::Height() // calculate the height of the piece and return the value.
{
    if(str == NULL)
    {
        return 0;
    }
    
    int wid = sqrt((double)size) ;
    int hei = sqrt((double)size);
    
    int height = 0;
    
    for(int y = 0; y < hei; y++)
    {
        for(int x = 0; x < wid; x++)
        {
            if(str[y*wid+x] == '1')
            {
                height = (y+1)*STEP;
            }
        }
    }
    
    return height;
}


int Piece::Width() // calculate the width of the piece and return the value.
{
    if(str == NULL)
    {
        return 0;
    }
    
    int wid = sqrt((double)size) ;
    int hei = sqrt((double)size);
    
    int width = 0;
    int i = 0;
    
    for(int x = 0; x < wid; x++)
    {
        for(int y = 0; y < hei; y++)
        {
            if(str[y*wid+x] == '1')
            {
                width = width + STEP;
                if(i == 0)
                    xLeft = xstart + ((x)*STEP);
                i = i + 1;
                break;
            }
        }
    }
    
    return width;
}


void Piece::Rotate() //rotate the piece 90 degrees clockwise
{
    if(str == NULL)
    {
        return;
    }
    
    int wid = sqrt((double)size) ;
    int hei = sqrt((double)size);
    
    char *temp = new char [size];
    
    for(int y = 0; y < hei; y++)
    {
        for(int x = 0; x < wid; x++)
        {
            int row = x;
            int col = (wid-1) - y;
            temp[row*wid+col] = str[y*wid+x];
        }
    }
    
    for(int i = 0; i < size; i++)
    {
        str[i] = temp[i];
    }
    
    delete [] temp;
    
}

// Board ---------------------------------------------------------

Board::Board()
{
    wid = (XMAX/STEP);
    hei = (YMAX/STEP);
    size = wid*hei;
    board = new char[size];
    red = new int[size];
    green = new int[size];
    blue = new int[size];
}
Board::~Board()
{
    ClearOut();
}

void Board::ClearOut()
{
    if(board != NULL)
    {
        delete [] board;
    }
    if(red != NULL)
    {
        delete [] red;
    }
    if(blue != NULL)
    {
        delete [] blue;
    }
    if(green != NULL)
    {
        delete [] green;
    }
    
    size = 0;
    wid = 0;
    hei = 0;
}

void Board::Initialize()
{
    if(board == NULL)
        return;
    
    for(int i = 0; i < size; i++)
    {
        board[i] = '.';
        red[i] = 0;
        green[i] = 0;
        blue[i] = 0;
    }
}

int Board::Check(int xstart, int ystart,char matrix[],int mat_size) // checks if board currently contains a value at given position
{
    if(board == NULL)
        return -1;
    
    int posx = xstart/STEP;
    int posy = ystart/STEP;
    int mwidth = sqrt((double)mat_size);
    int mheight = mwidth; // square matrix
    
    if(posy < 0)
    {
        return 0;
    }
    
    for(int x = posx; x < (posx+mwidth); x++)
    {
        for(int y = posy; y < (posy+mheight); y++)
        {
            if(board[y*wid+x] == '1' && matrix[(y-posy)*(mwidth)+(x-posx)] == '1')
            {
                return 1;
            }
        }
    }
    
    return 0;
    
}

void Board::Add(int xstart, int ystart,char matrix[],int mat_size,int r, int g, int b) // Adds the new piece to the board
{
    if(board == NULL)
    {
        return;
    }
    
    int posx = xstart/STEP;
    int posy = ystart/STEP;
    int mwidth = sqrt((double)mat_size);
    int mheight = mwidth; // square matrix
    
    for(int x = posx; x < (posx+mwidth); x++)
    {
        for(int y = posy; y < (posy+mheight); y++)
        {
            
            if(matrix[(y-posy)*(mwidth)+(x-posx)] == '1')
            {
                board[y*wid+x] = matrix[(y-posy)*(mwidth)+(x-posx)];
                red[y*wid+x] = r;
                green[y*wid+x] = g;
                blue[y*wid+x] = b;
            }
        }
    }
    
}

void Board::DrawBoard(int x, int y,int r, int g, int b)
{
    glColor3ub(r,g,b);
    glBegin(GL_QUADS);
    glVertex2i(x,y);
    glVertex2i((x+STEP),y);
    glVertex2i((x+STEP),(y+STEP));
    glVertex2i(x,(y+STEP));
    glEnd();
    
    
    glColor3ub(0,0,0);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i((x+STEP),y);
    
    glBegin(GL_LINES);
    glVertex2i((x+STEP),y);
    glVertex2i((x+STEP),(y+STEP));
    
    glBegin(GL_LINES);
    glVertex2i((x+STEP),(y+STEP));
    glVertex2i(x,(y+STEP));
    
    glBegin(GL_LINES);
    glVertex2i(x,(y+STEP));
    glVertex2i(x,y);
    glEnd();
}

void Board::Draw(int r, int g, int b) // Draw the board.
{
    if(board == NULL)
        return;
    
    for(int i = 0; i < size; i++)
    {
        if(board[i] == '1')
        {
            int a = i % wid;
            int b = i / wid;
            int x = (a * STEP);
            int y = (b * STEP);
            
            DrawBoard(x,y,red[i],green[i],blue[i]);
        }
    }
}

void Board::DrawGrid() // Inactive in the current game, but could be called if we chose.
{
    if(board == NULL)
        return;
    
    for(int i = 0; i < size; i++)
    {
        int a = i % wid;
        int b = i / wid;
        int x = (a * STEP);
        int y = (b * STEP);
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1,(GLushort)1010101010101010);
        
        glShadeModel(GL_SMOOTH);
        
        
        glColor3ub(0,0,0);
        glBegin(GL_LINES);
        glVertex2i(x,y);
        glVertex2i((x+STEP),y);
        
        glBegin(GL_LINES);
        glVertex2i((x+STEP),y);
        glVertex2i((x+STEP),(y+STEP));
        
        glBegin(GL_LINES);
        glVertex2i((x+STEP),(y+STEP));
        glVertex2i(x,(y+STEP));
        
        glBegin(GL_LINES);
        glVertex2i(x,(y+STEP));
        glVertex2i(x,y);
        glEnd();
        
        glDisable(GL_LINE_STIPPLE);
        
    }
}


// Tetris ---------------------------------------------------------

void Tetris::Draw_Box(int total_score, int pause, int over) // Draw the help box that is always displayed.
{
    
    int i = 1;
    int size = 0;
    
    while(true)
    {
        int x = total_score / i;
        
        if(x >= 1)
        {
            size = size+1;
            i = i*10;
        }
        else
            break;
    }
    
    i = i / 10;
    
    char *score = new char[size];
    int total = total_score;
    
    for(int i = 0; i < size; i++)
    {
        
        int remainder = total % 10;
        total = total / 10;
        
        score[size-i-1] = 48 + remainder;
        
    }
    
    
    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(XMAX,0);
    glVertex2i(XMAX+Box_W,0);
    glVertex2i(XMAX+Box_W,YMAX);
    glVertex2i(XMAX,YMAX);
    glEnd();
    
    glColor3ub(0,0,255);
    glRasterPos2d(XMAX + 10,20);
    YsGlDrawFontBitmap6x7("Welcome to Tetris!");
    glRasterPos2d(XMAX + 10,40);
    YsGlDrawFontBitmap6x7("Press 'H' for Help.");
    glRasterPos2d(XMAX + 10,50);
    YsGlDrawFontBitmap6x7("Press 'R' to Resume.");
    glRasterPos2d(XMAX + 10,60);
    YsGlDrawFontBitmap6x7("Press 'ESC' to Quit.");

    
    glRasterPos2d(XMAX + 10,100);
    if(pause == 1)
        YsGlDrawFontBitmap6x7("Game Paused?: Yes");
    else
        YsGlDrawFontBitmap6x7("Game Paused?: No");
    
    glRasterPos2d(XMAX + 10,120);
    YsGlDrawFontBitmap6x7("Current Score:");
    if(total_score == 0)
    {
        glRasterPos2d(XMAX + 10,130);
        YsGlDrawFontBitmap6x7("-");
        
    }
    else{
        glRasterPos2d(XMAX + 10,130);
        YsGlDrawFontBitmap6x7(score);
    }
    
    
    if(over == 0)
    {
        glRasterPos2d(XMAX + 10,150);
        YsGlDrawFontBitmap6x7("GAME OVER! Press 'ESC' to Quit.");
        
    }
    
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
    glVertex2i((XMAX+Box_W-Box_W/2),0);
    glVertex2i((XMAX+Box_W),0);
    glVertex2i((XMAX+Box_W),YMAX);
    glVertex2i((XMAX+Box_W-Box_W/2),YMAX);
    glEnd();
    
    delete [] score;
}


void Tetris::Draw_Help(int pause) // draw the help menu that is displayed when the game is paused.
{
    if(pause == 0)
    {
        return;
    }
    
    int x = 0;
    int y = YMAX/2-100;
    
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);
    glVertex2i(x,y);
    glVertex2i((x+XMAX+Box_W/2),y);
    glVertex2i((x+XMAX+Box_W/2),(y+300));
    glVertex2i(x,(y+300));
    glEnd();

    glColor3ub(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x,y);
    glVertex2i((x+XMAX+Box_W/2),y);
    glVertex2i((x+XMAX+Box_W/2),(y+300));
    glVertex2i(x,(y+300));
    glEnd();
    
    glColor3ub(0,0,255);
    glRasterPos2d(x+10,y+20);
    YsGlDrawFontBitmap6x7("Game Instructions:");
    glColor3ub(0,0,255);
    glRasterPos2d(x+10,y+40);
    YsGlDrawFontBitmap6x7("Fill up horizontal lines on the board using the falling pieces.");
    glRasterPos2d(x+10,y+60);
    YsGlDrawFontBitmap6x7("When a line is filled on the board, it is cleared and you score points!");
    glRasterPos2d(x+10,y+80);
    YsGlDrawFontBitmap6x7("To Move a Piece Left: Press Left");
    glRasterPos2d(x+10,y+100);
    YsGlDrawFontBitmap6x7("To Move a Piece Right: Press Right");
    glRasterPos2d(x+10,y+120);
    YsGlDrawFontBitmap6x7("To Move a Piece Down Faster: Press Down");
    glRasterPos2d(x+10,y+140);
    YsGlDrawFontBitmap6x7("To Rotate a Piece 90 deg clockwise: Press Up");
    glRasterPos2d(x+10,y+180);
    YsGlDrawFontBitmap6x7("Scoring Rubric:");
    glRasterPos2d(x+10,y+200);
    YsGlDrawFontBitmap6x7("Clearing 1 Line @ a time: 100 points");
    glRasterPos2d(x+10,y+220);
    YsGlDrawFontBitmap6x7("Clearing 2 Lines @ a time: 300 points");
    glRasterPos2d(x+10,y+240);
    YsGlDrawFontBitmap6x7("Clearing 3 Lines @ a time: 600 points");
    glRasterPos2d(x+10,y+260);
    YsGlDrawFontBitmap6x7("Clearing 4 Lines @ a time: 1000 points");
    glRasterPos2d(x+10,y+290);
    YsGlDrawFontBitmap6x7("Press R to go back to game.");

    return;
}


int Tetris::Play() // Play tetris. This is function that should be called in the main function.
{
    
    Board MyBoard;
    MyBoard.Initialize();
    
    int terminate = 0; // checks when to break out of cycle with a particular piece
    int over = 0; // checking game over
    int counter = 0; // ticker for each iteration
    int pause = 1; // when to pause and show the help menu on the screen (0 for game, 1 for help menu).
    int total_score = 0; // rolling counter showing the total score of the game
    int check = 0; // checks when previous pieces are hit or overlapped
    int color = 0; // flips through drawing pieces in red, green and yellow
    
    while(true) // outer loop that runs until ESC key is pressed by user.
    {
        Piece block;
        block.Create();
        terminate = 0;
        int yold = 0; // ystart on previous step
        
        color = color + 1;
        int red; int green; int blue;
        switch(color % 3) // setting the color for the current piece
        {
            case 0: // green
            {
                red = 0;
                green = 255;
                blue = 0;
                break;
            }
            case 1: // red
            {
                red = 255;
                green = 0;
                blue = 0;
                break;
            }
            case 2: // yellow
            {
                red = 255;
                green = 255;
                blue = 0;
                break;
            }
            default: // green
            {
                red = 0;
                green = 255;
                blue = 0;
            }
        }

        
        while(terminate == 0 && over == 0)
        {
            
            yold = block.ystart; // position that the piece is at before the next step
            
            FsPollDevice();
            int key = FsInkey();
            
            switch(key)
            {
                case FSKEY_H: // pause the game and enter the help menu
                {
                    if(pause == 0)
                        pause = 1;
                    break;
                }
                    
                case FSKEY_R: // exit the help menu and resume the game
                {
                    if(pause == 1)
                        pause = 0;
                    break;
                }
                    
                case FSKEY_ESC:
                {
                    terminate = 2;
                    break;
                }
                case FSKEY_UP:
                {
                    
                    if(pause == 0)
                    {
                        if(block.state == 1)
                        {
                            block.Rotate(); // rotate the piece
                            int w = block.Width(); // find the new width of the piece
                            
                            if((block.xLeft+w) > XMAX) // if the rotation moves the piece off the board on the right
                            {
                                block.xstart = XMAX - (w);
                                block.Width();
                                break;
                            }
                            
                            if (block.xLeft < 0) // if the rotation moves the piece off the board on the left
                            {
                                block.xstart = 0;
                                block.Width();
                                break;
                            }
                            
                            // check if the rotated piece overlaps another piece already on the board
                            check = MyBoard.Check(block.xstart,block.ystart,block.str,block.size);
                            if(check != 0) // dont rotate if there is already a piece there
                            {// rotate 270 degrees back to original position
                                block.Rotate();
                                block.Rotate();
                                block.Rotate();
                                block.Width();
                            }
                        }
                        
                        break;
                    }
                }
                case FSKEY_RIGHT:
                {
                    
                    if(pause == 0)
                    {
                        int width = block.Width();
                        
                        if((block.xLeft+width) == XMAX && block.state == 1 )
                        {
                            break;
                        }
                        
                        if(block.state == 1)
                        {
                            
                            block.xstart = block.xstart + STEP;
                            block.Width();
                            
                            check = MyBoard.Check(block.xstart,block.ystart,block.str,block.size);
                            if(check != 0) // dont move right if there is already a piece there
                            {
                                block.xstart = block.xstart - STEP;
                                block.Width();
                            }
                            
                            break;
                            
                        }
                    }
                }
                case FSKEY_LEFT:
                {
                    
                    if (pause == 0)
                    {
                        block.Width();
                        
                        if(block.xLeft == 0 && block.state == 1)
                        {
                            break;
                        }
                        
                        if(block.state == 1)
                        {
                            block.xstart = block.xstart - STEP;
                            block.Width();
                            
                            check = MyBoard.Check(block.xstart,block.ystart,block.str,block.size);
                            if(check != 0) // dont move left if there is already a piece there
                            {
                                block.xstart = block.xstart + STEP;
                                block.Width();
                            }
                            
                            break;
                        }
                    }
                    
                    
                }
                case FSKEY_DOWN: // move down 2 steps at a time
                {
                  if(pause == 0)
                  {
                      block.ystart = block.ystart + STEP;
                      yold = block.ystart;
                      
                      check = MyBoard.Check(block.xstart,block.ystart,block.str,block.size);
                      
                      if(check !=0) // if you overlap piece
                      {
                          block.ystart = block.ystart - STEP; // move one step up
                          yold = block.ystart;
                          break;
                      }
                      else // move another step down
                      {
                          block.ystart = block.ystart + STEP;
                          yold = block.ystart;
                          
                          // check if you overlap a piece again
                          check = MyBoard.Check(block.xstart,block.ystart,block.str,block.size);
                          if(check !=0) // if you overlap piece
                          {
                              block.ystart = block.ystart - STEP; // move one step up
                              yold = block.ystart;
                              break;
                          }
                          
                      }
                  }
                    
                    break;
                    
                }
                    
            }
            
            if(pause == 0)
            {
                counter = counter + 1; // if the game is currently in progress, iterate time counter
            }

            if(counter % STEP == 0 && block.state == 1 && pause == 0)
            {
                block.ystart = block.ystart + STEP;
            }
            
            
            // check if the piece has reached a part of the board already occupied
            check = MyBoard.Check(block.xstart,block.ystart,block.str,block.size);
            
            if(check!=0) // if the piece has reached a part of the board already filled, stop this iteration
            {
                terminate = 1;
                break;
            }
            
            if((block.ystart+block.Height()) >= YMAX) // if the piece has reached the bottom of the board
            {
                block.ystart = YMAX - (block.Height());
                block.state = 0;
                terminate = 3;
            }
            
            
            glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
            
            
            block.Draw(red,green,blue); // draw the current piece
            MyBoard.Draw(0,255,0); //draw the current board
            Draw_Box(total_score,pause,1); // draw the game box
            Draw_Help(pause); // draw the help menu if pause = 1.

            
            FsSwapBuffers();
            FsSleep(10);
        }
        
        
        if(terminate == 2) // user has pressed the ESC key before the game is actually over.
        {
            break;
        }
        
        if(terminate == 1) // the current piece hit an old piece
        {
            block.ystart = yold;
        }
        
        if(block.ystart <= Y_START && over == 0) // the game is over
        {
            glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
            
            MyBoard.Draw(0,255,0);
            
            Draw_Box(total_score,pause,0);
            
            FsSwapBuffers();
            FsSleep(10);
            
            over = 1;
        }
        
        if(over != 1)
        {
            MyBoard.Add(block.xstart,block.ystart,block.str,block.size,red,green,blue); // add most recent piece to board.
        }
        
        // looking for complete lines
        
        int count = 0;
        int points = 0;
        
        for(int d = 0; d < MyBoard.hei; d++)
        {
            int sum = 0;
            for(int g = 0; g < MyBoard.wid; g++)
            {
                
                if(MyBoard.board[d*MyBoard.wid+g] == '1')
                {
                    sum = sum + 1; // counting the number of '1's found in a horizontal line
                }
            }
            
            if(sum == MyBoard.wid) // the horizontal line is completely filled and needs to be cleared.
            {
                count = count + 1; // keep track of the number of horizontal lines cleared in this iteration.
                
                if(d == 0)
                {
                    for(int g = 0; g < MyBoard.wid; g++)
                    {
                        MyBoard.board[d*MyBoard.wid+g] = '.'; // clear the line
                    }
                    
                }
                else // d > 0
                {
                    for(int j = d; j >= 0; j--)
                    {
                        if(j == 0) // this is the top most line
                        {
                            for(int g = 0; g < MyBoard.wid; g++)
                            {
                                MyBoard.board[j*MyBoard.wid+g] = '.';
                            }
                        }
                        else
                            for(int g = 0; g < MyBoard.wid; g++) // copy items from the line above
                            {
                                MyBoard.board[j*MyBoard.wid+g] = MyBoard.board[(j-1)*MyBoard.wid+g];
                                MyBoard.red[j*MyBoard.wid+g] = MyBoard.red[(j-1)*MyBoard.wid+g];
                                MyBoard.green[j*MyBoard.wid+g] = MyBoard.green[(j-1)*MyBoard.wid+g];
                                MyBoard.blue[j*MyBoard.wid+g] = MyBoard.blue[(j-1)*MyBoard.wid+g];
                            }
                    } // end of for
                } // end of else
            } // end of if
            
        }
        
        switch(count) // calculate points based on # of lines cleared in this iteration (0 to 4)
        {
            case 0:
            {
                points = 0;
                break;
            }
            case 1:
            {
                points = 100;
                break;
            }
            case 2:
            {
                points = 300;
                break;
            }
            case 3:
            {
                points = 600;
                break;
            }
            case 4:
            {
                points = 1000;
                break;
            }
            default:
            {
                points = 0;
                break;
            }
        }
        
        total_score = total_score + points; // update the total score
        
        FsPollDevice();
        int gameKey = FsInkey();
        
        if (gameKey == FSKEY_ESC) // we need this when the game is over and the final screen is being displayed.
            break;
    
    }
    return total_score;
    
}
