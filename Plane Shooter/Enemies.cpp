#include "biblioteki.h"
#include "Random_Font.hpp"
#include <fstream>
#include <random>
#include <stdlib.h>
#include <time.h>
//#include "loader.cpp"
//#include "loader.hpp"


using namespace std;

const float FPS = 60;

int main();

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int CURSOR_SIZE = 16;

int worldWidth = 10000;
int worldHeight = 10000;

int camera_x = 100;
int camera_y = 100;

int tabEn[200][210];
int tabMiMa[10][13];
int tabPrzedmioty[200][210] = {};
int tabminiPrzedmioty[10][13] = {};

ALLEGRO_BITMAP *loader(string sciezka);

void generatorPoziomu();

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_S, KEY_L, KEY_B, KEY_ESCAPE, KEY_SPACE
};

int MapaKolizji(int tabEn[200][210], int Player_x, int Player_y, int kierunek)
{
	//0 - gora
	//1 - dol
	//2 - lewo
	//3 - prawo

	// 0 dla pustego pola
	// 1 dla sciany
	// 2 dla sklepu
	// zmaiast dodawac wszystkich pikseli ruchu do przemieszczenia (5), dodatkowa funkcja bedzie sprawdzala, jak malo brakuje do sciany, i dodao tyle pikseli do przemieszczenia.
	int kolizja_x1 = Player_x / 32 ;
	int kolizja_y1 = Player_y / 32 ;
	int kolizja_x2 = (Player_x + 16) / 32;
	int kolizja_y2 = (Player_y + 16) / 32;

	int i = /*-2 + */kolizja_x1;
	int j = /*-2 + */kolizja_y1;

	switch (kierunek)
	{
	case 1:
		j++;
		break;
	case 3:
		i++;
		break;
	}

	//for (int i = -2 + kolizja_x1; i < 2 + kolizja_x1; i++)
	{
		//for (int j = -2 + kolizja_y1; j < 2 + kolizja_y1; j++)
		{
			if (tabEn[i][j] != 0)
			{
				//cout << "i " << i << endl;
				//cout << "j " << j << endl;
				//cout << "entered if tabEn[i][j] !=0 " << endl;
				int wsp_i1 = (i * 32) /*- camera_x*/;
				int wsp_j1 = (j * 32) /*- camera_y*/;
				if (tabEn[i][j] == 1 || tabEn[i][j] == 4)
				{

					switch (kierunek)
					{
					case 3:

						//wsp_i1 -= 15;
						//al_draw_filled_rectangle(wsp_i1, wsp_j1, wsp_i1 + 32, wsp_j1 + 32, al_map_rgb(250, 250, 250));
						//Player_x += 16;
						//al_draw_filled_rectangle(Player_x, Player_y, Player_x + 16, Player_y + 16, al_map_rgb(25, 250, 250));
						//cout << "prawa wspolrzedna player_x " << Player_x + 16 << " Lewa sciana " << wsp_i1 - 15 - 1 << endl;
						if (Player_x + 15 < wsp_i1 )
						{
							return 0;
						}
						else
						{
							//cout << "kolizja prawej sciany" << endl; 
							if (tabEn[i][j] == 1)
							{
								return 1;
							}
							if (tabEn[i][j] == 4)
							{
								return 2;
							}
						}
						break;

					case 0:
						//al_draw_filled_rectangle(wsp_i1, wsp_j1, wsp_i1 + 32, wsp_j1 + 32, al_map_rgb(250, 250, 25));
						//al_draw_filled_rectangle(Player_x, Player_y, Player_x + 16, Player_y + 16, al_map_rgb(25, 250, 250));
						if (Player_y > (Player_y + 15) + (wsp_j1 + 16) - 1)
						{
							return 0;
						}
						else
						{
							//cout << "kolizja gornej sciany" << endl; // GOOD
							if (tabEn[i][j] == 1)
							{
								return 1;
							}
							if (tabEn[i][j] == 4)
							{
								return 2;
							}
						}
						break;

					case 2:
						//al_draw_filled_rectangle(wsp_i1, wsp_j1, wsp_i1 + 32, wsp_j1 + 32, al_map_rgb(250, 25, 250));
						//al_draw_filled_rectangle(Player_x, Player_y, Player_x + 16, Player_y + 16, al_map_rgb(25, 250, 250));
						if ((Player_x + 15) > Player_x + wsp_i1 - 1)
						{
							return 0;
						}
						else
						{
							//cout << "kolizja lewej sciany" << endl; // GOOD
							if (tabEn[i][j] == 1)
							{
								return 1;
							}
							if (tabEn[i][j] == 4)
							{
								return 2;
							}
						}
						break;

					case 1:

						//wsp_j1 -= 15;
						//al_draw_filled_rectangle(wsp_i1, wsp_j1, wsp_i1 + 32, wsp_j1 + 32, al_map_rgb(25, 250, 250));
						//Player_y += 16;
						//al_draw_filled_rectangle(Player_x, Player_y, Player_x + 16, Player_y + 16, al_map_rgb(25, 250, 250));
						//cout << "dolna wspolrzedna player_y " << Player_y + 16 << " gorna sciana " << wsp_j1 - 1 << endl;
						if (Player_y + 15 < wsp_j1)
						{
							return 0;
						}
						else
						{
							//cout << "kolizja dolnej sciany" << endl;
							if (tabEn[i][j] == 1)
							{
								return 1;
							}
							if (tabEn[i][j] == 4)
							{
								return 2;
							}
						}
						break;
					}
				}
				else if (tabEn[i][j] == 4)
				{
					//cout << "entered else if tabEn[i][j] == 4 " << endl;
					if ((Player_x > (Player_x + 16) + (wsp_i1 + 16) - 1) || // is b1 on the right side of b2?
						(Player_y > (Player_y + 16) + (wsp_j1 + 16) - 1) || // is b1 under b2?
						((Player_x + 16) > Player_x + wsp_i1 - 1) || // is b2 on the right side of b1?
						((Player_y + 16) > Player_y + wsp_j1 - 1))   // is b2 under b1?
					{
						return 0;
					}
					else return 2;
				}
				else return 0;
			}
			else return 0;
		}
	}
}


void LogikaSklepu(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_BITMAP *sklep_strzalka, ALLEGRO_BITMAP *przedmiot1, ALLEGRO_BITMAP *przedmiot2, ALLEGRO_BITMAP *przedmiot3, ALLEGRO_BITMAP *przedmiot4, int *playerMoney,int *playerHealth, float *dodatekpredkosc, int *kupionabron)
{
	//sklep screen size 600x440

	ALLEGRO_EVENT ev;
	//ALLEGRO_EVENT_QUEUE *event_queue;

	bool exit = 0;
	int selectedItem = 0;
	int standard_x = 60 - camera_x;
	int strzalka_x = standard_x;
	int	strzalka_y = 280 - camera_y;
	
	
	//cout << "entered function logikasklepu" << endl;
	while (!exit)
	{
		//cout << "entered while in function logikasklepu" << endl;

		al_wait_for_event(event_queue, &ev);

		al_draw_filled_rectangle(20 - camera_x, 80 - camera_y, 620 - camera_x, 460 - camera_y, al_map_rgb(0, 128, 255));
		al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 80 - camera_y, ALLEGRO_ALIGN_CENTER, "You entered Shop!");
		al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 100 - camera_y, ALLEGRO_ALIGN_CENTER, "Use arrows, to select, press enter, to buy, press B to exit.");

		al_draw_bitmap(sklep_strzalka, strzalka_x, strzalka_y, 0);

		al_draw_bitmap(przedmiot1, 60 - camera_x, 200 - camera_y, 0);
		al_draw_bitmap(przedmiot2, 220 - camera_x, 200 - camera_y, 0);
		al_draw_bitmap(przedmiot3, 380 - camera_x, 200 - camera_y, 0);
		al_draw_bitmap(przedmiot4, 540 - camera_x, 200 - camera_y, 0);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
			{
				if (selectedItem <= 2) selectedItem++;
				strzalka_x = standard_x;
				strzalka_x += selectedItem * 160;
				cout << selectedItem << endl;
				break;
			}

			case ALLEGRO_KEY_LEFT:
			{
				if (selectedItem >= 1) selectedItem--;
				strzalka_x = standard_x;
				strzalka_x += selectedItem * 160;
				cout << selectedItem << endl;
				break;
			}

			case ALLEGRO_KEY_B:
			{
				cout << "Player pressed B key" << endl;
				exit = 1;
				break;
			}

			case ALLEGRO_KEY_ESCAPE:
			{
				cout << "Player pressed ESC key" << endl;
				exit = 1;
				break;
			}
			case ALLEGRO_KEY_ENTER:
			{
				if(*playerMoney >= 30)
				{
					cout << "Player bought: ";
					switch (selectedItem)
					{
					case 0:
						*playerMoney -= 30;
						*playerHealth += 1;
						cout << "1 up!" << endl;
						cout << "playerhealth = " << *playerHealth << endl;
						break;
					case 1:
						*playerMoney -= 30;
						*dodatekpredkosc+=0.5;
						cout << "speed up!" << endl;
						cout << "dodatekpredkosc = " << *dodatekpredkosc << endl;
						break;
					case 2:
						*playerMoney -= 30;
						*kupionabron += 1;
						cout << "weapon nr 1 !" << endl;
						break;
					case 3:
						*playerMoney -= 30;
						*kupionabron += 2;
						cout << "weapon nr 2 up!" << endl;
						break;
					}
				}
				break;
			}

			}
		}
		al_flip_display();
	}

	//int wsp_i = ((miniPlayer_x * 4) - camera_x) + 10;
	//int wsp_j = ((miniPlayer_y * 4) - camera_y) + 10;

	//return 1;
}

void PlayerMiniMapPosition(int Player_x, int Player_y, ALLEGRO_BITMAP *miniMap_Player)
{
	//minimapa = 10x13
	// 3520 / 32 = 110
	// 110 / 20 = 5,5
	// 3616 / 32 = 113
	// 113 / 15 = 7,5(3)
	int miniPlayer_x = Player_x / 32;
	int miniPlayer_y = Player_y / 32;

	miniPlayer_x /= 20;
	miniPlayer_y /= 15;

	int wsp_i = ((miniPlayer_x * 4) - camera_x) + 10;
	int wsp_j = ((miniPlayer_y * 4) - camera_y) + 10;

	al_draw_bitmap(miniMap_Player, wsp_i, wsp_j, 0);

}

int Losowanie(int x, int y)
{
	int los = rand() % (y - x + 1) + x;
	return los;
}

void SpawnerWszystkiego(int tabMiMa[10][13], int tabEn[200][210],int tabPrzedmioty[200][210], int tabminiPrzedmioty[10][13], int *spawn_x, int *spawn_y, int *przedmiotynapokuj, int *ostatnipokujspawnu_x, int *ostatnipokujspawnu_y)
{
	srand(time(NULL));

	int losowaminimap_x = rand() % 10;
	int losowaminimap_y = rand() % 13;

	int stalaminimap_x = 0;
	int stalaminimap_y = 0;

	int losowaniewolnegomiejsca_x =0;
	int losowaniewolnegomiejsca_y =0;

	bool petla = 0;

	if (*przedmiotynapokuj == 0)
	{
		*przedmiotynapokuj = 0;
	}

	//cout << endl << "tabMiMa =  " << tabMiMa[losowaminimap_x][losowaminimap_y] << endl;

	while (petla == 0)
	{
		//cout << "entered while" << endl;
		losowaminimap_x = rand()%10;
		losowaminimap_y = rand()%13;
		/*cout << "losowax = " << losowaminimap_x << endl;
		cout << "losoway = " << losowaminimap_y << endl;
		cout << "tabMiMa =  " << tabMiMa[losowaminimap_x][losowaminimap_y]<< endl;*/

		if (tabMiMa[losowaminimap_x][losowaminimap_y] != 0 && tabminiPrzedmioty[losowaminimap_x][losowaminimap_y] != 1)
		{
			petla = 1;
		}

		if (*ostatnipokujspawnu_x == losowaminimap_x && *ostatnipokujspawnu_y == losowaminimap_y)
		{
			if (*przedmiotynapokuj >= 2)
			{
				petla = 0;
				*przedmiotynapokuj = 0;
				tabminiPrzedmioty[losowaminimap_x][losowaminimap_y] = 1;
			}
		}
	} 

	if (*ostatnipokujspawnu_x == losowaminimap_x && *ostatnipokujspawnu_y == losowaminimap_y)
	{
		*przedmiotynapokuj += 1;
		//cout << "++ do przedmioty na pokuj";
	}

	//cout << "ostatnipokujspawnu_x  = " << *ostatnipokujspawnu_x << endl;
	//cout << "ostatnipokujspawnu_y  = " << *ostatnipokujspawnu_y << endl << endl;

	*ostatnipokujspawnu_x = losowaminimap_x;
	*ostatnipokujspawnu_y = losowaminimap_y;

	//cout << "przedmiotynapokuj = " << *przedmiotynapokuj << endl;
	/*cout << "ostatnipokujspawnu_x  = " << *ostatnipokujspawnu_x << endl;
	cout << "ostatnipokujspawnu_y  = " << *ostatnipokujspawnu_y << endl << endl;

	cout << "losowax = " << losowaminimap_x << endl;
	cout << "losoway = " << losowaminimap_y << endl;*/

	stalaminimap_x = losowaminimap_x *20;
	stalaminimap_y = losowaminimap_y *15;

	/*cout << "stalax = " << stalaminimap_x << endl;
	cout << "stalay = " << stalaminimap_y << endl;

	cout << "tabMiMa =  " << tabMiMa[losowaminimap_x][losowaminimap_y] << endl;*/

	petla = 0;

	while (petla == 0)
	{
		losowaniewolnegomiejsca_x = Losowanie(stalaminimap_x, stalaminimap_x + 20);
		losowaniewolnegomiejsca_y = Losowanie(stalaminimap_y, stalaminimap_y + 15);

		//cout << "losowaxwersja2 = " << losowaniewolnegomiejsca_x << endl;
		//cout << "losowaywersja2 = " << losowaniewolnegomiejsca_y << endl;
		if (tabEn[losowaniewolnegomiejsca_x][losowaniewolnegomiejsca_y] == 2 && tabPrzedmioty[losowaniewolnegomiejsca_x][losowaniewolnegomiejsca_y] != 1)
		{
			petla = 1;
		}
	} 

	tabPrzedmioty[losowaniewolnegomiejsca_x][losowaniewolnegomiejsca_y] = 1;

	cout << "tabPrzedmioty = " << tabPrzedmioty[losowaniewolnegomiejsca_x][losowaniewolnegomiejsca_y] << endl;
	cout << "losowaniewolnegomiejsca_x = " << losowaniewolnegomiejsca_x <<  endl;
	cout << "losowaniewolnegomiejsca_y = " << losowaniewolnegomiejsca_y << endl;

	*spawn_x = losowaniewolnegomiejsca_x*32;
	*spawn_y = losowaniewolnegomiejsca_y*32;

}

void ruchPionowyPrzeciwnika(int *Enemy_x, int *Enemy_y, int tabEn[200][210], int *kierunek)
{
	int tymczasowka_x = *Enemy_x / 32;
	int tymczasowka_y = *Enemy_y / 32;

	//cout << "tym_y " << tymczasowka_y << endl;
	//cout << "tym_x " << tymczasowka_x << endl;

	//cout << "tabEn[tym_x][tym_y + kier] = " << tabEn[tymczasowka_x][tymczasowka_y + *kierunek] << endl << endl;

	//al_draw_filled_rectangle(tymczasowka_x *32, (tymczasowka_y + *kierunek )*32, (tymczasowka_x *32) + 32, (tymczasowka_y + *kierunek) *32 + 32, al_map_rgb(250, 250, 250));

	if (tabEn[tymczasowka_x][tymczasowka_y + *kierunek] == 2)
	{
		//cout << "Enemy_y " << *Enemy_y << endl;
		*Enemy_y += *kierunek;
		//cout << "Enemy_y " << *Enemy_y << endl << endl;
	}
	else
	{
		//cout << "Flliped kierunek" << endl;
		*kierunek *= -1;
	}

}

void ruchPoziomyPrzeciwnika(int *Enemy_x, int *Enemy_y, int tabEn[200][210], int *kierunek)
{
	int tymczasowka_x = *Enemy_x / 32;
	int tymczasowka_y = *Enemy_y / 32;

	//cout << "tym_y " << tymczasowka_y << endl;
	//cout << "tym_x " << tymczasowka_x << endl;

	//cout << "tabEn[tym_x][tym_y + kier] = " << tabEn[tymczasowka_x][tymczasowka_y + *kierunek] << endl << endl;

	//al_draw_filled_rectangle(tymczasowka_x *32, (tymczasowka_y + *kierunek )*32, (tymczasowka_x *32) + 32, (tymczasowka_y + *kierunek) *32 + 32, al_map_rgb(250, 250, 250));

	if (tabEn[tymczasowka_x + *kierunek][tymczasowka_y] == 2)
	{
		//cout << "Enemy_y " << *Enemy_y << endl;
		*Enemy_x += *kierunek;
		//cout << "Enemy_y " << *Enemy_y << endl << endl;
	}
	else
	{
		//cout << "Flliped kierunek" << endl;
		*kierunek *= -1;
	}
}

void SpawnerBossa(int tabEn[200][210], int *spawn_x, int *spawn_y)
{
	int miniplanszabossa_x;
	int miniplanszabossa_y;
	int losowaniewolnegomiejsca_x;
	int losowaniewolnegomiejsca_y;

	//znajduje miejsce w tablicy, gdzie jest numer 5.

	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 210; j++)
		{
			if (tabEn[i][j] == 5)
			{
				miniplanszabossa_x = i ;
				miniplanszabossa_y = j ;
			}
		}
	}

	//wiem ze to miejsce, jest pokojem bossa.
	//tworze wspolrzedne minimapy tego pokoju.

	//cout << miniplanszabossa_x << endl;
	//cout << miniplanszabossa_y << endl;

	miniplanszabossa_x /= 20;
	miniplanszabossa_y /= 15;
	miniplanszabossa_x *= 20;
	miniplanszabossa_y *= 15;

	//zeby potem moc spokojnie generowac losowe wartosci, do momentu znalezienia kolejnej 5, zeby moc na niej postawic bossa.

	bool petla = 0;

	while (petla == 0)
	{
		//losuje pewien punkt w pokoju bossa
		losowaniewolnegomiejsca_x = Losowanie(miniplanszabossa_x, miniplanszabossa_x + 20);
		losowaniewolnegomiejsca_y = Losowanie(miniplanszabossa_y, miniplanszabossa_y + 15);

		//sprawdzam, czy ten punkt ma wartosc 5
		if (tabEn[losowaniewolnegomiejsca_x][losowaniewolnegomiejsca_y] == 5 && tabPrzedmioty[losowaniewolnegomiejsca_x][losowaniewolnegomiejsca_y] != 1)
		{
			//jezeli tak, zakoncz
			petla = 1;
		}
	}
	//umiejscowienie bossa na planszy
	*spawn_x = losowaniewolnegomiejsca_x * 32;
	*spawn_y = losowaniewolnegomiejsca_y * 32;

}

void BOSS(int *Enemy_x, int *Enemy_y, int tabEn[200][210], int *kierunek, int *czasowspomagacz)
{
	//cout << "boss_x: " << *Enemy_x << endl;
	//cout << "boss_y: " << *Enemy_y << endl;

	if (*czasowspomagacz == 1)
	{
		ruchPionowyPrzeciwnika(Enemy_x, Enemy_y, tabEn, kierunek);
	}

	if (*czasowspomagacz == 0)
	{
		ruchPoziomyPrzeciwnika(Enemy_x, Enemy_y, tabEn, kierunek);
	}
	
}

void WeaponHandler()
{

}

int Enemies()
{
	srand(time(NULL));

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();

	bool redraw = true;
	bool doexit = false;

	int klasapostaci = rand() % 2 + 1;

	int Player_y = 3520;
	int Player_x = 3516;

	int Enemy1_y = rand() % 448 + 3392;
	int Enemy1_x = rand() % 608 + 3232;

	int *ptr_Enemy1_y = &Enemy1_y;
	int *ptr_Enemy1_x = &Enemy1_x;

	int Enemy2_y = rand() % 448 + 3392;
	int Enemy2_x = rand() % 608 + 3232;

	int *ptr_Enemy2_y = &Enemy2_y;
	int *ptr_Enemy2_x = &Enemy2_x;

	int Enemy3_y;
	int Enemy3_x;

	int *ptr_Enemy3_y = &Enemy3_y;
	int *ptr_Enemy3_x = &Enemy3_x;

	int Enemy4_y;
	int Enemy4_x;

	int *ptr_Enemy4_y = &Enemy4_y;
	int *ptr_Enemy4_x = &Enemy4_x;

	int Enemy5_y;
	int Enemy5_x;

	int *ptr_Enemy5_y = &Enemy5_y;
	int *ptr_Enemy5_x = &Enemy5_x;

	int bron1_y = rand() % 448 + 3392;
	int bron1_x = rand() % 608 + 3232;

	int *ptr_bron1_y = &bron1_y;
	int *ptr_bron1_x = &bron1_x;

	int bron2_y = rand() % 448 + 3392;
	int bron2_x = rand() % 608 + 3232;

	int *ptr_bron2_y = &bron2_y;
	int *ptr_bron2_x = &bron2_x;

	int bonus1_y = rand() % 448 + 3392;
	int bonus1_x = rand() % 608 + 3232;

	int *ptr_bonus1_y = &bonus1_y;
	int *ptr_bonus1_x = &bonus1_x;

	int bonus2_y = rand() % 448 + 3392;
	int bonus2_x = rand() % 608 + 3232;

	int *ptr_bonus2_y = &bonus2_y;
	int *ptr_bonus2_x = &bonus2_x;

	int bron3_y = bron1_y + 32;
	int bron3_x = bron1_x;

	int *ptr_bron3_y = &bron3_y;
	int *ptr_bron3_x = &bron3_x;

	int bron4_y = bron2_y + 32;
	int bron4_x = bron2_x;

	int *ptr_bron4_y = &bron4_y;
	int *ptr_bron4_x = &bron4_x;

	int bron5_y = bron1_y - 32;
	int bron5_x = bron1_x;

	int *ptr_bron5_y = &bron5_y;
	int *ptr_bron5_x = &bron5_x;

	int bonus3_y = bonus1_y + 32;
	int bonus3_x = bonus1_x;

	int *ptr_bonus3_y = &bonus3_y;
	int *ptr_bonus3_x = &bonus3_x;

	int bonus4_y = bonus2_y + 32;
	int bonus4_x = bonus2_x;

	int *ptr_bonus4_y = &bonus4_y;
	int *ptr_bonus4_x = &bonus4_x;

	int bonus5_y = bonus1_y - 32;
	int bonus5_x = bonus1_x;

	int *ptr_bonus5_y = &bonus5_y;
	int *ptr_bonus5_x = &bonus5_x;

	int przedmiotynapokuj = 0;
	int *ptr_przedmiotynapokuj = &przedmiotynapokuj;

	int ostatnipokujspawnu_x = 0;
	int ostatnipokujspawnu_y = 0;
	int *ptr_ostatnipokujspawnu_x = &ostatnipokujspawnu_x;
	int *ptr_ostatnipokujspawnu_y = &ostatnipokujspawnu_y;

	int kierunek1 = 1;
	int kierunek2 = 1;
	int *ptr_kierunek1 = &kierunek1;
	int *ptr_kierunek2 = &kierunek2;
	int kierunek3 = 1;
	int kierunek4 = 1;
	int *ptr_kierunek3 = &kierunek3;
	int *ptr_kierunek4 = &kierunek4;
	int kierunek5 = 1;
	int *ptr_kierunek5 = &kierunek5;

	int Boss_y = 3440;
	int Boss_x = 3616;
	int *ptr_Boss_y = &Boss_y;
	int *ptr_Boss_x = &Boss_x;
	int bosskierunek = 1;
	int *ptr_bosskierunek = &bosskierunek;

	bool key[9] = { false, false, false, false, false, false, false, false, false };

	ALLEGRO_DISPLAY* displayEn = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_FONT* font = Random_Font();
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timerEn = NULL;
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);

	timerEn = al_create_timer(1.0 / FPS);

	fstream HubL;
	HubL.open("Generowanie/Wyjscie.txt", ios::in | ios::out);
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 210; j++)
		{
			HubL >> tabEn[i][j];
		}
	}
	cout << "wczytano mape" << endl;
	HubL.close();


	fstream MiniMapE;
	MiniMapE.open("Generowanie/MiniMapa.txt", ios::in | ios::out);
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 210; j++)
		{
			MiniMapE >> tabMiMa[i][j];
		}
	}
	cout << "wczytano mini mape" << endl;
	HubL.close();


	int aktualnybiom = 0;
	fstream plik;

	plik.open("Save.txt", ios::in | ios::out);

	plik >> aktualnybiom;

	plik.close();



	//---------------------------------------- LOSOWANIE WSPOLRZEDNYCH ----------------------------------------

	cout << "przed losowaniem" << endl;
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bonus1_x, ptr_bonus1_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	cout << "po jednym losowaniu" << endl;
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bonus2_x, ptr_bonus2_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bonus3_x, ptr_bonus3_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bonus4_x, ptr_bonus4_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bonus5_x, ptr_bonus5_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);

	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bron1_x, ptr_bron1_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bron2_x, ptr_bron2_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bron3_x, ptr_bron3_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bron4_x, ptr_bron4_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_bron5_x, ptr_bron5_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);

	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_Enemy1_x, ptr_Enemy1_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_Enemy2_x, ptr_Enemy2_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_Enemy3_x, ptr_Enemy3_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_Enemy4_x, ptr_Enemy4_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);
	SpawnerWszystkiego(tabMiMa, tabEn, tabPrzedmioty, tabminiPrzedmioty, ptr_Enemy5_x, ptr_Enemy5_y, ptr_przedmiotynapokuj, ptr_ostatnipokujspawnu_x, ptr_ostatnipokujspawnu_y);

	SpawnerBossa(tabEn, ptr_Boss_x, ptr_Boss_y);


	ALLEGRO_BITMAP *obrazek1 = loader("bitmapy/sciana_Placeholder.png");
	ALLEGRO_BITMAP *obrazek2 = loader("bitmapy/Droga_Placeholder.png");
	ALLEGRO_BITMAP *obrazek3 = loader("bitmapy/Drzwi_Placeholder.png");
	ALLEGRO_BITMAP *Enemy1 = loader("Enemies/Enemy1_Placeholder.png");
	ALLEGRO_BITMAP *Enemy2 = loader("Enemies/Enemy2_Placeholder.png");
	ALLEGRO_BITMAP *bron1 = loader("bron/bron1_Placeholder.png");
	ALLEGRO_BITMAP *bron2 = loader("bron/bron2_Placeholder.png");
	ALLEGRO_BITMAP *bonus1 = loader("bonus/bonus1_Placeholder.png");
	ALLEGRO_BITMAP *bonus2 = loader("bonus/bonus2_Placeholder.png");

	ALLEGRO_BITMAP *Player = loader("Player/Player1_Placeholder.png");
	ALLEGRO_BITMAP *Player2 = loader("Player/Player2_Placeholder.png");
	ALLEGRO_BITMAP *serce = loader("Player/Serce_Placeholder.png");
	ALLEGRO_BITMAP *moneta = loader("Player/Moneta_Placeholder.png");

	ALLEGRO_BITMAP *bonus3 = loader("bonus/bonus3_Placeholder.png");
	ALLEGRO_BITMAP *bonus4 = loader("bonus/bonus4_Placeholder.png");
	ALLEGRO_BITMAP *bonus5 = loader("bonus/bonus5_Placeholder.png");
	ALLEGRO_BITMAP *bron3 = loader("bron/bron3_Placeholder.png");
	ALLEGRO_BITMAP *bron4 = loader("bron/bron4_Placeholder.png");
	ALLEGRO_BITMAP *bron5 = loader("bron/bron5_Placeholder.png");
	ALLEGRO_BITMAP *Enemy3 = loader("Enemies/Enemy3_Placeholder.png");
	ALLEGRO_BITMAP *Enemy4 = loader("Enemies/Enemy4_Placeholder.png");
	ALLEGRO_BITMAP *Enemy5 = loader("Enemies/Enemy5_Placeholder.png");

	ALLEGRO_BITMAP *miniMap_empty = loader("MiniMap/MiniMap_Empty.png");
	ALLEGRO_BITMAP *miniMap_Arena = loader("MiniMap/MiniMap_Arena.png");
	ALLEGRO_BITMAP *miniMap_Player = loader("MiniMap/MiniMap_Player.png");

	ALLEGRO_BITMAP *obrazek4 = loader("bitmapy/Sklep_Placeholder.png");
	ALLEGRO_BITMAP *sklep_strzalka = loader("Sklep/Strzalka_Sklep_Placeholder.png");

	ALLEGRO_BITMAP *Boss = loader("Enemies/Boss_Placeholder.png");


	ALLEGRO_TRANSFORM camera; // KAMERA TUTAJ!!!!!!!!


	Player = al_create_bitmap(CURSOR_SIZE, CURSOR_SIZE);

	al_set_target_bitmap(Player);

	//al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(displayEn));

	Player = al_load_bitmap("Player/Player_Placeholder.png");



	//al_clear_to_color(al_map_rgb(255,255,255));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(displayEn));
	al_register_event_source(event_queue, al_get_timer_event_source(timerEn));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timerEn);

	ALLEGRO_COLOR Zielonyen = al_map_rgb(0, 255, 128);
	ALLEGRO_COLOR Czerwonyen = al_map_rgb(255, 102, 102);
	ALLEGRO_COLOR Niebieskien = al_map_rgb(153, 204, 255);
	ALLEGRO_COLOR Jakis = al_map_rgb(192, 192, 192);
	ALLEGRO_COLOR AktualnyKolor = al_map_rgb(255, 204, 229);

	switch (aktualnybiom)
	{
	case 0:
		AktualnyKolor = Zielonyen;
		break;
	case 1:
		AktualnyKolor = Czerwonyen;
		break;
	case 2:
		AktualnyKolor = Niebieskien;
		break;
	case 3:
		AktualnyKolor = Jakis;
		break;
	}


	


	int test = 0;
	int wyjscie = 0;
	int czas = 0;
	int miniczas = 0;

	int minitest = 0;

	int bonusEffect = 0;
	int bonusEffect2 = 0;
	int bronEffect = 0;
	int bronEffect2 = 0;
	int enemyEffect = 0;
	int enemyEffect2 = 0;
	int enemyDead = 0;
	int enemyDead2 = 0;
	int enemyDead3 = 0;
	int enemyDead4 = 0;
	int enemyDead5 = 0;
	int bossDead = 0;
	int bronEffect3 = 0;
	int bronEffect4 = 0;
	int bronEffect5 = 0;
	int bonusEffect3 = 0;
	int bonusEffect4 = 0;
	int bonusEffect5 = 0;
	int lastKey = 1;
	int lastweapon = 0;

	int playerMoney = 30;
	int playerHealth = 3;
	float predkoscruchu = 2.5;

	bool gracznasklepie = 0;

	int *ptr_playerMoney = &playerMoney;
	int *ptr_playerHealth = &playerHealth;
	float dodatekpredkosci = 0;
	float *ptr_dodatekpredkosci = &dodatekpredkosci;
	int kupionabron = 0;
	int *ptr_kupionabron = &kupionabron;

	int movetest = 0;

	int czasowspomagacz = 0;
	int *ptr_czasowspomagacz = &czasowspomagacz;
	int bosstimer = 0;

	int wygrana = 0;
	bool wartosctestowawyjscia = false;

	switch (klasapostaci)
	{
	case 1:
		bronEffect = 1;
			break;
	case 2:
		playerHealth += 1;
		playerMoney += 30;
		Player = Player2;
		break;
	}

	/*
	
	4-GÓRA
	3-DÓ£
	1-LEWO
	2-PRAWO

	*/



	











	while (!doexit)
	{
		/*Player_y -= camera_y;
		Player_x -= camera_x;*/

		/*cout << Player_x << endl;
		cout << Player_y << endl;*/

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		int sprawdztablica_x, sprawdztablica_y;

		//al_clear_to_color(al_map_rgb(50, 206, 250)); // ---------- W zale¿noœci od biomu bêdzie inne t³o. ---------- 
		al_clear_to_color(AktualnyKolor);


		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 210; j++)
			{
				if (tabEn[i][j] != 0)
				{
					int wsp_i = (i * 32) /*- camera_x*/;
					int wsp_j = (j * 32) /*- camera_y*/;
					if (tabEn[i][j] == 1)
					{
						al_draw_bitmap(obrazek1, wsp_i, wsp_j, 0);
					}
					else if (tabEn[i][j] == 2)
					{
						al_draw_bitmap(obrazek2, wsp_i, wsp_j, 0);
					}
					else if (tabEn[i][j] == 3)
					{
						al_draw_bitmap(obrazek3, wsp_i, wsp_j, 0);
					}
					else if (tabEn[i][j] == 4)
					{
						al_draw_bitmap(obrazek4, wsp_i, wsp_j, 0);
					}
					else if (tabEn[i][j] == 5)
					{
						al_draw_bitmap(obrazek2, wsp_i, wsp_j, 0);
					}
					sprawdztablica_x = wsp_i;
					sprawdztablica_y = wsp_j;
					//cout << wsp_i << endl << wsp_j << endl;
				}
				/*if (tabEn[i][j] == 0)
				{
					int wsp_i = (i * 32);
					int wsp_j = (j * 32);
					al_draw_bitmap(obrazek1, wsp_i, wsp_j, 0);
				}*/
			}
		}


		// miniMapa 40x52

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				int wsp_i = ((i * 4) - camera_x) + 10;
				int wsp_j = ((j * 4) - camera_y) + 10;
				if (tabMiMa[i][j] == 0)
				{
					al_draw_bitmap(miniMap_empty, wsp_i, wsp_j, 0);

					/*al_draw_bitmap(serce, 60 - camera_x, 10 - camera_y, 0);
					al_draw_textf(font, al_map_rgb(135, 206, 50), 110 - camera_x, 10 - camera_y, ALLEGRO_ALIGN_CENTER, "x %i", playerHealth);*/


				}
				else if (tabMiMa[i][j] == 1)
				{
					al_draw_bitmap(miniMap_Arena, wsp_i, wsp_j, 0);
				}
				//al_draw_bitmap(, wsp_i, wsp_j);
				//al_draw_bitmap(, wsp_i, wsp_j);
				PlayerMiniMapPosition(Player_x, Player_y, miniMap_Player);
				
			}
		}

		{
			al_draw_bitmap(serce, 60 - camera_x, 10 - camera_y, 0);
			al_draw_textf(font, al_map_rgb(135, 206, 50), 110 - camera_x, 10 - camera_y, ALLEGRO_ALIGN_CENTER, "x %i", playerHealth);

			al_draw_bitmap(moneta, 160 - camera_x, 10 - camera_y, 0);
			al_draw_textf(font, al_map_rgb(135, 206, 50), 220 - camera_x, 10 - camera_y, ALLEGRO_ALIGN_CENTER, "x %i", playerMoney);
		}

		if (gracznasklepie)
		{
			al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 180 - camera_y, ALLEGRO_ALIGN_CENTER, "to enter shop press B");
		}

		//cout << sprawdztablica_x << endl << sprawdztablica_y << endl;
		//cout << Enemy1_x << endl << Enemy1_y << endl;


		// --------------------------------------------------------------------------------- Trzeba poprawiæ warunki kolizji !!! ---------------------------------------------------------------------------------
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] /*&& Player_y >= 4.0*/) {
				//cout << "Up key was pressed" << endl;

				//movetest = MapaKolizji(tabEn, Player_x, Player_y,0);
				//cout << "up " <<  movetest << endl;
				//if (movetest == 0 || movetest == 2)
					if (bonusEffect == 1)
					{
						predkoscruchu = 3 + dodatekpredkosci;
					}
					else {
						predkoscruchu = 2.5 + dodatekpredkosci;
					}


					{
						//Player_y -= 8.0;
						for (int i = -predkoscruchu; i <= 0; i++)
						{
							movetest = MapaKolizji(tabEn, Player_x, Player_y + i, 0);
							if (movetest == 0)
							{
								Player_y += i;
							}
							if (movetest == 2)
							{
								//al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 180 - camera_y, ALLEGRO_ALIGN_CENTER, "to enter shop press B");
								gracznasklepie = 1;
								Player_y += i;
							}
							else
							{
								gracznasklepie = 0;
							}
						}
					}/*
				else
				{
					Player_y += 10.0;
				}*/
			}

			if (key[KEY_DOWN] /*&& Player_y <= SCREEN_H - CURSOR_SIZE - 4.0*/) {
				//cout << "Down key was pressed" << endl;

				//movetest = MapaKolizji(tabEn, Player_x, Player_y,1);
				//cout << "down " << movetest << endl;
				//if (movetest == 0 || movetest == 2)

				if (bonusEffect == 1)
				{
					predkoscruchu = 3 + dodatekpredkosci;
				}
				else {
					predkoscruchu = 2.5 + dodatekpredkosci;
				}

				
						//Player_y += 8.0;
						for (int i = predkoscruchu; i >= 0; i--)
						{
							movetest = MapaKolizji(tabEn, Player_x, Player_y + i, 1);
							if (movetest == 0)
							{
								Player_y += i;
							}
							if (movetest == 2)
							{
								//al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 180 - camera_y, ALLEGRO_ALIGN_CENTER, "to enter shop press B");
								gracznasklepie = 1;
								Player_y += i;
							}
							else
							{
								gracznasklepie = 0;
							}
						}
					/*
				else
				{
					Player_y -= 10.0;
				}*/
			}

			if (key[KEY_LEFT] /*&& Player_x >= 4.0*/) {
				//cout << "Left key was pressed" << endl;

				//movetest = MapaKolizji(tabEn, Player_x, Player_y,2);
				//cout << "left " << movetest << endl;

				if (bonusEffect == 1)
				{
					predkoscruchu = 3 + dodatekpredkosci;
				}
				else {
					predkoscruchu = 2.5 + dodatekpredkosci;
				}
				//if (movetest == 0 || movetest == 2)
				{
					for (int i = -predkoscruchu; i <= 0; i++)
					{
						movetest = MapaKolizji(tabEn, Player_x + i, Player_y, 2);
						if (movetest == 0)
						{
							Player_x += i;
						}
						if (movetest == 2)
						{
							//al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 180 - camera_y, ALLEGRO_ALIGN_CENTER, "to enter shop press B");
							gracznasklepie = 1;
							Player_x += i;
						}
						else
						{
							gracznasklepie = 0;
						}
					}
				}/*
				else
				{ 
					Player_x += 10.0;
				}*/
			}

			if (key[KEY_RIGHT] /*&& Player_x <= SCREEN_W - CURSOR_SIZE - 4.0*/) {
				//cout << "Right key was pressed" << endl;

				//movetest = MapaKolizji(tabEn, Player_x, Player_y,3);
				//cout << "right " << movetest << endl;

				if (bonusEffect == 1)
				{
					predkoscruchu = 3 + dodatekpredkosci;
				}
				else {
					predkoscruchu = 2.5 + dodatekpredkosci;
				}
					{
						for (int i = predkoscruchu; i >= 0; i--)
						{
							movetest = MapaKolizji(tabEn, Player_x + i, Player_y, 3);
							if (movetest == 0)
							{
								Player_x += i;
							}
							if (movetest == 2)
							{
								//al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 180 - camera_y, ALLEGRO_ALIGN_CENTER, "to enter shop press B");
								gracznasklepie = 1;
								Player_x += i;
							}
							else
							{
								gracznasklepie = 0;
							}
						}
					}
				/*
				else
				{
					Player_x -= 10.0;
				}*/
				
			}

			if (key[KEY_SPACE]) {
				// ---------------------------------------- TRZEBA POSPRZATAC, I WRZUCIC TO DO OSOBNEJ FUNKCJI, BO SZLAK JASNY TRAFI, KREW NAGLA ZALEJE KAZDEGO PRZEGLADAJACEGO TEN KOD ----------------------------------------
				if (lastweapon == 1)
				{

					switch (lastKey)
					{
					case 4:
						al_draw_bitmap(bron1, Player_x + 16, Player_y, 0);
						if ((Player_x + 16 >= Enemy1_x && Player_x + 16 <= Enemy1_x + 16) || (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 16 >= Enemy2_x && Player_x + 16 <= Enemy2_x + 16) || (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 16 >= Boss_x && Player_x + 16 <= Boss_x + 16) && (Player_y >= Boss_y && Player_y <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 3:
						al_draw_bitmap(bron1, Player_x - 16, Player_y, 0);
						if ((Player_x - 16 >= Enemy1_x && Player_x - 16 <= Enemy1_x + 16) || (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 16 >= Enemy2_x && Player_x - 16 <= Enemy2_x + 16) || (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 16 >= Boss_x && Player_x - 16 <= Boss_x + 16) && (Player_y >= Boss_y && Player_y <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 1:
						al_draw_bitmap(bron1, Player_x, Player_y - 16, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 16) || (Player_y - 16 >= Enemy1_y && Player_y - 16 <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 16) || (Player_y - 16 >= Enemy2_y && Player_y - 16 <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 16) && (Player_y - 16 >= Boss_y && Player_y - 16 <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 2:
						al_draw_bitmap(bron1, Player_x, Player_y + 16, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 16) || (Player_y + 16 >= Enemy1_y && Player_y + 16 <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 16) || (Player_y + 16 >= Enemy2_y && Player_y + 16 <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 16) && (Player_y + 16 >= Boss_y && Player_y + 16 <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					}


					if (key[KEY_RIGHT])
					{
						al_draw_bitmap(bron1, Player_x + 16, Player_y, 0);
						if ((Player_x + 16 >= Enemy1_x && Player_x + 16 <= Enemy1_x + 16) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 16 >= Enemy2_x && Player_x + 16 <= Enemy2_x + 16) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 16 >= Boss_x && Player_x + 16 <= Boss_x + 16) && (Player_y >= Boss_y && Player_y <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 16 >= Enemy3_x && Player_x + 16 <= Enemy3_x + 16) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 16))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 16 >= Enemy4_x && Player_x + 16 <= Enemy4_x + 16) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 16))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 16 >= Enemy5_x && Player_x + 16 <= Enemy5_x + 16) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 16))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_LEFT])
					{
						al_draw_bitmap(bron1, Player_x - 16, Player_y, 0);
						if ((Player_x - 16 >= Enemy1_x && Player_x - 16 <= Enemy1_x + 16) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 16 >= Enemy2_x && Player_x - 16 <= Enemy2_x + 16) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 16 >= Boss_x && Player_x - 16 <= Boss_x + 16) && (Player_y >= Boss_y && Player_y <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 16 >= Enemy3_x && Player_x - 16 <= Enemy3_x + 16) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 16))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 16 >= Enemy4_x && Player_x - 16 <= Enemy4_x + 16) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 16))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 16 >= Enemy5_x && Player_x - 16 <= Enemy5_x + 16) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 16))
						{
							cout << "Enemy4 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_UP])
					{
						al_draw_bitmap(bron1, Player_x, Player_y - 16, 0);
						if ((Player_x  >= Enemy1_x && Player_x  <= Enemy1_x + 16) && (Player_y - 16 >= Enemy1_y && Player_y - 16 <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x  >= Enemy2_x && Player_x  <= Enemy2_x + 16) && (Player_y - 16 >= Enemy2_y && Player_y - 16 <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}

						if ((Player_x >= Boss_x && Player_x <= Boss_x + 16) && (Player_y - 16 >= Boss_y && Player_y - 16 <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x>= Enemy3_x && Player_x<= Enemy3_x + 16) && (Player_y - 16 >= Enemy3_y && Player_y - 16 <= Enemy3_y + 16))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x>= Enemy4_x && Player_x <= Enemy4_x + 16) && (Player_y - 16 >= Enemy4_y && Player_y - 16 <= Enemy4_y + 16))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x>= Enemy5_x && Player_x <= Enemy5_x + 16) && (Player_y - 16 >= Enemy5_y && Player_y - 16 <= Enemy5_y + 16))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_DOWN])
					{
						al_draw_bitmap(bron1, Player_x, Player_y + 16, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 16) && (Player_y + 16 >= Enemy1_y && Player_y + 16 <= Enemy1_y + 16))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 16) && (Player_y + 16 >= Enemy2_y && Player_y + 16 <= Enemy2_y + 16))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 16) && (Player_y + 16 >= Boss_y && Player_y + 16 <= Boss_y + 16))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 16) && (Player_y +16 >= Enemy3_y && Player_y + 16 <= Enemy3_y + 16))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 16) && (Player_y + 16 >= Enemy4_y && Player_y + 16 <= Enemy4_y + 16))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 16) && (Player_y + 16 >= Enemy5_y && Player_y + 16 <= Enemy5_y + 16))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
				}

				if(lastweapon == 2)
				{

					switch (lastKey)
					{
					case 4:
						al_draw_bitmap(bron2, Player_x + 32, Player_y, 0);/*
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) || (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) || (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}*/
						break;
					case 3:
						al_draw_bitmap(bron2, Player_x - 32, Player_y, 0);/*
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) || (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) || (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}*/
						break;
					case 1:
						al_draw_bitmap(bron2, Player_x, Player_y - 32, 0);/*
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) || (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) || (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}*/
						break;
					case 2:
						al_draw_bitmap(bron2, Player_x, Player_y + 32, 0);/*
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) || (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) || (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}*/
						break;
					}

					if (key[KEY_RIGHT])
					{
						al_draw_bitmap(bron2, Player_x + 32, Player_y, 0);
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy3_x && Player_x + 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy4_x && Player_x + 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy5_x && Player_x + 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_LEFT])
					{
						al_draw_bitmap(bron2, Player_x - 32, Player_y, 0);
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy3_x && Player_x - 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy4_x && Player_x - 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy5_x && Player_x - 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_UP])
					{
						al_draw_bitmap(bron2, Player_x, Player_y - 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y - 32 >= Enemy3_y && Player_y - 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y - 32 >= Enemy4_y && Player_y - 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y - 32 >= Enemy5_y && Player_y - 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_DOWN])
					{
						al_draw_bitmap(bron2, Player_x, Player_y + 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y + 32 >= Enemy3_y && Player_y + 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y + 32 >= Enemy4_y && Player_y + 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y + 32 >= Enemy5_y && Player_y + 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
				}

				if (lastweapon == 3)
				{

					switch (lastKey)
					{
					case 4:
						al_draw_bitmap(bron3, Player_x + 32, Player_y, 0);
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Boss_x && Player_x + 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 3:
						al_draw_bitmap(bron3, Player_x - 32, Player_y, 0);
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Boss_x && Player_x - 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 1:
						al_draw_bitmap(bron3, Player_x, Player_y - 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}

						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y - 32 >= Boss_y && Player_y - 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 2:
						al_draw_bitmap(bron3, Player_x, Player_y + 32, 0);

						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y + 32 >= Boss_y && Player_y + 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					}


					if (key[KEY_RIGHT])
					{
						al_draw_bitmap(bron3, Player_x + 32, Player_y, 0);
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Boss_x && Player_x + 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy3_x && Player_x + 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy4_x && Player_x + 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy5_x && Player_x + 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_LEFT])
					{
						al_draw_bitmap(bron3, Player_x - 32, Player_y, 0);
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Boss_x && Player_x - 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy3_x && Player_x - 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy4_x && Player_x - 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy5_x && Player_x - 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_UP])
					{
						al_draw_bitmap(bron3, Player_x, Player_y - 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}

						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y - 32 >= Boss_y && Player_y - 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y - 32 >= Enemy3_y && Player_y - 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y - 32 >= Enemy4_y && Player_y - 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y - 32 >= Enemy5_y && Player_y - 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_DOWN])
					{
						al_draw_bitmap(bron3, Player_x, Player_y + 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y + 32 >= Boss_y && Player_y + 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y + 32 >= Enemy3_y && Player_y + 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y + 32 >= Enemy4_y && Player_y + 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y + 32 >= Enemy5_y && Player_y + 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
				}

				if (lastweapon == 4)
				{

					switch (lastKey)
					{
					case 4:
						al_draw_bitmap(bron4, Player_x + 32, Player_y, 0);
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Boss_x && Player_x + 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 3:
						al_draw_bitmap(bron4, Player_x - 32, Player_y, 0);
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Boss_x && Player_x - 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 1:
						al_draw_bitmap(bron4, Player_x, Player_y - 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y - 32 >= Boss_y && Player_y - 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 2:
						al_draw_bitmap(bron4, Player_x, Player_y + 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y + 32 >= Boss_y && Player_y + 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					}


					if (key[KEY_RIGHT])
					{
						al_draw_bitmap(bron4, Player_x + 32, Player_y, 0);
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Boss_x && Player_x + 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy3_x && Player_x + 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy4_x && Player_x + 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy5_x && Player_x + 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_LEFT])
					{
						al_draw_bitmap(bron4, Player_x - 32, Player_y, 0);
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Boss_x && Player_x - 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy3_x && Player_x - 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy4_x && Player_x - 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy5_x && Player_x - 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_UP])
					{
						al_draw_bitmap(bron4, Player_x, Player_y - 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y - 32 >= Boss_y && Player_y - 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y - 32 >= Enemy3_y && Player_y - 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y - 32 >= Enemy4_y && Player_y - 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y - 32 >= Enemy5_y && Player_y - 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_DOWN])
					{
						al_draw_bitmap(bron4, Player_x, Player_y + 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y + 32 >= Boss_y && Player_y + 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y + 32 >= Enemy3_y && Player_y + 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y + 32 >= Enemy4_y && Player_y + 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y + 32 >= Enemy5_y && Player_y + 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
				}


				if (lastweapon == 5)
				{

					switch (lastKey)
					{
					case 4:
						al_draw_bitmap(bron5, Player_x + 32, Player_y, 0);
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Boss_x && Player_x + 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 3:
						al_draw_bitmap(bron5, Player_x - 32, Player_y, 0);
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Boss_x && Player_x - 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 1:
						al_draw_bitmap(bron5, Player_x, Player_y - 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}

						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y - 32 >= Boss_y && Player_y - 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					case 2:
						al_draw_bitmap(bron5, Player_x, Player_y + 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y + 32 >= Boss_y && Player_y + 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						break;
					}


					if (key[KEY_RIGHT])
					{
						al_draw_bitmap(bron5, Player_x + 32, Player_y, 0);
						if ((Player_x + 32 >= Enemy1_x && Player_x + 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy2_x && Player_x + 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Boss_x && Player_x + 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy3_x && Player_x + 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy4_x && Player_x + 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x + 32 >= Enemy5_x && Player_x + 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_LEFT])
					{
						al_draw_bitmap(bron5, Player_x - 32, Player_y, 0);
						if ((Player_x - 32 >= Enemy1_x && Player_x - 32 <= Enemy1_x + 32) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy2_x && Player_x - 32 <= Enemy2_x + 32) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Boss_x && Player_x - 32 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy3_x && Player_x - 32 <= Enemy3_x + 32) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy4_x && Player_x - 32 <= Enemy4_x + 32) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x - 32 >= Enemy5_x && Player_x - 32 <= Enemy5_x + 32) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_UP])
					{
						al_draw_bitmap(bron5, Player_x, Player_y - 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y - 32 >= Enemy1_y && Player_y - 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y - 32 >= Enemy2_y && Player_y - 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}

						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y - 32 >= Boss_y && Player_y - 32 <= Boss_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y - 32 >= Enemy3_y && Player_y - 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y - 32 >= Enemy4_y && Player_y - 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y - 32 >= Enemy5_y && Player_y - 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
					if (key[KEY_DOWN])
					{
						al_draw_bitmap(bron5, Player_x, Player_y + 32, 0);
						if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 32) && (Player_y + 32 >= Enemy1_y && Player_y + 32 <= Enemy1_y + 32))
						{
							cout << "Enemy killed!";
							enemyDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 32) && (Player_y + 32 >= Enemy2_y && Player_y + 32 <= Enemy2_y + 32))
						{
							cout << "Enemy2 killed!";
							enemyDead2 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Boss_x && Player_x <= Boss_x + 32) && (Player_y + 32 >= Boss_y && Player_y + 32 <= Boss_y + 32))
						{
							cout << "Boss killed!";
							bossDead = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 32) && (Player_y + 32 >= Enemy3_y && Player_y + 32 <= Enemy3_y + 32))
						{
							cout << "Enemy3 killed!";
							enemyDead3 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 32) && (Player_y + 32 >= Enemy4_y && Player_y + 32 <= Enemy4_y + 32))
						{
							cout << "Enemy4 killed!";
							enemyDead4 = 1;
							playerMoney += 30;
						}
						if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 32) && (Player_y + 32 >= Enemy5_y && Player_y + 32 <= Enemy5_y + 32))
						{
							cout << "Enemy5 killed!";
							enemyDead5 = 1;
							playerMoney += 30;
						}
					}
				}

			}

			/*cout << "Player_x: " << Player_x << endl;
			cout << "Player_y: " << Player_y << endl;*/

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			test = main();
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				lastKey = 1;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				lastKey = 2;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				lastKey = 3;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				lastKey = 4;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;

			case ALLEGRO_KEY_V:
				switch (lastKey)
				{
				case 4:
					/*if(Player_y >= 4.0)*/
					{ Player_x += 44;}
					break;
				case 3:
					/*if (Player_y <= SCREEN_H - CURSOR_SIZE - 4.0)*/
					{ Player_x -= 44;}
					break;
				case 2:
					/*if(Player_x >= 4.0)*/
					{ Player_y += 44;}
					break;
				case 1:
					/*if(Player_x <= SCREEN_W - CURSOR_SIZE - 4.0)*/
					{ Player_y -= 44;}
				}
				cout << "Player_x: " << Player_x << endl;
				cout << "Player_y: " << Player_y << endl;
				break;


				case ALLEGRO_KEY_B:
					{
						/*if (minitest == 0)
						{
							minitest = 1;
						}
						else
						{
							minitest = 0;
						}*/
							//al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 80 - camera_y, ALLEGRO_ALIGN_CENTER, "You entered Shop!");
					if (gracznasklepie)
					{
						LogikaSklepu(event_queue, font, sklep_strzalka, bonus3, bonus1, bron3, bron4, ptr_playerMoney,ptr_playerHealth,ptr_dodatekpredkosci,ptr_kupionabron);

						switch (kupionabron)
						{
						case 1:
							bronEffect3 = 1;
							break;
						case 2:
							bronEffect4 = 1;
							break;
						case 3:
							bronEffect3 = 1;
							bronEffect4 = 1;
							break;
						default:
							break;
						}
					}
					break;
					}
				
				case ALLEGRO_KEY_1:
				{

					if(bronEffect == 1)
					{
						lastweapon = 1;
					}
					break;
				}

				case ALLEGRO_KEY_2:
				{

					if (bronEffect2 == 1)
					{
						lastweapon = 2;
					}
					break;
				}

				case ALLEGRO_KEY_3:
				{

					if (bronEffect3 == 1)
					{
						lastweapon = 3;
					}
					break;
				}

				case ALLEGRO_KEY_4:
				{

					if (bronEffect4 == 1)
					{
						lastweapon = 4;
					}
					break;
				}

				case ALLEGRO_KEY_5:
				{

					if (bronEffect5 == 1)
					{
						lastweapon = 5;
					}
					break;
				}

			}

			

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		/*if (minitest == 0)
		{
			al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 80 - camera_y, ALLEGRO_ALIGN_CENTER, "You entered Shop!");
		}*/


		if ((Player_x >= bonus1_x && Player_x <= bonus1_x +16 ) && (Player_y >= bonus1_y && Player_y <= bonus1_y +16))
		{
			bonusEffect = 1;
			cout << "Bonus was picked up!";
			bonus1_x = -10000;
			bonus1_y = -10000;
		}

		if ((Player_x >= bonus2_x && Player_x <= bonus2_x + 16) && (Player_y >= bonus2_y && Player_y <= bonus2_y + 16))
		{
			bonusEffect2 = 1;
			cout << "Bonus2 was picked up!";
			bonus2_x = -10000;
			bonus2_y = -10000;
		}

		if ((Player_x >= bonus3_x && Player_x <= bonus3_x + 16) && (Player_y >= bonus3_y && Player_y <= bonus3_y + 16))
		{
			bonusEffect3 = 1;
			playerHealth++;
			cout << "Bonus3 was picked up!";
			bonus3_x = -10000;
			bonus3_y = -10000;
		}

		if ((Player_x >= bonus4_x && Player_x <= bonus4_x + 16) && (Player_y >= bonus4_y && Player_y <= bonus4_y + 16))
		{
			bonusEffect4 = 1;
			playerHealth += 2;
			cout << "Bonus4 was picked up!";
			bonus4_x = -10000;
			bonus4_y = -10000;
		}

		if ((Player_x >= bonus5_x && Player_x <= bonus5_x + 16) && (Player_y >= bonus5_y && Player_y <= bonus5_y + 16))
		{
			bonusEffect5 = 1;
			playerMoney += 60;
			cout << "Bonus5 was picked up!";
			bonus5_x = -10000;
			bonus5_y = -10000;
		}

		if ((Player_x >= bron1_x && Player_x <= bron1_x + 16) && (Player_y >= bron1_y && Player_y <= bron1_y + 16))
		{
			bronEffect = 1;
			lastweapon = 1;
			cout << "Bron1 was picked up!";
			bron1_x = -10000;
			bron1_y = -10000;
		}

		if ((Player_x >= bron2_x && Player_x <= bron2_x + 16) && (Player_y >= bron2_y && Player_y <= bron2_y + 16))
		{
			bronEffect2 = 1;
			lastweapon = 2;
			cout << "Bron2 was picked up!";
			bron2_x = -10000;
			bron2_y = -10000;
		}

		if ((Player_x >= bron3_x && Player_x <= bron3_x + 32) && (Player_y >= bron3_y && Player_y <= bron3_y + 32))
		{
			bronEffect3 = 1;
			lastweapon = 3;
			cout << "Bron3 was picked up!";
			bron3_x = -10000;
			bron3_y = -10000;
		}

		if ((Player_x >= bron4_x && Player_x <= bron4_x + 32) && (Player_y >= bron4_y && Player_y <= bron4_y + 32))
		{
			bronEffect4 = 1;
			lastweapon = 4;
			cout << "Bron4 was picked up!";
			bron4_x = -10000;
			bron4_y = -10000;
		}

		if ((Player_x >= bron5_x && Player_x <= bron5_x + 32) && (Player_y >= bron5_y && Player_y <= bron5_y + 32))
		{
			bronEffect5 = 1;
			lastweapon = 5;
			cout << "Bron5 was picked up!";
			bron5_x = -10000;
			bron5_y = -10000;
		}

		if ((Player_x >= Enemy1_x && Player_x <= Enemy1_x + 16) && (Player_y >= Enemy1_y && Player_y <= Enemy1_y + 16))
		{
			enemyEffect = 1;
			if (bonusEffect2 == 1)
			{
				cout << "Player has killed enemy1 with bonus.";
				enemyDead = 1;
				playerMoney += 10;
			}
			else
			{
				if (playerHealth >= 1)
				{
					cout << "Enemy1 hit Player!";
					playerHealth--;
				}
				else
				{
					cout << "Enemy1 killed Player!";

					al_destroy_display(displayEn);
					wyjscie = main();
					return 0;
				}
			}
			Enemy1_x = -10000;
			Enemy1_y = -10000;
		}

		if ((Player_x >= Enemy2_x && Player_x <= Enemy2_x + 16) && (Player_y >= Enemy2_y && Player_y <= Enemy2_y + 16))
		{
			enemyEffect2 = 1;
			if (bonusEffect2 == 1)
			{
				cout << "Player has killed enemy2 with bonus.";
				enemyDead2 = 1;
				playerMoney += 10;
			}
			else
			{
				if (playerHealth >= 1)
				{
					cout << "Enemy2 hit Player!";
					playerHealth--;
				}
				else
				{
					cout << "Enemy2 killed Player!";

					al_destroy_display(displayEn);
					wyjscie = main();
					return 0;
				}
			}
			Enemy2_x = -10000;
			Enemy2_y = -10000;
		}

		if ((Player_x >= Enemy3_x && Player_x <= Enemy3_x + 16) && (Player_y >= Enemy3_y && Player_y <= Enemy3_y + 16))
		{
			enemyEffect = 1;
			if (bonusEffect2 == 1)
			{
				cout << "Player has killed enemy3 with bonus.";
				enemyDead = 1;
				playerMoney += 10;
			}
			else
			{
				if (playerHealth >= 1)
				{
					cout << "Enemy3 hit Player!";
					playerHealth--;
				}
				else
				{
					cout << "Enemy3 killed Player!";

					al_destroy_display(displayEn);
					wyjscie = main();
					return 0;
				}
			}
			Enemy3_x = -10000;
			Enemy3_y = -10000;
		}

		if ((Player_x >= Enemy4_x && Player_x <= Enemy4_x + 16) && (Player_y >= Enemy4_y && Player_y <= Enemy4_y + 16))
		{
			enemyEffect = 1;
			if (bonusEffect2 == 1)
			{
				cout << "Player has killed enemy3 with bonus.";
				enemyDead = 1;
				playerMoney += 10;
			}
			else
			{
				if (playerHealth >= 1)
				{
					cout << "Enemy3 hit Player!";
					playerHealth--;
				}
				else
				{
					cout << "Enemy3 killed Player!";

					al_destroy_display(displayEn);
					wyjscie = main();
					return 0;
				}
			}
			Enemy4_x = -10000;
			Enemy4_y = -10000;
		}

		if ((Player_x >= Enemy5_x && Player_x <= Enemy5_x + 16) && (Player_y >= Enemy5_y && Player_y <= Enemy5_y + 16))
		{
			enemyEffect = 1;
			if (bonusEffect2 == 1)
			{
				cout << "Player has killed enemy3 with bonus.";
				enemyDead = 1;
				playerMoney += 10;
			}
			else
			{
				if (playerHealth >= 1)
				{
					cout << "Enemy3 hit Player!";
					playerHealth--;
				}
				else
				{
					cout << "Enemy3 killed Player!";

					al_destroy_display(displayEn);
					wyjscie = main();
					return 0;
				}
			}
			Enemy5_x = -10000;
			Enemy5_y = -10000;
		}

		if ((Player_x >= Boss_x && Player_x + 16 <= Boss_x + 32) && (Player_y >= Boss_y && Player_y + 16 <= Boss_y + 16))
		{
			enemyEffect2 = 1;
			if (bonusEffect2 == 1)
			{
				cout << "Player has killed Boss with bonus.";
				bossDead = 1;
				playerMoney += 10;
			}
			else
			{
				if (playerHealth >= 1)
				{
					cout << "Boss hit Player!";
					playerHealth--;
				}
				else
				{
					cout << "Boss killed Player!";

					al_destroy_display(displayEn);
					wyjscie = main();
					return 0;
				}
			}
			Boss_x = -10000;
			Boss_y = -10000;
		}

		if (enemyDead == 0)
		{
			ruchPionowyPrzeciwnika(ptr_Enemy1_x, ptr_Enemy1_y, tabEn, ptr_kierunek1);
		}
		
		if (enemyDead2 == 0)
		{
			ruchPoziomyPrzeciwnika(ptr_Enemy2_x, ptr_Enemy2_y, tabEn, ptr_kierunek2);
		}

		if (enemyDead3 == 0)
		{
			ruchPionowyPrzeciwnika(ptr_Enemy3_x, ptr_Enemy3_y, tabEn, ptr_kierunek3);
		}

		if (enemyDead4 == 0)
		{
			ruchPoziomyPrzeciwnika(ptr_Enemy4_x, ptr_Enemy4_y, tabEn, ptr_kierunek4);
		}

		if (enemyDead5 == 0)
		{
			ruchPoziomyPrzeciwnika(ptr_Enemy5_x, ptr_Enemy5_y, tabEn, ptr_kierunek5);
		}

		if (bossDead == 0)
		{
			if (bosstimer >= 120)
			{
				if (czasowspomagacz == 0)
				{
					czasowspomagacz = 1;
				}
				else czasowspomagacz = 0;

				bosstimer = 0;
			}
			BOSS(ptr_Boss_x, ptr_Boss_y, tabEn, ptr_bosskierunek, ptr_czasowspomagacz);
			bosstimer++;
		}

		/*
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (tabEn[i][j] != 0)
				{
					if (tabEn[i][j] == 1)
					{
						al_draw_bitmap(obrazek1, i * 32, j * 32, 0);
					}
					else if (tabEn[i][j] == 2)
					{
						al_draw_bitmap(obrazek2, i * 32, j * 32, 0);
					}
				}
			}
		}
		*/


		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

		
			camera_x = -(Player_x - SCREEN_W / 2);
			camera_y = -(Player_y - SCREEN_H / 2);

			al_identity_transform(&camera);
			al_translate_transform(&camera, camera_x, camera_y);
			al_use_transform(&camera);

			//al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(Player, Player_x, Player_y, 0);

			/*{
				al_draw_bitmap(serce, 60-camera_x, 10-camera_y, 0);
				al_draw_textf(font, al_map_rgb(135, 206, 50), 110-camera_x, 10-camera_y, ALLEGRO_ALIGN_CENTER, "x %i", playerHealth);
				
				al_draw_bitmap(moneta, 160 - camera_x, 10 - camera_y, 0);
				al_draw_textf(font, al_map_rgb(135, 206, 50), 220 - camera_x, 10 - camera_y, ALLEGRO_ALIGN_CENTER, "x %i", playerMoney);
			}*/

			if (bronEffect == 0)
			{
				al_draw_bitmap(bron1, bron1_x, bron1_y, 0);
			}

			if (bronEffect2 == 0)
			{
				al_draw_bitmap(bron2, bron2_x, bron2_y, 0);
			}

			if (bronEffect3 == 0)
			{
				al_draw_bitmap(bron3, bron3_x, bron3_y, 0);
			}

			if (bronEffect4 == 0)
			{
				al_draw_bitmap(bron4, bron4_x, bron4_y, 0);
			}

			if (bronEffect5 == 0)
			{
				al_draw_bitmap(bron5, bron5_x, bron5_y, 0);
			}

			if (bonusEffect == 0)
			{
				al_draw_bitmap(bonus1, bonus1_x, bonus1_y, 0);
			}
			
			if (bonusEffect2 == 0)
			{
				al_draw_bitmap(bonus2, bonus2_x, bonus2_y, 0);
			}

			if (enemyDead == 0)
			{
				al_draw_bitmap(Enemy1, Enemy1_x, Enemy1_y, 0);
			}
			else
			{
				Enemy1_x = -10000;
				Enemy1_y = -10000;
			}

			if (enemyDead2 == 0)
			{
				al_draw_bitmap(Enemy2, Enemy2_x, Enemy2_y, 0);
			}
			else
			{
				Enemy2_x = -10000;
				Enemy2_y = -10000;
			}

			if (enemyDead3 == 0)
			{
				al_draw_bitmap(Enemy3, Enemy3_x, Enemy3_y, 0);
			}
			else
			{
				Enemy3_x = -10000;
				Enemy3_y = -10000;
			}

			if (enemyDead4 == 0)
			{
				al_draw_bitmap(Enemy4, Enemy4_x, Enemy4_y, 0);
			}
			else
			{
				Enemy4_x = -10000;
				Enemy4_y = -10000;
			}

			if (enemyDead5 == 0)
			{
				al_draw_bitmap(Enemy5, Enemy5_x, Enemy5_y, 0);
			}
			else
			{
				Enemy5_x = -10000;
				Enemy5_y = -10000;
			}

			if (bossDead == 0)
			{
				al_draw_bitmap(Boss, Boss_x, Boss_y, 0);
			}
			else
			{
				wygrana++;
				al_draw_text(font, al_map_rgb(135, 206, 50), 320 - camera_x, 180 - camera_y, ALLEGRO_ALIGN_CENTER, "You Have Defeated Boss of this Biome!!!");
				cout << aktualnybiom << endl;
				Boss_x = -10000;
				Boss_y = -10000;
				if (wygrana >= 320)
				{
					
					

					if (aktualnybiom>=3)
					{
						ofstream plik("Save.txt");

						plik << 0;

						plik.close();
						doexit = true;
						wartosctestowawyjscia = true;
					}
					else
					{

						ofstream plik("Save.txt");

						plik << aktualnybiom + 1;

						plik.close();

						test = Enemies();
					}
				}
			}

			if (bonusEffect3 == 0)
			{
				al_draw_bitmap(bonus3, bonus3_x, bonus3_y, 0);
			}

			if (bonusEffect4 == 0)
			{
				al_draw_bitmap(bonus4, bonus4_x, bonus4_y, 0);
			}

			if (bonusEffect5 == 0)
			{
				al_draw_bitmap(bonus5, bonus5_x, bonus5_y, 0);
			}



			/*camera_x = -(Player_x - SCREEN_W / 2);
			camera_y = -(Player_y - SCREEN_H / 2);*/

			/*camera_x = -(Player_x - SCREEN_W / 2);
			camera_y = -(Player_y - SCREEN_H / 2);

			al_identity_transform(&camera);
			al_translate_transform(&camera, camera_x, camera_y);
			al_use_transform(&camera);*/

			al_flip_display();
		}





	}

	if (wartosctestowawyjscia = true)
	{
		return 0;
	}

	al_destroy_bitmap(Player);
	al_destroy_timer(timerEn);
	al_destroy_display(displayEn);
	al_destroy_event_queue(event_queue);
	test = main();

	return 0;
}






/*
al_flip_display();

for (int i = 0; i < 20; i++)
{
for (int j = 0; j < 15; j++)
{
if (tabEn[i][j] != 0)
{
if (tabEn[i][j] == 1)
{
al_draw_bitmap(obrazek1, i * 32, j * 32, 0);
}
else if (tabEn[i][j] == 2)
{
al_draw_bitmap(obrazek2, i * 32, j * 32, 0);
}
}
}
}
*/

//al_draw_bitmap(Player, 100, 100,0);

/*
al_draw_text(font, al_map_rgb(0, 255, 0), 300, 50, ALLEGRO_ALIGN_LEFT, "S-zapisz");
al_draw_text(font, al_map_rgb(0, 255, 0), 300, 100, ALLEGRO_ALIGN_LEFT, "L-Wczytaj");
al_draw_text(font, al_map_rgb(0, 255, 0), 300, 150, ALLEGRO_ALIGN_LEFT, "B-Blok");
al_draw_text(font, al_map_rgb(0, 255, 0), 300, 200, ALLEGRO_ALIGN_LEFT, "ESC-Wyjscie");
*/



/*
fstream Hub;
Hub.open("Mapy/Hub.txt", ios::in | ios::out);
for (int i = 0; i < 20; i++)
{
for (int j = 0; j < 15; j++)
{
Hub >> tabEn[i][j];
}
}
cout << "wczytano mape" << endl;
Hub.close();
*/







/*
ALLEGRO_BITMAP *obrazek1 = NULL;
ALLEGRO_BITMAP *obrazek2 = NULL;
ALLEGRO_BITMAP *Enemy1 = NULL;
ALLEGRO_BITMAP *Enemy2 = NULL;
ALLEGRO_BITMAP *Player = NULL;
ALLEGRO_BITMAP *bron1 = NULL;
ALLEGRO_BITMAP *bron2 = NULL;
ALLEGRO_BITMAP *bonus1 = NULL;
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
*/



/*
Enemy1 = al_load_bitmap("Enemies/sciana_Placeholder.png");
if (!Enemy1)
{
fprintf(stderr, "failed to create Enemy1 bitmap!\n");
al_destroy_display(displayEn);
al_destroy_timer(timerEn);
return -1;
}

Enemy2 = al_load_bitmap("Enemies/Droga_Placeholder.png");
if (!Enemy2)
{
fprintf(stderr, "failed to create Enemy2 bitmap!\n");
al_destroy_display(displayEn);
al_destroy_timer(timerEn);
return -1;
}
*/