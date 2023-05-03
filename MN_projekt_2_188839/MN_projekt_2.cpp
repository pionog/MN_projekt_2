//-----------------------------------------------------------
//|                                                         |
//|     Napisane przez: Piotr Noga, 188839                  |
//|     Metody Numeryczne Projekt 2                         |
//|     Uklady rownan liniowych                             |
//|                                                         |
//-----------------------------------------------------------

//dolaczanie plikow naglowkowych
#include <iostream>
#include <cmath>
#include <chrono>
#include "Macierz.hpp"
#include "Macierz.cpp"
#include "stale.h"

//deklaracja funkcji
template <class t> void jacobi(Macierz<t> macierzA, Macierz<t> wektorb);
template <class t> void gauss(Macierz<t> macierzA, Macierz<t> wektorb);

//glowna funkcja
int main()
{
    //zad A

    //macierz A
    Macierz<double> A = Macierz<double>(N, N);
    A.stworzMacierzA(a1A, a2, a3);
    //wektor b
    Macierz<double> b = Macierz<double>(N, 1);
    b.stworzWektorB();

    //zad B
    jacobi(A, b);
    gauss(A, b);
    Macierz<double> Ac = Macierz<double>(N, N);
    Ac.stworzMacierzA(a1C, a2, a3);
    //jacobi(Ac, b);
    //gauss(Ac, b);

    //Macierz<double> x = Ac.LUfactorization(b);
    //x.drukuj();

    int rozmiary[7] = { 100,500,1000,2000,3000,5000,10000 };
    for (int rozmiar : rozmiary) {
        Macierz<double> Ae = Macierz<double>(rozmiar, rozmiar);
        Ae.stworzMacierzA(a1A, a2, a3);
        Macierz<double> be = Macierz<double>(rozmiar, 1);
        be.stworzWektorB();
        jacobi(Ae, b);
        gauss(Ae, b);
        Ae.LUfactorization(b);
    }

}

template <class t> void jacobi(Macierz<t> macierzA, Macierz<t> wektorb) {
    printf("Rozpoczeto rozwiazywanie ukladu rownan za pomoca metody Jacobiego.\n");
    auto start = std::chrono::high_resolution_clock::now();
    //macierz gorna trojkatna U
    Macierz<double> U = macierzA.gornaTrojkatna(1);
    //macierz dolna trojkatna L
    Macierz<double> L = macierzA.dolnaTrojkatna(-1);
    //macierz diagonalna D
    Macierz<double> D = macierzA.diagonala();
    //L+U
    Macierz<double> LplusU = L + U;
    //D^-1
    Macierz<double> Dinv = Macierz<double>();
    Dinv.kopiuj(D);
    Dinv.odwrocDiagonalna();
    //-D^-1
    Macierz<double> minusDinv = Macierz<double>();
    minusDinv.kopiuj(Dinv);
    minusDinv.iloczynSkalarny(-1);
    //-D^-1(L+U)
    Macierz<double> jacob1 = minusDinv.mnozDiagonalnie(LplusU);
    //D^-1*b
    Macierz<double> jacob2 = Macierz<double>();
    jacob2.kopiuj(Dinv);
    jacob2 = jacob2 * wektorb;
    Macierz<double> r = Macierz<double>(macierzA.getWiersze(), 1);
    r.wypelnij(1);
    Macierz<double> res = Macierz<double>();
    Macierz<double> resy = Macierz<double>(maksymalnaLiczbaIteracji, 1);
    resy.wypelnij(0);
    int i = 0;
    double normaRes = 0;
    //-b
    wektorb.iloczynSkalarny(-1);
    while (true) {
        r = (jacob1 * r) + jacob2;
        res = (macierzA * r) + wektorb;
        normaRes = res.norma();
        resy.setCell(i, 0, normaRes);
        if (normaRes <= norma || normaRes == std::numeric_limits<double>::infinity() || i+1 >= maksymalnaLiczbaIteracji) {
            if (i+1 >= maksymalnaLiczbaIteracji) {
                printf("Przekroczono limit iteracji wynoszacy %d.\n", maksymalnaLiczbaIteracji);
            }
            else {
                printf("Liczba iteracji metoda Jacobiego:%d\n", i);
            }
            break;

        }
        i++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto difference = end - start;
    double duration = std::chrono::duration<double, std::milli>(difference).count();
    printf("Czas dzialania: %f sekund\n\n", duration / 1000);
    wektorb.iloczynSkalarny(-1);
}

template <class t> void gauss(Macierz<t> macierzA, Macierz<t> wektorb) {
    printf("Rozpoczeto rozwiazywanie ukladu rownan za pomoca metody Gaussa-Seidla.\n");
    auto start = std::chrono::high_resolution_clock::now();
    //macierz gorna trojkatna U
    Macierz<double> U = macierzA.gornaTrojkatna(1);
    //macierz dolna trojkatna L
    Macierz<double> L = macierzA.dolnaTrojkatna(-1);
    //macierz diagonalna D
    Macierz<double> D = macierzA.diagonala();

    Macierz<double> r = Macierz<double>(macierzA.getWiersze(), 1);
    r.wypelnij(1);
    Macierz<double> res = Macierz<double>();
    Macierz<double> resy = Macierz<double>(500, 1);
    resy.wypelnij(0);
    int i = 0;
    double normaRes = 0;

    Macierz<double> gauss1 = D + L;
    gauss1.iloczynSkalarny(-1);

    Macierz<double> gauss2 = D + L;
    gauss2 = gauss2.fs(wektorb);

    wektorb.iloczynSkalarny(-1);
    while (true) {
        r = gauss1.fs(U * r) + gauss2;
        res = (macierzA * r) + wektorb;
        normaRes = res.norma();
        resy.setCell(i, 0, normaRes);
        if (normaRes <= norma || normaRes == std::numeric_limits<double>::infinity() || i+1 >= maksymalnaLiczbaIteracji) {
            if (i+1 >= maksymalnaLiczbaIteracji) {
                printf("Przekroczono limit iteracji wynoszacy %d.\n", maksymalnaLiczbaIteracji);
            }
            else {
                printf("Liczba iteracji metoda Gaussa-Seidla:%d\n", i);
            }
            break;

        }
        i++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto difference = end - start;
    double duration = std::chrono::duration<double, std::milli>(difference).count();
    printf("Czas dzialania: %f sekund\n\n", duration / 1000);
    wektorb.iloczynSkalarny(-1);
}
