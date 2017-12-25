#include "biblioteki.h"
#include "Player.hpp"

using namespace Players;

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


//Player numer1;
//
//numer1.directory = "Player/Player_Placeholder.png";
//
//Player numer2;
//
//numer2.directory = "Player/Player_Placeholder.png";