#include "biblioteki.h"
#include "Random_Font.hpp"
//#include "kolkokwadrat.cpp"
//#include <Edytor.cpp>
#include <fstream>


using namespace std;

const float FPS = 60;

int kolkokwadrat();
int Edytor();
int main();

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int CURSOR_SIZE = 32;

int tab[20][15];

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_S, KEY_L, KEY_B, KEY_ESCAPE, KEY_SPACE
};
/*
struct Bloki
{
//struktura przechowywuje informacje o mo¿liwych do u¿ycia blokach
fstream plik;
int numer;
string nazwa;
};
*/

int Edytor()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();

	bool key[9] = { false, false, false, false, false, false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	int cursor_y = 0;
	int cursor_x = 0;

	int x, y;

	ALLEGRO_DISPLAY* displayE = al_create_display(1024, 768);
	ALLEGRO_FONT* font = Random_Font();
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timerE = NULL;
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);

	timerE = al_create_timer(1.0 / FPS);

	ALLEGRO_BITMAP *obrazek1 = NULL;
	ALLEGRO_BITMAP *obrazek2 = NULL;
	ALLEGRO_BITMAP *cursor = NULL;

	obrazek1 = al_load_bitmap("bitmapy/sciana_Placeholder.png");
	if (!obrazek1)
	{
		fprintf(stderr, "failed to create obrazek1 bitmap!\n");
		al_destroy_display(displayE);
		al_destroy_timer(timerE);
		return -1;
	}

	obrazek2 = al_load_bitmap("bitmapy/Droga_Placeholder.png");
	if (!obrazek2)
	{
		fprintf(stderr, "failed to create obrazek2 bitmap!\n");
		al_destroy_display(displayE);
		al_destroy_timer(timerE);
		return -1;
	}

	cursor = al_create_bitmap(CURSOR_SIZE, CURSOR_SIZE);

	//al_set_target_bitmap(cursor);
	//al_clear_to_color(al_map_rgb(255, 0, 255));

	cursor = obrazek2;

	al_set_target_bitmap(al_get_backbuffer(displayE));


	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(displayE));
	al_register_event_source(event_queue, al_get_timer_event_source(timerE));

	al_start_timer(timerE);

	int test = 0;
	int wyjscie = 0;
	int czas = 0;
	int miniczas = 0;



	while (1)
	{
		al_flip_display();

		
		while (!doexit)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				al_destroy_display(displayE);
				wyjscie = main();
				return 0;
			}

			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (key[KEY_UP] && cursor_y >= 4.0) {
					czas++;
					if (czas >= 30)
					{
						miniczas++;
						if (miniczas >= 3)
						{
							cursor_y -= 32.0;
							miniczas = 0;
						}
					}
				}

				if (key[KEY_DOWN] && cursor_y <= SCREEN_H - CURSOR_SIZE - 4.0) {
					czas++;
					if (czas >= 30)
					{
						miniczas++;
						if (miniczas >= 3)
						{
							cursor_y += 32.0;
							miniczas = 0;
						}
					}
				}

				if (key[KEY_LEFT] && cursor_x >= 4.0) {
					czas++;
					if (czas >= 30)
					{
						miniczas++;
						if (miniczas >= 3)
						{
							cursor_x -= 32.0;
							miniczas = 0;
						}
					}
				}

				if (key[KEY_RIGHT] && cursor_x <= SCREEN_W - CURSOR_SIZE - 4.0) {
					czas++;
					if (czas >= 30)
					{
						miniczas++;
						if (miniczas >= 3)
						{
							cursor_x += 32.0;
							miniczas = 0;
						}
					}
				}

				if (key[KEY_B])
				{
					//cursor = obrazek1;
					//cursor = obrazek2;
				}
				if (key[KEY_SPACE])
				{
					if (test == 0)
					{
						tab[cursor_x / 32][cursor_y / 32] = 2;
					}
					else if (test == 1)
					{
						tab[cursor_x / 32][cursor_y / 32] = 1;
					}
				}


				redraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					if (cursor_y >= 4.0)
					{
						cursor_y -= 32.0;
					}
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					if (cursor_y <= SCREEN_H - CURSOR_SIZE - 4.0)
					{
						cursor_y += 32.0;
					}
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					if (cursor_x >= 4.0)
					{
						cursor_x -= 32.0;
					}
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					if (cursor_x <= SCREEN_W - CURSOR_SIZE - 4.0)
					{
						cursor_x += 32.0;
					}
					break;

				case ALLEGRO_KEY_B:
					key[KEY_B] = true;
					break;

				case ALLEGRO_KEY_S:
					key[KEY_S] = true;
					break;

				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = true;
					break;

				case ALLEGRO_KEY_L:
					key[KEY_L] = true;
					cout << "L was pressed" << endl;
					fstream pliczek1;
					pliczek1.open("Mapy/mapaL.txt", ios::in | ios::out);
					for (int i = 0; i < 20; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							pliczek1 >> tab[i][j];
						}
					}
					cout << "wczytano mape" << endl;
					pliczek1.close();
					break;
				}
				cout << cursor_x << endl;
				cout << cursor_y << endl;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					czas = 0;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					czas = 0;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					czas = 0;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					czas = 0;
					break;

				case ALLEGRO_KEY_B:
					key[KEY_B] = false;
					if (test == 0)
					{
						cursor = obrazek1;
						test++;
					}
					else if (test == 1)
					{
						cursor = obrazek2;
						test = 0;
					}
					break;

				case ALLEGRO_KEY_ESCAPE:
					al_destroy_display(displayE);
					wyjscie = main();
					return 0;
					//doexit = true;
					break;

				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = false;
					break;

				case ALLEGRO_KEY_S:
					key[KEY_S] = false;
					fstream pliczek;
					pliczek.open("Mapy/mapa.txt", ios::in | ios::out);
					for (int i = 0; i < 20; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							pliczek << tab[i][j];
							pliczek << " ";
						}
						pliczek << endl;
					}
					cout << "zapisano mape" << endl;
					pliczek.close();
					break;

				}
			}
			if (redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;

				al_clear_to_color(al_map_rgb(0, 0, 0));

				al_draw_filled_rectangle(0, 0, 640, 480, White);


				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						if (tab[i][j] != 0)
						{
							if (tab[i][j] == 1)
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

				al_draw_bitmap(cursor, cursor_x, cursor_y, 0);

				al_draw_text(font, al_map_rgb(0, 255, 0), 700, 50, ALLEGRO_ALIGN_LEFT, "S-zapisz");
				al_draw_text(font, al_map_rgb(0, 255, 0), 700, 100, ALLEGRO_ALIGN_LEFT, "L-Wczytaj");
				al_draw_text(font, al_map_rgb(0, 255, 0), 700, 150, ALLEGRO_ALIGN_LEFT, "B-Blok");
				al_draw_text(font, al_map_rgb(0, 255, 0), 700, 200, ALLEGRO_ALIGN_LEFT, "ESC-Wyjscie");

				al_flip_display();
			}

		}
	}


	al_destroy_display(displayE);
	al_destroy_timer(timerE);

	return 0;
}
