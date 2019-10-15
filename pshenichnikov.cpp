#include "utilities.h"
using namespace std;
void comparison()
{
	char* infile2;
	read_file();
	long int sum1 = 0;
	int smp1 = 0;

	for (int i = 0; i < h_bmp.height; i++)
		for (int j = 0; j < h_bmp.width; j++)
		{
			if (p_in[i][j].b > p_in[i][j].r && p_in[i][j].b > p_in[i][j].g)
			{
				sum1 = sum1 + p_in[i][j].b;
			}
			if (p_in[i][j].r > p_in[i][j].b && p_in[i][j].r > p_in[i][j].g)
			{
				sum1 = sum1 + p_in[i][j].r;
			}
			if (p_in[i][j].g > p_in[i][j].b && p_in[i][j].g > p_in[i][j].r)
			{
				sum1 = sum1 + p_in[i][j].g;
			}
			smp1++;
		}

	infile = infile2;
	read_file();
	long int sum2 = 0;
	int smp2 = 0;

	for (int i = 0; i < h_bmp.height; i++)
		for (int j = 0; j < h_bmp.width; j++)
		{
			if (p_in[i][j].b > p_in[i][j].r && p_in[i][j].b > p_in[i][j].g)
			{
				sum2 = sum2 + p_in[i][j].b;
			}
			if (p_in[i][j].r > p_in[i][j].b && p_in[i][j].r > p_in[i][j].g)
			{
				sum2 = sum2 + p_in[i][j].r;
			}
			if (p_in[i][j].g > p_in[i][j].b && p_in[i][j].g > p_in[i][j].r)
			{
				sum2 = sum2 + p_in[i][j].g;
			}
			smp2++;
		}

	if (sum1 / smp1 == sum2 / smp2)
		cout << "  the result of the comparison: BOTH images are of the SAME brightness [" << sum2 / smp2 << "]\n";
	else
	{
		if (sum1 / smp1 > sum2 / smp2)
			cout << "  the result of the comparison: the FIRST image ["<< sum1 / smp1 <<"] is LIGHTER than the SECOND [" << sum2 / smp2 << "] \n";
		else
			cout << "  the result of the comparison: the FIRST image [" << sum1 / smp1 << "] is DARKER than the SECOND [" << sum2 / smp2 << "] \n";
	}
	
}
