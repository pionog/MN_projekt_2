#include <iostream>
#include "Macierz.hpp"
#include "stale.h"
#include <cmath>

template <class t>
Macierz<t>::Macierz() {
		this->wiersze = 5;
		this->kolumny = 5;
		this->calkowity = true;
		this->data = new int* [5];
		for (int i = 0; i < 5; i++) this->dataI[i] = new int[5];
	}

template <class t>
Macierz<t>::Macierz(int wiersze, int kolumny, bool calkowity) {
		this->wiersze = wiersze;
		this->kolumny = kolumny;
		this->data = new t * [wiersze];
		for (int i = 0; i < wiersze; i++) this->data[i] = new t[kolumny];
	}

template <class t>
int Macierz<t>::getWiersze() {
	return this->wiersze;
}
template <class t>
int Macierz<t>::getKolumny() {
	return this->kolumny;
}
template <class t>
bool Macierz<t>::getCalkowity() {
	return this->calkowity;
}
template <class t>
t Macierz<t>::getData() {
	return this->data;
}
template <class t>
t Macierz<t>::getCell(int wiersz, int kolumna) {
	return this->data[wiersz][kolumna];
}
template <class t>
void Macierz<t>::setCell(int wiersz, int kolumna, t wartosc) {
	this->data[wiersz][kolumna] = wartosc;
}
template <class t>
Macierz<t> Macierz<t>::mnoz(Macierz drugaMacierz) {
	bool calkowity = false;
	if (this->getCalkowity() && drugaMacierz->getCalkowity()) calkowity = true;
	Macierz rezultat = new Macierz(this->getWiersze(), drugaMacierz->getKolumny(), calkowity);
	for (int i = 0; i < rezultat.getWiersze(); i++) {
		for (int j = 0; j < rezultat.getKolumny(); j++) {
			rezultat.setCell(i, j, 0);
		}
	}
	for (int i = 0; i < this->getWiersze(); i++) {
		for (int j = 0; j < drugaMacierz->getKolumny(); j++) {
			for (int k = 0; k < drugaMacierz->getKolumny(); k++) {
				rezultat[i][j] += this->getCell(i, k) * drugaMacierz->getCell(k, j);
			}
		}
	}
	return rezultat;
}


template <class t> 
void Macierz<t>::drukujMacierz() {
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
template <class t>
void Macierz<t>::stworzMacierzA(int a1, int a2, int a3) {
    int wiersze = this->getWiersze();
    int kolumny = this->getKolumny();
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            this->setCell(i, j, 0);
        }
    }
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

template <class t>
void Macierz<t>::stworzWektorB() {
    int kolumny = this->getKolumny();
    for (int j = 0; j < kolumny; j++) {
        this->setCell(0, j, sin(j * (f + 1)));
    }
}
