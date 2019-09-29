#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996) // Что вот это за хуйня ?

using namespace std;


void cutFromPic(struct pointOfPixel, struct pointOfPixel);               

void help();


void help() 
{
	cout << "\nusage: \n";
	cout << "  name_of_program cutFromPic x1 y1 x2 y2 in_file out_file \n";
	system("Pause");
}

int main(int argc, char** argv) 
{
	setlocale(0, ""); 

	if (argc < 7)
	{
		help();
		return 1;
	}

	if (!strcmp(argv[1], "cutFromPic"))
	{
		struct pointOfPixel point1, point2;

		point1.x = atoi(argv[2]);
		point1.y = atoi(argv[3]);
		point2.x = atoi(argv[4]);         
		point2.y = atoi(argv[5]);

		infile = argv[6];        
		outfile = argv[7];

		read_file();
		cutFromPic(point1, point2);
		write_file();
		return 0;
	}
}

void cutFromPic(struct pointOfPixel point1, struct pointOfPixel point2)
{
	p_out = new struct pixel*[abs(point2.y - point1.y)];
	for (int i = 0; i < abs(point2.y - point1.y); i++)
	{
		p_out[i] = new struct pixel[abs(point2.x - point1.x)];
	}
	for (int i = 0; i < abs(point2.y - point1.y); i++)
	{
		for (int j = 0; j < abs(point2.x - point1.x); j++)
		{
			p_out[i][j] = p_in[i + int(point1.y)][j + int(point1.x)];
		}
	}
	h_bmp.height = abs(point2.y - point1.y);
	h_bmp.width = abs(point2.x - point1.x);

}
