/*
 * main.c
 *
 *  Created on: 23.10.2012
 *      Author: mihkelk
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //värvide jaoks
int x;
int y;
int z;
int koordinaadid[100][100][100];
int suurus = 1000;
int m = 0;
int px = 30;
int py = 30;
int jsuurus = 10; //joonistatava vaatevälja suurus

// Maailma loomine failist
int maailm()
{
	//int x;
	//int y;
//char failinimi[7];
 //char failinimi = "z"+ znumber + ".txt"
// korrus b1
	FILE *bp = fopen("z49.txt", "r"); //Faili sisselugemine
	char asukohtb1 = '0';

	z = 49;

	for (y = 0; asukohtb1 != '-'; y++)
	{
		for (x = 0; asukohtb1 != '\n'; x++)
		{
			asukohtb1 = fgetc(bp);
			switch (asukohtb1)
			{
			case '0':
				koordinaadid[z][y][x] = 0; //tühjus
				break;
			case '1':
				koordinaadid[z][y][x] = 1; //sein
				break;
			case '2':
				koordinaadid[z][y][x] = 2; //muru
				break;
			case '4':
				koordinaadid[z][y][x] = 4; //põõsas
				break;
			case '5':
				koordinaadid[z][y][x] = 5; //trepp alla
				break;
			case '6':
				koordinaadid[z][y][x] = 6; //trepp yles
				break;
			case '7':
				koordinaadid[z][y][x] = 7; //puitpõrand
				break;
			default:
				koordinaadid[z][y][x] = 9;
				break;
			}
		};
		asukohtb1 = fgetc(bp);
	};

	printf("Laetud 50");
	// korrus 0

	FILE *fp = fopen("z50.txt", "r"); //Faili sisselugemine
	char asukoht = '0';
	z = 50;

	for (y = 0; asukoht != '-'; y++)
	{
		for (x = 0; asukoht != '\n'; x++)
		{
			asukoht = fgetc(fp);
			switch (asukoht)
			{
			case '0':
				koordinaadid[z][y][x] = 0; //tühjus
				break;
			case '1':
				koordinaadid[z][y][x] = 1; //sein
				break;
			case '2':
				koordinaadid[z][y][x] = 2; //muru
				break;
			case '4':
				koordinaadid[z][y][x] = 4; //põõsas
				break;
			case '5':
				koordinaadid[z][y][x] = 5; //trepp alla
				break;
			case '6':
				koordinaadid[z][y][x] = 6; //trepp yles
				break;
			default:
				koordinaadid[z][y][x] = 9;
				break;
			}
		};
		asukoht = fgetc(fp);
	};

	return 1;
}

//-------------------------------joonistamine-----------------------------//
int joonistamine()
{
	system("cls");

	for (y = py - jsuurus; y < (py + jsuurus + 1); y++)
	{
		for (x = px - jsuurus; x < (px + jsuurus + 1); x++)
		{
			if (x == px && y == py)
			{
				koordinaadid[z][y][x] = 3;
			}
			switch (koordinaadid[z][y][x])
			{
			case 0:
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34);
				printf(" ");
				break;
			case 1:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\333"); //ASCII koodid kaheksanddsüsteemis
				break;
			case 2:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("\261");
				break;
			case 3:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 154);
				printf("\1");
				break;
			case 4:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 294); //42
				printf("\260");
				break;
			case 5:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("v");
				break;
			case 6:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("^");
				break;
			case 7:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2680);
				printf("\262");
				// \334
				break;

			default:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				printf("%d", koordinaadid[z][y][x]);
				break;
			};
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0); // värv tagasi mustaks, et ei tomuks jama taustavärvidega

		};
		printf("\n");
	};
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("Kulda 50");
	printf("   Elusid 50\n");
	printf("Kõike 50");
	return 0;
}
//------------------------------------------------------------------------//

//-------------------------------peafunktsioon----------------------------//
int main()
{

	maailm();
	z = 50;
	joonistamine();

	int Q = 1;
	int rs1 = 0; // salvestab ruudu kus mängja seisab, et see hiljem taastada
	int rs2 = 0; // salvestab teise ruudu kus mängija seisis
	int s1 = 1; // samm 1
	int s2 = 0; // samm 2
	while (Q == 1) {
//----------Klahvivajutuste-järgi-mängija-koordinaatide-muutmine----------//
		char klahv = getch();

		if (klahv == 'd' && (koordinaadid[z][py][px + 1] != 1))
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
		else if (klahv == 'a' && (koordinaadid[z][py][px - 1] != 1))
		{
			//rsalvestatud = koordinaadid[z][py][px + 1];
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
			//koordinaadid[z][py][px + 3] = rsalvestatud;*/
		}
		if (klahv == 'w' && (koordinaadid[z][py - 1][px] != 1))
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
		if (klahv == 's' && (koordinaadid[z][py + 1][px] != 1))
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
		if (klahv == 'q')
		{
			Q = 0;
		}
		s2 = 1;

		switch (koordinaadid[z][py][px])
		{
		case 5:
			z--;
			rs1 = 2;
			rs2 = 2;
			break;
		case 6:
			z++;
			rs1 = 2;
			rs2 = 2;

			break;
		}
		joonistamine();
		Sleep(10);

	};
	return 0;
//------------------------------------------------------------------------//
}
//------------------------------------------------------------------------//

// SetCursorPos(xpos,ypos); kursori paigutamine kuhugi, pole veel kasutusel

