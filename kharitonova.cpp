#pragma once
#include "utilities.h"
using namespace std;
pixel blackPix{ 0,0,0 };

void horizontalLine(int posX)
{
	for (int I = 0; I < h_bmp.width; I++)
	{
		p_out[posX][I] = blackPix;
	}
}
void verticalLine(int posX, int posY)
{
	for (int I = posY; I < posY + h_bmp.height / 2; I++)
	{
		p_out[I][posX] = blackPix;
	}
}
int NumToPic(char** argv)
{
	h_bmp = head{ 66,77,138,0, 54, 40, 3, 7, 1572865,0,768,0,0,0,0 };
	int num;
	outfile = argv[3];
	p_out = new pixel*[h_bmp.height];
	for (int I = 0; I < h_bmp.height; I++)
	{
		p_out[I] = new pixel[h_bmp.width];
		for (int G = 0; G < h_bmp.width; G++)
		{
			p_out[I][G] = { 255,255,255 };
		}
	}
	num = atoi(argv[2]);
	if (num == 0)
	{
		horizontalLine(0);
		horizontalLine(h_bmp.height - 1);
		verticalLine(0, 0);
		verticalLine(0, h_bmp.height / 2);
		verticalLine(2, 0);
		verticalLine(2, h_bmp.height / 2);
	}
	if (num == 1)
	{
		verticalLine(1, 0);
		verticalLine(1, h_bmp.height / 2);
	}
	if (num == 2)
	{
		horizontalLine(0);
		horizontalLine(h_bmp.height / 2);
		horizontalLine(h_bmp.height - 1);
		verticalLine(0, 0);

		verticalLine(2, h_bmp.height / 2);
	}
	if (num == 3)
	{
		horizontalLine(0);
		horizontalLine(h_bmp.height / 2);
		horizontalLine(h_bmp.height - 1);
		verticalLine(2, 0);
		verticalLine(2, h_bmp.height / 2);
	}
	if (num == 4)
	{
		verticalLine(2, 0);
		verticalLine(2, h_bmp.height / 2);
		horizontalLine(h_bmp.height / 2);
		verticalLine(0, h_bmp.height / 2);
	}
	if (num == 5)
	{
		horizontalLine(0);
		horizontalLine(h_bmp.height - 1);
		verticalLine(0, h_bmp.height / 2);
		horizontalLine(h_bmp.height / 2);
		verticalLine(2, 0);
	}

	if (num == 6)
	{
		horizontalLine(0);
		horizontalLine(h_bmp.height - 1);
		verticalLine(0, 0);
		horizontalLine(h_bmp.height / 2);
		verticalLine(2, 0);
		verticalLine(0, h_bmp.height / 2);
	}
	if (num == 7)
	{
		horizontalLine(h_bmp.height - 1);
		verticalLine(2, 0);
		verticalLine(2, h_bmp.height / 2);
	}
	if (num == 8)
	{
		horizontalLine(0);
		horizontalLine(h_bmp.height - 1);
		verticalLine(0, 0);
		verticalLine(0, h_bmp.height / 2);
		verticalLine(2, 0);
		horizontalLine(h_bmp.height / 2);
		verticalLine(2, h_bmp.height / 2);
	}
	if (num == 9)
	{
		horizontalLine(0);
		horizontalLine(h_bmp.height - 1);
		verticalLine(0, h_bmp.height / 2);
		horizontalLine(h_bmp.height / 2);
		verticalLine(2, 0);
		verticalLine(2, h_bmp.height / 2);
	}
	write_file();
	return 0;
}