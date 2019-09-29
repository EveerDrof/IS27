#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include <io.h>
using namespace std;
int main() {

	FILE *out;
	out = fopen("Img1.bmp", "rb");

	fseek(out, 0, SEEK_END);
	long int s = ftell(out);
	char *buffer = new char[s];
	fseek(out, 0, SEEK_SET);
	fread(&buffer, sizeof(char), s, out);
	fclose(out);
	cout << "The end";
	return 0;
}
