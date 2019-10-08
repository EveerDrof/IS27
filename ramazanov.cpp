//Проверяем является ли линией череда пикселей
#include "utilities.h"
bool isLine(int Y ,int X)
{
	for (int I = X; I < h_bmp.width - 1; I++)
	{
		if (Y == 0)
		{
			if ( p_in[Y][I] == p_in[Y + 1][I])
				return false;
		}			
		if (Y == h_bmp.height-1)
		{
			if (p_in[Y][I] == p_in[Y - 1][I])
				return false;
		}
		else
		{
			//Если пиксель сверху или снизу равен текущему то это не линия 
			if (p_in[Y][I] == p_in[Y - 1][I] || p_in[Y][I] == p_in[Y + 1][I])
				return false;
			if (!(p_in[Y][I] == p_in[Y][I + 1]))
				break;
		}
	}
	return true;
}
int checkLines(int argc, char** argv)

{	//argс - число слов, которые ввёл пользователь в командную строку
	//argv-массив строк состоящий из чаров, которые ввёл пользователь в консоль
	//Записываем из командной строки в строки именя файла
	infile = argv[1];
	if (argc < 2)
	{
		help();
		return 1;
	}
	int count = 0;
	read_file();
	//Пробежимся по каждому пикселю
	//Цикл по вертикали
	for (int Y = 0; Y < h_bmp.height; Y++)
	{
		//Цикл по горизонтали
		for (int X = 0; X < h_bmp.width - 1; X++)
		{
			//Если пиксель равен следующему
			if (p_in[Y][X] == p_in[Y][X + 1])
			{
			
				if (Y == 0)
				{
					if (X == 0)
					{
						if ((!(p_in[Y][X] == p_in[Y+ 1][X ])) && (isLine(Y, X)))
							count++;
					}
					else
					{
						if ((!(p_in[Y][X] == p_in[Y ][X- 1]) && !(p_in[Y][X] == p_in[Y + 1][X])) && (isLine(Y, X)))
							count++;
					}
				}
				else
				{
					if (Y == h_bmp.height-1)
					{
						if (X == 0)
						{
							if ((!(p_in[Y][X] == p_in[Y- 1][X ])) && (isLine(Y, X)))
								count++;
						}
						else
						{
							if ((!(p_in[Y][X] == p_in[Y][X - 1]) && !(p_in[Y][X] == p_in[Y- 1][X ])) && (isLine(Y, X)))
								count++;
						}
					}
					else
					{
						if (X == 0)
						{
							if ((!(p_in[Y][X] == p_in[Y- 1][X ]) && !(p_in[Y][X] == p_in[Y+ 1][X ])) && (isLine(Y, X)))
								count++;
						}
						else
						{
							if ((!(p_in[Y][X] == p_in[Y ][X- 1]) && !(p_in[Y][X] == p_in[Y- 1][X ]) && (isLine(Y, X)))
								&& !(p_in[Y][X] == p_in[Y + 1][X]))
								count++;
						}
					}
				}
			}
		}
	}
	cout << count;
	cin >> count;
	return 0;
}
