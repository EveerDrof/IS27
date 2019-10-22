#pragma warning(disable:4996)
using namespace std;
//Структура  пикселя
#include "utilities.h"

char *infile2;

void compare(pixel**, pixel**);



int comparePics(int argc, char** argv)
{
//Массивы для пикселей.Пока делаем их нулевыми
struct pixel **p_in=nullptr;
struct pixel **p_in2=nullptr;
	if (argc < 3)
	{
		return 1;
	}
	//Записываем из командной строки С-стайл в переменную  имя файла которое ввёл пользователь	
	infile = argv[1];
	
	read_file();

	infile = argv[2];
	read_file();


	compare(p_in,p_in2);
	return 0;
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
			if (!(p_in[Y][X] == p_in2[Y][X]))
			{
				count++;
			}
		}
	}
	cout <<count;
}