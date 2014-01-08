/*
 * main.c
 *
 *  Created on: 07.06.2013
 *      Author: mihkelk
 */

#include <curses.h>  //Vajalik PDCurses kasutamiseks.
#include "maailm.h"

//-------------------------------Peafunktsioon----------------------------//
int main()
{

	int i, j;
	int jsuurus = 25; //joonistatava vaatev‰lja suurus
	int px = 248, py = 247, pz = 50; //m‰ngija algkoordinaadid

	//Toetab 100 korrust mille suuruseks umbes 500x500 t‰hem‰rki, reavahetus loeb samuti t‰hem‰rgina.
    char ***koordinaadid = malloc(100 * sizeof(char**)); //maatriksi loomine ja sellele m‰lu m‰‰ramine
    for(i = 0; i < 100; ++i)
    {
            koordinaadid[i] = malloc(501 * sizeof(char*));                                                                                                                        //
            for(j = 0; j < 500; ++j)
            {
                    koordinaadid[i][j] = malloc(501 * sizeof(char));
            }
    }

	maailm(koordinaadid);

	initscr();

	resize_term(jsuurus * 2, jsuurus * 2); //Konsooli suuruse muutmine.

	//PDCurses v‰rvindus.
	start_color(); //Alustab v‰rvide kasutust.
	//---------V‰rvipaaride m‰‰ramine.---------//
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_WHITE);
	init_pair(5, COLOR_GREEN, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	//-----------------------------------------//

	joonistamine(koordinaadid, px, py, pz, jsuurus);

	BOOL lopp = FALSE;

	while (lopp == FALSE)
	{

//----------Klahvivajutuste-j‰rgi-m‰ngija-koordinaatide-muutmine----------//

		char klahv = getch();

		if (klahv == 'd' && (koordinaadid[pz][py][px + 1] != '1'))
		{
			px++;

		}
		else if (klahv == 'a' && (koordinaadid[pz][py][px - 1] != '1'))
		{
			px--;

		}
		else if (klahv == 'w' && (koordinaadid[pz][py - 1][px] != '1'))
		{
			py--;

		}
		else if (klahv == 's' && (koordinaadid[pz][py + 1][px] != '1'))
		{
			py++;

		}
		else if (klahv == 'q')
		{
			lopp = TRUE;
		}

		switch (koordinaadid[pz][py][px]) //Kui on tegu treppidega.
		{
		case '5':
			pz--;
			break;
		case '6':
			pz++;
			break;
		}
		//------------------------------------------------------------------------//

		refresh();	     									 //////////////////////////////////////////////////
		joonistamine(koordinaadid, px, py, pz, jsuurus);    // Peab l‰bi viima mitu korda et jooned kustuks.//
		refresh();										   //                                              //
		joonistamine(koordinaadid, px, py, pz, jsuurus);  //////////////////////////////////////////////////

	};
	return 0;
}
//------------------------------------------------------------------------//

