#include "biblioteki.h"
#include <time.h>
#include <iostream>
#include <fstream>


using namespace std;

void generatorPoziomu()
{
	srand(time(NULL));

	ofstream Poziom ("Poziom.txt", ofstream::out);
	int tabGP[200][200] = {};
	int tabPrzejsciowy[20][15] = {};
	int tabMiniMap[10][13] = {};

	string start = "Generowanie/SektorStartowy";
	string arena = "Generowanie/Arena";
	string boss = "Generowanie/Boss";
	string wyjscie = "Generowanie/Wyjscie";

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
		//cout << "wczytano mape uzytkownika" << endl;
	}
	else
	{
		cout << "Nie mo¿na by³o wczytaæ mapy: ";
		//cout << start << endl;
	}

	wczytaj.close();

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
	mapa œwiata domyœlnie ma rozmiar tablicy 200x200. Sektor startowy umieœæmy gdzieœ w œrodku. Powiedzmy 100x100. (10x7 na minimapie)
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

}