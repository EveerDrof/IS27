struct pixel
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
};
pixel blackPix{ 0,0,0 };
#pragma pack(push, 1)
struct head
{
	char type[2] = { 66,77 };
	unsigned int size = 138;
	unsigned int reserv = 0;
	unsigned int offset = 54;
	unsigned int head_size = 40;
	unsigned int width;
	unsigned int height;
	unsigned int end[7] = { 1572865,0,768,0,0,0,0 };
};
#pragma pack(pop)
struct pixel **p_out;
struct head h_bmp;
char *outfile;


int get_pad(int);
void write_file();
void help();
int get_pad(int width)
{
	int i = 0;
	while ((width * 3 + i) % 4 != 0)
		i++;
	return i;
}

void help()
{
	cout << "\nusage: \n";
	cout << "  chbmp intnumber out_file \n";
}
void horizontalLine(int posX)
{
	for (int I = 0; I < h_bmp.width; I++)
	{
		p_out[posX][I] = blackPix;
	}
}
void verticalLine(int posX, int posY)
{
	for (int I = posY; I < posY + h_bmp.height / 2; I++)
	{
		p_out[I][posX] = blackPix;
	}
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
