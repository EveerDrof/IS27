#pragma once
#include "utilities.h"
void cutsizev(picture &pic ,int pers)
{
	if (pers <= 0 )
	{
		return;
	}
	else
	{

		int x = 100 / pers;
		int c = 0;

		for (int i = 0; i < pic.h_bmp.height; i++)
			if (i%x == 0)
				c++;

		pic.h_bmp.height -= c;

		pixel **p_out = new struct pixel*[pic.h_bmp.height];
		int m = 0, n;
		int C = 0;
		for (int i = 0; i < pic.h_bmp.height + c; i++)
		{
			if (i%x == 0)
			{
				C++;
			}
			else
			{

				p_out[i - C] = new struct pixel[pic.h_bmp.width];
				for (int j = 0; j < pic.h_bmp.width; j++)
				{
					p_out[i - C][j] = pic.arr[i][j];
				}
			}
		}
		for (int I = 0; I < pic.h_bmp.height + c;I++)
		{
			delete[] pic.arr[I];
		}
		delete[] pic.arr;
		pic.arr = p_out;
	}
}
void cutsizeh(picture &pic, int pers)
{
	if (pers <= 0)
	{
		return;
	}
	else
	{
		int x = 100 / pers;
		int c = 0;

		for (int i = 0; i < pic.h_bmp.width; i++)
			if (i%x == 0)
				c++;
		pic.h_bmp.width -= c;
		pixel **p_out = new struct pixel*[pic.h_bmp.height];
		int m = 0, n;
		int C = 0;
		for (int i = 0; i < pic.h_bmp.height; i++)
		{
			p_out[i] = new struct pixel[pic.h_bmp.width];
			C = 0;
			for (int j = 0; j < pic.h_bmp.width+c; j++)
			{
				if (j%x == 0)
				{
					C++;
				}
				else
				{
					p_out[i ][j- C] = pic.arr[i][j];
				}
			}
		}
		for (int I = 0; I < pic.h_bmp.height; I++)
		{
			delete[] pic.arr[I];
		}
		delete[] pic.arr;
		pic.arr = p_out;
	}
}
