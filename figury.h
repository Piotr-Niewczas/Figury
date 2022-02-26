#pragma once
#include <string>
#include <vector>
#include "pomocnicze.h"

class Figura {
private:
	int numer = 0;
	char znakLinii = '*', znakWierzch = '#';		// Znakwierzch / œrodka ko³a
	int kolorLinii = 0, kolorWierzch = 0;			// domyœlny bia³y
	bool czyRysowano = false;
	std::string nazwa;
public:
	virtual void Narysuj(int trybRysowania = 0) = 0;
	void Ukryj();
	virtual int PrzesunCaly(int dx, int dy) = 0;
	virtual void Losuj() = 0;
	char ZnakLinii();
	char ZnakWierzch();
	int KolorLinii();
	int KolorWierzch();
	void SetKolorLinii(int kolor);
	void SetKolorWierzch(int kolor);
	int Numer();
	void SetNumer(int nowyNr);
	bool CzyRysowano();
	void SetCzyRysowano(bool czyRysowano);
	std::string Nazwa();
	void SetNazwa(std::string nazwa);
};

class Wielokat : public Figura {
protected:
	std::vector<Punkt> punkty;
	int ileWierzch = 0;
public:
	int LiczbaWierzch();
	int PrzesunCaly(int dx, int dy) override;
	void Narysuj(int trybRysowania = 0) override;
};
class Trojkat : public Wielokat
{
public:
	Trojkat();
	Trojkat(int numer);
	Trojkat(Punkt A, Punkt B, Punkt C, int numer);

	void Losuj() override;
};

		// prostok¹t

class Prostokat : public Wielokat {
public:
	Prostokat();
	Prostokat(int numer);
	Prostokat(Punkt glPunkt, int dx, int dy, int numer);
	void Losuj() override;
};

		// okr¹g

class Okrag : public Figura {
private:
	int promien;
	Punkt srodek;
public:
	Okrag();
	Okrag(int numer);
	Okrag(Punkt srodek, int promien, int numer);
	void Narysuj(int trybRysowania = 0) override;
	bool CzySieMiesci(Punkt srodek, int r);
	int PrzesunCaly(int dx, int dy) override;
	void Losuj() override;
};