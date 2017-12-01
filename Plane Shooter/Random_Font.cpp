#include "jakas.h"

ALLEGRO_FONT* Random_Font()
{
    ALLEGRO_FONT* font1 = al_load_font("fonts/font-1.ttf", 22, 0);
	ALLEGRO_FONT* font2 = al_load_font("fonts/font-2.ttf", 22, 0);

    bool temp = rand()%2;

    if(temp==0)
        return font1;

    if(temp==1)
        return font2;
}
