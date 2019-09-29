#include "utilities.h"

void cutFromPic(struct pointOfPixel, struct pointOfPixel);

struct pointOfPixel   
{
	double x;
	double y;
};

void cutFromPic(struct pointOfPixel point1, struct pointOfPixel point2)
{
	read_file();

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

	write_file();

}