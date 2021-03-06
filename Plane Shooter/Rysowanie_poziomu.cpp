#include "biblioteki.h"
#include "loader.hpp"

using namespace std;
//Using loader() here uses allegro before initialization.
/*
ALLEGRO_BITMAP *Enemy1 = loader("Enemies/Enemy1_Placeholder.png");
ALLEGRO_BITMAP *Enemy2 = loader("Enemies/Enemy2_Placeholder.png");
ALLEGRO_BITMAP *Player = loader("Player/Player_Placeholder.png");
ALLEGRO_BITMAP *bron1 = loader("bron/bron1_Placeholder.png");
ALLEGRO_BITMAP *bron2 = loader("bron/bron2_Placeholder.png");
ALLEGRO_BITMAP *bonus1 = loader("bonus/bonus1_Placeholder.png");
ALLEGRO_BITMAP *bonus2 = loader("bonus/bonus2_Placeholder.png");

ALLEGRO_BITMAP *bonus3 = loader("bonus/bonus3_Placeholder.png");
ALLEGRO_BITMAP *bonus4 = loader("bonus/bonus4_Placeholder.png");
ALLEGRO_BITMAP *bonus5 = loader("bonus/bonus5_Placeholder.png");
ALLEGRO_BITMAP *bron3 = loader("bron/bron3_Placeholder.png");
ALLEGRO_BITMAP *bron4 = loader("bron/bron4_Placeholder.png");
ALLEGRO_BITMAP *bron5 = loader("bron/bron5_Placeholder.png");
*/

int Rysowanie_Poziomu()
{
    int tabRP[20][15];


	fstream Hub;
	Hub.open("Mapy/Hub.txt", ios::in | ios::out);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Hub >> tabRP[i][j];
		}
	}
	cout << "wczytano mape" << endl;
	Hub.close();
	//int test = loader();//error: too few arguments to function 'ALLEGRO_BITMAP* loader(std::__cxx11::string)'

	ALLEGRO_BITMAP *obrazek1 = loader("bitmapy/sciana_Placeholder.png");
    ALLEGRO_BITMAP *obrazek2 = loader("bitmapy/Droga_Placeholder.png");

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (tabRP[i][j] != 0)
			{
				if (tabRP[i][j] == 1)
				{
					al_draw_bitmap(obrazek1, i * 32, j * 32, 0);
				}
				else if (tabRP[i][j] == 2)//tab[i][j] was compared before, probably bug.
				{
					al_draw_bitmap(obrazek2, i * 32, j * 32, 0);
				}
			}
		}
	}


	return 0;
}
