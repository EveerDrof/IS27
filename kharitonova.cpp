#pragma once
#include "utilities.h"
using namespace std;
pixel blackPix{ 0,0,0 };

void horizontalLine(picture pic, int posX)
{
	for (int I = 0; I < pic.h_bmp.width; I++)
	{
		pic.arr[posX][I] = blackPix;
	}
}
void verticalLine(picture pic, int posX, int posY)
{
	for (int I = posY; I < posY + pic.h_bmp.height / 2; I++)
	{
		pic.arr[I][posX] = blackPix;
	}
}
void NumToPic(picture &pic, int num)
{
	for(int i=0;i<pic.h_bmp.height, i++)
	{
		delete[] pic.arr[i];
	}
	delete[] pic.arr;
	
	pic.h_bmp = head{ 66,77,138,0, 54, 40, 3, 7, 1572865,0,768,0,0,0,0 };
	
	pic.arr= new pixel*[pic.h_bmp.height];
	for (int i = 0; i < pic.h_bmp.height; i++)
	{
		pic.arr[i] = new pixel[pic.h_bmp.width];
		for (int j = 0; j < pic.h_bmp.width; j++)
		{
			pic.arr[i][j] = { 255,255,255 };
		}
	}
	
	if (num == 0)
	{
		horizontalLine(0);
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(0, 0);
		verticalLine(0, pic.h_bmp.height / 2);
		verticalLine(2, 0);
		verticalLine(2, pic.h_bmp.height / 2);
	}
	if (num == 1)
	{
		verticalLine(1, 0);
		verticalLine(1, pic.h_bmp.height / 2);
	}
	if (num == 2)
	{
		horizontalLine(0);
		horizontalLine(pic.h_bmp.height / 2);
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(0, 0);

		verticalLine(2, pic.h_bmp.height / 2);
	}
	if (num == 3)
	{
		horizontalLine(0);
		horizontalLine(pic.h_bmp.height / 2);
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(2, 0);
		verticalLine(2, pic.h_bmp.height / 2);
	}
	if (num == 4)
	{
		verticalLine(2, 0);
		verticalLine(2, pic.h_bmp.height / 2);
		horizontalLine(pic.h_bmp.height / 2);
		verticalLine(0, pic.h_bmp.height / 2);
	}
	if (num == 5)
	{
		horizontalLine(0);
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(0, pic.h_bmp.height / 2);
		horizontalLine(pic.h_bmp.height / 2);
		verticalLine(2, 0);
	}

	if (num == 6)
	{
		horizontalLine(0);
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(0, 0);
		horizontalLine(pic.h_bmp.height / 2);
		verticalLine(2, 0);
		verticalLine(0, pic.h_bmp.height / 2);
	}
	if (num == 7)
	{
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(2, 0);
		verticalLine(2, pic.h_bmp.height / 2);
	}
	if (num == 8)
	{
		horizontalLine(0);
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(0, 0);
		verticalLine(0, pic.h_bmp.height / 2);
		verticalLine(2, 0);
		horizontalLine(pic.h_bmp.height / 2);
		verticalLine(2, pic.h_bmp.height / 2);
	}
	if (num == 9)
	{
		horizontalLine(0);
		horizontalLine(pic.h_bmp.height - 1);
		verticalLine(0, pic.h_bmp.height / 2);
		horizontalLine(pic.h_bmp.height / 2);
		verticalLine(2, 0);
		verticalLine(2, pic.h_bmp.height / 2);
	}
}