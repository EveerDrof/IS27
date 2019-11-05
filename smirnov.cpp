#pragma warning(disable:4996)
using namespace std;
#include "utilities.h"

void compare(picture &pic1, picture &pic2)
{  
  int count = 0;
  for (int Y = 0; Y < pic1.h_bmp.height; Y++)
  {
    for (int X = 0; X < pic1.h_bmp.width; X++)
    {
      if (!(pic1.arr[Y][X] == pic2.arr[Y][X]))
      {
        count++;
      }
    }
  }
  cout <<count;
}
