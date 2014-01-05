/*
 * m8.c
 *
 *  Created on: 07.11.2012
 *      Author: mihkelk
 */

#include <stdlib.h>
#include <windows.h> //Vajalik fondi muutuste k�skluse jaoks.
#include <curses.h>  //Vajalik PDCurses kasutamiseks.

int x, y, z;
char koordinaadid[100][500][500]; //Toetab 100 korrust mille suuruseks umbes 500x500 t�hem�rki, reavahetus loeb samuti t�hem�rgina.
int px = 248, py = 247; //m�ngija algkoordinaadid
int jsuurus = 25; //joonistatava vaatev�lja suurus

BOOL WINAPI SetConsoleFont(HANDLE hOutput, DWORD fontIndex); //Defineeritud et hiljem kasutada fondimuutus k�sku.

//---------------------------Maailma-loomine-failist----------------------//
int maailm()
{
	char cz[10];

	for (z = 49; z < 51; z++)
	{

		cz[10] = itoa(z, cz, 10); //itoa(arv mida teisaldan, string millesse teisaldan, arvus�steem)
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

			if (x == px && y == py)
			{
				koordinaadid[z][y][x] = '3';
			}
			switch (koordinaadid[z][y][x])
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
				printw("%d", koordinaadid[z][y][x]);
				break;

			};

		};

	};

	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 2); // Vahetab fondi suurust, vajalik kuna kaotab �ra jooned suuremat vilkumist p�hjustamatta.

	return 0;
}
//------------------------------------------------------------------------//

//-------------------------------Peafunktsioon----------------------------//
int main()
{

	maailm();

	initscr();

//http://pdcurses.sourceforge.net/doc/PDCurses.txt

	resize_term(jsuurus * 2, jsuurus * 2); //Konsooli suuruse muutmine.

	//PDCurses v�rvindus.
	start_color(); //Alustab v�rvide kasutust.
	//---------V�rvipaaride m��ramine.---------//
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
	char rs1 = '0'; // Salvestab ruudu kus m�ngja seisab, et see hiljem taastada.
	char rs2 = '2'; // Salvestab teise ruudu kus m�ngija seisis.
	int s1 = 1, s2 = 0; // Sammuloendurid 1 ja 2.

	while (lopp == FALSE)
	{

//----------Klahvivajutuste-j�rgi-m�ngija-koordinaatide-muutmine----------//

		char klahv = getch();

		if (klahv == 'd' && (koordinaadid[z][py][px + 1] != '1'))
		{
			if (s1 == 1)
			{
				s2 = 0;
				rs1 = koordinaadid[z][py][px + 1];
				px++;
				koordinaadid[z][py][px - 1] = rs2;
				s1 = 0;
			}
			if (s2 == 1)
			{
				rs2 = koordinaadid[z][py][px + 1];
				px++;
				koordinaadid[z][py][px - 1] = rs1;
				s2 = 0;
				s1 = 1;
			}
		}
		else if (klahv == 'a' && (koordinaadid[z][py][px - 1] != '1'))
		{
			if (s1 == 1)
			{
				s2 = 0;
				rs1 = koordinaadid[z][py][px - 1];
				px--;
				koordinaadid[z][py][px + 1] = rs2;
				s1 = 0;
			}
			if (s2 == 1)
			{
				rs2 = koordinaadid[z][py][px - 1];
				px--;
				koordinaadid[z][py][px + 1] = rs1;
				s2 = 0;
				s1 = 1;
			}
		}
		else if (klahv == 'w' && (koordinaadid[z][py - 1][px] != '1'))
		{
			if (s1 == 1)
			{
				s2 = 0;
				rs1 = koordinaadid[z][py - 1][px];
				py--;
				koordinaadid[z][py + 1][px] = rs2;
				s1 = 0;
			}
			if (s2 == 1)
			{
				rs2 = koordinaadid[z][py - 1][px];
				py--;
				koordinaadid[z][py + 1][px] = rs1;
				s2 = 0;
				s1 = 1;
			}
		}
		else if (klahv == 's' && (koordinaadid[z][py + 1][px] != '1'))
		{
			if (s1 == 1)
			{
				s2 = 0;
				rs1 = koordinaadid[z][py + 1][px];
				py++;
				koordinaadid[z][py - 1][px] = rs2;
				s1 = 0;
			}
			if (s2 == 1)
			{
				rs2 = koordinaadid[z][py + 1][px];
				py++;
				koordinaadid[z][py - 1][px] = rs1;
				s2 = 0;
				s1 = 1;
			}
		}
		else if (klahv == 'q')
		{
			lopp = TRUE;
		}

		s2 = 1;

		switch (koordinaadid[z][py][px])	//Kui on tegu treppidega.
		{
		case '5':
			z--;
			rs1 = '7';
			rs2 = '7';
			break;
		case '6':
			z++;
			rs1 = '7';
			rs2 = '7';
			break;
		}
		//------------------------------------------------------------------------//

		refresh();         //////////////////////////////////////////////////
		joonistamine();    // Peab l�bi viima mitu korda et jooned kustuks.//
		refresh();         //                                              //
		joonistamine();    //////////////////////////////////////////////////

	};
	return 0;
}
//------------------------------------------------------------------------//

