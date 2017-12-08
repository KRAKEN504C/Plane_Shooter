#include "biblioteki.h"
#include "Edytor.cpp"
#include "Random_Font.hpp"
#include <fstream>


using namespace std;

const float FPS = 60;

int main();
int Edytor();
int loader();

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int CURSOR_SIZE = 16;

int tabRP[20][15];

int Rysowanie_Poziomu()
{



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
	int test = loader();

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
				else if (tab[i][j] == 2)
				{
					al_draw_bitmap(obrazek2, i * 32, j * 32, 0);
				}
			}
		}
	}


	return 0;
}