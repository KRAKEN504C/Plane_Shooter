#pragma once
#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "biblioteki.h"
#include "Random_Font.hpp"
#include <fstream>
#include <string.h>
#include <string>

class Player
{
public:
	std::string directory;

	bool PlayerLoadBitmap();
	bool istnieje = PlayerLoadBitmap();
	ALLEGRO_BITMAP * bitmapa()
	{
		const char * directory_char = directory.c_str();

		if (istnieje)
		{
			return al_load_bitmap(directory_char);
		}
		else
		{
			return al_load_bitmap("bitmapy/sciana_Placeholder.png");
		}
	}


private:
	ALLEGRO_BITMAP *Player_Bit;

};

bool Player::PlayerLoadBitmap()
{
	const char * sciezka_char = directory.c_str();

	if (!al_load_bitmap(sciezka_char))
	{
		fprintf(stderr, "failed to create bitmap!\n");
		return false;
	}
	else
		return true;

}

//ALLEGRO_BITMAP Player :: *bitmapa(std::string directory, bool istnieje)
//{
//	const char * directory_char = directory.c_str();
//
//	if (istnieje)
//	{
//		return al_load_bitmap(directory_char);
//	}
//	else
//	{
//		return al_load_bitmap("bitmapy/sciana_Placeholder.png");
//	}
//}


#endif