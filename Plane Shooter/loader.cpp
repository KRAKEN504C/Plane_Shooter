#include "biblioteki.h"
//#include "Edytor.cpp"
#include "Random_Font.hpp"
#include <fstream>

using namespace std;

int tabL[20][15];

int loader()
{
	ALLEGRO_FONT* font = Random_Font();

	ALLEGRO_BITMAP *obrazek1 = NULL;
	ALLEGRO_BITMAP *obrazek2 = NULL;
	ALLEGRO_BITMAP *Enemy1 = NULL;
	ALLEGRO_BITMAP *Enemy2 = NULL;
	ALLEGRO_BITMAP *Player = NULL;
	ALLEGRO_BITMAP *bron1 = NULL;
	ALLEGRO_BITMAP *bron2 = NULL;
	ALLEGRO_BITMAP *bonus1= NULL;
	ALLEGRO_BITMAP *bonus2 = NULL;


	obrazek1 = al_load_bitmap("bitmapy/sciana_Placeholder.png");
	if (!obrazek1)
	{
		fprintf(stderr, "failed to create obrazek1 bitmap!\n");
		return -1;
	}

	obrazek2 = al_load_bitmap("bitmapy/Droga_Placeholder.png");
	if (!obrazek2)
	{
		fprintf(stderr, "failed to create obrazek2 bitmap!\n");
		return -1;
	}

	Enemy1 = al_load_bitmap("Enemies/Enemy1_Placeholder.png");
	if (!Enemy1)
	{
		fprintf(stderr, "failed to create Enemy1 bitmap!\n");
		return -1;
	}

	Enemy2 = al_load_bitmap("Enemies/Enemy2_Placeholder.png");
	if (!Enemy2)
	{
		fprintf(stderr, "failed to create Enemy2 bitmap!\n");
		return -1;
	}

	Player = al_load_bitmap("Player/Player_Placeholder.png");
	if (!Player)
	{
		fprintf(stderr, "failed to create Player bitmap!\n");
		return -1;
	}

	bron1 = al_load_bitmap("bron/bron1_Placeholder.png");
	if (!bron1)
	{
		fprintf(stderr, "failed to create bron1 bitmap!\n");
		return -1;
	}

	bron2 = al_load_bitmap("bron/bron2_Placeholder.png");
	if (!bron2)
	{
		fprintf(stderr, "failed to create bron2 bitmap!\n");
		return -1;
	}

	bonus1 = al_load_bitmap("bonus/bonus1_Placeholder.png");
	if (!bonus1)
	{
		fprintf(stderr, "failed to create bonus1 bitmap!\n");
		return -1;
	}

	bonus2 = al_load_bitmap("bonus/bonus2_Placeholder.png");
	if (!bonus2)
	{
		fprintf(stderr, "failed to create bonus2 bitmap!\n");
		return -1;
	}



	fstream HubL;
	HubL.open("Mapy/Hub.txt", ios::in | ios::out);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			HubL >> tabL[i][j];
		}
	}
	cout << "wczytano mape" << endl;
	HubL.close();

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (tabL[i][j] != 0)
			{
				if (tabL[i][j] == 1)
				{
					al_draw_bitmap(obrazek1, i * 32, j * 32, 0);
				}
				else if (tabL[i][j] == 2)
				{
					al_draw_bitmap(obrazek2, i * 32, j * 32, 0);
				}
			}
		}
	}

}