#pragma once
#include "utilities.h"
void cutsizev(int pers)
{
	read_file();
	if (pers == 0)
	{
		p_out = p_in;
	}
	else
	{

		int x = 100 / pers;
		int c = 0;

		for (int i = 0; i < h_bmp.height; i++)
			if (i%x == 0)
				c++;

		h_bmp.height -= c;

		p_out = new struct pixel*[h_bmp.height];

		int m = 0, n;
		if (pers < 0)
		{
			return;
		}
		else
		{
			int C = 0;
			for (int i = 0; i < h_bmp.height + c; i++)
			{
				if (i%x == 0)
				{
					C++;
				}
				else
				{

					p_out[i - C] = new struct pixel[h_bmp.width];
					for (int j = 0; j < h_bmp.width; j++)
					{

						p_out[i - C][j] = p_in[i][j];
					}
				}
			}
		}
	}
	write_file();
}
void cutsizeh(int pers)
{
	read_file();
	if (pers == 0)
	{
		p_out = p_in;
	}
	else
	{
		int x = 100 / pers;
		int c = 0;
		for (int i = 0; i < h_bmp.width; i++)
			if (i%x == 0)
				c++;
		h_bmp.width -= c;
		p_out = new struct pixel*[h_bmp.height];

		int m = 0, n;
		if (pers < 0)
		{
			return;
		}
		else
		{

			for (int i = 0; i < h_bmp.height; i++)
			{
				int C = 0;

				p_out[i] = new struct pixel[h_bmp.width];
				for (int j = 0; j < h_bmp.width + c; j++)
				{
					if (j%x == 0)
					{
						C++;
					}
					else
					{
						p_out[i][j - C] = p_in[i][j];
					}
				}
			}
		}
	}
	write_file();
}

