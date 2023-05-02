#include <iostream>
#include "Macierz.hpp"
#include "stale.h"
#include <cmath>

template <class t> Macierz<t>::Macierz() {
		this->wiersze = 5;
		this->kolumny = 5;
		this->data = new t* [5];
		for (int i = 0; i < 5; i++) this->data[i] = new t[5];
	}

template <class t> Macierz<t>::Macierz(int wiersze, int kolumny) {
		this->wiersze = wiersze;
		this->kolumny = kolumny;
		this->data = new t * [wiersze];
		for (int i = 0; i < wiersze; i++) this->data[i] = new t[kolumny];
	}

template <class t> int Macierz<t>::getWiersze() {
	return this->wiersze;
}
template <class t> int Macierz<t>::getKolumny() {
	return this->kolumny;
}

template <class t> t Macierz<t>::getData() {
	return this->data;
}
template <class t> t Macierz<t>::getCell(int wiersz, int kolumna) {
	return this->data[wiersz][kolumna];
}
template <class t> void Macierz<t>::setCell(int wiersz, int kolumna, t wartosc) {
	this->data[wiersz][kolumna] = wartosc;
}

template <class t> void Macierz<t>::wypelnij(t liczba) {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            this->setCell(i, j, liczba);
        }
    }
}

template <class t> Macierz<t> Macierz<t>::dodaj(Macierz<t> drugaMacierz) {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    Macierz<t> rezultat = Macierz<t>(wiersze, kolumny);
    rezultat.wypelnij(0);
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            rezultat.setCell(i, j, (this->getCell(i, j) + drugaMacierz.getCell(i, j)));
        }
    }
    return rezultat;
}

template <class t> Macierz<t> Macierz<t>::mnoz(Macierz<t> drugaMacierz) {
    int wiersze1 = this->getWiersze();
    //int kolumny1 = this->getKolumny();
    int wiersze2 = drugaMacierz.getWiersze();
    int kolumny2 = drugaMacierz.getKolumny();
	Macierz<t> rezultat = Macierz<t>(wiersze1, kolumny2);
    rezultat.wypelnij((t)0);
    double wynik = 0;
	for (int i = 0; i < wiersze1; i++) {
		for (int j = 0; j < kolumny2; j++) {
			for (int k = 0; k < wiersze2; k++) {
                wynik += this->getCell(i, k) * drugaMacierz.getCell(k, j);
			}
            rezultat.setCell(i, j, wynik);
            wynik = 0;
		}
	}
	return rezultat;
}
template <class t> void Macierz<t>::kopiuj(Macierz<t> drugaMacierz) {
    for (int i = 0; i < this->getWiersze(); i++) {
        delete[] this->data[i];
    }
    delete[] this->data;
    int wiersze = drugaMacierz.getWiersze();
    int kolumny = drugaMacierz.getKolumny();
    Macierz<t> kopia = Macierz<t>(wiersze, kolumny);
    this->data = kopia.data;
    this->wiersze = wiersze;
    this->kolumny = kolumny;
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            this->setCell(i, j, drugaMacierz.getCell(i, j));
        }
    }
}
template <class t> void Macierz<t>::iloczynSkalarny(t mnoznik) {
    for (int i = 0; i < this->getWiersze(); i++) {
        for (int j = 0; j < this->getKolumny(); j++) {
            this->setCell(i, j, (this->getCell(i, j) * mnoznik));
        }
    }
}
template <class t> double Macierz<t>::norma() {
    double kwadrat = 0;
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    double jednostka = 0;

    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            jednostka = this->getCell(i, j);
            kwadrat += (jednostka * jednostka);
            jednostka = 0;
        }
    }
    int n = wiersze * kolumny;
    return (double)sqrt((kwadrat / n));
}
template <class t> void Macierz<t>::drukuj() {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();

    if (wiersze < 6 && kolumny < 6) {
        for (int i = 0; i < wiersze; i++) {
            for (int j = 0; j < kolumny; j++) {
                printf("%f\t", (double)this->getCell(i,j));
            }
            printf("\n");
        }
    }
    else if (wiersze < 6) {
        for (int i = 0; i < wiersze; i++) {
            for (int j = 0; j < 7; j++) {
                if (j < 5) printf("%f\t", (double)this->getCell(i, j));
                else if (j == 5) printf("...\t\t");
                else printf("%f\t", (double)this->getCell(i, kolumny - 1));
            }
            printf("\n");
        }
    }
    else if (kolumny < 6) {
        for (int i = 0; i < 7; i++) {
            if (i < 5) {
                for (int j = 0; j < kolumny; j++) {
                    printf("%f\t", (double)this->getCell(i, j));
                }
            }
            else if (i == 5) {
                for (int j = 0; j < kolumny; j++) {
                    printf("...\t\t");
                }
            }
            else {
                for (int j = 0; j < kolumny; j++) {
                    printf("%f\t", (double)this->getCell(wiersze - 1, j));
                }
            }
            printf("\n");
        }
    }
    else {
        for (int i = 0; i < 7; i++) {
            if (i < 5) {
                for (int j = 0; j < 7; j++) {
                    if (j < 5) printf("%f\t", (double)this->getCell(i, j));
                    else if (j == 5) printf("...\t\t");
                    else printf("%f\t", (double)this->getCell(i, kolumny - 1));
                }
            }
            else if (i == 5) {
                for (int j = 0; j < 7; j++) printf("...\t\t");
            }
            else {
                for (int j = 0; j < 7; j++) {
                    if (j < 5) printf("%f\t", (double)this->getCell(wiersze - 1, j));
                    else if (j == 5) printf("...\t\t");
                    else printf("%f\t", (double)this->getCell(wiersze - 1, kolumny - 1));
                }
            }
            printf("\n");
        }

    }
    printf("\n");
}
template <class t> void Macierz<t>::stworzMacierzA(int a1, int a2, int a3) {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    this->wypelnij((t)0);
    int j = 0;
    for (int i = 0; i < wiersze; i++) {
        if (j - 2 >= 0) this->setCell(i, j-2, a3);
        if (j - 1 >= 0) this->setCell(i, j-1, a2);
        this->setCell(i, j, a1);
        if (j + 1 < wiersze) this->setCell(i, j+1, a2);
        if (j + 2 < wiersze) this->setCell(i, j+2, a3);
        j++;
    }
}

template <class t> void Macierz<t>::stworzWektorB() {
    int wiersze = this->getWiersze();
    for (int i = 0; i < wiersze; i++) {
        this->setCell(i, 0, sin(i * (f + 1)));
    }
}


template <class t> void Macierz<t>::odwrocDiagonalna() {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    double wartosc;
    if (wiersze == kolumny) {
        for (int i = 0; i < wiersze; i++) {
            wartosc = this->getCell(i, i);
            wartosc = 1 / wartosc;
            this->setCell(i, i, wartosc);
        }
    }
    else return;
}

template <class t> Macierz<t> Macierz<t>::dolnaTrojkatna(int przesuniecie) {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    Macierz<t> rezultat = Macierz<t>(wiersze, kolumny);
    rezultat.wypelnij((t)0);
    int ile = 1;
    for (int i = 0-przesuniecie; i < wiersze; i++) {
        for (int j = 0; j < ile; j++) {
            if ((0 <= i) && (i <= wiersze) && (0 <= j) && (j <= wiersze)) {
                rezultat.setCell(i, j, this->getCell(i, j));
            }
        }
        ile++;
    }
    return rezultat;
}

template <class t> Macierz<t> Macierz<t>::gornaTrojkatna(int przesuniecie) {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    Macierz<t> rezultat = Macierz<t>(wiersze, kolumny);
    rezultat.wypelnij((t)0);
    int ile = przesuniecie;
    for (int i = 0; i < wiersze; i++) {
        for (int j = ile; j < kolumny; j++) {
            if ((0 <= i) && (i <= wiersze) && (0 <= j) && (j <= wiersze)) {
                rezultat.setCell(i, j, this->getCell(i, j));
            }
        }
        ile++;
    }
    return rezultat;
}

template <class t> Macierz<t> Macierz<t>::diagonala() {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    Macierz<t> rezultat = Macierz<t>(wiersze, kolumny);
    rezultat.wypelnij((t)0);
    for (int i = 0; i < wiersze; i++) {
        rezultat.setCell(i, i, this->getCell(i, i));
    }
    return rezultat;
}