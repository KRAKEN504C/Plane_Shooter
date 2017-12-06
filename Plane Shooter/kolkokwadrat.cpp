#include "biblioteki.h"
#include <iostream>
#include "Random_Font.hpp"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 16;

int main();

enum MYKEYS {
	 KEY_SPACE
};


//---------->NIGDY NIE INICJALIZOWAC DWA RAZY DISPLAYA!!!<----------




int kolkokwadrat()
{
	al_init();
	al_init_ttf_addon();
	al_init_font_addon();
	al_init_primitives_addon();
	al_install_keyboard();

	al_install_mouse();
	al_init_image_addon();

	ALLEGRO_DISPLAY* display1 = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_COLOR DarkBlue = al_map_rgb(0, 0, 100);
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR LovelyPink = al_map_rgb(255, 20, 147);

	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT* font = Random_Font();

	bool key[1] = { false };

	ALLEGRO_EVENT_QUEUE *event_queueK = NULL;
	ALLEGRO_TIMER *timerK = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	bool doexit = false;

	timerK = al_create_timer(1.0 / FPS);

	event_queueK = al_create_event_queue();
	if (!event_queueK) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display1);
		al_destroy_timer(timerK);
		return -1;
	}

	al_register_event_source(event_queueK, al_get_mouse_event_source());
	al_register_event_source(event_queueK, al_get_display_event_source(display1));
	al_register_event_source(event_queueK, al_get_timer_event_source(timerK));
	al_register_event_source(event_queueK, al_get_keyboard_event_source());

	float x1 = 300, x2 = 300+BOUNCER_SIZE, y1 = 220, y2 = 220+BOUNCER_SIZE;
	float velx = 0.02, vely = 0.02;
	short int zmianaKoloru = 0;
	int wyjscie = 0;


	while (!doexit)
	{
		ALLEGRO_EVENT evK;
		al_get_next_event(event_queueK, &evK);
		//al_wait_for_event(event_queuek, &evk);

		al_clear_to_color(DarkBlue);
		al_draw_text(font, al_map_rgb(0, 255, 0), 400, 100, ALLEGRO_ALIGN_CENTER, "Nacisnij spacje, zeby zakonczyc.");

		if (evK.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			doexit = true;
			al_destroy_display(display1);
			al_destroy_bitmap(bouncer);
			al_destroy_timer(timerK);
			wyjscie = main();
			printf("w teorii zakonczono myszkiem. ");
			return 0;
		}

		if (zmianaKoloru == 0)
		{
			al_draw_filled_rectangle(x1, y1, x2, y2, LovelyPink);
		}
		else
		{
			al_draw_filled_rectangle(x1, y1, x2, y2, White);
		}
		al_flip_display();


		if ((x2 > SCREEN_W || x1 < 0))
		{
			velx = -velx;
			zmianaKoloru = 1;
			printf("%i", zmianaKoloru);
		}
		if (y2 > SCREEN_H || y1 < 0)
		{
			vely = -vely;
			zmianaKoloru = 0;
			printf("%i", zmianaKoloru);
		}


		if (evK.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ALLEGRO_KEY_SPACE || ALLEGRO_KEY_ESCAPE)
			{
				doexit = true;
				al_destroy_display(display1);
				wyjscie = main();
				al_destroy_bitmap(bouncer);
				al_destroy_timer(timerK);
				printf("w teorii zakonczono klawitura. ");
				return 0;

			}
		}

		x1 += velx;
		x2 += velx;
		y1 += vely;
		y2 += vely;
		//std::cout << "x1: " << x1 << std::endl;
		//std::cout << "y1: " << y1 << std::endl;
		//std::cout << "x2: " << x2 << std::endl;
		//std::cout << "y2: " << y2 << std::endl;



	}

	printf("w teorii zakonczono petle. ");
	al_destroy_display(display1);
	return 0;
}
