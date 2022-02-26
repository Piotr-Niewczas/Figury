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
			std::cout << "\u001b[" << _figury[i]->Numer() + 31 << ";101m";
		}
		else
		{
			std::cout << "\u001b[" << _figury[i]->Numer() + 31 << ";47m";
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

void LosujFigure(std::vector<std::string> komendy, std::vector<Figura*>& figury, int wybranaFigura) {
	if (komendy.size() == 2 && komendy[1] == "*")
	{
		for (int i = 0; i < figury.size(); i++)
		{
			figury[i]->Losuj();
		}
		for (int i = 0; i < figury.size(); i++)
		{
			figury[i]->Narysuj();
		}

	}
	else if (wybranaFigura > -1)
	{
		figury[wybranaFigura]->Losuj();
		for (int i = 0; i < figury.size(); i++)
		{
			figury[i]->Narysuj();
		}
	}
	else
	{
		PrintError("Nie wybrano figury!");
	}
}
void WybierzFigure(std::vector<std::string> komendy, std::vector<Figura*>& figury, int& wybranaFigura) {
	if (komendy.size() == 2 && komendy[1] != "*")
	{
		try
		{
			int temp = stoi(komendy[1]);
			if (temp > -1 && temp < figury.size())
			{
				wybranaFigura = temp;
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
void UtworzFigure(std::vector<std::string> komendy, std::vector<Figura*>& figury, std::vector<std::string>& figuryNazwy) {
	if (komendy.size() >= 2)
	{
		if (figury.size() == 6)
		{
			PrintError("Maksymalna ilosc figur!");
		}
		else
		{
			if (komendy[1] == "T")
			{
				Trojkat* t = new Trojkat(figury.size());
				figury.push_back(t);
				figuryNazwy.push_back(t->Nazwa());
			}
			else if (komendy[1] == "O")
			{
				Okrag* o = new Okrag(figury.size());
				figury.push_back(o);
				figuryNazwy.push_back(o->Nazwa());
			}
			else if (komendy[1] == "P")
			{
				Prostokat* p = new Prostokat(figury.size());
				figury.push_back(p);
				figuryNazwy.push_back(p->Nazwa());
			}
			else
			{
				PrintError("Niepoprawny typ figury!");
			}

			if (komendy.size() == 3 && komendy[2] == "L")
			{
				figury[figury.size() - 1]->Losuj();
				figury[figury.size() - 1]->Narysuj();
			}
		}
		
	}
}
void UsunFigure(std::vector<std::string> komendy, std::vector<Figura*>& figury, std::vector<std::string>& figuryNazwy, int& _wybranaFigura) {
	for (int i = 0; i < figury.size(); i++)
	{
		figury[i]->Ukryj();
	}

	if (komendy.size() == 1 && _wybranaFigura > -1)
	{
		Figura* f = figury[_wybranaFigura];
		delete f;
		f = NULL;
		figury.erase(figury.begin() + _wybranaFigura);
		figuryNazwy.erase(figuryNazwy.begin() + _wybranaFigura);
		for (int i = 0; i < figury.size(); i++)
		{
			figury[i]->SetNumer(i);
		}
		_wybranaFigura = -1;
	}
	else if (komendy.size() == 2)
	{
		if (komendy[1] == "*") // usun wszystko
		{
			for (auto p : figury)
			{
				delete p;
			}
			figury.clear();
			figuryNazwy.clear();
			_wybranaFigura = -1;
		}
	}
	else
	{
		PrintError("Niepoprawny argument!");
	}
	for (int i = 0; i < figury.size(); i++)
	{
		figury[i]->Narysuj();
	}
}
void PrzesunFigure(std::vector<std::string> komendy, std::vector<Figura*>& figury, int wybranaFigura) {
	for (int i = 0; i < figury.size(); i++)
	{
		figury[i]->Ukryj();
	}
	if (wybranaFigura > -1)
	{
		if (komendy.size() == 3)
		{
			try
			{
				int dx = stoi(komendy[1]);
				int dy = stoi(komendy[2]);

				if (figury[wybranaFigura]->PrzesunCaly(dx, dy) == -1)
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
	for (int i = 0; i < figury.size(); i++)
	{
		figury[i]->Narysuj();
	}
}

int main()
{
	system("cls");	// wymagane żeby działały kody ANSI 
	std::cout << "\u001b[0m";
	srand(time(NULL));
	
	std::vector<Figura*> figury;
	std::vector<std::string> figuryNazwy;
	int wybranaFigura = -1;

	while (true)
	{
		
		NarysyjGornyPasek(figury, figuryNazwy, wybranaFigura);
		NarysujDolnyPasek(wybranaFigura);

		std::vector<std::string> komendy;
		{ // przetwarzanie wejścia na vektor _komendy
			std::string rawIn;
			getline(std::cin, rawIn);

			std::stringstream in(rawIn);
			std::string segment;

			while (std::getline(in, segment, ' '))
			{
				komendy.push_back(segment);
			}
		}
		std::cout << "\u001b[0m";
		if (komendy.size() > 0)
		{
			switch (zamienPolecenie(komendy[0]))
			{
			case Polecenia::niepoprawne:
				PrintError("Nieznane polecenie");
				break;	
			case Polecenia::przesun:
				PrzesunFigure(komendy, figury, wybranaFigura);
				break;
			case Polecenia::los:
				LosujFigure(komendy,figury,wybranaFigura);
				break;	
			case Polecenia::wybierz:
				WybierzFigure(komendy, figury, wybranaFigura);
				break;
			case Polecenia::utworz:
				UtworzFigure(komendy, figury, figuryNazwy);
				break;	
			case Polecenia::usun:
				UsunFigure(komendy, figury, figuryNazwy, wybranaFigura);
				break;
			case Polecenia::trybogolny:
				wybranaFigura = -1;
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
