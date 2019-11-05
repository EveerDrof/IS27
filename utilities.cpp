#include "utilities.h"

using namespace std;
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

void read_file(const char *infile,picture &pic)
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
	fread(&pic.h_bmp, sizeof(struct head), 1, fd);
	int pad = get_pad(pic.h_bmp.width);
	pic.arr = new  pixel*[pic.h_bmp.height];
	for (i = 0; i < pic.h_bmp.height; i++)
	{
		pic.arr[i] = new struct pixel[pic.h_bmp.width];
		for (j = 0; j < pic.h_bmp.width; j++)
		{
			n = fread(&pic.arr[i][j], 3, 1, fd);
		}
		if (pad != 0)
			fread(buf, pad, 1, fd);
	}
	fclose(fd);
}

void write_file(const char *outfile,picture &pic)
{
	int i, j;
	struct pixel buf[4];
	FILE *fd = fopen(outfile, "wb");
	if (!fd)
	{
		perror("open file for write");
		exit(1);
	}
	fwrite(&pic.h_bmp, sizeof(struct head), 1, fd);
	int pad = get_pad(pic.h_bmp.width);
	for (i = 0; i < pic.h_bmp.height; i++)
	{
		for (j = 0; j < pic.h_bmp.width; j++)
			fwrite(&pic.arr[i][j], 3, 1, fd);
		if (pad != 0)
			fwrite(buf, pad, 1, fd);
	}
	cout << "\nbyte write= " << ftell(fd) << endl;
	fclose(fd);
}
