//
//  Tetris.hpp
//  Tetris_2
//
//  Created by Rahul Raina on 11/19/17.
//  Copyright © 2017 CMU. All rights reserved.
//

#ifndef Tetris_hpp
#define Tetris_hpp

#include <stdio.h>

class Piece{
    
public:
    char *str;
    int size;
    int xstart;
    int ystart;
    int state;
    int xLeft;
    int xRight;
    
public:
    Piece();
    Piece(int length);
    void Set(int length);
    ~Piece();
    void DrawPiece(int x, int y, int r, int g, int b);
    void Draw(int r, int g, int b);
    void Rotate();
    void Create();
    int Height();
    int Width();
    void Cleanup();
    
};

class Board
{
    
public:
    char *board;
    int *red;
    int *blue;
    int *green;
    int size;
    int wid;
    int hei;
public:
    Board();
    ~Board();
    int Check(int x, int y,char matrix[],int mat_size);
    void Add(int xstart, int ystart,char matrix[],int mat_size,int r, int g, int b);
    void Initialize();
    void DrawBoard(int x, int y,int r, int g, int b);
    void Draw(int r, int g, int b);
    void DrawGrid();
    void ClearOut();
};


class Tetris
{
public:
    void Draw_Box(int total_score, int pause, int over);
    int Play();
    void Draw_Help(int pause);  
};




#endif /* Tetris_hpp */
