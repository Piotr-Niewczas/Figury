#include "pomocnicze.h"
#include <windows.h>	/* ust kursora w konsoli, poznaj wymiary */
#include <iostream>
#include <stdlib.h> 

int KonsolaX() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return (csbi.srWindow.Right - csbi.srWindow.Left + 1);
}
int KonsolaY() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

void ClearLine() {

	printf("\33[2K\r");
}

int Punkt::X() { return x; }
int Punkt::Y() { return y; }
Punkt::Punkt(int X, int Y) 
{
	x = X;
	y = Y;
}
Punkt::Punkt() 
{
	x = NULL;
	y = NULL;
}
/// <summary>
/// Przesuwa punkt bez sprawdzania czy wartosci sa w poprawnym zakresie
/// </summary>
/// <param name="dx"> Przesuniêcie na osi X </param>
/// <param name="dy"> Przesuniêcie na osi Y </param>
void Punkt::Przesun(int dx, int dy)
{
	x += dx;
	y += dy;
}
/// <summary>
/// Ustawia punkt w nowe miejsce bez sprawdzania poprawnosci wartosci
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Punkt::Ustaw(int x, int y) {
	x = x;
	y = y;
}

/// <summary>
/// Losuje punkt o podanych parametrach
/// </summary>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
/// <param name="minX">(opc)</param>
/// <param name="minY">(opc)</param>
/// <returns></returns>
Punkt LosPunkt(int maxX, int maxY, int minX = 0, int minY = 1) { // wylosuj punkt z zakresu
	int x, y;
	x = minX + (rand() % (maxX - minX + 1));
	y = minY + (rand() % (maxY - minY + 1));

	return Punkt(x, y);
}

void UstawKursor(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void UstawZnak(int x, int y, int Kolor, char Znak = '*') {
	UstawKursor(x, y);
	std::cout << "\u001b[" << Kolor << "m" << Znak;
}
/// <summary>
/// Wstawia znak w okreœlonej pozycji na konsoli
/// </summary>
/// <param name="pkt">Miejsce wstawienia</param>
/// <param name="Kolor">(opc) Kod ANSI koloru w którym znak ma byæ wstawiony</param>
/// <param name="Znak">(opc) Znak do wstawienia</param>
void UstawZnak(Punkt pkt, int Kolor = 0, char Znak = '*') {
	UstawZnak(pkt.X(), pkt.Y(), Kolor, Znak);
}

/// <summary>
/// Algorytm Bresenhama rysowania linii miêdzy punktami 
/// </summary>
/// <param name="A">Punkt Pocz¹tkowy</param>
/// <param name="B">Punkty Koñcowy</param>
/// <param name="kolorWierzch">(opc) Kolor ANSI wierzcho³ków</param>
/// <param name="kolorLini">(opc) Kolor ANSI linii</param>
/// <param name="znakWierzch">(opc) Znak Wierzcho³ka</param>
/// <param name="znakLinii">(opc) Znak Linii</param>
void NarysujLinie(Punkt A, Punkt B, int kolorWierzch = 0, int kolorLini = 0, char znakWierzch = '*', char znakLinii = '*')
{
	int x0 = A.X(), y0 = A.Y();
	int x1 = B.X(), y1 = B.Y();

	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while (true)
	{
		UstawZnak(Punkt(x0, y0), kolorLini, znakLinii);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;

		if (e2 >= dy) {
			if (x0 == x1) break;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) break;
			err += dx;
			y0 += sy;
		}
	}

	UstawZnak(A, kolorWierzch, znakWierzch);
	UstawZnak(B, kolorWierzch, znakWierzch);

}
bool CzyWZakresieOkna(int x, int y) {
	int maxX = KonsolaX() - 1, maxY = KonsolaY() - 3;	// maksymalne wartoœci wspó³rzednych konsoli
	if (x < 0 || x > maxX || y < 1 || y > maxY) return false;
	return true;
}


Polecenia zamienPolecenie(std::string in) {
	if (in == "UTWORZ") return Polecenia::utworz;
	else if (in == "LOSUJ" || in == "LOS") return Polecenia::los;
	else if (in == "EDYTUJ" || in == "ZAZNACZ" || in == "WYBIERZ") return Polecenia::wybierz;
	else if (in == "WYJDZ" || in == "ODZNACZ") return Polecenia::trybogolny;
	else if (in == "USUN") return Polecenia::usun;
	else if (in == "PRZESUN") return Polecenia::przesun;
	else if (in == "ZAMKNIJ" || in == "ZAKONCZ" || in == "EXIT") return Polecenia::zamknijprogram;
	return Polecenia::niepoprawne;
}

void PrintError(std::string text) {
	UstawKursor(0, KonsolaY() - 1);
	std::cout << "\u001b[0;101m\a Error: " << text;
	getchar();
	printf("\033[A");
	printf("\33[2K\r");
	std::cout << "\u001b[0m";
}