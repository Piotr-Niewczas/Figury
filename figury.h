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