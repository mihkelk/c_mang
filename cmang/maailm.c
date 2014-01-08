/*
 * maailm.c
 *
 *  Created on: 08.01.2014
 *      Author: mihkelk
 */

//#include <stdlib.h>
//#include <windows.h>
#include <stdio.h>
//#include "maailm.h"

//---------------------------Maailma-lugemine-failist----------------------//
void maailm(char ***koordinaadid)
{
	char cz[10];
	int x, y, z;
	for (z = 49; z < 51; z++)
	{

		cz[10] = itoa(z, cz, 10); //itoa(arv mida teisaldan, string millesse teisaldan, arvusüsteem)
		//	printf("%s", cz); //[0], cz[1], cz[2]);

		FILE *korrus = fopen(cz, "r");
		char casukoht = '0';
		for (y = 0; casukoht != '-'; y++)
		{
			for (x = 0; casukoht != '\n'; x++)
			{

				casukoht = fgetc(korrus);

				koordinaadid[z][y][x] = casukoht;

			}
			casukoht = fgetc(korrus);
		};

	};

	//return 1;
}
