#include <iostream>
#include <stdio.h>
#include <time.h>		/* time */ 
#include <sstream>		/* string stream */
#include <vector>
#include "figury.h"

//dom rozmiar okna 120x30 znaków


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
