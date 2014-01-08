/*
 * joonistamine.c
 *
 *  Created on: 08.01.2014
 *      Author: mihkelk
 */

#include <curses.h>
#include <windows.h> //Vajalik fondi muutuste k�skluse jaoks.

int x, y;
BOOL WINAPI SetConsoleFont(HANDLE hOutput, DWORD fontIndex); //Defineeritud et hiljem kasutada fondimuutus k�sku.

//-------------------------------joonistamine-----------------------------//
void joonistamine(char ***koordinaadid, int px, int py, int pz, int jsuurus)
{

	curs_set(0); //Peidab kursori.
	int reavahetus = -1;

	for (y = py - jsuurus; y < (py + jsuurus); y++)
	{
		reavahetus++;
		move(reavahetus, 0);
		for (x = px - jsuurus; x < (px + jsuurus); x++)
		{
			if (x == px && y == py) {
				addch('\1' | COLOR_PAIR(4) | A_ALTCHARSET); // Altcharset vajalik naerun�eo n�itamiseks.

			}
			else
			{
				switch (koordinaadid[pz][y][x])
				{
				case '0': //T�hjus
					addch(ACS_BLOCK | COLOR_PAIR(6)); // S�mbolid laiendatud ascii tabelist pdcursesiga nimetused ACS_*
					break;
				case '1': //Sein
					addch(ACS_BLOCK | COLOR_PAIR(1)); // V�rve v�etakse paaridena mis on defineeritud peafunktsioonis.
					break;
				case '2': //Muru
					addch(ACS_CKBOARD | COLOR_PAIR(2));
					break;
				case '3': //M�ngija
					addch('\1' | COLOR_PAIR(4) | A_ALTCHARSET); // Altcharset vajalik naerun�eo n�itamiseks.
					break;
				case '4': //Heledam muru
					addch(ACS_BOARD | COLOR_PAIR(5));
					break;
				case '5': //Trepp alla
					addch('v' | COLOR_PAIR(4));
					break;
				case '6': //Trepp �les
					addch('^' | COLOR_PAIR(4));
					break;
				case '7': //Kivip�rand
					addch(ACS_CKBOARD | COLOR_PAIR(7));
					break;
				default:
					printw("%d", koordinaadid[pz][y][x]);
					break;

				};
			};

		};

	};

	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 2); // Vahetab fondi suurust, vajalik kuna kaotab �ra jooned suuremat vilkumist p�hjustamatta.

}
