
int KonsolaX();
int KonsolaY();
void ClearLine();
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
