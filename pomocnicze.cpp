#include "pomocnicze.h"
#include <windows.h>	/* ust kursora w konsoli, poznaj wymiary */
#include <iostream>

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

int Punkt::x() { return _x; }
int Punkt::y() { return _y; }
Punkt::Punkt(int X, int Y) 
{
	_x = X;
	_y = Y;
}
Punkt::Punkt() 
{
	_x = NULL;
	_y = NULL;
}
/// <summary>
/// Przesuwa punkt bez sprawdzania czy wartosci sa w poprawnym zakresie
/// </summary>
/// <param name="dx"> Przesuniêcie na osi X </param>
/// <param name="dy"> Przesuniêcie na osi Y </param>
void Punkt::Przesun(int dx, int dy)
{
	_x += dx;
	_y += dy;
}
/// <summary>
/// Ustawia punkt w nowe miejsce bez sprawdzania poprawnosci wartosci
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Punkt::Ustaw(int x, int y) {
	_x = x;
	_y = y;
}