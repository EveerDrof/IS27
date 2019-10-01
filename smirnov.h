#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;
//Структура  пикселя
struct pixel
{
	//Чар занимает один байт и в политре rgb все цвета по одному байту поэтому
	//используем беззнаковый чар для хранения каждого цвета
	unsigned char b;
	unsigned char g;
	unsigned char r;
	//Перегрузка оператора сравнения для пикселя,чтобы их можно было сравнить 
	bool operator!=(pixel &pix)
	{
		if ((b != pix.b) || (g != pix.g) || (r != pix.r))
			return true;
		else
			return false;
	}
};
//Т.к компьютер автоматически выделит память чётную самому большом члену структуры нам нужно это убрать
//чтобы из bmp файла всё точь-вточь скопировалось
#pragma pack(push, 1)
//Структура с главной инфой картинки
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
//Отключаем нашу директиву по памяти
#pragma pack(pop)


//Структура данных для главной информации о картинке
struct head h_bmp;
//Массивы чаров(строки С-стайл)
char *infile;
char *infile2;

void compare(pixel**, pixel**);

//Похоже тут та же ситуация, что и для структуры head. Только для файла нам нужна чётность
int get_pad(int);

pixel** read_file();
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
	cout << "  chbmp in_file out_file \n";
}

int main(int argc, char** argv)
{
//Массивы для пикселей.Пока делаем их нулевыми
struct pixel **p_in=nullptr;
struct pixel **p_in2=nullptr;
	if (argc < 3)
	{
		help();
		return 1;
	}
	//Записываем из командной строки С-стайл в переменную  имя файла которое ввёл пользователь	
	infile = argv[1];
	
	p_in=read_file();

	infile = argv[2];
	p_in2=read_file();


	compare(p_in,p_in2);
	return 0;
}
//Функция для чтения будет возвращать двумерный массив пикселей
pixel** read_file()
{
	pixel** p_in;
	long int count = 0;
	int i, j, n;
	//Буферный массив пикселей
	struct pixel buf[4];
	FILE *fd = fopen(infile, "rb");
	if (!fd)
	{
		//Ошибка при открытии если не удалось открыть файл
		perror("open file for read");
		exit(1);
	}
	//Читаем из bmp файла в структуру head
	fread(&h_bmp, sizeof(struct head), 1, fd);
	//Для кратности
	int pad = get_pad(h_bmp.width);
	//Выделяем память на указатели на массивы пикселей
	p_in = new struct pixel*[h_bmp.height];
	//Циклы для чтения самих пикселей
	//Цикл по вертикали
	for (i = 0; i < h_bmp.height; i++)
	{
		//Выделяем память на пиксели
		p_in[i] = new struct pixel[h_bmp.width];
		//Цикл по горизонтали
		for (j = 0; j < h_bmp.width; j++)
		{
			//Считываем пиксели
			n = fread(&p_in[i][j], 3, 1, fd);
		}
		if (pad != 0)
			fread(buf, pad, 1, fd);
	}
	fclose(fd);
	return p_in;
}
void compare(pixel** p_in, pixel** p_in2)
{
	
	int count = 0;
	//Два цикла для пробега по двумерному массиву пикселей
	for (int Y = 0; Y < h_bmp.height; Y++)
	{
		for (int X = 0; X < h_bmp.width; X++)
		{
			//Исрользуем наш оператор для сравнения
			if (p_in[Y][X] != p_in2[Y][X])
			{
				count++;
			}
		}
	}
	cout <<count;
}
