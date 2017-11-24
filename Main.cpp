#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

int main()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	//ALLEGRO_FONT* font = al_create_builtin_font();
	ALLEGRO_FONT* font = al_load_font("C:\\Windows\\Fonts\\bauhs93.ttf", 22, 0);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_rectangle(300, 50, 500, 400, al_map_rgb(255,0,0),1 );

	al_draw_filled_rectangle(300, 100, 500, 130, al_map_rgb(255, 0, 0));

	al_draw_text(font, al_map_rgb(0, 255, 0), 400, 100, ALLEGRO_ALIGN_CENTER, "Nowa Gra");
	al_draw_text(font, al_map_rgb(0, 255, 0), 400, 150, ALLEGRO_ALIGN_CENTER, "Wczytaj Gre");
	al_draw_text(font, al_map_rgb(0, 255, 0), 400, 200, ALLEGRO_ALIGN_CENTER, "Ranking");
	al_draw_text(font, al_map_rgb(0, 255, 0), 400, 300, ALLEGRO_ALIGN_CENTER, "Wyjscie");
	
	al_flip_display();

	al_rest(5.0);



	return 0;
}
