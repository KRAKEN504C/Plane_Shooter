#include "jakas.h"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

enum MYKEYS {
	 KEY_SPACE
};


int kolkokwadrat()
{
	al_init();
	al_init_ttf_addon();
	al_init_font_addon();
	al_init_primitives_addon();
	al_install_keyboard();

	ALLEGRO_DISPLAY* display1 = al_create_display(640, 480);
	ALLEGRO_COLOR DarkBlue = al_map_rgb(0, 0, 100);
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR LovelyPink = al_map_rgb(255, 20, 147);

	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT* font = al_load_ttf_font("C:\\Windows\\Fonts\\bauhs93.ttf", 22, 0);

	bool key[1] = { false };

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	bool redraw = true;
	bool doexit = false;

	timer = al_create_timer(1.0 / FPS);

	display1 = al_create_display(SCREEN_W, SCREEN_H);


	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display1);
		al_destroy_timer(timer);
		return -1;
	}


	al_register_event_source(event_queue, al_get_keyboard_event_source());

	float x1 = 300, x2 = 340, y1 = 220, y2 = 260;
	float velx = 0.02, vely = 0.02;
	short int zmianaKoloru = 0;

	bool loop = true;

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_get_next_event(event_queue, &ev);

		al_clear_to_color(DarkBlue);
		al_draw_text(font, al_map_rgb(0, 255, 0), 400, 100, ALLEGRO_ALIGN_CENTER, "Nacisnij spacje, zeby zakonczyc.");

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return 0;
			al_destroy_display(display1);
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


		if ((x2 > 640 || x1 < 0))
		{
			velx = -velx;
			zmianaKoloru = 1;
			printf("%i", zmianaKoloru);
		}
		if (y2 > 480 || y1 < 0)
		{
			vely = -vely;
			zmianaKoloru = 0;
			printf("%i", zmianaKoloru);
		}


		x1 += velx;
		x2 += velx;
		y1 += vely;
		y2 += vely;

		

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ALLEGRO_KEY_SPACE)
			{
				al_destroy_display(display1);
				al_destroy_bitmap(bouncer);
				al_destroy_timer(timer);
				return 0;
				
			}
		}
	}

}