#include "figury.h"
#include "pomocnicze.h"
#include <iostream>

void Figura::Ukryj() { std::cout << "\u001b[0m"; Narysuj(-1); }
void Figura::Wyszarz() { Narysuj(1); }
int Figura::GetNumer() { return _numer; }
void Figura::SetNumer(int nowyNr) {
	_numer = nowyNr;
	_kolorWierzch = 31 + nowyNr;
	_kolorLinii = 91 + nowyNr;
}


		// Wielok�t

int Wielokat::GetWierzch() { return _ileWierzch; };
/// <summary>
/// Zwraca Punkt z wielok�ta o wskazanym indeksie
/// </summary>
/// <param name="index">Indeks punktu w wielok�cie</param>
/// <returns>Wsp�edne punktu, lub (-1,-1) je�eli index poza zakresem</returns>
Punkt Wielokat::GetPunkt(int index) {
	if (index >= 0 && index < _ileWierzch) // sprawdza czy ��dany punkt istnieje
	{
		return Punkt(-1, -1);
	}
	return _punkty[index];

}
/// <summary>
///	Ustawia punkt w nowym miejscu sprawdzaj�� poprawno�� wsp��dnych 
/// </summary>
/// <param name="index">Indeks punktu do przestawienia</param>
/// <param name="x">Nowy X</param>
/// <param name="y">Nowy Y</param>
/// <returns>-1 je�eli b��d, 0 jak sukcess</returns>
int Wielokat::SetPunkt(int index, int x, int y) {
	if (CzyWZakresieOkna(x, y))
	{
		Ukryj();
		_punkty[index].Ustaw(x, y);
		Narysuj();
		return 0;
	}
	return -1;
}
/// <summary>
/// Przesuwa Wielok�t o podane warto�ci
/// </summary>
/// <param name="dx"> Przesuni�cie X na osi </param>
/// <param name="dy"> Przesuni�cie Y na osi </param>
/// <returns>0 je�eli uda�o si� przesun��, -1 je�eli nie mo�na przesun��</returns>
int Wielokat::PrzesunCaly(int dx, int dy) {

	for (int i = 0; i < _ileWierzch; i++)
	{
		int finalX = _punkty[i].x() + dx;
		int finalY = _punkty[i].y() + dy;
		if (!CzyWZakresieOkna(finalX, finalY)) return -1; // je�eli wsp�rzedne poza zakresem, zwr�� -1
	}
	for (int i = 0; i < _ileWierzch; i++)
	{
		Ukryj();
		_punkty[i].Przesun(dx, dy); // przesuwa punkty
		Narysuj();
	}
	return 0;
}
/// <summary>
/// Rysyje Wielok�t nie sprawdzaj�c czy jest to mo�liwe
/// </summary>
/// <param name="trybRysowania">0 - normalny, 1 - szary, -1 - ukryj</param>
void Wielokat::Narysuj(int trybRysowania) {
	_czyRysowano = true;
	int KW = _kolorWierzch, KL = _kolorLinii; // kopia warto�ci kolor�w
	char ZW = _znakWierzch, ZL = _znakLinii;
	if (trybRysowania == 1)
	{
		KW = szary, KL = szary; // je�eli wielok�t ma by� przeciemniony, zamie� kolory na szary
	}
	if (trybRysowania == -1)
	{
		ZW = ' ';
		ZL = ' ';
		KW = 0;
		KL = 0;
	}

	for (int i = 0; i < (_ileWierzch - 1); i++)
	{
		NarysujLinie(_punkty[i], _punkty[i + 1], KW, KL, ZW, ZL);
	}
	NarysujLinie(_punkty[_ileWierzch - 1], _punkty[0], KW, KL, ZW, ZL);
}

		// Trojk�t

Trojkat::Trojkat() {
	_ileWierzch = 3;
	_nazwa = "Trojkat";
}
Trojkat::Trojkat(int numer) : Trojkat()
{
	SetNumer(numer);
}
Trojkat::Trojkat(Punkt A, Punkt B, Punkt C, int numer) : Trojkat(numer) {
	_punkty.push_back(A);
	_punkty.push_back(B);
	_punkty.push_back(C);
};

void Trojkat::WyroznijPunkt(Punkt pkt) {
	UstawZnak(pkt, 37, '#');
};

/// <summary>
/// Losuje trojkat, nie wy�wietla go, ukrywa poprzedni je�eli istnia�
/// </summary>
void Trojkat::Losuj() {
	if (_czyRysowano)
	{
		Ukryj();
	}
	if (_punkty.size() == 3)
	{
		for (int i = 0; i < 3; i++)
		{
			_punkty[i] = LosPunkt(KonsolaX() - 5, KonsolaY() - 5, 0, 1);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			_punkty.push_back(LosPunkt(KonsolaX() - 5, KonsolaY() - 5, 0, 1));
		}
	}

}