/*
 * main.c
 *
 *  Created on: 07.06.2013
 *      Author: mihkelk
 */

#include <stdlib.h>
#include <windows.h> //Vajalik fondi muutuste käskluse jaoks.
#include <curses.h>  //Vajalik PDCurses kasutamiseks.
int x, y, z;
char koordinaadid[100][500][500]; //Toetab 100 korrust mille suuruseks umbes 500x500 tähemärki, reavahetus loeb samuti tähemärgina.
int px = 248, py = 247; //mängija algkoordinaadid
int jsuurus = 25; //joonistatava vaatevälja suurus

BOOL WINAPI SetConsoleFont(HANDLE hOutput, DWORD fontIndex); //Defineeritud et hiljem kasutada fondimuutus käsku.

//---------------------------Maailma-loomine-failist----------------------//
int maailm()
{
	char cz[10];

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

	return 1;
}
//------------------------------------------------------------------------//

//-------------------------------joonistamine-----------------------------//
int joonistamine()
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

				switch (koordinaadid[z][y][x])
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
					printw("%d", koordinaadid[z][y][x]);
					break;

				};
			};

		};

	};

	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 2); // Vahetab fondi suurust, vajalik kuna kaotab ära jooned suuremat vilkumist põhjustamatta.

	return 0;
}
//------------------------------------------------------------------------//

//-------------------------------Peafunktsioon----------------------------//
int main()
{

	maailm();

	initscr();

//http://pdcurses.sourceforge.net/doc/PDCurses.txt

	//resize_term(jsuurus * 2, jsuurus * 2); //Konsooli suuruse muutmine.
	resize_term(jsuurus * 2 + 60, jsuurus * 2 + 60); //Konsooli suuruse muutmine.
	move(55,0);
	printf("joonistamine");
	//PDCurses värvindus.
	start_color(); //Alustab värvide kasutust.
	//---------Värvipaaride määramine.---------//
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_WHITE);
	init_pair(5, COLOR_GREEN, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	//-----------------------------------------//
	z = 50;
	joonistamine();

	BOOL lopp = FALSE; //

	while (lopp == FALSE)
	{

//----------Klahvivajutuste-järgi-mängija-koordinaatide-muutmine----------//

		char klahv = getch();

		if (klahv == 'd' && (koordinaadid[z][py][px + 1] != '1'))
		{
			px++;

		}
		else if (klahv == 'a' && (koordinaadid[z][py][px - 1] != '1'))
		{
			px--;

		}
		else if (klahv == 'w' && (koordinaadid[z][py - 1][px] != '1'))
		{
			py--;

		}
		else if (klahv == 's' && (koordinaadid[z][py + 1][px] != '1'))
		{
			py++;

		}
		else if (klahv == 'q')
		{
			lopp = TRUE;
		}

		switch (koordinaadid[z][py][px]) //Kui on tegu treppidega.
		{
		case '5':
			z--;
			break;
		case '6':
			z++;
			break;
		}
		//------------------------------------------------------------------------//

		refresh();         //////////////////////////////////////////////////
		joonistamine();    // Peab läbi viima mitu korda et jooned kustuks.//
		refresh();         //                                              //
		joonistamine();    //////////////////////////////////////////////////

	};
	return 0;
}
//------------------------------------------------------------------------//

