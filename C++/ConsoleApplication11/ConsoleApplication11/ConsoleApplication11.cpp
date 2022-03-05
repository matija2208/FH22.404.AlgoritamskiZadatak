#include <iostream>
#include <Windows.h>
#include <math.h>

using namespace std;

//nizovi sa mogucim vrednostima rezolucije
int Width[] = { 631, 364, 121};
int Height[] = { 546, 315, 105};
//izabrana rezolucija
int width, height;

//matrica koja sadrzi ceo ispis
char **buffer;

void inicijalizacija(int x, int y)
{
	//menjanje velicine fonta na x*y
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = x;
	cfi.dwFontSize.Y = y;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	//ciscenje outputa
	system("cls");
}

void nacrtaj(int x, int y, char col)
{
	buffer[y][x] = col;
}

void nacrtajLiniju(int x1, int y1, int x2, int y2, char col)
{
	//deklaracija promenjivih koje prate trenutno x i y
	float x = x1;
	float y = y1;
	
	//racunanje razlike izmedju x2-x1 i y2-y1
	int dx = x2 - x1;
	int dy = y2 - y1;

	//deklaracija promenljivih ya broj koraka, koracni pomeraj x-a i koracni pomeraj y-a
	int steps;
	float xi;
	float yi;

	//racunanje koliko ima koraka od pocetne do krajnje tacke
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	//racunanje koliko treba x da se uvece u jednom koraku
	xi = (1.0 * dx) / (1.0 * steps);
	//racunanje koliko treba y da se uvece u jednom koraku
	yi = (1.0 * dy) / (1.0 * steps);

	//crtanje svih tacaka od pocetne do krajnje
	nacrtaj(x, y, col);
	for (int i = 0; i < steps; i++)
	{
		x += xi;
		y += yi;

		nacrtaj(round(x), round(y), col);
	}
	
}

void nacrtajTrougao(int x1, int y1, int x2, int y2, int x3, int y3, char col)
{
	//crtanje okvira
	nacrtajLiniju(x1, y1, x2, y2, col);
	nacrtajLiniju(x2, y2, x3, y3, col);
	nacrtajLiniju(x3, y3, x1, y1, col);

	//trazenje najmanjih i najve'ih x i y koordinata
	int miny = y1;
	int maxy = y1;
	int minx = x1;
	int maxx = x1;

	if (y2 < miny)
		miny = y2;
	if (y2 > maxy)
		maxy = y2;

	if (y3 < miny)
		miny = y3;
	if (y3 > maxy)
		maxy = y3;

	if (x2 < minx)
		minx = x2;
	if (x2 > maxx)
		maxx = x2;

	if (x3 < minx)
		minx = x3;
	if (x3 > maxx)
		maxx = x3;

	//redno popunjavanje prostora od linije do linije
	for (int i = miny; i < maxy; i++)
	{
		for (int j = minx; j <= maxx; j++)
		{
			if (buffer[i][j] == col && buffer[i][j + 1] != col)
			{
				for (int k = j + 1; k <= maxx; k++)
				{
					if (buffer[i][k] == col)
					{
						for (int z = j + 1; z < k; z++)
						{
							nacrtaj(z, i, col);
						}
						break;
					}
				}
				break;
			}
		}
	}
}

int crtaj(double x, double y, int duzina, int n, int i)
{
	//uslov za prekid rekurzije
	if (i == n)
	{
		return 0;
	}

	//racunanje temena trougla koj trebamo da oduzmemo
	double x1 = x + duzina / 2.0;
	double y1 = y;
	double x2 = x + duzina * 0.75;
	double y2 = y - (duzina / 2.0) * sin(1.047198);
	double x3 = x + duzina / 4.0;
	double y3 = y2;

	//oduzimanje prethodno nadjenog trougla
	nacrtajTrougao(round(x1), round(y1), round(x2), round(y2), round(x3), round(y3), ' ');

	//ponovno pozivanje funkcije za manje trouglove
	crtaj(x, y, duzina / 2, n, i + 1);
	crtaj(x1, y1, duzina / 2, n, i + 1);
	crtaj(x3, y3, duzina / 2, n, i + 1);
}

int main()
{
	//menjanje boje teksta u zeleno
	cout << "\033[32m";
	system("cls");

	//biranje rezolucije zbog lakseg prikaza
	int n, m;
	cout << "(1) Maksimalna rezolucija\t(631x546)\n" <<
		    "(2) Srednja rezolucija\t\t(364x315)\n" <<
		    "(3) Minimalna rezolucija\t(121x105)\n" <<
		    "+-------------------------------------------+\n" <<
		    "Unesite rezoluciju : ";
	cin >> m;
	cout << "Unesite dubinu : ";
	cin >> n;

	height = Height[m - 1];
	width = Width[m - 1];

	//inicijalizovanje matrice koja nam predstavlja ispis
	buffer = new char* [height + 1];

	for (int i = 0; i <= height; i++)
	{
		buffer[i] = new char[width + 1];
		for (int j = 0; j <= width; j++)
		{
			buffer[i][j] = 32;
		}
	}

	//menjanje velicine fonta
	int t = (m == 3) ? 9 : 3;
	inicijalizacija(t, t);

	//crtanje pocetnog trougla
	nacrtajTrougao(0, height, width, height, width/2, 0, '*');
	//oduyimanje trougla do odredjene dubine
	crtaj(0, height, width, n, 0);
	
	//ispis matrice
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			std::cout << buffer[i][j];
		}
		std::cout << std::endl;
	}

	return 0;
}