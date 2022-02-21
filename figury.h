#pragma once
#include <string>
#include <vector>
#include "pomocnicze.h"

class Figura {
private:
	int _numer = 0;
public:
	virtual void Narysuj(int trybRysowania = 0) = 0;
	void Ukryj();
	void Wyszarz();
	virtual int PrzesunCaly(int dx, int dy) = 0;
	virtual void Losuj() = 0;
	char _znakLinii = '*', _znakWierzch = '#';		// Znakwierzch / œrodka ko³a
	int _kolorLinii = 0, _kolorWierzch = 0;			// domyœlny bia³y
	std::string _nazwa;
	int GetNumer();
	void SetNumer(int nowyNr);
	bool _czyRysowano = false;
};

class Wielokat : public Figura {
protected:
	std::vector<Punkt> _punkty;
	int _ileWierzch = 0;
public:
	Punkt GetPunkt(int index);
	int SetPunkt(int index, int x, int y);
	int GetWierzch();
	int PrzesunCaly(int dx, int dy) override;
	void Narysuj(int trybRysowania = 0) override;
};
class Trojkat : public Wielokat
{
public:
	Trojkat();
	Trojkat(int numer);
	Trojkat(Punkt A, Punkt B, Punkt C, int numer);
	Trojkat(Punkt Punkty[3], int numer) : Trojkat(Punkty[0], Punkty[1], Punkty[2], numer) {};

	void WyroznijPunkt(Punkt pkt);
	void Losuj() override;
};

		// prostok¹t

class Prostokat : public Wielokat {
public:
	Prostokat();
	Prostokat(int numer);
	Prostokat(Punkt gpPunkt, int dx, int dy, int numer);
	void Losuj() override;
};

		// okr¹g

class Okrag : public Figura {
protected:
	int _promien;
	Punkt _srodek;
public:
	Okrag();
	Okrag(int numer);
	Okrag(Punkt srodek, int promien, int numer);
	void Narysuj(int trybRysowania = 0) override;
	bool CzySieMiesci(Punkt pkt, int r);
	int PrzesunCaly(int dx, int dy) override;
	void Losuj() override;
};