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
    A.usunMacierz();
    Macierz<double> Ac = Macierz<double>(N, N);
    Ac.stworzMacierzA(a1C, a2, a3);
    jacobi(Ac, b);
    gauss(Ac, b);

    Macierz<double> x = Ac.LUfactorization(b);
    x.drukuj();
    b.usunMacierz();

    int rozmiary[7] = { 100,500,1000,2000,3000,5000,10000 };
    for (int rozmiar : rozmiary) {
        printf("\n---------------------------------------------------\nObecnie rozpatrywany rozmiar macierzy N: %d\n", rozmiar);
        Macierz<double> Ae = Macierz<double>(rozmiar, rozmiar);
        Ae.stworzMacierzA(a1A, a2, a3);
        Macierz<double> be = Macierz<double>(rozmiar, 1);
        be.stworzWektorB();
        jacobi(Ae, be);
        gauss(Ae, be);
        Ae.LUfactorization(be);
        Ae.usunMacierz();
        be.usunMacierz();
    }

}

template <class t> void jacobi(Macierz<t> macierzA, Macierz<t> wektorb) {
    printf("Rozpoczeto rozwiazywanie ukladu rownan za pomoca metody Jacobiego.\n");
    auto start = std::chrono::high_resolution_clock::now();
    //macierz gorna trojkatna U
    Macierz<t> U = macierzA.gornaTrojkatna(1);
    //macierz dolna trojkatna L
    Macierz<t> L = macierzA.dolnaTrojkatna(-1);
    //macierz diagonalna D
    Macierz<t> D = macierzA.diagonala();
    //L+U
    Macierz<t> LplusU = L + U;
    //D^-1
    Macierz<t> Dinv = Macierz<t>();
    Dinv.kopiuj(D);
    Dinv.odwrocDiagonalna();
    //-D^-1
    Macierz<t> minusDinv = Macierz<t>();
    minusDinv.kopiuj(Dinv);
    minusDinv.iloczynSkalarny(-1);
    //-D^-1(L+U)
    Macierz<t> jacob1 = minusDinv.mnozDiagonalnie(LplusU);
    //D^-1*b
    Macierz<t> jacob2 = Macierz<t>();
    jacob2.kopiuj(Dinv);
    jacob2 = jacob2 * wektorb;
    Macierz<t> r = Macierz<t>(macierzA.getWiersze(), 1);
    r.wypelnij(1);
    Macierz<t> res = Macierz<t>();
    Macierz<t> resy = Macierz<t>(maksymalnaLiczbaIteracji, 1);
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
        //r.usunMacierz();
        res.usunMacierz();
        i++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto difference = end - start;
    double duration = std::chrono::duration<double, std::milli>(difference).count();
    printf("Czas dzialania: %f sekund\n\n", duration / 1000);
    wektorb.iloczynSkalarny(-1);

    U.usunMacierz();
    L.usunMacierz();
    D.usunMacierz();

    minusDinv.usunMacierz();
    Dinv.usunMacierz();
    LplusU.usunMacierz();

    jacob1.usunMacierz();
    jacob2.usunMacierz();

    resy.usunMacierz();
    res.usunMacierz();
    r.usunMacierz();
}

template <class t> void gauss(Macierz<t> macierzA, Macierz<t> wektorb) {
    printf("Rozpoczeto rozwiazywanie ukladu rownan za pomoca metody Gaussa-Seidla.\n");
    auto start = std::chrono::high_resolution_clock::now();
    //macierz gorna trojkatna U
    Macierz<t> U = macierzA.gornaTrojkatna(1);
    //macierz dolna trojkatna L
    Macierz<t> L = macierzA.dolnaTrojkatna(-1);
    //macierz diagonalna D
    Macierz<t> D = macierzA.diagonala();

    Macierz<t> r = Macierz<t>(macierzA.getWiersze(), 1);
    r.wypelnij(1);

    Macierz<t> res = Macierz<t>();
    Macierz<t> resy = Macierz<t>(500, 1);
    resy.wypelnij(0);
    int i = 0;
    double normaRes = 0;

    Macierz<t> gauss1 = D + L;
    gauss1.iloczynSkalarny(-1);

    Macierz<t> gauss2 = D + L;
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
        res.usunMacierz();
        i++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto difference = end - start;
    double duration = std::chrono::duration<double, std::milli>(difference).count();
    printf("Czas dzialania: %f sekund\n\n", duration / 1000);
    wektorb.iloczynSkalarny(-1);
    
    L.usunMacierz();
    D.usunMacierz();
    U.usunMacierz();

    r.usunMacierz();
    resy.usunMacierz();
    res.usunMacierz();

    gauss1.usunMacierz();
    gauss2.usunMacierz();


}
