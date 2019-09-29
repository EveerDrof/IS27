#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "konstantinov.h"
void help()
{
    cout << "\nusage: \n";
    cout << "  chbmp resizev N in_file out_file \n";
    cout << "  chbmp resizeh N in_file out_file \n";
    cout << "  chbmp rotater  in_file out_file \n";
    cout << "  chbmp rotatel  in_file out_file \n";
	cout << "  chbmp chb  in_file out_file \n";
	cout << "  chbmp raskras  in_file out_file \n";
	cout << "  chbmp limitcolors  in_file out_file \n";
}

int main(int argc, char** argv)
{
    int pers;

    if(argc < 3)
    {
		help();
		return 1;
    }
  
    if(strcmp(argv[1],"resizev") && strcmp(argv[1],"resizeh") && strcmp(argv[1],"rotater") &&  strcmp(argv[1],"rotatel")
		//Konstantinov
		&& strcmp(argv[1], "chb") && strcmp(argv[1], "raskras") && strcmp(argv[1], "limitcolors"))
    {
		help();
		return 1;
    }

    if(!strcmp(argv[1],"resizev"))
    {
		pers = atoi(argv[2]);
		if(argc < 5)
		 {
			 help();
			 return 1;
		 }
		infile=argv[3];
		outfile=argv[4];
		resizev(pers);
    }

    if(!strcmp(argv[1],"resizeh"))
    {
		pers = atoi(argv[2]);
		if(argc < 5)
		{
			 help();
			 return 1;
		}
		infile=argv[3];
		outfile=argv[4];
		resizeh(pers);
    }

    if(!strcmp(argv[1],"rotater"))
    {
		if(argc < 4)
		{
			 help();
			 return 1;
		}
		infile=argv[2];
		outfile=argv[3];
		rotater();
    }

    if(!strcmp(argv[1],"rotatel"))
    {
		if(argc < 4)
		{
			 help();
			 return 1;
		}
		infile=argv[2];
		outfile=argv[3];
		rotatel();
    }
	//Konstantinov
	if (!strcmp(argv[1], "chb"))
	{
		if (argc < 4)
		{
			help();
			return 1;
		}
		infile = argv[2];
		outfile = argv[3];
		chb();

	}
	if (!strcmp(argv[1], "raskras"))
	{
		infile = argv[2];
		outfile = argv[3];
		Color COL;
		Color COL2;
		if (argc < 6)
		{
			help();
			return 1;
		}
		COL = Color_Check(argv[5]);
		if (argc == 6)
		{
			COL2 = COL;
			raskras(true, atoi(argv[4]), COL, COL2);
		}
		else
		{
			COL2 = Color_Check(argv[6]);
			raskras(false, atoi(argv[4]), COL, COL2);
		}

	}			
	if (!strcmp(argv[1], "limitcolors"))
		{
			if (argc < 4)
			{
				help();
				return 1;
			}
			infile = argv[2];
			outfile = argv[3];
			limitcolors(atoi(argv[4]));

		}
    return 0;
}
