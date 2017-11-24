#include "jakas.h"

using namespace std;

int main()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();

	int x, y;

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	ALLEGRO_FONT* font = al_load_font("C:\\Windows\\Fonts\\bauhs93.ttf", 22, 0);
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	al_clear_to_color(al_map_rgb(0, 0, 0));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());


	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		al_draw_rectangle(300, 50, 500, 300, al_map_rgb(255, 0, 0), 1);

		al_draw_text(font, al_map_rgb(0, 255, 0), 400, 100, ALLEGRO_ALIGN_CENTER, "Nowa Gra");
		al_draw_text(font, al_map_rgb(0, 255, 0), 400, 150, ALLEGRO_ALIGN_CENTER, "Wczytaj Gre");
		al_draw_text(font, al_map_rgb(0, 255, 0), 400, 200, ALLEGRO_ALIGN_CENTER, "Opcje");
		al_draw_text(font, al_map_rgb(0, 255, 0), 400, 250, ALLEGRO_ALIGN_CENTER, "Wyjscie");

		al_flip_display();

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			x = ev.mouse.x;
			y = ev.mouse.y;

			if ((x >= 300 && x <= 500) && (y >= 100 && y <= 130))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 100, 500, 130, al_map_rgb(255, 0, 0));

			}
			else if ((x >= 300 && x <= 500) && (y >= 150 && y <= 180))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 150, 500, 180, al_map_rgb(255, 0, 0));
			}
			else if ((x >= 300 && x <= 500) && (y >= 200 && y <= 230))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 200, 500, 230, al_map_rgb(255, 0, 0));
			}
			else if ((x >= 300 && x <= 500) && (y >= 250 && y <= 280))
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(300, 250, 500, 280, al_map_rgb(255, 0, 0));
			}
			else
			{
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}

			cout << x<<"\t";
			cout << y;
			cout << endl;
		}

	}

	al_rest(5.0);

	return 0;
}