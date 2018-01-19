#include "biblioteki.h"

ALLEGRO_FONT* Random_Font()
{
    switch( rand() % 3 )
    {
    case 0:
        {
            return al_load_font("fonts/ARIAL.TTF", 22, 0);
        }
    case 1:
        {
            return al_load_font("fonts/font-1.ttf", 22, 0);
        }
    case 2:
        {
            return al_load_font("fonts/font-2.ttf", 22, 0);
        }
    default:
        {
            return nullptr;
        }
    }
}
