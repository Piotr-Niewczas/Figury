#pragma once
#include <string>

int KonsolaX();
int KonsolaY();
void ClearLine();
void UstawKursor(int x, int y);
/// <summary>
/// Definicje kodów kolorów ANSI
/// </summary>
enum Kolory {
	czerwony = 31,
	zielony = 32,
	zolty = 33,
	niebieski = 34,
	magenta = 35,
	cyan = 36,
	reset = 0,
	szary = 90
};

class Punkt
{
private:
	int _x;
	int _y;
public:
	int x();
	int y();
	Punkt(int X, int Y);
	Punkt();
	
	void Przesun(int dx, int dy);
	void Ustaw(int x, int y);

};
Punkt LosPunkt(int maxX, int maxY, int minX, int minY);
void UstawZnak(int x, int y, int Kolor, char Znak);
void UstawZnak(Punkt pkt, int Kolor, char Znak);
void NarysujLinie(Punkt A, Punkt B, int kolorWierzch, int kolorLini, char znakWierzch, char znakLinii);
bool CzyWZakresieOkna(int x, int y);

enum class Polecenia
{
	niepoprawne,
	przesun,
	los,
	wybierz,
	utworz,
	trybogolny,
	zamknijprogram,
	usun

};
Polecenia zamienPolecenie(std::string in);