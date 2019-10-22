#pragma once
#include "utilities.h"

void cutFromPic(struct pointOfPixel, struct pointOfPixel);
int abs(int A)
{
	if(A<0)
	return -A;
	else
	return A;
}

void cutFromPic(struct pointOfPixel point1, struct pointOfPixel point2)
{
	read_file();
	int A=abs(point2.y - point1.y);
	p_out = new struct pixel*[A];
	int B=abs(point2.x - point1.x);
	for (int i = 0; i < A; i++)
	{
		p_out[i] = new struct pixel[B];
	}
	for (int i = 0; i < A; i++)
	{
		for (int j = 0; j < abs(point2.x - point1.x); j++)
		{
			p_out[i][j] = p_in[i + int(point1.y)][j + int(point1.x)];
		}
	}
	h_bmp.height = abs(point2.y - point1.y);
	h_bmp.width = abs(point2.x - point1.x);

	write_file();

}
