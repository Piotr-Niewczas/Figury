#include <iostream>
#include <stdio.h>
#include <time.h>		/* time */ 
#include <sstream>		/* string stream */
#include <vector>
#include "figury.h"


//dom rozmiar okna 120x30 znaków





class Trojkat : public Wielokat
{	
public:
	Trojkat() {
		_ileWierzch = 3;
		_nazwa = "Trojkat";
	}
	Trojkat(int numer) : Trojkat() {
		SetNumer(numer);
	}
	Trojkat(Punkt A, Punkt B, Punkt C, int numer) : Trojkat(numer) {
		_punkty.push_back(A);
		_punkty.push_back(B);
		_punkty.push_back(C);
	};
	Trojkat(Punkt Punkty[3],int numer) : Trojkat(Punkty[0], Punkty[1], Punkty[2], numer) {};
	
	void WyroznijPunkt(Punkt pkt) {
		UstawZnak(pkt, 37, '#');
	};
	void Losuj() override;
};
/// <summary>
/// Losuje trojkat, nie wyświetla go, ukrywa poprzedni jeżeli istniał
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
			_punkty[i] = LosPunkt(KonsolaX() - 5, KonsolaY() - 5, 0 ,1);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			_punkty.push_back(LosPunkt(KonsolaX() - 5, KonsolaY() - 5, 0 ,1));
		}
	}
	
}

class Prostokat : public Wielokat {
public:
	Prostokat() { 
		_nazwa = "Prostokat"; 
		_ileWierzch = 4; }
	Prostokat(int numer) : Prostokat() {
		SetNumer(numer);
	}
	Prostokat(Punkt gpPunkt, int dx, int dy, int numer) : Prostokat(numer) {
		_punkty.push_back(gpPunkt);
		_punkty.push_back(Punkt(gpPunkt.x() + dx, gpPunkt.y()));
		_punkty.push_back(Punkt(gpPunkt.x() + dx, gpPunkt.y() + dy));
		_punkty.push_back(Punkt(gpPunkt.x(), gpPunkt.y() + dy));
	}
	void Losuj() override;
};
/// <summary>
/// Losuje Prostokąt, ukrywa i usuje obecny jeżeli już istnieje, nie rusyje nowego
/// </summary>
void Prostokat::Losuj() {
	if (_czyRysowano) // ukryj prostokąt jeżeli istnieje
	{
		Ukryj();
	}

	bool gotowe = false;
	Punkt pktStart;
	int dx, dy;
	do
	{
		pktStart = LosPunkt(KonsolaX() - 30, KonsolaY() - 20, 0 ,1);
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

class Okrag : public Figura {
protected:
	int _promien;
	Punkt _srodek;
public:
	Okrag() {
		_nazwa = "Okrag";
	}
	Okrag(int numer) : Okrag() {
		SetNumer(numer);
	}
	/// <summary>
	/// Tworzy okrąg
	/// </summary>
	/// <param name="srodek">Pozycja środka</param>
	/// <param name="promien">Promień</param>
	/// <param name="numer">Unikalny numer figury</param>
	Okrag(Punkt srodek, int promien, int numer) : Okrag(numer) {
		_srodek = srodek;
		_promien = promien;
	};
	void Narysuj(int trybRysowania = 0) override;
	bool CzySieMiesci(Punkt pkt, int r);
	int PrzesunCaly(int dx, int dy) override;
	void Losuj() override;
};
/// <summary>
/// Rysyje Okrąg nie sprawdzając czy jest to możliwe
/// </summary>
/// <param name="trybRysowania">0 - normalny, 1 - szary, -1 - ukryj</param>
void Okrag::Narysuj(int trybRysowania) {
	_czyRysowano = true;
	int x = _promien;
	int y = 0, err = 0;

	int KW = _kolorWierzch, KL = _kolorLinii; // kopia wartości kolorów
	char ZW = _znakWierzch, ZL = _znakLinii;
	if (trybRysowania == 1)
	{
		KW = szary, KL = szary; // jeżeli okrag ma być przeciemniony, zamień kolory na szary
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
/// Sprawdza czy podany okrąg nie wychodzi z zakresu
/// </summary>
bool Okrag::CzySieMiesci(Punkt sr, int r) {

	if (CzyWZakresieOkna(sr.x() + r, sr.y() - r) && CzyWZakresieOkna(sr.x() - r, sr.y() + r))
	{
		return true;
	}
	return false;
}
/// <summary>
/// Przesuwa Okrąg o podane wartości
/// </summary>
/// <param name="dx"> Przesunięcie środka X na osi </param>
/// <param name="dy"> Przesunięcie środka Y na osi </param>
/// <returns>0 jeżeli udało się przesunąć, -1 jeżeli nie można przesunąć</returns>
int Okrag::PrzesunCaly(int dx, int dy) {
	int finalX = _srodek.x() + dx;
	int finalY = _srodek.y() + dy;
	if (CzySieMiesci(Punkt(finalX,finalY),_promien))
	{
		Ukryj();
		_srodek.Ustaw(finalX, finalY);
		Narysuj();
		return 0;
	}
	return -1;
}
/// <summary>
/// Losuje okrąg
/// </summary>
void Okrag::Losuj() {
	if (_czyRysowano) // jezeli okrag istnieje
	{
		Ukryj();
	}

	do // potwarzaj dopóki wylosowany okrąg nie będzie w poprawnym zakresie
	{
		_srodek = LosPunkt(KonsolaX() - 20, KonsolaY() - 10, 0 ,1);
		_promien = 2 + (rand() % ((KonsolaY() / 2) - 2 + 1));
	} while (!CzySieMiesci(_srodek, _promien));
	
}



void PrintError(std::string text) {
	UstawKursor(0, KonsolaY() - 1);
	std::cout << "\u001b[0;101m\a Error: " << text;
	getchar();
	printf("\033[A");
	printf("\33[2K\r");
	std::cout << "\u001b[0m";
}

void NarysyjGornyPasek(std::vector<Figura*> _figury, std::vector<std::string> _figuryNazwy, int _wybranaFigura) {
	UstawKursor(0, 0);
	std::cout << "\u001b[0;100m";
	printf("\33[2K\r");
	for (int i = 0; i < _figury.size(); i++)
	{
		if (_wybranaFigura == i)
		{
			std::cout << "\u001b[" << _figury[i]->GetNumer() + 31 << ";101m";
		}
		else
		{
			std::cout << "\u001b[" << _figury[i]->GetNumer() + 31 << ";47m";
		}
		//cout << "[" << i << "]: " << _figury[i]->_nazwa << " \t";
		std::cout << "[" << i << "]: " << _figuryNazwy[i] << "\u001b[0;100m" << "    ";
	}
}
void NarysujDolnyPasek(int _wybranaFigura) {
	UstawKursor(0, KonsolaY() - 1);
	std::cout << "\u001b[92;100m";
	ClearLine(); // zapewnia cała linię w szarym kolorze

	if (_wybranaFigura>-1)
	{
		std::cout << "[" << _wybranaFigura << "]: ";
	}
	else
	{
		std::cout << "> ";
	}
}

void LosujFigure(std::vector<std::string> _komendy, std::vector<Figura*>& _figury, int _wybranaFigura) {
	if (_komendy.size() == 2 && _komendy[1] == "*")
	{
		for (int i = 0; i < _figury.size(); i++)
		{
			_figury[i]->Losuj();
		}
		for (int i = 0; i < _figury.size(); i++)
		{
			_figury[i]->Narysuj();
		}

	}
	else if (_wybranaFigura > -1)
	{
		_figury[_wybranaFigura]->Losuj();
		for (int i = 0; i < _figury.size(); i++)
		{
			_figury[i]->Narysuj();
		}
	}
	else
	{
		PrintError("Nie wybrano figury!");
	}
}
void WybierzFigure(std::vector<std::string> _komendy, std::vector<Figura*> _figury, int& _wybranaFigura) {
	if (_komendy.size() == 2 && _komendy[1] != "*")
	{
		try
		{
			int temp = stoi(_komendy[1]);
			if (temp > -1 && temp < _figury.size())
			{
				_wybranaFigura = temp;
			}
			else
			{
				PrintError("Wybrana figura nie istnieje!");
			}
		}
		catch (const std::exception&)
		{
			PrintError("Zly argument!");
		}
	}
	else
	{
		PrintError("Zly argument!");
	}
}
void UtworzFigure(std::vector<std::string> _komendy, std::vector<Figura*>& _figury, std::vector<std::string>& _figuryNazwy) {
	if (_komendy.size() >= 2)
	{
		if (_figury.size() == 6)
		{
			PrintError("Maksymalna ilosc figur!");
		}
		else
		{
			if (_komendy[1] == "T")
			{
				Trojkat* t = new Trojkat(_figury.size());
				_figury.push_back(t);
				_figuryNazwy.push_back(t->_nazwa);
			}
			else if (_komendy[1] == "O")
			{
				Okrag* o = new Okrag(_figury.size());
				_figury.push_back(o);
				_figuryNazwy.push_back(o->_nazwa);
			}
			else if (_komendy[1] == "P")
			{
				Prostokat* p = new Prostokat(_figury.size());
				_figury.push_back(p);
				_figuryNazwy.push_back(p->_nazwa);
			}
			else
			{
				PrintError("Niepoprawny typ figury!");
			}

			if (_komendy.size() == 3 && _komendy[2] == "L")
			{
				_figury[_figury.size() - 1]->Losuj();
				_figury[_figury.size() - 1]->Narysuj();
			}
		}
		
	}
}
void UsunFigure(std::vector<std::string> _komendy, std::vector<Figura*>& _figury, std::vector<std::string>& _figuryNazwy, int& _wybranaFigura) {
	for (int i = 0; i < _figury.size(); i++)
	{
		_figury[i]->Ukryj();
	}

	if (_komendy.size() == 1 && _wybranaFigura > -1)
	{
		Figura* f = _figury[_wybranaFigura];
		delete f;
		f = NULL;
		_figury.erase(_figury.begin() + _wybranaFigura);
		_figuryNazwy.erase(_figuryNazwy.begin() + _wybranaFigura);
		for (int i = 0; i < _figury.size(); i++)
		{
			_figury[i]->SetNumer(i);
		}
		_wybranaFigura = -1;
	}
	else if (_komendy.size() == 2)
	{
		if (_komendy[1] == "*") // usun wszystko
		{
			for (auto p : _figury)
			{
				delete p;
			}
			_figury.clear();
			_figuryNazwy.clear();
			_wybranaFigura = -1;
		}
	}
	else
	{
		PrintError("Niepoprawny argument!");
	}
	for (int i = 0; i < _figury.size(); i++)
	{
		_figury[i]->Narysuj();
	}
}
void PrzesunFigure(std::vector<std::string> _komendy, std::vector<Figura*>& _figury, int _wybranaFigura) {
	for (int i = 0; i < _figury.size(); i++)
	{
		_figury[i]->Ukryj();
	}
	if (_wybranaFigura > -1)
	{
		if (_komendy.size() == 3)
		{
			try
			{
				int dx = stoi(_komendy[1]);
				int dy = stoi(_komendy[2]);

				if (_figury[_wybranaFigura]->PrzesunCaly(dx, dy) == -1)
				{
					PrintError("Nie udalo sie przsunac / figura wychodzi poza zakres");
				}
			}
			catch (const std::exception&)
			{
				PrintError("Niepoprawny argument!");
			}
		}
		else
		{
			PrintError("Zla liczba argumentow!");
		}
	}
	else PrintError("Nie wybrano figury!");
	for (int i = 0; i < _figury.size(); i++)
	{
		_figury[i]->Narysuj();
	}
}

int main()
{
	system("cls");	// wymagane żeby działały kody ANSI
	std::cout << "\u001b[0m";
	srand(time(NULL));
	
	std::vector<Figura*> _figury;
	std::vector<std::string> _figuryNazwy;
	int _wybranaFigura = -1;

	while (true)
	{
		
		NarysyjGornyPasek(_figury, _figuryNazwy, _wybranaFigura);
		NarysujDolnyPasek(_wybranaFigura);

		std::vector<std::string> _komendy;
		{ // przetwarzanie wejścia na vektor _komendy
			std::string _rawIn;
			getline(std::cin, _rawIn);

			std::stringstream _in(_rawIn);
			std::string _segment;

			while (std::getline(_in, _segment, ' '))
			{
				_komendy.push_back(_segment);
			}
		}
		std::cout << "\u001b[0m";
		if (_komendy.size() > 0)
		{
			switch (zamienPolecenie(_komendy[0]))
			{
			case Polecenia::niepoprawne:
				PrintError("Nieznane polecenie");
				break;	
			case Polecenia::przesun:
				PrzesunFigure(_komendy, _figury, _wybranaFigura);
				break;
			case Polecenia::los:
				LosujFigure(_komendy,_figury,_wybranaFigura);
				break;	
			case Polecenia::wybierz:
				WybierzFigure(_komendy, _figury, _wybranaFigura);
				break;
			case Polecenia::utworz:
				UtworzFigure(_komendy, _figury, _figuryNazwy);
				break;	
			case Polecenia::usun:
				UsunFigure(_komendy, _figury, _figuryNazwy, _wybranaFigura);
				break;
			case Polecenia::trybogolny:
				_wybranaFigura = -1;
				break;
			case Polecenia::zamknijprogram:
				std::cout << "\u001b[0m" << std::endl;
				return 0;
				break;		
			default:
				PrintError("Nieznane polecenie");
				break;
			}
		}
	}
	system("pause");
	std::cout << "\u001b[0m" << std::endl;
	return 0;
}
