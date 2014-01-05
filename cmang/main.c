/*
 * main.c
 *
 *  Created on: 02.10.2012
 *      Author: mihkelk
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x;
	int y;
	int koordinaadid[64][64];
	int px = 2;
	int py = 2;
	int suurus = 20;

	while ("TRUE")
	{
		for (y = 0; y < (suurus + 1); y++)
		{
			for (x = 0; x < (suurus + 1); x++)
			{
				if (x == px && y == py)
				{
					koordinaadid[y][x] = 3;
					printf("%d", koordinaadid[y][x]);
				}
				else if ((y == suurus || y == 0) || (x == suurus || x == 0))
				{
					koordinaadid[y][x] = 1;
					printf("%d", koordinaadid[y][x]);
				}
				else
				{
					koordinaadid[y][x] = 0;
					printf("%d", koordinaadid[y][x]);
				};

			};

			printf("\n");

		};

		char klahv = getch();
		printf("%c", klahv);
		if (klahv == 'd' && (koordinaadid[py][px + 1] != 1))
		{
			px++;
		}
		else if (klahv == 'a' && (koordinaadid[py][px - 1] != 1))
		{
			px--;
		}
		if (klahv == 'w' && (koordinaadid[py][py - 1] != 1))
		{
			py--;
		}
		if (klahv == 's' && (koordinaadid[py][py + 1] != 1))
		{
			py++;
		}
		system("cls"); // tühjendab ekraani
	}
	return 0;
}
