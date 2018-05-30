
#include "ysglfontdata.h"
#include <stdio.h>

int YsGlWriteStringToRGBA8Bitmap(
    const char str[],unsigned int c0,unsigned int c1,unsigned int c2,unsigned int c3,
    unsigned char bmpPtr[],unsigned int bmpWid,unsigned int bmpHei,
    int bottomLeftX,int bottomLeftY,
    const unsigned char *const fontPtr[],int fontWid,int fontHei);