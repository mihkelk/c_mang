/*
 * joonistamine.c
 *
 *  Created on: 08.01.2014
 *      Author: mihkelk
 */

#include <curses.h>
#include <windows.h> //Vajalik fondi muutuste käskluse jaoks.

int x, y;
BOOL WINAPI SetConsoleFont(HANDLE hOutput, DWORD fontIndex); //Defineeritud et hiljem kasutada fondimuutus käsku.

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
				addch('\1' | COLOR_PAIR(4) | A_ALTCHARSET); // Altcharset vajalik naerunäeo näitamiseks.

			}
			else
			{
				switch (koordinaadid[pz][y][x])
				{
				case '0': //Tühjus
					addch(ACS_BLOCK | COLOR_PAIR(6)); // Sümbolid laiendatud ascii tabelist pdcursesiga nimetused ACS_*
					break;
				case '1': //Sein
					addch(ACS_BLOCK | COLOR_PAIR(1)); // Värve võetakse paaridena mis on defineeritud peafunktsioonis.
					break;
				case '2': //Muru
					addch(ACS_CKBOARD | COLOR_PAIR(2));
					break;
				case '3': //Mängija
					addch('\1' | COLOR_PAIR(4) | A_ALTCHARSET); // Altcharset vajalik naerunäeo näitamiseks.
					break;
				case '4': //Heledam muru
					addch(ACS_BOARD | COLOR_PAIR(5));
					break;
				case '5': //Trepp alla
					addch('v' | COLOR_PAIR(4));
					break;
				case '6': //Trepp üles
					addch('^' | COLOR_PAIR(4));
					break;
				case '7': //Kivipõrand
					addch(ACS_CKBOARD | COLOR_PAIR(7));
					break;
				default:
					printw("%d", koordinaadid[pz][y][x]);
					break;

				};
			};

		};

	};

	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 2); // Vahetab fondi suurust, vajalik kuna kaotab ära jooned suuremat vilkumist põhjustamatta.

}
