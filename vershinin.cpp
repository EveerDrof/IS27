#pragma once
#include "utilities.h"

void cutFromPic(picture &pic);
int abs(int A)
{
	if(A<0)
	return -A;
	else
	return A;
}

void cutFromPic(picture &pic,int X1,int Y1,int X2,int Y2)
{
	pointOfPixel point1={X1,Y1};
	pointOfPixel point2={X2,Y2};
	int A=abs(point2.y - point1.y);
	 pixel **p_out = new struct pixel*[A];
	int B=abs(point2.x - point1.x);
	for (int i = 0; i < A; i++)
	{
		p_out[i] = new struct pixel[B];
	}
	for (int i = 0; i < A; i++)
	{
		for (int j = 0; j < abs(point2.x - point1.x); j++)
		{
			p_out[i][j] = pic.arr[i + int(point1.y)][j + int(point1.x)];
		}
	}
	pic.h_bmp.height = abs(point2.y - point1.y);
	pic.h_bmp.width = abs(point2.x - point1.x);
	for(int I=0;I<A;I++)
	{
		delete[] pic.arr[I];
	}
	delete[] pic.arr;
	pic.arr=p_out;


}
