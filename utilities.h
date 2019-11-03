#pragma warning(disable : 4996) //(отлючение ошибки из visual studio)
#pragma once
// #include "stdafx.h" (нyжно только для visual studio)
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>
#include <cmath>
using namespace std;

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

struct pixel
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	bool operator==(pixel &pix)
	{
		if ((b == pix.b) && (g == pix.g) && (r == pix.r))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
struct picture
{
	head h_bmp;
	pixel **arr;
};

struct pointOfPixel
{
	double x;
	double y;
};




int get_pad(int);

int get_pad(int width);

int padding(int width);

void read_file(const char *infile, picture &pic);

void write_file(const char *outfile, picture &pic);
