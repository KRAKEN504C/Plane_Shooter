#include "biblioteki.h"
#include <fstream>


using namespace std;

const float FPS = 60;

int main();

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int CURSOR_SIZE = 32;

int tab[20][15];

int enemies()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();





	fstream Hub;
	Hub.open("Mapy/Hub.txt", ios::in | ios::out);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Hub >> tab[i][j];
		}
	}
	cout << "wczytano mape" << endl;
	Hub.close();


	while (1)
	{

	}


	return 0;
}