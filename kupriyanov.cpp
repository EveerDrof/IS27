#include "pch.h"

#include <iostream>

#include <stdlib.h>

#include <stdio.h>

#define _USE_MATH_DEFINES

#include <string.h>

#include <math.h>

#pragma warning(disable : 4996)

using namespace std;

struct pixel

{

unsigned char b;

unsigned char g;

unsigned char r;

};

struct point

{

int X, Y;

};

#pragma pack(push, 1)

struct head

{

char type[2];

unsigned int size;

unsigned int reserv;

unsigned int offset;

unsigned int head_size;

unsigned int width;

unsigned int height;

unsigned int end[7];

};

#pragma pack(pop)

struct pixel **p_in;

struct head h_bmp;

char *infile;

int get_pad(int);

void read_file();

void help();

int get_pad(int width)

{

int i = 0;

while ((width * 3 + i) % 4 != 0)

i++;

return i;

}

bool isBlack(pixel A)

{

if (A.b ==0 && A.g ==0 && A.r == 0)

{

return true;

}

else

{

return false;

}

}

void help()

{

cout << "\nusage: \n";

cout << " chbmp in_file \n";

}

void findPoints();

int main(int argc, char** argv)

{

int pers;

if (argc < 2)

{

help();

return 1;

}

infile = argv[1];

read_file();

findPoints();

return 0;

}

void read_file()

{

long int count = 0;

int i, j, n;

struct pixel buf[4];

FILE *fd = fopen(infile, "rb");

if (!fd)

{

perror("open file for read");

exit(1);

}

fread(&h_bmp, sizeof(struct head), 1, fd);

int pad = get_pad(h_bmp.width);

p_in = new struct pixel*[h_bmp.height+2];

for (i = 0; i < h_bmp.height+2; i++)

{

p_in[i] = new struct pixel[h_bmp.width+2];

for (j = 0; j < h_bmp.width+2; j++)

{

if (i == 0 || j==0 || i==h_bmp.height+1 || j == h_bmp.width+1)

p_in[i][j] = { 255,255,255 };

else

{

n = fread(&p_in[i][j], 3, 1, fd);

}

}

if (pad != 0)

fread(buf, pad, 1, fd);

}

fclose(fd);

}

void findPoints()

{

point *points = new point[2];

int count = 0, C = 0;

for (int Y = 1; Y < h_bmp.height+1; Y++)

{

for (int X = 1; X < h_bmp.width+1; X++)

{

count = 0;

for (int I = -1; I < 2; I++)

{

for (int J = -1; J < 2; J++)

{

if ((isBlack(p_in[Y+I][X+J]))&&

(isBlack(p_in[Y] [X ])))

count++;

}

}

if (count == 2)

{

cout << "Found"<<endl;

points[C] = { X,Y };

C++;

}

}

}

cout << points[0].X << endl;

cout << points[0].Y << endl;

cout << points[1].X << endl;

cout << points[1].Y << endl;

cout << "Length : " << sqrt( pow( points[1].X-points[0].X , 2)

+pow( points[1].Y-points[0].Y , 2))<<endl;

cout << "Angle : " << (static_cast<float>(points[1].X - points[0].X) / static_cast<float>(points[1].Y - points[0].Y))<<endl;

}