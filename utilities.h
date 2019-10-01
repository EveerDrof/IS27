#pragma once
#pragma warning(disable : 4996) //(отлючение ошибки из visual studio)

// #include "stdafx.h" (нyжно только для visual studio)
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;

#pragma pack(push, 1)
struct head
{
	char type[2];
	unsigned int size;
	unsigned int reserv;
	unsigned int offset;
	unsigned int head_size;
	unsigned int width;
	unsigned int height;
	unsigned int end[7];
};
#pragma pack(pop)

struct pixel
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
};

struct pointOfPixel
{
	double x;
	double y;
};

struct pixel **p_in;
struct pixel **p_out;
struct head h_bmp;
char *infile;
char *outfile;


int get_pad(int);
void read_file();
void write_file();

int get_pad(int width)
{
	int i = 0;
	while ((width * 3 + i) % 4 != 0)
		i++;
	return i;
}

int padding(int width)
{
	int i = 0;
	while (width % 4 == 0)
		i++;
	return i;
}

void read_file()
{
	long int count = 0;
	int i, j, n;
	struct pixel buf[4];
	FILE *fd = fopen(infile, "rb");
	if (!fd)
	{
		perror("open file for read");
		exit(1);
	}
	fread(&h_bmp, sizeof(struct head), 1, fd);
	int pad = get_pad(h_bmp.width);
	p_in = new struct pixel*[h_bmp.height];
	for (i = 0; i < h_bmp.height; i++)
	{
		p_in[i] = new struct pixel[h_bmp.width];
		for (j = 0; j < h_bmp.width; j++)
		{
			n = fread(&p_in[i][j], 3, 1, fd);
		}
		if (pad != 0)
			fread(buf, pad, 1, fd);
	}
	fclose(fd);
}

void write_file()
{
	int i, j;
	struct pixel buf[4];
	FILE *fd = fopen(outfile, "wb");
	if (!fd)
	{
		perror("open file for write");
		exit(1);
	}
	fwrite(&h_bmp, sizeof(struct head), 1, fd);
	int pad = get_pad(h_bmp.width);
	for (i = 0; i < h_bmp.height; i++)
	{
		for (j = 0; j < h_bmp.width; j++)
			fwrite(&p_out[i][j], 3, 1, fd);
		if (pad != 0)
			fwrite(buf, pad, 1, fd);
	}
	cout << "\nbyte write= " << ftell(fd) << endl;
	fclose(fd);
}

