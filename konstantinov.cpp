#pragma once
#include "utilities.h"
enum Color { RED, BLUE, GREEN, GRAY };
Color Color_Check(char *CN);
void Prepare();
void PaintPixel(enum Color, int, struct pixel*);
int NearColor(int, int);
void chb()
{
	Prepare();
	struct pixel *P;
	for (int i = 0; i < h_bmp.height; i++)
		for (int j = 0; j < h_bmp.width; j++)

		{
			p_out[i][j] = p_in[i][j];
			P = &p_out[i][j];
			int S = 0;
			if (S < P->b)S = P->b;
			if (S < P->b)S = P->r;
			if (S < P->b)S = P->g;
			P->b = S;
			P->g = S;
			P->r = S;

		}
	write_file();
}
void raskras(int argc,char **argv)
{
	Color COL;
	Color COL2;
	COL = Color_Check(argv[5]);
	if (argc == 6)
		{
			COL2 = COL;
		}
		else
		{
			COL2 = Color_Check(argv[6]);
		}
	int Dif = 255 / atoi(argv[4]);
	Prepare();
	struct pixel *P;
	for (int i = 0; i < h_bmp.height; i++)
		for (int j = 0; j < h_bmp.width; j++)

		{
			int S = 0;
			if (S < p_in[i][j].g)S = p_in[i][j].g;
			if (S < p_in[i][j].b)S = p_in[i][j].b;
			if (S < p_in[i][j].r)S = p_in[i][j].r;

			int I = 0;
			P = &p_out[i][j];
			S = NearColor(S, Dif);
			for (I; I*Dif < S; I++);
			if (argc==6)
			{
				PaintPixel(COL, S, P);
			}
			else
			{
				if (I % 2 == 1)
				{
					PaintPixel(COL, S, P);
				}
				else
				{
					PaintPixel(COL2, S, P);
				}
			}

		}
	write_file();
}
void limitcolors(int Colors)
{
	int Dif = 255 / (Colors - 1);
	Prepare();
	for (int i = 0; i < h_bmp.height; i++)
		for (int j = 0; j < h_bmp.width; j++)
		{
			p_out[i][j].b = NearColor(p_in[i][j].b, Dif);
			p_out[i][j].g = NearColor(p_in[i][j].g, Dif);
			p_out[i][j].r = NearColor(p_in[i][j].r, Dif);
		}
	write_file();
}
void PaintPixel(Color COL, int S, struct pixel *P)
{
	switch (COL)
	{
	case RED:
		P->b = 0;
		P->g = 0;
		P->r = S;
		break;
	case BLUE:
		P->b = S;
		P->g = 0;
		P->r = 0;
		break;
	case GREEN:
		P->b = 0;
		P->g = S;
		P->r = 0;
		break;
	case GRAY:
		P->b = S;
		P->g = S;
		P->r = S;
		break;
	}
}
void Prepare()
{
	read_file();
	p_out = new struct pixel*[h_bmp.height];
	for (int i = 0; i < h_bmp.height; i++)
		p_out[i] = new struct pixel[h_bmp.width];
}
int NearColor(int C, int Dif)
{
	int K = 0;
	while (K*Dif < C)
	{
		K++;
	}
	if ((C - (K - 1) * Dif) < K*Dif - C)
	{
		return (K - 1) * Dif > 255 ? 255 : (K - 1)*Dif;
	}
	else
	{
		return K * Dif > 255 ? 255 : K * Dif;
	}
}
Color Color_Check(char *CN)
{
	Color COL;
	if (!strcmp(CN, "GREEN"))
	{
		COL = GREEN;
	}
	if (!strcmp(CN, "GREY"))
	{
		COL = GRAY;
	}
	if (!strcmp(CN, "BLUE"))
	{
		COL = BLUE;
	}
	if (!strcmp(CN, "RED"))
	{
		COL = RED;
	}
	return COL;
}

