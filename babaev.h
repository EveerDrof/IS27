#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

using namespace std;

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

struct pixel **p_in; 
struct pixel **p_out; 
struct head h_bmp;

struct pointOfPixel point1;
struct pointOfPixel point2;
struct pointOfPixel tempPoint1;
struct pointOfPixel tempPoint2;
struct pixel color;

char *infile;
char *outfile;

void lineshort(pointOfPixel, pointOfPixel, pointOfPixel, pointOfPixel, pixel );
void lineinf(pointOfPixel, pointOfPixel, pixel);
void circle(int, int, int, int, pixel);
void circle2(int, int, int, int, pixel);
void filledcircle(int, int, int, pixel);

int get_pad(int);
void read_file();
void write_file();
void help();

int get_pad(int width)
{
	int i=0;
	while( (width*3 + i) % 4 != 0)
		i++;
	return i;
}

void help()
{
    cout << "\nusage: \n";
	cout << "  progmam_name lineinf x1 y1 x2 y2 Size R G B in_file out_file \n";
	cout << "  progmam_name lineshort x1 y1 x2 y2 Size R G B in_file out_file \n";
	cout << "  progmam_name circle x0 y0 Radius Size R G B in_file out_file \n";
	cout << "  progmam_name circle2 x0 y0 Radius Size R G B in_file out_file \n";
	cout << "  progmam_name filledcircle x0 y0 Radius R G B in_file out_file \n";
	system("Pause");
}

int main(int argc, char** argv)
{
	setlocale(0, "");

    if(argc < 3)
    {
		help();
		return 1;
    }
  
    if (strcmp(argv[1], "lineshort"     ) &&
		strcmp(argv[1], "lineinf"       ) &&
		strcmp(argv[1], "circle"        ) &&
		strcmp(argv[1], "circle2"       ) &&
		strcmp(argv[1], "filledcircle"  )   )
    {
		help();
		return 1;
    }

	if(!strcmp(argv[1], "lineinf"))
	{
		point1.x = atof(argv[2]);
		point1.y = atof(argv[3]);
		point2.x = atof(argv[4]);
		point2.y = atof(argv[5]);

		int size = atoi(argv[6]);

		color.r = atoi(argv[7]); 
		color.g = atoi(argv[8]); 
		color.b = atoi(argv[9]); 

		if (argc < 12)
		{
			help();
			return 1;
		}
		infile = argv[10];
		outfile = argv[11];
		read_file();
		for (int i = 0; i < size; i++)
		{
			point1.y += i;
			point2.y += i;
			lineinf(point1, point2, color);
			point1.y -= i;
			point2.y -= i;

			point1.x -= i;
			point2.x -= i;
			lineinf(point1, point2, color);
			point1.x += i;
			point2.x += i;

			if (i != size-1)
			{
				point1.y -= i;
				point2.y -= i;
				lineinf(point1, point2, color);
				point1.y += i;
				point2.y += i;

				point1.x += i;
				point2.x += i;
				lineinf(point1, point2, color);
				point1.x -= i;
				point2.x -= i;
			}
		}
		write_file();
	}

	if(!strcmp(argv[1], "lineshort"))
	{
		point1.x = atof(argv[2]);
		point1.y = atof(argv[3]);
		point2.x = atof(argv[4]);
		point2.y = atof(argv[5]);

		tempPoint1 = point1; 
		tempPoint2 = point2;

		int size = atoi(argv[6]);

		color.r = atoi(argv[7]);
		color.g = atoi(argv[8]);
		color.b = atoi(argv[9]);

		if (argc < 12)
		{
			help();
			return 1;
		}
		infile = argv[10];
		outfile = argv[11];
		read_file();
		for (int i = 0; i < size; i++)
		{
			point1.y += i;
			point2.y += i;
			lineshort(point1, point2, tempPoint1, tempPoint2, color);
			point1.y -= i;
			point2.y -= i;

			point1.x -= i;
			point2.x -= i;
			lineshort(point1, point2, tempPoint1, tempPoint2, color);
			point1.x += i;
			point2.x += i;

			if (i != size - 1)
			{
				point1.y -= i;
				point2.y -= i;
				lineshort(point1, point2, tempPoint1, tempPoint2, color);
				point1.y += i;
				point2.y += i;

				point1.x += i;
				point2.x += i;
				lineshort(point1, point2, tempPoint1, tempPoint2, color);
				point1.x -= i;
				point2.x -= i;
			}
		}
		write_file();
	}

	if (!strcmp(argv[1], "circle"))
	{
		int x0 = atoi(argv[2]);
		int y0 = atoi(argv[3]);
		int R = atoi(argv[4]);
		int Size = atoi(argv[5]);;

		color.r = atoi(argv[6]);
		color.g = atoi(argv[7]);
		color.b = atoi(argv[8]);

		if (argc < 11)
		{
			help();
			return 1;
		}
		infile = argv[9];
		outfile = argv[10];
		bool noyes;
		cout << "\nХотите выбрать интерактивный режим?\n";
		cout << "\n(в ином случае будет нарисована одна простая окружность с заданными в консольной строке параметрами)\n";
		cout << "\n1 (интерактив) или 0 (одна окружность): "; cin >> noyes;
		read_file();

		if (noyes)
		{
			int scenario; cout << "Доступные сценарии:\n\n";
			cout << "1 - Рисование заканчивается, когда радиус, уменьшаясь, достигает определенного значения.\n";
			cout << "2 - Рисование заканчивается, когда радиус, увеличиваясь, достигает определенного значения.\n";
			cout << "3 - Рисование заканчивается, когда координата центра x, уменьшаясь, достигает определенного значения.\n";
			cout << "4 - Рисование заканчивается, когда координата центра x, увеличиваясь, достигает определенного значения.\n";
			cout << "5 - Рисование заканчивается, когда координата центра y, уменьшаясь, достигает определенного значения.\n";
			cout << "6 - Рисование заканчивается, когда координата центра y, увеличиваясь, достигает определенного значения.\n";
			cout << "7 - Рисование заканчивается, когда одно из значений R, G, B, уменьшаясь, достигает определенного значения.\n";
			cout << "8 - Рисование заканчивается, когда одно из значений R, G, B, увеличиваясь, достигает определенного значения.\n";
			cout << "9 - Рисование заканчивается, когда одно из значений R, G, уменьшаясь, достигает определенного значения.\n";
			cout << "10 - Рисование заканчивается, когда одно из значений R, G, увеличиваясь, достигает определенного значения.\n";
			cout << "11 - Рисование заканчивается, когда одно из значений R, B, уменьшаясь, достигает определенного значения.\n";
			cout << "12 - Рисование заканчивается, когда одно из значений R, B, увеличиваясь, достигает определенного значения.\n";
			cout << "13 - Рисование заканчивается, когда одно из значений G, B, уменьшаясь, достигает определенного значения.\n";
			cout << "14 - Рисование заканчивается, когда одно из значений G, B, увеличиваясь, достигает определенного значения.\n";
			cout << "15 - Рисование заканчивается, когда значение R, уменьшаясь, достигает определенного значения.\n";
			cout << "16 - Рисование заканчивается, когда значение R, увеличиваясь, достигает определенного значения.\n";
			cout << "17 - Рисование заканчивается, когда значение G, уменьшаясь, достигает определенного значения.\n";
			cout << "18 - Рисование заканчивается, когда значение G, увеличиваясь, достигает определенного значения.\n";
			cout << "19 - Рисование заканчивается, когда значение B, уменьшаясь, достигает определенного значения.\n";
			cout << "20 - Рисование заканчивается, когда значение B, увеличиваясь, достигает определенного значения.\n";
			cout << "21 - Рисование заканчивается, когда счетчик итератора достигает определенного значения.\n";
			cout << "22 - Рисование заканчивается, когда значение Size, уменьшаясь, достигает определенного значения.\n";
			cout << "23 - Рисование заканчивается, когда значение Size, увеличиваясь, достигает определенного значения.\n";

			cout << "\nВыберете сценарий: "; cin >> scenario;

			//Конечные значения для сценариев.

			int radend;
			int x0end;
			int y0end;
			int Rend;
			int Gend;
			int Bend;
			int Iterend;
			int Sizeend;

			if (scenario == 1 or scenario == 2)
			{
				cout << "Введите конечный радиус: "; cin >> radend;
			}
			if (scenario == 3 or scenario == 4)
			{
				cout << "Введите конечную координату x: "; cin >> x0end;
			}
			if (scenario == 5 or scenario == 6)
			{
				cout << "Введите конечную координату y: "; cin >> y0end;
			}
			if (scenario == 7 or scenario == 8)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение G: "; cin >> Gend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 9 or scenario == 10)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение G: "; cin >> Gend;
			}
			if (scenario == 11 or scenario == 12)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 13 or scenario == 14)
			{
				cout << "Введите конечное значение G: "; cin >> Gend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 15 or scenario == 16)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
			}
			if (scenario == 17 or scenario == 18)
			{
				cout << "Введите конечное значение G: "; cin >> Gend;
			}
			if (scenario == 19 or scenario == 20)
			{
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 21)
			{
				cout << "Введите количество повторений: "; cin >> Iterend;
			}
			if (scenario == 22 or scenario == 23)
			{
				cout << "Введите конечное значение Size: "; cin >> Sizeend;
			}

			int stepX0 = 0;
			int stepY0 = 0;
			int stepR = 0;
			int stepSize = 0;
			int stepColorR = 0;
			int stepColorG = 0;
			int stepColorB = 0;

			double x0A, x0B, x0C;
			double y0A, y0B, y0C;
			double RA, RB, RC;
			double cRA, cRB, cRC;
			double cGA, cGB, cGC;
			double cBA, cBB, cBC;
			double SizeA, SizeB, SizeC;

			bool ez; cout << "\nХотите использовать в рисовании линейные преобразования или сложные формулы? (1 или 0): "; cin >> ez;
			cout << "\nЗнак следующих переменных имеет большое значение и определяет направление изменения!\n\n";
			if (ez)
			{
				cout << "Введите stepX0 (шаг изменения координаты x центра окружности): "; cin >> stepX0;
				cout << "Введите stepY0 (шаг изменения координаты y центра окружности): "; cin >> stepY0;
				cout << "Введите stepR (шаг изменения радиуса окружности): "; cin >> stepR;
				cout << "Введите stepSize (шаг изменения радиуса окружности): "; cin >> stepSize;
				cout << "Введите stepColorR (шаг изменения красного спектра цвета): "; cin >> stepColorR;
				cout << "Введите stepColorG (шаг изменения зелёного спектра цвета): "; cin >> stepColorG;
				cout << "Введите stepColorB (шаг изменения синего спектра цвета): "; cin >> stepColorB;
			}
			else
			{
				cout << "\nФормула для x0:\n";
				cout << "x0=round(pow(A*x0, B)+C)\n";
				cout << "A = "; cin >> x0A;
				cout << "B = "; cin >> x0B;
				cout << "C = "; cin >> x0C;

				cout << "\nФормула для y0:\n";
				cout << "y0=round(pow(A*y0, B)+C)\n";
				cout << "A = "; cin >> y0A;
				cout << "B = "; cin >> y0B;
				cout << "C = "; cin >> y0C;

				cout << "\nФормула для R:\n";
				cout << "R=round(pow(A*R, B)+C)\n";
				cout << "A = "; cin >> RA;
				cout << "B = "; cin >> RB;
				cout << "C = "; cin >> RC;

				cout << "\nФормула для Size:\n";
				cout << "Size=round(pow(A*Size, B)+C)\n";
				cout << "A = "; cin >> SizeA;
				cout << "B = "; cin >> SizeB;
				cout << "C = "; cin >> SizeC;

				cout << "\nФормула для color.r:\n";
				cout << "color.r=round(pow(A*color.r, B)+C)\n";
				cout << "A = "; cin >> cRA;
				cout << "B = "; cin >> cRB;
				cout << "C = "; cin >> cRC;

				cout << "\nФормула для color.g:\n";
				cout << "color.g=round(pow(A*color.g, B)+C)\n";
				cout << "A = "; cin >> cGA;
				cout << "B = "; cin >> cGB;
				cout << "C = "; cin >> cGC;

				cout << "\nФормула для color.b:\n";
				cout << "color.b=round(pow(A*color.b, B)+C)\n";
				cout << "A = "; cin >> cBA;
				cout << "B = "; cin >> cBB;
				cout << "C = "; cin >> cBC;
			}

			cout << "\nЕсли что-то пошло не по плану и получился бесконечный цикл, используйте сочитание клавиш Ctrl+C.\n";

			if (scenario == 1)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					R > radend; // условия
					R += stepR, Size += stepSize, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 2)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					R < radend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 3)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					x0 >= x0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 4)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					x0 <= x0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 5)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					y0 >= y0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 6)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					y0 <= y0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 7)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend && color.g >= Gend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 8)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend && color.g <= Gend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 9)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend && color.g >= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 10)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend && color.g <= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 11)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 12)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 13)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g >= Gend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 14)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g <= Gend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 15)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 16)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 17)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g >= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 18)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g <= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 19)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 20)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 21)
			{
				int iteration = 0;
				for (x0, y0, R, color.r, color.g, color.b, Size, iteration; // переменные
					iteration < Iterend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, iteration++, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 22)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					Size >= Sizeend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 23)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					Size <= Sizeend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
		}
		else
			circle(x0, y0, R, Size, color);
		write_file();
	}

	if (!strcmp(argv[1], "circle2"))
	{
		int x0 = atoi(argv[2]);
		int y0 = atoi(argv[3]);
		int R = atoi(argv[4]);
		int Size = atoi(argv[5]);

		color.r = atoi(argv[6]);
		color.g = atoi(argv[7]);
		color.b = atoi(argv[8]);

		if (argc < 11)
		{
			help();
			return 1;
		}
		infile = argv[9];
		outfile = argv[10];
		bool noyes; 
		cout << "\nХотите выбрать интерактивный режим?\n";
		cout << "\n(в ином случае будет нарисована одна простая окружность с заданными в консольной строке параметрами)\n";
		cout << "\n1 (интерактив) или 0 (одна окружность): "; cin >> noyes;
		read_file();

		if (noyes)
		{
			int scenario; cout << "Доступные сценарии:\n\n";
			cout << "1 - Рисование заканчивается, когда радиус, уменьшаясь, достигает определенного значения.\n";
			cout << "2 - Рисование заканчивается, когда радиус, увеличиваясь, достигает определенного значения.\n";
			cout << "3 - Рисование заканчивается, когда координата центра x, уменьшаясь, достигает определенного значения.\n";
			cout << "4 - Рисование заканчивается, когда координата центра x, увеличиваясь, достигает определенного значения.\n";
			cout << "5 - Рисование заканчивается, когда координата центра y, уменьшаясь, достигает определенного значения.\n";
			cout << "6 - Рисование заканчивается, когда координата центра y, увеличиваясь, достигает определенного значения.\n";
			cout << "7 - Рисование заканчивается, когда одно из значений R, G, B, уменьшаясь, достигает определенного значения.\n";
			cout << "8 - Рисование заканчивается, когда одно из значений R, G, B, увеличиваясь, достигает определенного значения.\n";
			cout << "9 - Рисование заканчивается, когда одно из значений R, G, уменьшаясь, достигает определенного значения.\n";
			cout << "10 - Рисование заканчивается, когда одно из значений R, G, увеличиваясь, достигает определенного значения.\n";
			cout << "11 - Рисование заканчивается, когда одно из значений R, B, уменьшаясь, достигает определенного значения.\n";
			cout << "12 - Рисование заканчивается, когда одно из значений R, B, увеличиваясь, достигает определенного значения.\n";
			cout << "13 - Рисование заканчивается, когда одно из значений G, B, уменьшаясь, достигает определенного значения.\n";
			cout << "14 - Рисование заканчивается, когда одно из значений G, B, увеличиваясь, достигает определенного значения.\n";
			cout << "15 - Рисование заканчивается, когда значение R, уменьшаясь, достигает определенного значения.\n";
			cout << "16 - Рисование заканчивается, когда значение R, увеличиваясь, достигает определенного значения.\n";
			cout << "17 - Рисование заканчивается, когда значение G, уменьшаясь, достигает определенного значения.\n";
			cout << "18 - Рисование заканчивается, когда значение G, увеличиваясь, достигает определенного значения.\n";
			cout << "19 - Рисование заканчивается, когда значение B, уменьшаясь, достигает определенного значения.\n";
			cout << "20 - Рисование заканчивается, когда значение B, увеличиваясь, достигает определенного значения.\n";
			cout << "21 - Рисование заканчивается, когда счетчик итератора достигает определенного значения.\n";
			cout << "22 - Рисование заканчивается, когда значение Size, уменьшаясь, достигает определенного значения.\n";
			cout << "23 - Рисование заканчивается, когда значение Size, увеличиваясь, достигает определенного значения.\n";

			cout << "\nВыберете сценарий: "; cin >> scenario;

			//Конечные значения для сценариев.

			int radend;
			int x0end;
			int y0end;
			int Rend;
			int Gend;
			int Bend;
			int Iterend;
			int Sizeend;

			if (scenario == 1 or scenario == 2) 
			{ 
				cout << "Введите конечный радиус: "; cin >> radend; 
			}
			if (scenario == 3 or scenario == 4) 
			{ 
				cout << "Введите конечную координату x: "; cin >> x0end; 
			}
			if (scenario == 5 or scenario == 6) 
			{ 
				cout << "Введите конечную координату y: "; cin >> y0end; 
			}
			if (scenario == 7 or scenario == 8) 
			{ 
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение G: "; cin >> Gend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 9 or scenario == 10)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение G: "; cin >> Gend;
			}
			if (scenario == 11 or scenario == 12)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 13 or scenario == 14)
			{
				cout << "Введите конечное значение G: "; cin >> Gend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 15 or scenario == 16)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
			}
			if (scenario == 17 or scenario == 18)
			{
				cout << "Введите конечное значение G: "; cin >> Gend;
			}
			if (scenario == 19 or scenario == 20)
			{
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 21)
			{
				cout << "Введите количество повторений: "; cin >> Iterend;
			}
			if (scenario == 22 or scenario == 23)
			{
				cout << "Введите конечное значение Size: "; cin >> Sizeend;
			}

			int stepX0 = 0;
			int stepY0 = 0;
			int stepR = 0;
			int stepSize = 0;
			int stepColorR = 0;
			int stepColorG = 0;
			int stepColorB = 0;

			double x0A, x0B, x0C;
			double y0A, y0B, y0C;
			double RA, RB, RC;
			double cRA, cRB, cRC;
			double cGA, cGB, cGC;
			double cBA, cBB, cBC;
			double SizeA, SizeB, SizeC;

			bool ez; cout << "\nХотите использовать в рисовании линейные преобразования или сложные формулы? (1 или 0): "; cin >> ez;
			cout << "\nЗнак следующих переменных имеет большое значение и определяет направление изменения!\n\n";
			if (ez)
			{
				cout << "Введите stepX0 (шаг изменения координаты x центра окружности): "; cin >> stepX0;
				cout << "Введите stepY0 (шаг изменения координаты y центра окружности): "; cin >> stepY0;
				cout << "Введите stepR (шаг изменения радиуса окружности): "; cin >> stepR;
				cout << "Введите stepSize (шаг изменения радиуса окружности): "; cin >> stepSize;
				cout << "Введите stepColorR (шаг изменения красного спектра цвета): "; cin >> stepColorR;
				cout << "Введите stepColorG (шаг изменения зелёного спектра цвета): "; cin >> stepColorG;
				cout << "Введите stepColorB (шаг изменения синего спектра цвета): "; cin >> stepColorB;
			}
			else
			{
				cout << "\nФормула для x0:\n";
				cout << "x0=round(pow(A*x0, B)+C)\n";
				cout << "A = "; cin >> x0A;
				cout << "B = "; cin >> x0B;
				cout << "C = "; cin >> x0C;

				cout << "\nФормула для y0:\n";
				cout << "y0=round(pow(A*y0, B)+C)\n";
				cout << "A = "; cin >> y0A;
				cout << "B = "; cin >> y0B;
				cout << "C = "; cin >> y0C;

				cout << "\nФормула для R:\n";
				cout << "R=round(pow(A*R, B)+C)\n";
				cout << "A = "; cin >> RA;
				cout << "B = "; cin >> RB;
				cout << "C = "; cin >> RC;

				cout << "\nФормула для Size:\n";
				cout << "Size=round(pow(A*Size, B)+C)\n";
				cout << "A = "; cin >> SizeA;
				cout << "B = "; cin >> SizeB;
				cout << "C = "; cin >> SizeC;

				cout << "\nФормула для color.r:\n";
				cout << "color.r=round(pow(A*color.r, B)+C)\n";
				cout << "A = "; cin >> cRA;
				cout << "B = "; cin >> cRB;
				cout << "C = "; cin >> cRC;

				cout << "\nФормула для color.g:\n";
				cout << "color.g=round(pow(A*color.g, B)+C)\n";
				cout << "A = "; cin >> cGA;
				cout << "B = "; cin >> cGB;
				cout << "C = "; cin >> cGC;

				cout << "\nФормула для color.b:\n";
				cout << "color.b=round(pow(A*color.b, B)+C)\n";
				cout << "A = "; cin >> cBA;
				cout << "B = "; cin >> cBB;
				cout << "C = "; cin >> cBC;
			}

			cout << "\nЕсли что-то пошло не по плану и получился бесконечный цикл, используйте сочитание клавиш Ctrl+C.\n";

			if (scenario == 1)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					R > radend; // условия
					R += stepR, Size += stepSize, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 2)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					R < radend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 3)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					x0 >= x0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 4)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					x0 <= x0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 5)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					y0 >= y0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 6)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					y0 <= y0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 7)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend && color.g >= Gend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 8)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend && color.g <= Gend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 9)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend && color.g >= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 10)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend && color.g <= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 11)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 12)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 13)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g >= Gend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 14)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g <= Gend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 15)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r >= Rend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 16)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.r <= Rend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 17)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g >= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 18)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.g <= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 19)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 20)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 21)
			{
				int iteration = 0;
				for (x0, y0, R, color.r, color.g, color.b, Size, iteration ; // переменные
					iteration < Iterend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, iteration++, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 22)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					Size >= Sizeend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 23)
			{
				for (x0, y0, R, color.r, color.g, color.b, Size; // переменные
					Size <= Sizeend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, Size += stepSize) // шаги изменения
				{
					circle2(x0, y0, R, Size, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						Size = round(pow(SizeA*Size, SizeB) + SizeC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
		}
		else
			circle2(x0, y0, R, Size, color);
		write_file();
	}

	if (!strcmp(argv[1], "filledcircle"))
	{
		int x0 = atoi(argv[2]);
		int y0 = atoi(argv[3]);
		int R = atoi(argv[4]);

		color.r = atoi(argv[5]);
		color.g = atoi(argv[6]);
		color.b = atoi(argv[7]);

		if (argc < 10)
		{
			help();
			return 1;
		}
		infile = argv[8];
		outfile = argv[9];

		bool noyes; 
		cout << "\nХотите выбрать интерактивный режим?\n";
		cout << "\n(в ином случае будет нарисована одна простая окружность с заданными в консольной строке параметрами)\n";
		cout << "\n1 (интерактив) или 0 (одна окружность): "; cin >> noyes;
		read_file();

		if (noyes)
		{
			int scenario; cout << "Доступные сценарии:\n\n";
			cout << "1 - Рисование заканчивается, когда радиус, уменьшаясь, достигает определенного значения.\n";
			cout << "2 - Рисование заканчивается, когда радиус, увеличиваясь, достигает определенного значения.\n";
			cout << "3 - Рисование заканчивается, когда координата центра x, уменьшаясь, достигает определенного значения.\n";
			cout << "4 - Рисование заканчивается, когда координата центра x, увеличиваясь, достигает определенного значения.\n";
			cout << "5 - Рисование заканчивается, когда координата центра y, уменьшаясь, достигает определенного значения.\n";
			cout << "6 - Рисование заканчивается, когда координата центра y, увеличиваясь, достигает определенного значения.\n";
			cout << "7 - Рисование заканчивается, когда одно из значений R, G, B, уменьшаясь, достигает определенного значения.\n";
			cout << "8 - Рисование заканчивается, когда одно из значений R, G, B, увеличиваясь, достигает определенного значения.\n";
			cout << "9 - Рисование заканчивается, когда одно из значений R, G, уменьшаясь, достигает определенного значения.\n";
			cout << "10 - Рисование заканчивается, когда одно из значений R, G, увеличиваясь, достигает определенного значения.\n";
			cout << "11 - Рисование заканчивается, когда одно из значений R, B, уменьшаясь, достигает определенного значения.\n";
			cout << "12 - Рисование заканчивается, когда одно из значений R, B, увеличиваясь, достигает определенного значения.\n";
			cout << "13 - Рисование заканчивается, когда одно из значений G, B, уменьшаясь, достигает определенного значения.\n";
			cout << "14 - Рисование заканчивается, когда одно из значений G, B, увеличиваясь, достигает определенного значения.\n";
			cout << "15 - Рисование заканчивается, когда значение R, уменьшаясь, достигает определенного значения.\n";
			cout << "16 - Рисование заканчивается, когда значение R, увеличиваясь, достигает определенного значения.\n";
			cout << "17 - Рисование заканчивается, когда значение G, уменьшаясь, достигает определенного значения.\n";
			cout << "18 - Рисование заканчивается, когда значение G, увеличиваясь, достигает определенного значения.\n";
			cout << "19 - Рисование заканчивается, когда значение B, уменьшаясь, достигает определенного значения.\n";
			cout << "20 - Рисование заканчивается, когда значение B, увеличиваясь, достигает определенного значения.\n";
			cout << "21 - Рисование заканчивается, когда счетчик итератора достигает определенного значения.\n";
			cout << "\nВыберете сценарий: "; cin >> scenario;

			//Конечные значения для сценариев.

			int radend;
			int x0end;
			int y0end;
			int Rend;
			int Gend;
			int Bend;
			int Iterend;

			if (scenario == 1 or scenario == 2) 
			{ 
				cout << "Введите конечный радиус: "; cin >> radend; 
			}
			if (scenario == 3 or scenario == 4) 
			{ 
				cout << "Введите конечную координату x: "; cin >> x0end; 
			}
			if (scenario == 5 or scenario == 6) 
			{ 
				cout << "Введите конечную координату y: "; cin >> y0end; 
			}
			if (scenario == 7 or scenario == 8) 
			{ 
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение G: "; cin >> Gend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 9 or scenario == 10)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение G: "; cin >> Gend;
			}
			if (scenario == 11 or scenario == 12)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 13 or scenario == 14)
			{
				cout << "Введите конечное значение G: "; cin >> Gend;
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 15 or scenario == 16)
			{
				cout << "Введите конечное значение R: "; cin >> Rend;
			}
			if (scenario == 17 or scenario == 18)
			{
				cout << "Введите конечное значение G: "; cin >> Gend;
			}
			if (scenario == 19 or scenario == 20)
			{
				cout << "Введите конечное значение B: "; cin >> Bend;
			}
			if (scenario == 21)
			{
				cout << "Введите количество повторений: "; cin >> Iterend;
			}

			int stepX0 = 0;
			int stepY0 = 0;
			int stepR = 0;
			int stepColorR = 0;
			int stepColorG = 0;
			int stepColorB = 0;

			double x0A, x0B, x0C;
			double y0A, y0B, y0C;
			double RA, RB, RC;
			double cRA, cRB, cRC;
			double cGA, cGB, cGC;
			double cBA, cBB, cBC;

			bool ez; cout << "\nХотите использовать в рисовании линейные преобразования или сложные формулы? (1 или 0): "; cin >> ez;
			cout << "\nЗнак следующих переменных имеет большое значение и определяет направление изменения!\n\n";
			if (ez)
			{
				cout << "Введите stepX0 (шаг изменения координаты x центра окружности): "; cin >> stepX0;
				cout << "Введите stepY0 (шаг изменения координаты y центра окружности): "; cin >> stepY0;
				cout << "Введите stepR (шаг изменения радиуса окружности): "; cin >> stepR;
				cout << "Введите stepColorR (шаг изменения красного спектра цвета): "; cin >> stepColorR;
				cout << "Введите stepColorG (шаг изменения зелёного спектра цвета): "; cin >> stepColorG;
				cout << "Введите stepColorB (шаг изменения синего спектра цвета): "; cin >> stepColorB;
			}
			else
			{
				cout << "\nФормула для x0:\n";
				cout << "x0=round(pow(A*x0, B)+C)\n";
				cout << "A = "; cin >> x0A;
				cout << "B = "; cin >> x0B;
				cout << "C = "; cin >> x0C;

				cout << "\nФормула для y0:\n";
				cout << "y0=round(pow(A*y0, B)+C)\n";
				cout << "A = "; cin >> y0A;
				cout << "B = "; cin >> y0B;
				cout << "C = "; cin >> y0C;

				cout << "\nФормула для R:\n";
				cout << "R=round(pow(A*R, B)+C)\n";
				cout << "A = "; cin >> RA;
				cout << "B = "; cin >> RB;
				cout << "C = "; cin >> RC;

				cout << "\nФормула для color.r:\n";
				cout << "color.r=round(pow(A*color.r, B)+C)\n";
				cout << "A = "; cin >> cRA;
				cout << "B = "; cin >> cRB;
				cout << "C = "; cin >> cRC;

				cout << "\nФормула для color.g:\n";
				cout << "color.g=round(pow(A*color.g, B)+C)\n";
				cout << "A = "; cin >> cGA;
				cout << "B = "; cin >> cGB;
				cout << "C = "; cin >> cGC;

				cout << "\nФормула для color.b:\n";
				cout << "color.b=round(pow(A*color.b, B)+C)\n";
				cout << "A = "; cin >> cBA;
				cout << "B = "; cin >> cBB;
				cout << "C = "; cin >> cBC;
			}

			cout << "\nЕсли что-то пошло не по плану и получился бесконечный цикл, используйте сочитание клавиш Ctrl+C.\n";

			if (scenario == 1)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					R > radend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 2)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					R < radend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 3)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					x0 >= x0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 4)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					x0 <= x0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 5)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					y0 >= y0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 6)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					y0 <= y0end; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 7)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r >= Rend && color.g >= Gend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 8)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r <= Rend && color.g <= Gend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 9)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r >= Rend && color.g >= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 10)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r <= Rend && color.g <= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 11)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r >= Rend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 12)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r <= Rend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 13)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.g >= Gend && color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 14)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.g <= Gend && color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 15)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r >= Rend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 16)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.r <= Rend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 17)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.g >= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 18)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.g <= Gend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 19)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.b >= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 20)
			{
				for (x0, y0, R, color.r, color.g, color.b; // переменные
					color.b <= Bend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
			if (scenario == 21)
			{
				int iteration = 0;
				for (x0, y0, R, color.r, color.g, color.b, iteration ; // переменные
					iteration < Iterend; // условия
					R += stepR, x0 += stepX0, y0 += stepY0, color.r += stepColorR, color.g += stepColorG, color.b += stepColorB, iteration++) // шаги изменения
				{
					filledcircle(x0, y0, R, color);
					if (!ez)
					{
						x0 = round(pow(x0A*x0, x0B) + x0C);
						y0 = round(pow(y0A*y0, y0B) + y0C);
						R = round(pow(RA*R, RB) + RC);
						color.r = round(pow(cRA*color.r, cRB) + cRC);
						color.g = round(pow(cGA*color.g, cGB) + cGC);
						color.b = round(pow(cBA*color.b, cBB) + cBC);
					}
				}
			}
		}
		else
			filledcircle(x0, y0, R, color);
		write_file();
	}
    return 0;
}

double angleToYLine(pointOfPixel point1, pointOfPixel point2) 
{
	int vector1[2] = { point2.x - point1.x, point2.y - point1.y };
	int vector2[2] = { 1, 0 };
	double angle = acos((vector1[0] * vector2[0] + vector1[1] * vector2[1]) / (sqrt(pow(vector1[0], 2)+pow(vector1[1], 2))*sqrt(pow(vector2[0], 2) + pow(vector2[1], 2))));
	return angle;
}

void lineinf(pointOfPixel point1, pointOfPixel point2, pixel color)
{
	p_out = p_in;
	double angle = angleToYLine(point1, point2);
	int stat;
	if (angle < atan(1))
		stat = 1;
	else if (angle > atan(1)+0.0000001)
		stat = 2;
	else
		stat = 3;
	for (int y = 0; y < h_bmp.height; y++)
	{
		for (int x = 0, count = 0; x < h_bmp.width; x++, count = 0)
		{
			if (stat == 1 or stat == 2)
			{
				if (((x + 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y >= y - 0.5 &&
					((x + 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y <= y + 0.5)
					count++;
				if (((x - 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y >= y - 0.5 &&
					((x - 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y <= y + 0.5)
					count++;
				if (((y + 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x > x - 0.5 &&
					((y + 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x < x + 0.5)
					count++;
				if (((y - 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x > x - 0.5 &&
					((y - 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x < x + 0.5)
					count++;
			}
			else if (stat == 3)
			{
				if (y == ((x - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y)
					count += 2;
			}
			if (count>=2)
			{
				p_out[y][x].b = color.b;
				p_out[y][x].g = color.g;
				p_out[y][x].r = color.r;
			}
		}
	}
}

void lineshort(pointOfPixel point1, pointOfPixel point2, pointOfPixel tempPoint1, pointOfPixel tempPoint2, pixel color)
{
	p_out = p_in;
	double angle = angleToYLine(point1, point2);
	int stat;
	if (angle < atan(1))
		stat = 1;
	else if (angle > atan(1) + 0.0000001)
		stat = 2;
	else
		stat = 3;
	int x1=tempPoint1.x, x2=tempPoint2.x;
	int y1 = tempPoint1.y, y2 = tempPoint2.y;
	if (x1 > x2)
	{
		x1 = point2.x; x2 = point1.x;
	}
	if (y1 > y2)
	{
		y1 = point2.y; y2 = point1.y;
	}
	for (int y = y1; y < y2+1; y++ )
	{
		for (int x = x1, count = 0; x < x2 + 1; x++, count = 0)
		{
			if (stat == 1 or stat == 2)
			{
				if (((x + 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y >= y - 0.5 &&
					((x + 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y <= y + 0.5)
					count++;
				if (((x - 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y >= y - 0.5 &&
					((x - 0.5 - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y <= y + 0.5)
					count++;
				if (((y + 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x > x - 0.5 &&
					((y + 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x < x + 0.5)
					count++;
				if (((y - 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x > x - 0.5 &&
					((y - 0.5 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y)) + point1.x < x + 0.5)
					count++;
			}
			else if (stat == 3)
			{
				if (y == ((x - point1.x)*(point2.y - point1.y) / (point2.x - point1.x)) + point1.y)
					count += 2;
			}
			if (count >= 2)
			{
				p_out[y][x].r = color.r;
				p_out[y][x].g = color.g;
				p_out[y][x].b = color.b;
			}
		}
	}
}

void circle(int x0, int y0, int R, int size, pixel color)
{
	p_out = p_in;
	int y = y0, y1 = 0;
	int r = R;
	for (int a = 1; a < size + 1; a++, R--)
	{
		for (int x = x0 + R, count = 0; x > x0 - R - 1; x--, count++)
		{
			y1 = sqrt(pow(R, 2) - pow(R - count, 2));

			p_out[(y0 + y1) % h_bmp.height][x%h_bmp.width].r = color.r; p_out[(y0 - y1) % h_bmp.height][x%h_bmp.width].r = color.r;
			p_out[(y0 + y1) % h_bmp.height][x%h_bmp.width].g = color.g; p_out[(y0 - y1) % h_bmp.height][x%h_bmp.width].g = color.g;
			p_out[(y0 + y1) % h_bmp.height][x%h_bmp.width].b = color.b; p_out[(y0 - y1) % h_bmp.height][x%h_bmp.width].b = color.b;

			p_out[(y0 - R + count) % h_bmp.height][(x0 - y1) % h_bmp.width].r = color.r; p_out[(y0 + R - count) % h_bmp.height][(x0 + y1) % h_bmp.width].r = color.r;
			p_out[(y0 - R + count) % h_bmp.height][(x0 - y1) % h_bmp.width].g = color.g; p_out[(y0 + R - count) % h_bmp.height][(x0 + y1) % h_bmp.width].g = color.g;
			p_out[(y0 - R + count) % h_bmp.height][(x0 - y1) % h_bmp.width].b = color.b; p_out[(y0 + R - count) % h_bmp.height][(x0 + y1) % h_bmp.width].b = color.b;
		}
	}
}

void circle2(int x0, int y0, int R, int size, pixel color)
{
	p_out = p_in;
	for (int y = y0 + R; y >= y0 - R; y--)
	{
		for (int x = x0 - R; x <= x0 + R; x++)
		{
			if ((pow(R, 2) >= pow(x - x0, 2) + pow(y - y0, 2)) && ((pow(R-size-1, 2) <= pow(x - x0, 2) + pow(y - y0, 2))))
			{
				p_out[y%h_bmp.height][x%h_bmp.width].r = color.r;
				p_out[y%h_bmp.height][x%h_bmp.width].g = color.g;
				p_out[y%h_bmp.height][x%h_bmp.width].b = color.b;
			}
		}
	}
}

void filledcircle(int x0, int y0, int R, pixel color)
{
	p_out = p_in;
	for (int y = y0 + R; y >= y0 - R; y--)
	{
		for (int x = x0 - R; x <= x0 + R; x++)
		{
			if (pow(R, 2) >= pow(x - x0, 2) + pow(y - y0, 2))
			{
				p_out[y%h_bmp.height][x%h_bmp.width].r = color.r;
				p_out[y%h_bmp.height][x%h_bmp.width].g = color.g;
				p_out[y%h_bmp.height][x%h_bmp.width].b = color.b;
			}
		}
	}
}

void read_file()
{
	long int count = 0;
	int i,j,n;
	struct pixel buf[4];
	FILE *fd = fopen(infile, "rb");
	if(!fd)
	{
		perror("open file for read");
		exit(1);
	}
	fread(&h_bmp, sizeof(struct head), 1, fd);
	int pad = get_pad(h_bmp.width);
	p_in = new struct pixel*[h_bmp.height];
	for(i=0; i < h_bmp.height; i++)
	{
		p_in[i] = new struct pixel[h_bmp.width];
		for(j=0; j < h_bmp.width; j++)
		{
			n = fread(&p_in[i][j], 3, 1, fd);
		}
		if(pad != 0)
			fread(buf, pad, 1, fd);
	}
	fclose(fd);
}

void write_file()
{
	int i,j;
	struct pixel buf[4];
	FILE *fd = fopen(outfile, "wb");
	if(!fd)
	{
		perror("open file for write");
		exit(1);
	}
	fwrite(&h_bmp, sizeof(struct head), 1, fd);
	int pad = get_pad(h_bmp.width);
	for(i=0; i < h_bmp.height; i++)
	{
		for(j=0; j < h_bmp.width; j++)
			fwrite(&p_out[i][j], 3, 1, fd);
		if(pad != 0)
			fwrite(buf, pad, 1, fd);
	}
	cout<< "\nbyte write= " << ftell(fd) << endl;
	fclose(fd);
}

