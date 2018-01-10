#include "biblioteki.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <Windows.h>


using namespace std;

void polozenieNowegoSektora(int miniMap_x, int miniMap_y, int tabMiniMap[10][13], int realMap_x, int realMap_y)
{
	int tymczasowa_miniMap_x = miniMap_x;
	int tymczasowa_miniMap_y = miniMap_y;
	int los;
	int counter = 0;
	bool found = 0;
	do {
		tymczasowa_miniMap_x = miniMap_x;
		tymczasowa_miniMap_y = miniMap_y;
		if (counter >= 10)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 13; j++)
				{
					if (!found)
					{
						if (miniMap_x != i && miniMap_y != j)
						{
							if (tabMiniMap[i][j] == 1)
							{
								tabMiniMap[miniMap_x][miniMap_y] = 2;
								miniMap_x = i;
								miniMap_y = j;
								found = 1;
							}
						}
					}
				}
			}
		}
		los = rand() % 4;
		switch (los)
		{
		case 0:
			tymczasowa_miniMap_x++;
			break;
		case 1:
			tymczasowa_miniMap_x--;
			break;
		case 2:
			tymczasowa_miniMap_y++;
			break;
		case 3:
			tymczasowa_miniMap_y--;
			break;
		}
		counter++;
	} while (tabMiniMap[miniMap_x][miniMap_y] != 0);

	realMap_x = miniMap_x * 20;
	realMap_y = miniMap_y * 15;

}


void wczytanieZPliku(string nazwaPliku,int tabPrzejsciowy[20][15])
{
	fstream wczytaj;

	wczytaj.open(nazwaPliku, ios::in | ios::out);

	if (wczytaj)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				wczytaj >> tabPrzejsciowy[i][j];
			}
		}
		//cout << "wczytano mape uzytkownika" << endl;
	}
	else
	{
		cout << "Nie mozna bylo wczytac mapy: ";
		//cout << start << endl;
	}

	wczytaj.close();
}


void RysowanieNaMapie(int tabGP[200][210], int tabPrzejsciowy[20][15], int realMap_x, int realMap_y)
{


	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			tabGP[realMap_x + i][realMap_y + j] = tabPrzejsciowy[i][j];
		}
	}
	//tabMiniMap[miniMap_x][miniMap_y] = 1;
}


void LosowanieStringa()
{

}

void generatorPoziomu()
{
	srand(time(NULL));

	ofstream Poziom ("Poziom.txt", ofstream::out);
	int tabGP[200][210] = {};
	int tabPrzejsciowy[20][15] = {};
	int tabMiniMap[10][13] = {};
	int tabMiniMapa[10][13];

	int miniMap_x = 5;
	int miniMap_y = 7;

	int realMap_x = miniMap_x * 20;
	int realMap_y = miniMap_y * 15;

	string start = "Generowanie/SektorStartowy";
	string originalarena = "Generowanie/Arena";
	string arena = "Generowanie/Arena";
	string sklep = "Generowanie/Sklep";
	string boss = "Generowanie/Boss";
	string wyjscie = "Generowanie/Wyjscie.txt";

	string testowe = "Generowanie/test_zapisu_sektorastartowego.txt";

	fstream wczytaj;

	start += ".txt";




	wczytaj.open(start, ios::in | ios::out);

	if (wczytaj)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				wczytaj >> tabPrzejsciowy[i][j];
			}
		}
	}
	else
	{
		cout << "Nie mozna bylo wczytac mapy: ";
	}

	wczytaj.close();



	fstream test;

	test.open(testowe, ios::in | ios::out);
	if (test)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				test << tabPrzejsciowy[i][j];
				test << " ";
			}
			test << endl;
		}
	}
	else
	{
		cout << "Nie mozna bylo otworzyc pliku wyjscowego: ";
	}

	test.close();
	//wygl¹da na to, ¿e wszystko dobrze siê zapisuje do tabPrzejsciowy.



	/*
	Jak ogarnac generowanie poziomu?
	3 rodzaje blokow podanych w tablicy 

	1-œciana
	2-droga
	3-drzwi

	poziom powinien sie sk³adaæ z po³¹czeñ miêdzy drzwiami we wszystkich mapach (³¹cznie mo¿e ich byæ maksymalnie oko³o 16)
	poziom (wed³ug specyfikacji) generuje siê tak:
	
	1.Losuje sektor startowy(oraz liczbe Y z przedzia³u od 3 do 8 oraz A z przedzia³u od 9 do 16). (inicjalizacja X i A)
	2.Losuje mape, i ³¹cze j¹ z poprzednio wybran¹ map¹.(3-drzwi w tym momencie zamieniaja sie w 2-droge miêdzy jedn¹ a drug¹ map¹.) X zwiêkszam o 1 (X startowo wynosi 0). Je¿eli x >= y powtórz.
	3.Wylosowanie sklepu i po³¹czenie go z jak¹œ map¹.
	4.To samo co w punkcie 2 tylko ¿e tym razem z pêtl¹ dla X >= A.
	5.Wylosowanie areny Bossa pasuj¹cego do aktualnego biomu.
	6.Wygenerowanie iluzorycznych œcian, przeciwników oraz gracza.

	Teraz tylko zamieniæ to w kod.

	To wszystko bêdzie proste jak tylko znajdê prosty sposób na po³¹czenie jednej mapy z drug¹.

	hmmm...
	mapa œwiata domyœlnie ma rozmiar tablicy 200x200. Sektor startowy umieœæmy gdzieœ w œrodku. Powiedzmy 100x100. (5x7 na minimapie)
	teraz niech bedzie losowanie od 0 do 3.
	w zale¿noœci od liczby jaka wypad³a nastepny sektor bêdzie ustawiany nad/pod/za/przed poprzednim sektorem.
	maksymalna iloœæ sektorów jaka mo¿na ustaliæ wynosi 10x13. stworzymy mini-mape o rozmiarze 10x13. 0 oznacza dostepne miejsce, a 1 zajete.

	sektory bêd¹ stawiane z przerwa od siebie 10 kratek (10 x 32 px = 10 dowolnych bloków tworz¹cych mape.)
	w tej 10 blokowej przerwie bêdzie teraz generowany korytarz.
	Jak wygenerowaæ korytarz?

	hmm...
	weŸmy pozycje drzwi do sektora A oraz drzwi do sektora B. je¿eli odleg³oœæ wzglêdem osi x jest wiêksza od odleg³oœci wzglêdem osi y to oznacza, ¿e ³¹czym sektory pionowo (jeden nad/pod drugim).
	w takim wypadku generujem poziomo droge miedzy punktem A i B w przerwie pomiêdzy tymi sektorami (gdzieœ w œrodku.) a potem ³¹czym oba sektory t¹ drog¹ za pomoc¹ pionowych œcie¿ek prowadz¹cych od jednych drzwi do drogi, i z drogi do drugich drzwi.
	podobnie w przypadku kiedy odleg³oœæ wzglêdem osi y jest wiêksza od odleg³oœci wzglêdem osi x, tylko ¿e droge generujem pionowo, i ³¹czymy j¹ poziomymi œcie¿kami.

	teraz zamieniæ to w kod.
	*/

	int X = 0;
	int Y = 3;
	int A = 9;

	Y = rand() % 5 + 3;
	A = rand() % 6 + 9;

	// sektor startowy minimap = 5x7

	//narysowanie sektoru startowego na g³ównej mapie.    Coœ tu nie dzia³a     EDIT: juz jest ok.
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			tabGP[realMap_x + i][realMap_y + j] = tabPrzejsciowy[i][j];
		}
	}

	tabMiniMap[miniMap_x][miniMap_y] = 1;

	//wyrzucenie wszystkiego do pliku, i sprawdzenie jak dzia³a.
	


	//wszystko na razie dzia³a!

	{
		miniMap_x++;
		realMap_x = miniMap_x * 20;
		realMap_y = miniMap_y * 15;
		arena += "_1.txt";

		wczytanieZPliku(arena, tabPrzejsciowy);
		RysowanieNaMapie(tabGP, tabPrzejsciowy, realMap_x, realMap_y);

		tabMiniMap[miniMap_x][miniMap_y] = 1;
	}

	{
		miniMap_y++;
		realMap_x = miniMap_x * 20;
		realMap_y = miniMap_y * 15;
		arena = originalarena;
		arena += "_2.txt";

		wczytanieZPliku(arena, tabPrzejsciowy);
		RysowanieNaMapie(tabGP, tabPrzejsciowy, realMap_x, realMap_y);

		tabMiniMap[miniMap_x][miniMap_y] = 1;
	}

	{
		miniMap_x--;
		realMap_x = miniMap_x * 20;
		realMap_y = miniMap_y * 15;
		arena = originalarena;
		arena += "_3.txt";

		wczytanieZPliku(arena, tabPrzejsciowy);
		RysowanieNaMapie(tabGP, tabPrzejsciowy, realMap_x, realMap_y);

		tabMiniMap[miniMap_x][miniMap_y] = 1;
	}

	{
		miniMap_y++;
		realMap_x = miniMap_x * 20;
		realMap_y = miniMap_y * 15;
		arena = originalarena;
		arena += "_1.txt";

		wczytanieZPliku(arena, tabPrzejsciowy);
		RysowanieNaMapie(tabGP, tabPrzejsciowy, realMap_x, realMap_y);

		tabMiniMap[miniMap_x][miniMap_y] = 1;
	}
















	fstream zapisz;

	zapisz.open(wyjscie, ios::in | ios::out);
	if (zapisz)
	{
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 210; j++)
			{
				zapisz << tabGP[i][j];
				zapisz << " ";
			}
			zapisz << endl;
		}
	}
	else
	{
		cout << "Nie mozna bylo otworzyc pliku wyjsciowego: ";
	}

	zapisz.close();












	fstream MiniMapa;
	MiniMapa.open("Generowanie/MiniMapa.txt", ios::in | ios::out);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			MiniMapa << tabMiniMap[i][j];
			MiniMapa << " ";
		}
		MiniMapa << endl;
	}











	system("pause");
}














/*
miniMap_x++;

realMap_x = miniMap_x * 20;
realMap_y = miniMap_y * 15;

arena += "_1.txt";


//wczytaj.open(arena, ios::in | ios::out);

//if (wczytaj)
//{
//	for (int i = 0; i < 20; i++)
//	{
//		for (int j = 0; j < 15; j++)
//		{
//			wczytaj >> tabPrzejsciowy[i][j];
//		}
//	}
//	//cout << "wczytano mape uzytkownika" << endl;
//}
//else
//{
//	cout << "Nie mozna bylo wczytac mapy: ";
//	//cout << start << endl;
//}

//wczytaj.close();

wczytanieZPliku(arena, tabPrzejsciowy);

RysowanieNaMapie(tabGP, tabPrzejsciowy, realMap_x, realMap_y);

/*for (int i = 0; i < 20; i++)
{
for (int j = 0; j < 15; j++)
{
tabGP[realMap_x + i][realMap_y + j] = tabPrzejsciowy[i][j];
}
}*/
