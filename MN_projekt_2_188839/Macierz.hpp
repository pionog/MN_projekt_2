#pragma once
template <class t>

class Macierz {
private:
	int wiersze;
	int kolumny;
	bool calkowity;
	t** data;
public:
	Macierz<t>();
	Macierz<t>(int wiersze, int kolumny, bool calkowity);
	int getWiersze();
	int getKolumny();
	bool getCalkowity();
	t getData();
	t getCell(int wiersz, int kolumna);
	void setCell(int wiersz, int kolumna, t wartosc);
	Macierz<t> mnoz(Macierz drugaMacierz);
	void drukujMacierz();
	void stworzMacierzA(int a1, int a2, int a3);
	void stworzWektorB();
};