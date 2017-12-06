#include "biblioteki.h"

ALLEGRO_FONT* Random_Font()
{
    ALLEGRO_FONT* font1 = al_load_font("fonts/font-1.ttf", 22, 0);
	ALLEGRO_FONT* font2 = al_load_font("fonts/font-2.ttf", 22, 0);

    switch( rand()%2 )
    {
    case 0:
        {
            return font1;
        }
    case 1:
        {
            return font2;
        }
    default:
        {
            return nullptr;
        }
    }
}
