#include "utilities.h" 
void Glue()
{
	read_file();
	h_bmp.height*=2;
	p_out = new struct pixel*[h_bmp.heiht];
	int i = 0;
	for(i;i<(h_bmp.height/2);i++)
	{
		p_out[i] = new stuct pixel[h_bmp.width];
		for(int j = 0; j < h_bmp.width;j++)
			p_out[i][j] = p.in[i][j];
	}
	infile = infile2;
	read_file();
	h_bmp.height*=2;
	for(i;i<h_bmp.height;i++)
	{
		p_out[i][j] = new struct pixel[h_bmp.width];
		for(int j = 0; j<h_bmp.width;i++)
			p_out[i][j] = p_int[i-h_bmp.height/2][j];
	}
	write_file();
}




