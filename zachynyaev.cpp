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
			if (i - C >= pic.h_bmp.height)
			{
				continue;
			}
			if (i%x == 0)
			{
				p_out[i - C] = new struct pixel[pic.h_bmp.width];
				if (i == 0)
				{
					for (int j = 0; j < pic.h_bmp.width; j++)
					{
						p_out[0][j].b =( pic.arr[0][j].b+pic.arr[1][j].b)/2;
						p_out[0][j].r = (pic.arr[0][j].r + pic.arr[1][j].r)/2;
						p_out[0][j].g = (pic.arr[0][j].g + pic.arr[1][j].g)/2;
					}
				}
				else
				{
					if (pic.h_bmp.height-1+c > i )
					{
						
						for (int j = 0; j < pic.h_bmp.width; j++)
						{
							p_out[i-1-C][j].b = (pic.arr[i-1][j].b + pic.arr[i][j].b) / 2;
							p_out[i-1-C][j].r = (pic.arr[i-1][j].r + pic.arr[i][j].r) / 2;
							p_out[i-1-C][j].g = (pic.arr[i-1][j].g + pic.arr[i][j].g) / 2;
							p_out[i- C][j].b = (pic.arr[i][j].b + pic.arr[i+1][j].b) / 2;
							p_out[i- C][j].r = (pic.arr[i][j].r + pic.arr[i+1][j].r) / 2;
							p_out[i- C][j].g = (pic.arr[i][j].g + pic.arr[i+1][j].g) / 2;
						}
					}
					else
					{
						if (i == pic.h_bmp.height+c-1)
						{
							for (int j = 0; j < pic.h_bmp.width; j++)
							{
								p_out[i-C-1][j].b = (pic.arr[i][j].b + pic.arr[i-1][j].b) / 2;
								p_out[i-C-1][j].r = (pic.arr[i][j].r + pic.arr[i-1][j].r) / 2;
								p_out[i-C-1][j].g = (pic.arr[i][j].g + pic.arr[i-1][j].g) / 2;
							}
						}
					}
				}
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
			pic.arr[I] = nullptr;
		}
		delete pic.arr;
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
			pixel **p_out = new  pixel*[pic.h_bmp.height];
			for (int i = 0; i < pic.h_bmp.width; i++)
				if (i%x == 0)
					c++;
			for (int i = 0; i < pic.h_bmp.height; i++)
				p_out[i] = new struct pixel[pic.h_bmp.width-c];
			pic.h_bmp.width -= c;

			
			int m = 0, n;
			int C = 0;
			for (int i = 0; i < pic.h_bmp.width+c; i++)
			{
				if (i - C >= pic.h_bmp.width)
				{
					continue;
				}
				if (i%x == 0)
				{
					if (i == 0)
					{
						for (int j = 0; j < pic.h_bmp.height; j++)
						{
							p_out[j][0].b = (pic.arr[j][0].b + pic.arr[j][1].b) / 2;
							p_out[j][0].r = (pic.arr[j][0].r + pic.arr[j][1].r) / 2;
							p_out[j][0].g = (pic.arr[j][0].g + pic.arr[j][1].g) / 2;
						}
					}
					else
					{
						if (pic.h_bmp.width - 1 + c > i)
						{
							for (int j = 0; j < pic.h_bmp.height; j++)
							{
								p_out[j][i - 1 - C].b = (pic.arr[j][i - 1].b + pic.arr[j][i].b) / 2;
								p_out[j][i - 1 - C].r = (pic.arr[j][i - 1].r + pic.arr[j][i].r) / 2;
								p_out[j][i - 1 - C].g = (pic.arr[j][i - 1].g + pic.arr[j][i].g) / 2;
								p_out[j][i - C].b = (pic.arr[j][i].b + pic.arr[j][i + 1].b) / 2;
								p_out[j][i - C].r = (pic.arr[j][i].r + pic.arr[j][i + 1].r) / 2;
								p_out[j][i - C].g = (pic.arr[j][i].g + pic.arr[j][i + 1].g) / 2;
							}
						}
						else
						{
							if (i == pic.h_bmp.width + c - 1)
							{
								for (int j = 0; j < pic.h_bmp.height; j++)
								{
									p_out[j][i - C - 1].b = (pic.arr[j][i].b + pic.arr[j][i - 1].b) / 2;
									p_out[j][i - C - 1].r = (pic.arr[j][i].r + pic.arr[j][i - 1].r) / 2;
									p_out[j][i - C - 1].g = (pic.arr[j][i].g + pic.arr[j][i - 1].g) / 2;
								}
							}
						}
					}
					C++;
				}
				else
				{
					for (int j = 0; j < pic.h_bmp.height; j++)
					{
						p_out[j][i - C].b = pic.arr[j][i].b;
						p_out[j][i - C].g = pic.arr[j][i].g;
						p_out[j][i - C].r = pic.arr[j][i].r;
					}
				}
			}
		for (int I = 0; I < pic.h_bmp.height; I++)
		{
			//delete[] pic.arr[I];	
		}
		delete []pic.arr;
		pic.arr = p_out;
	}
}

