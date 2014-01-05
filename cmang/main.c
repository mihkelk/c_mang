/*
 * main.c
 *
 *  Created on: 02.10.2012
 *      Author: mihkelk
 */

#include <stdio.h>

int main() {
	int x;
	int y;
	int koordinaadid[64][64];
	int px = 2;
	int py = 2;

	for (y = 0; y < 21; y++)
	{
		for (x = 0; x < 21; x++)
		{
			if (x == px && y == py)
			{
				koordinaadid[y][x] = 3;
				printf("%d", koordinaadid[y][x]);
			}
			else if ((y % 4 == 0) || (x % 4 == 0))
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

	getch();
	return 0;
}
