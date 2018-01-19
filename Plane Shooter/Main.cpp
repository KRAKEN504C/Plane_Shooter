#include "biblioteki.h"
#include "Random_Font.hpp"
//#include "kolkokwadrat.cpp"
//#include <Edytor.cpp>
#include <fstream>

using namespace std;

const float FPS = 60;

int kolkokwadrat();
int Edytor();
int Enemies();
void generatorPoziomu();

int main()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();

	int x, y;

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	ALLEGRO_FONT* font = Random_Font();
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_COLOR Zielony = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR Czerwony = al_map_rgb(255, 0, 0);


	timer = al_create_timer(1.0 / FPS);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	int test = 0;


	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//Rozrysowanie menu

		al_draw_rectangle(300, 50, 500, 300, Czerwony, 1);

		al_draw_text(font, Zielony, 400, 100, ALLEGRO_ALIGN_CENTER, "Nowa Gra");
		al_draw_text(font, Zielony, 400, 150, ALLEGRO_ALIGN_CENTER, "Wczytaj Gre");
		al_draw_text(font, Zielony, 400, 200, ALLEGRO_ALIGN_CENTER, "Edytor");
		al_draw_text(font, Zielony, 400, 250, ALLEGRO_ALIGN_CENTER, "Wyjscie");

		al_flip_display();

		//koniec rozrysowania menu.
		//podswietlenie aktywnych opcji menu, oraz dzialanie podczas ich wyboru.

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			al_destroy_display(display);
			return 0;
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
			ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			x = ev.mouse.x;
			y = ev.mouse.y;


			if ((x >= 300 && x <= 500) && (y >= 100 && y <= 130))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 100, 500, 130, Czerwony);
				if (ev.mouse.button & 1)
				{
					cout << "Left mouse has been clicked on start" << endl;
					al_destroy_display(display);
					ofstream plik("Save.txt");

					plik << 0;

					plik.close();
					test = Enemies();
					return 0;													//---------->Teraz dobrze wychodzi, dzieki tej malutkiej prosciutkiej linijce<----------
					//display = al_create_display(800, 600);
				}
			}
			else if ((x >= 300 && x <= 500) && (y >= 150 && y <= 180))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 150, 500, 180, Czerwony);
				if (ev.mouse.button & 1)
				{
					cout << "Left mouse has been clicked on Load game" << endl;
					al_destroy_display(display);
					generatorPoziomu();
					test = Enemies();
					return 0;													//---------->Teraz dobrze wychodzi, dzieki tej malutkiej prosciutkiej linijce<----------
					//display = al_create_display(800, 600);
				}
			}
			else if ((x >= 300 && x <= 500) && (y >= 200 && y <= 230))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 200, 500, 230, Czerwony);
				if (ev.mouse.button & 1)
				{
					cout << "Left mouse has been clicked on options" << endl;
					al_destroy_display(display);
					test = Edytor();
					return 0;													//---------->Teraz dobrze wychodzi, dzieki tej malutkiej prosciutkiej linijce<----------
					//display = al_create_display(800, 600);
				}
			}
			else if ((x >= 300 && x <= 500) && (y >= 250 && y <= 280))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 250, 500, 280, Czerwony);
				if (ev.mouse.button & 1)
				{
					cout << "Left mouse has been clicked on exit" << endl;
					al_destroy_display(display);
					return 0;
				}
			}
			else
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));//czarny
			}

			//cout << x << "\t";
			//cout << y << "\t";
			//cout << test;
			//cout << endl;
		}
		
	}

	//al_rest(5.0);

	return 0;
}
