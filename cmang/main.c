/*
 * main.c
 *
 *  Created on: 16.10.2012
 *      Author: mihkelk
 */

#include <stdio.h>
#include <stdlib.h>

int x;
int y;
int koordinaadid[64][64][64];
int suurus = 20;
int m = 0;
int px = 2;
int py = 2;

int toad(r)
{
	int x;
	int y;

	//üldise toa loomine

	for (y = 0; y < (suurus + 1); y++)
	{
		for (x = 0; x < (suurus + 1); x++)
		{
			if ((y == suurus || y == 0) || (x == suurus || x == 0))
			{
				koordinaadid[r][y][x] = 1;
			}
			else
			{
				koordinaadid[r][y][x] = 0;
			};
		};
	};

	//vastava toa loomine
	koordinaadid[10][20][10] = 2;
	koordinaadid[10][4][6] = 0;

	koordinaadid[20][4][6] = 1;
	koordinaadid[20][0][11] = 2;

	return 1;
}


int tuba1()
{
	px = 10;
	py = 19;
	return 1;
};
int tuba2(){

	//tegelase teise toa otsa liigutamine
	px = 11;
	py = 1;
	return 1;
};

int main()
{
	int x;
	int y;

	int suurus = 20;
	int r = 10;

	while ("TRUE")
	{
		toad(r);

		if (koordinaadid[10][py][px] == 2)
		{
			r = 20;
			tuba2();
		};
		if (koordinaadid[20][py][px] == 2)
		{
			r = 10;
			tuba1();
		};

//----------Klahvivajutuste-järgi-mängija-koordinaatide-muutmine----------//
		char klahv = getch();

		if (klahv == 'd' && (koordinaadid[r][py][px + 1] != 1))
		{
			px++;
			koordinaadid[r][py][px - 1] = 0;
		} else if (klahv == 'a' && (koordinaadid[r][py][px - 1] != 1))
		{
			px--;
			koordinaadid[r][py][px + 1] = 0;
		}
		if (klahv == 'w' && (koordinaadid[r][py - 1][px] != 1))
		{
			py--;
			koordinaadid[r][py + 1][px] = 0;
		}
		if (klahv == 's' && (koordinaadid[r][py + 1][px] != 1))
		{
			py++;
			koordinaadid[r][py - 1][px] = 0;
		}
		toad(r);
//------------------------------------------------------------------------//

//-------------------------------joonistamine-----------------------------//
		system("cls"); // tühjendab ekraani

		for (y = 0; y < (suurus + 1); y++)
		{
			for (x = 0; x < (suurus + 1); x++)
			{
				if (x == px && y == py)
				{
					koordinaadid[r][y][x] = 3;
				}
				switch (koordinaadid[r][y][x])
				{
				case 0:
					printf(" ");
					break;
				case 1:
					printf("\333"); //ASCII koodid kaheksanddsüsteemis
					break;
				case 3:
					printf("\1");
					break;
				default:
					printf("%d", koordinaadid[r][y][x]);
					break;
				};

			};
			printf("\n");
		};
//------------------------------------------------------------------------//
	};
	return 0;
}
