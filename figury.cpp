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


		// Wielok¹t

int Wielokat::GetWierzch() { return _ileWierzch; };
/// <summary>
/// Zwraca Punkt z wielok¹ta o wskazanym indeksie
/// </summary>
/// <param name="index">Indeks punktu w wielok¹cie</param>
/// <returns>Wspó³¿edne punktu, lub (-1,-1) je¿eli index poza zakresem</returns>
Punkt Wielokat::GetPunkt(int index) {
	if (index >= 0 && index < _ileWierzch) // sprawdza czy ¿¹dany punkt istnieje
	{
		return Punkt(-1, -1);
	}
	return _punkty[index];

}
/// <summary>
///	Ustawia punkt w nowym miejscu sprawdzaj¹æ poprawnoœæ wspó³¿êdnych 
/// </summary>
/// <param name="index">Indeks punktu do przestawienia</param>
/// <param name="x">Nowy X</param>
/// <param name="y">Nowy Y</param>
/// <returns>-1 je¿eli b³¹d, 0 jak sukcess</returns>
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
/// Przesuwa Wielok¹t o podane wartoœci
/// </summary>
/// <param name="dx"> Przesuniêcie X na osi </param>
/// <param name="dy"> Przesuniêcie Y na osi </param>
/// <returns>0 je¿eli uda³o siê przesun¹æ, -1 je¿eli nie mo¿na przesun¹æ</returns>
int Wielokat::PrzesunCaly(int dx, int dy) {

	for (int i = 0; i < _ileWierzch; i++)
	{
		int finalX = _punkty[i].x() + dx;
		int finalY = _punkty[i].y() + dy;
		if (!CzyWZakresieOkna(finalX, finalY)) return -1; // je¿eli wspó³rzedne poza zakresem, zwróæ -1
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
/// Rysyje Wielok¹t nie sprawdzaj¹c czy jest to mo¿liwe
/// </summary>
/// <param name="trybRysowania">0 - normalny, 1 - szary, -1 - ukryj</param>
void Wielokat::Narysuj(int trybRysowania) {
	_czyRysowano = true;
	int KW = _kolorWierzch, KL = _kolorLinii; // kopia wartoœci kolorów
	char ZW = _znakWierzch, ZL = _znakLinii;
	if (trybRysowania == 1)
	{
		KW = szary, KL = szary; // je¿eli wielok¹t ma byæ przeciemniony, zamieñ kolory na szary
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

		// Trojk¹t

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
/// Losuje trojkat, nie wyœwietla go, ukrywa poprzedni je¿eli istnia³
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

		// prostok¹t

Prostokat::Prostokat() {
	_nazwa = "Prostokat";
	_ileWierzch = 4;
}
Prostokat::Prostokat(int numer) : Prostokat() {
	SetNumer(numer);
}
Prostokat::Prostokat(Punkt gpPunkt, int dx, int dy, int numer) : Prostokat(numer) {
	_punkty.push_back(gpPunkt);
	_punkty.push_back(Punkt(gpPunkt.x() + dx, gpPunkt.y()));
	_punkty.push_back(Punkt(gpPunkt.x() + dx, gpPunkt.y() + dy));
	_punkty.push_back(Punkt(gpPunkt.x(), gpPunkt.y() + dy));
}

/// <summary>
/// Losuje Prostok¹t, ukrywa i usuje obecny je¿eli ju¿ istnieje, nie rusyje nowego
/// </summary>
void Prostokat::Losuj() {
	if (_czyRysowano) // ukryj prostok¹t je¿eli istnieje
	{
		Ukryj();
	}

	bool gotowe = false;
	Punkt pktStart;
	int dx, dy;
	do
	{
		pktStart = LosPunkt(KonsolaX() - 30, KonsolaY() - 20, 0, 1);
		int maxDx = KonsolaX() - pktStart.x();
		int maxDy = KonsolaY() - pktStart.y();
		dx = pktStart.x() + 2 + rand() % (maxDx - 2);
		dy = pktStart.y() + 2 + rand() % (maxDy - 2);

		gotowe = CzyWZakresieOkna(pktStart.x() + dx, pktStart.y() + dy);
	} while (!gotowe);

	if (_punkty.size() == 4)
	{
		_punkty[0] = pktStart;
		_punkty[1] = Punkt(pktStart.x() + dx, pktStart.y());
		_punkty[2] = Punkt(pktStart.x() + dx, pktStart.y() + dy);
		_punkty[3] = Punkt(pktStart.x(), pktStart.y() + dy);
	}
	else
	{
		_punkty.push_back(pktStart);
		_punkty.push_back(Punkt(pktStart.x() + dx, pktStart.y()));
		_punkty.push_back(Punkt(pktStart.x() + dx, pktStart.y() + dy));
		_punkty.push_back(Punkt(pktStart.x(), pktStart.y() + dy));
	}


}

Okrag::Okrag()
{
	_nazwa = "Okrag";
}
Okrag::Okrag(int numer) : Okrag() {
	SetNumer(numer);
}
/// <summary>
/// Tworzy okr¹g
/// </summary>
/// <param name="srodek">Pozycja œrodka</param>
/// <param name="promien">Promieñ</param>
/// <param name="numer">Unikalny numer figury</param>
Okrag::Okrag(Punkt srodek, int promien, int numer) : Okrag(numer) {
	_srodek = srodek;
	_promien = promien;
};

/// <summary>
/// Rysyje Okr¹g nie sprawdzaj¹c czy jest to mo¿liwe
/// </summary>
/// <param name="trybRysowania">0 - normalny, 1 - szary, -1 - ukryj</param>
void Okrag::Narysuj(int trybRysowania) {
	_czyRysowano = true;
	int x = _promien;
	int y = 0, err = 0;

	int KW = _kolorWierzch, KL = _kolorLinii; // kopia wartoœci kolorów
	char ZW = _znakWierzch, ZL = _znakLinii;
	if (trybRysowania == 1)
	{
		KW = szary, KL = szary; // je¿eli okrag ma byæ przeciemniony, zamieñ kolory na szary
	}
	if (trybRysowania == -1)
	{
		ZW = ' ';
		ZL = ' ';
	}

	while (x >= y)
	{
		UstawZnak(_srodek.x() + x, _srodek.y() + y, KL, ZL);
		UstawZnak(_srodek.x() + y, _srodek.y() + x, KL, ZL);
		UstawZnak(_srodek.x() - x, _srodek.y() + y, KL, ZL);
		UstawZnak(_srodek.x() - y, _srodek.y() + x, KL, ZL);
		UstawZnak(_srodek.x() - x, _srodek.y() - y, KL, ZL);
		UstawZnak(_srodek.x() - y, _srodek.y() - x, KL, ZL);
		UstawZnak(_srodek.x() + x, _srodek.y() - y, KL, ZL);
		UstawZnak(_srodek.x() + y, _srodek.y() - x, KL, ZL);

		if (err <= 0)
		{
			y++;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
	UstawZnak(_srodek, KW, ZW);
}
/// <summary>
/// Sprawdza czy podany okr¹g nie wychodzi z zakresu
/// </summary>
bool Okrag::CzySieMiesci(Punkt sr, int r) {

	if (CzyWZakresieOkna(sr.x() + r, sr.y() - r) && CzyWZakresieOkna(sr.x() - r, sr.y() + r))
	{
		return true;
	}
	return false;
}
/// <summary>
/// Przesuwa Okr¹g o podane wartoœci
/// </summary>
/// <param name="dx"> Przesuniêcie œrodka X na osi </param>
/// <param name="dy"> Przesuniêcie œrodka Y na osi </param>
/// <returns>0 je¿eli uda³o siê przesun¹æ, -1 je¿eli nie mo¿na przesun¹æ</returns>
int Okrag::PrzesunCaly(int dx, int dy) {
	int finalX = _srodek.x() + dx;
	int finalY = _srodek.y() + dy;
	if (CzySieMiesci(Punkt(finalX, finalY), _promien))
	{
		Ukryj();
		_srodek.Ustaw(finalX, finalY);
		Narysuj();
		return 0;
	}
	return -1;
}
/// <summary>
/// Losuje okr¹g
/// </summary>
void Okrag::Losuj() {
	if (_czyRysowano) // jezeli okrag istnieje
	{
		Ukryj();
	}

	do // potwarzaj dopóki wylosowany okr¹g nie bêdzie w poprawnym zakresie
	{
		_srodek = LosPunkt(KonsolaX() - 20, KonsolaY() - 10, 0, 1);
		_promien = 2 + (rand() % ((KonsolaY() / 2) - 2 + 1));
	} while (!CzySieMiesci(_srodek, _promien));

}