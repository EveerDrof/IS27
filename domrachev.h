#pragma once
#include "utilities.h"

void resizeHeight(int);
void resizeWidth(int);
void rotateRight();
void rotateLeft();

void resizeHeight(int pers)
{
	if (pers == 0)
	{
		read_file();
		p_out = p_in;
		write_file();
		return;
	}

	read_file();
	int x = 100 / pers;
	int c = 0;
	for (int i = 0; i < h_bmp.height; i++)
		if (i%x == 0)
			c++;

	p_out = new struct pixel*[h_bmp.height + c];

	int m = 0, n;
	for (int i = 0; i < h_bmp.height; i++)
	{
		n = 0;
		if (i%x == 0)
		{
			if (pers > 0)
			{
				p_out[m] = new struct pixel[h_bmp.width];
				for (int j = 0; j < h_bmp.width; j++)
				{
					p_out[m][n] = p_in[i][j];
					n++;
				}
				m++;
				n = 0;
			}

			if (pers < 0)
				continue;
		}

		p_out[m] = new struct pixel[h_bmp.width];

		for (int j = 0; j < h_bmp.width; j++)
		{
			p_out[m][n] = p_in[i][j];
			n++;
		}
		m++;
	}
	h_bmp.height = m;

	write_file();
}



void resizeWidth(int pers)
{
	if (pers == 0)
	{
		read_file();
		p_out = p_in;
		write_file();
		return;
	}

	read_file();
	int x = 100 / pers;
	int c = 0;
	for (int i = 0; i < h_bmp.width; i++)
		if (i%x == 0)
			c++;

	p_out = new struct pixel*[h_bmp.height];

	int m = 0, n;
	for (int i = 0; i < h_bmp.height; i++)
	{
		n = 0;
		p_out[m] = new struct pixel[h_bmp.width + c];
		for (int j = 0; j < h_bmp.width; j++)
		{
			if (j%x == 0)
			{
				if (pers > 0)
				{
					p_out[m][n] = p_in[i][j];
					n++;
				}
				if (pers < 0)
					continue;
			}
			p_out[m][n] = p_in[i][j];
			n++;
		}
		m++;
	}
	h_bmp.width = n;
	write_file();
}

void rotateRight()
{
	read_file();
	p_out = new struct pixel*[h_bmp.width];
	for (int i = 0; i < h_bmp.width; i++)
		p_out[i] = new struct pixel[h_bmp.height];

	for (int i = 0; i < h_bmp.height; i++)
		for (int j = 0; j < h_bmp.width; j++)
			p_out[j][i] = p_in[i][j];

	int tmp = h_bmp.height;
	h_bmp.height = h_bmp.width;
	h_bmp.width = tmp;
	write_file();
}

void rotateLeft()
{
	read_file();
	p_out = new struct pixel*[h_bmp.width];
	for (int i = 0; i < h_bmp.width; i++)
		p_out[i] = new struct pixel[h_bmp.height];

	for (int i = 0; i < h_bmp.height; i++)
		for (int j = 0; j < h_bmp.width; j++)
			p_out[j][i] = p_in[h_bmp.height - i - 1][j];

	int tmp = h_bmp.height;
	h_bmp.height = h_bmp.width;
	h_bmp.width = tmp;
	write_file();
}
