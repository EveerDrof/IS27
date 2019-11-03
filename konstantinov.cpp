#pragma once
#include "utilities.h"
enum Color { RED, BLUE, GREEN, GRAY };
Color Color_Check(const char *CN);
void PaintPixel(enum Color, int, struct pixel*);
int NearColor(int, int);
void chb(picture &pic)
{
	struct pixel *P;
	for (int i = 0; i < pic.h_bmp.height; i++)
		for (int j = 0; j < pic.h_bmp.width; j++)
		{
			P = &pic.arr[i][j];
			int S = 0;
			if (S < P->b)S = P->b;
			if (S < P->b)S = P->r;
			if (S < P->b)S = P->g;
			P->b = S;
			P->g = S;
			P->r = S;

		}
}
void raskras(picture &pic,int colvo,const char  *firstcolor,const char *secondcolor)
{
	Color COL;
	Color COL2;
	COL = Color_Check(firstcolor);
	if (secondcolor == "NULL")
		{
			COL2 = COL;
		}
		else
		{
			COL2 = Color_Check(secondcolor);
		}
	int Dif = 255 / colvo;
	struct pixel *P;
	for (int i = 0; i < pic.h_bmp.height; i++)
		for (int j = 0; j < pic.h_bmp.width; j++)

		{
			int S = 0;
			if (S < pic.arr[i][j].g)S = pic.arr[i][j].g;
			if (S < pic.arr[i][j].b)S = pic.arr[i][j].b;
			if (S < pic.arr[i][j].r)S = pic.arr[i][j].r;

			int I = 0;
			P = &pic.arr[i][j];
			S = NearColor(S, Dif);
			for (I; I*Dif < S; I++);
			if (secondcolor=="Null")
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
}
void limitcolors(int Colors,picture &pic)
{
	int Dif = 255 / (Colors - 1);
	for (int i = 0; i < pic.h_bmp.height; i++)
		for (int j = 0; j < pic.h_bmp.width; j++)
		{
			pic.arr[i][j].b = NearColor(pic.arr[i][j].b, Dif);
			pic.arr[i][j].g = NearColor(pic.arr[i][j].g, Dif);
			pic.arr[i][j].r = NearColor(pic.arr[i][j].r, Dif);
		}
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
Color Color_Check(const char *CN)
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

