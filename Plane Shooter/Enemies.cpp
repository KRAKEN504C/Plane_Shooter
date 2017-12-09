#include "biblioteki.h"
#include "Random_Font.hpp"
#include <fstream>
#include <random>
#include <stdlib.h>
#include <time.h>


using namespace std;

const float FPS = 60;

int main();

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int CURSOR_SIZE = 16;

int tabEn[20][15];



enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_S, KEY_L, KEY_B, KEY_ESCAPE, KEY_SPACE
};


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
	int Player_y = 0;
	int Player_x = 0;

	int Enemy1_y = rand()%300 + 64;
	int Enemy1_x = rand() % 360 + 164;

	int Enemy2_y = rand() % 30 + 364;
	int Enemy2_x = rand() % 30 + 364;

	int bron1_y = rand() % 10 + 264;
	int bron1_x = rand() % 150 + 364;

	int bron2_y = rand() % 200 + 164;
	int bron2_x = rand() % 225 + 364;

	int bonus1_y = rand() % 10 + 364;
	int bonus1_x = rand() % 190 + 364;

	int bonus2_y = rand() % 400 + 20;
	int bonus2_x = rand() % 300 + 120;



	bool key[9] = { false, false, false, false, false, false, false, false, false };

	ALLEGRO_DISPLAY* displayEn = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_FONT* font = Random_Font();
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timerEn = NULL;
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);

	timerEn = al_create_timer(1.0 / FPS);

	fstream HubL;
	HubL.open("Mapy/Hub.txt", ios::in | ios::out);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			HubL >> tabEn[i][j];
		}
	}
	cout << "wczytano mape" << endl;
	HubL.close();


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

	Player = al_create_bitmap(CURSOR_SIZE, CURSOR_SIZE);

	al_set_target_bitmap(Player);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(displayEn));

	//Player = al_load_bitmap("Player/Player_Placeholder.png");

	

	//al_clear_to_color(al_map_rgb(255,255,255));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(displayEn));
	al_register_event_source(event_queue, al_get_timer_event_source(timerEn));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timerEn);

	int test = 0;
	int wyjscie = 0;
	int czas = 0;
	int miniczas = 0;




	

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && Player_y >= 4.0) {
				cout << "Up key was pressed" << endl;
				Player_y -= 4.0;
			}

			if (key[KEY_DOWN] && Player_y <= SCREEN_H - CURSOR_SIZE - 4.0) {
				cout << "Down key was pressed" << endl;
				Player_y += 4.0;
			}

			if (key[KEY_LEFT] && Player_x >= 4.0) {
				cout << "Left key was pressed" << endl;
				Player_x -= 4.0;
			}

			if (key[KEY_RIGHT] && Player_x <= SCREEN_W - CURSOR_SIZE - 4.0) {
				cout << "Right key was pressed" << endl;
				Player_x += 4.0;
			}

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
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
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

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}



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



		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(Player, Player_x, Player_y, 0);

			al_draw_bitmap(bron1, bron1_x, bron1_y, 0);

			al_draw_bitmap(bron2, bron2_x, bron2_y, 0);

			al_draw_bitmap(bonus1, bonus1_x, bonus1_y, 0);

			al_draw_bitmap(bonus2, bonus2_x, bonus2_y, 0);

			al_draw_bitmap(Enemy1, Enemy1_x, Enemy1_y, 0);

			al_draw_bitmap(Enemy2, Enemy2_x, Enemy2_y, 0);

			al_flip_display();
		}





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