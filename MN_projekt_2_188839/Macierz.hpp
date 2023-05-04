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
	t getCell(int wiersz, int kolumna);
	void setCell(int wiersz, int kolumna, t wartosc);
	void usunMacierz();
	void wypelnij(t liczba);
	Macierz<t> operator+(Macierz<t> drugaMacierz);
	Macierz<t> operator*(Macierz<t> drugaMacierz);
	Macierz<t> mnozDiagonalnie(Macierz<t> drugaMacierz);
	void kopiuj(Macierz<t> drugaMacierz);
	void iloczynSkalarny(t mnoznik);
	double norma();
	void drukuj();
	void stworzMacierzA(int a1, int a2, int a3);
	void stworzWektorB();
	void odwrocDiagonalna();
	Macierz<t> dolnaTrojkatna(int przesuniecie);
	Macierz<t> gornaTrojkatna(int przesuniecie);
	Macierz<t> diagonala();
	Macierz<t> fs(Macierz<t> wektorb);
	Macierz<t> bs(Macierz<t> wektorb);
	Macierz<t> LUfactorization(Macierz<t> wektorb);
};