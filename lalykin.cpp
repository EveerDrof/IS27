#include "utilities.h" 
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
void Glue()
{
	char*infile2;
	read_file();
	h_bmp.height*=2;
	p_out = new struct pixel*[h_bmp.height];
	int i = 0;
	for(i;i<(h_bmp.height/2);i++)
	{
		p_out[i] = new struct pixel[h_bmp.width];
		for(int j = 0; j < h_bmp.width;j++)
			p_out[i][j] = p_in[i][j];
	}
	read_file();
	infile=infile2;
	h_bmp.height*=2;
	for(i;i<h_bmp.height;i++)
	{
		p_out[i] = new struct pixel[h_bmp.width];
		for(int j = 0; j<h_bmp.width;j++)
			p_out[i][j] = p_in[i-h_bmp.height/2][j];
	}
	write_file();
}




