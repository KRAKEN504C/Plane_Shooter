#ifndef BIOM_HPP_INCLUDED
#define BIOM_HPP_INCLUDED

#include "biblioteki.h"

namespace Biomki

{

class Biomy
{
public:
	int testek;
	std::string test;

	ALLEGRO_BITMAP *Biom_bitmapa(std::string test)
	{
		ALLEGRO_BITMAP *Testowa = al_load_bitmap("bitmapy/sciana_Placeholder.png");
		return Testowa;
	}


};

}

//ALLEGRO_BITMAP Biomy::*Biom_bitmapa()
//{
//	ALLEGRO_BITMAP *Testowa = al_load_bitmap("bitmapy/sciana_Placeholder.png");
//	return *Testowa;
//}

#endif