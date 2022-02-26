#include "figury.h"
#include "pomocnicze.h"
#include <iostream>

void Figura::Ukryj() { std::cout << "\u001b[0m"; Narysuj(-1); }
int Figura::Numer() { return numer; }
void Figura::SetNumer(int nowyNr) {
	numer = nowyNr;
	SetKolorWierzch(31 + nowyNr);
	SetKolorLinii(91 + nowyNr);
}
char Figura::ZnakLinii() {
	return znakLinii;
}
char Figura::ZnakWierzch() {
	return znakWierzch;
}
int Figura::KolorLinii() {
	return kolorLinii;
}
int Figura::KolorWierzch() {
	return kolorWierzch;
}
void Figura::SetKolorLinii(int kolor) {
	kolorLinii = kolor;
}
void Figura::SetKolorWierzch(int kolor) {
	kolorWierzch = kolor;
}
bool Figura::CzyRysowano() {
	return czyRysowano;
}
void Figura::SetCzyRysowano(bool czyRysowano) {
	this->czyRysowano = czyRysowano;
}
std::string Figura::Nazwa(){ return nazwa; };
void Figura::SetNazwa(std::string nazwa) {
	this->nazwa = nazwa;
}
		// Wielok�t

int Wielokat::LiczbaWierzch() { return ileWierzch; };

/// <summary>
///	Ustawia punkt w nowym miejscu sprawdzaj�� poprawno�� wsp��dnych 
/// </summary>
/// <param name="index">Indeks punktu do przestawienia</param>
/// <param name="x">Nowy X</param>
/// <param name="y">Nowy Y</param>
/// <returns>-1 je�eli b��d, 0 jak sukcess</returns>

/// <summary>
/// Przesuwa Wielok�t o podane warto�ci
/// </summary>
/// <param name="dx"> Przesuni�cie X na osi </param>
/// <param name="dy"> Przesuni�cie Y na osi </param>
/// <returns>0 je�eli uda�o si� przesun��, -1 je�eli nie mo�na przesun��</returns>
int Wielokat::PrzesunCaly(int dx, int dy) {

	for (int i = 0; i < ileWierzch; i++)
	{
		int finalX = punkty[i].X() + dx;
		int finalY = punkty[i].Y() + dy;
		if (!CzyWZakresieOkna(finalX, finalY)) return -1; // je�eli wsp�rzedne poza zakresem, zwr�� -1
	}
	for (int i = 0; i < ileWierzch; i++)
	{
		Ukryj();
		punkty[i].Przesun(dx, dy); // przesuwa punkty
		Narysuj();
	}
	return 0;
}
/// <summary>
/// Rysyje Wielok�t nie sprawdzaj�c czy jest to mo�liwe
/// </summary>
/// <param name="trybRysowania">0 - normalny, 1 - szary, -1 - ukryj</param>
void Wielokat::Narysuj(int trybRysowania) {
	SetCzyRysowano(true);
	int KW = KolorWierzch(), KL = KolorLinii(); // kopia warto�ci kolor�w
	char ZW = ZnakWierzch(), ZL = ZnakLinii();
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

	for (int i = 0; i < (ileWierzch - 1); i++)
	{
		NarysujLinie(punkty[i], punkty[i + 1], KW, KL, ZW, ZL);
	}
	NarysujLinie(punkty[ileWierzch - 1], punkty[0], KW, KL, ZW, ZL);
}

		// Trojk�t

Trojkat::Trojkat() {
	ileWierzch = 3;
	SetNazwa("Trojkat");
}
Trojkat::Trojkat(int numer) : Trojkat()
{
	SetNumer(numer);
}
Trojkat::Trojkat(Punkt A, Punkt B, Punkt C, int numer) : Trojkat(numer) {
	punkty.push_back(A);
	punkty.push_back(B);
	punkty.push_back(C);
};


/// <summary>
/// Losuje trojkat, nie wy�wietla go, ukrywa poprzedni je�eli istnia�
/// </summary>
void Trojkat::Losuj() {
	if (CzyRysowano())
	{
		Ukryj();
	}
	if (punkty.size() == 3)
	{
		for (int i = 0; i < 3; i++)
		{
			punkty[i] = LosPunkt(KonsolaX() - 5, KonsolaY() - 5, 0, 1);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			punkty.push_back(LosPunkt(KonsolaX() - 5, KonsolaY() - 5, 0, 1));
		}
	}

}

		// prostok�t

Prostokat::Prostokat() {
	SetNazwa("Prostokat");
	ileWierzch = 4;
}
Prostokat::Prostokat(int numer) : Prostokat() {
	SetNumer(numer);
}
Prostokat::Prostokat(Punkt gpPunkt, int dx, int dy, int numer) : Prostokat(numer) {
	punkty.push_back(gpPunkt);
	punkty.push_back(Punkt(gpPunkt.X() + dx, gpPunkt.Y()));
	punkty.push_back(Punkt(gpPunkt.X() + dx, gpPunkt.Y() + dy));
	punkty.push_back(Punkt(gpPunkt.X(), gpPunkt.Y() + dy));
}

/// <summary>
/// Losuje Prostok�t, ukrywa i usuje obecny je�eli ju� istnieje, nie rusyje nowego
/// </summary>
void Prostokat::Losuj() {
	if (CzyRysowano()) // ukryj prostok�t je�eli istnieje
	{
		Ukryj();
	}

	bool gotowe = false;
	Punkt pktStart;
	int dx, dy;
	do
	{
		pktStart = LosPunkt(KonsolaX() - 30, KonsolaY() - 20, 0, 1);
		int maxDx = KonsolaX() - pktStart.X();
		int maxDy = KonsolaY() - pktStart.Y();
		dx = pktStart.X() + 2 + rand() % (maxDx - 2);
		dy = pktStart.Y() + 2 + rand() % (maxDy - 2);

		gotowe = CzyWZakresieOkna(pktStart.X() + dx, pktStart.Y() + dy);
	} while (!gotowe);

	if (punkty.size() == 4)
	{
		punkty[0] = pktStart;
		punkty[1] = Punkt(pktStart.X() + dx, pktStart.Y());
		punkty[2] = Punkt(pktStart.X() + dx, pktStart.Y() + dy);
		punkty[3] = Punkt(pktStart.X(), pktStart.Y() + dy);
	}
	else
	{
		punkty.push_back(pktStart);
		punkty.push_back(Punkt(pktStart.X() + dx, pktStart.Y()));
		punkty.push_back(Punkt(pktStart.X() + dx, pktStart.Y() + dy));
		punkty.push_back(Punkt(pktStart.X(), pktStart.Y() + dy));
	}


}

Okrag::Okrag()
{
	SetNazwa("Okrag");
}
Okrag::Okrag(int numer) : Okrag() {
	SetNumer(numer);
}
/// <summary>
/// Tworzy okr�g
/// </summary>
/// <param name="srodek">Pozycja �rodka</param>
/// <param name="promien">Promie�</param>
/// <param name="numer">Unikalny numer figury</param>
Okrag::Okrag(Punkt srodek, int promien, int numer) : Okrag(numer) {
	this->srodek = srodek;
	this->promien = promien;
};

/// <summary>
/// Rysyje Okr�g nie sprawdzaj�c czy jest to mo�liwe
/// </summary>
/// <param name="trybRysowania">0 - normalny, 1 - szary, -1 - ukryj</param>
void Okrag::Narysuj(int trybRysowania) {
	SetCzyRysowano(true);
	int x = promien;
	int y = 0, err = 0;

	int KW = KolorWierzch(), KL = KolorLinii(); // kopia warto�ci kolor�w
	char ZW = ZnakWierzch(), ZL = ZnakLinii();
	if (trybRysowania == 1)
	{
		KW = szary, KL = szary; // je�eli okrag ma by� przeciemniony, zamie� kolory na szary
	}
	if (trybRysowania == -1)
	{
		ZW = ' ';
		ZL = ' ';
	}

	while (x >= y)
	{
		UstawZnak(srodek.X() + x, srodek.Y() + y, KL, ZL);
		UstawZnak(srodek.X() + y, srodek.Y() + x, KL, ZL);
		UstawZnak(srodek.X() - x, srodek.Y() + y, KL, ZL);
		UstawZnak(srodek.X() - y, srodek.Y() + x, KL, ZL);
		UstawZnak(srodek.X() - x, srodek.Y() - y, KL, ZL);
		UstawZnak(srodek.X() - y, srodek.Y() - x, KL, ZL);
		UstawZnak(srodek.X() + x, srodek.Y() - y, KL, ZL);
		UstawZnak(srodek.X() + y, srodek.Y() - x, KL, ZL);

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
	UstawZnak(srodek, KW, ZW);
}
/// <summary>
/// Sprawdza czy podany okr�g nie wychodzi z zakresu
/// </summary>
bool Okrag::CzySieMiesci(Punkt sr, int r) {

	if (CzyWZakresieOkna(sr.X() + r, sr.Y() - r) && CzyWZakresieOkna(sr.X() - r, sr.Y() + r))
	{
		return true;
	}
	return false;
}
/// <summary>
/// Przesuwa Okr�g o podane warto�ci
/// </summary>
/// <param name="dx"> Przesuni�cie �rodka X na osi </param>
/// <param name="dy"> Przesuni�cie �rodka Y na osi </param>
/// <returns>0 je�eli uda�o si� przesun��, -1 je�eli nie mo�na przesun��</returns>
int Okrag::PrzesunCaly(int dx, int dy) {
	int finalX = srodek.X() + dx;
	int finalY = srodek.Y() + dy;
	if (CzySieMiesci(Punkt(finalX, finalY), promien))
	{
		Ukryj();
		srodek.Ustaw(finalX, finalY);
		Narysuj();
		return 0;
	}
	return -1;
}
/// <summary>
/// Losuje okr�g
/// </summary>
void Okrag::Losuj() {
	if (CzyRysowano()) // jezeli okrag istnieje
	{
		Ukryj();
	}

	do // potwarzaj dop�ki wylosowany okr�g nie b�dzie w poprawnym zakresie
	{
		srodek = LosPunkt(KonsolaX() - 20, KonsolaY() - 10, 0, 1);
		promien = 2 + (rand() % ((KonsolaY() / 2) - 2 + 1));
	} while (!CzySieMiesci(srodek, promien));

}