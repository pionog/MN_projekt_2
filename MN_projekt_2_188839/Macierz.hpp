#pragma once
template <class t>

class Macierz {
private:
	int wiersze;
	int kolumny;
	t** data;
public:
	Macierz<t>();
	Macierz<t>(int wiersze, int kolumny);
	int getWiersze();
	int getKolumny();
	t getData();
	t getCell(int wiersz, int kolumna);
	void setCell(int wiersz, int kolumna, t wartosc);
	void wypelnij(t liczba);
	Macierz<t> dodaj(Macierz<t> drugaMacierz);
	Macierz<t> mnoz(Macierz<t> drugaMacierz);
	void drukuj();
	void stworzMacierzA(int a1, int a2, int a3);
	void stworzWektorB();
	void odwrocDiagonalna();
	Macierz<t> dolnaTrojkatna(int przesuniecie);
	Macierz<t> gornaTrojkatna(int przesuniecie);
	Macierz<t> diagonala();
};