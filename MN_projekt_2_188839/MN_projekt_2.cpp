//-----------------------------------------------------------
//|                                                         |
//|     Stworzone przez: Piotr Noga, 188839                 |
//|     Metody Numeryczne Projekt 2                         |
//|     Uklady rownan liniowych                             |
//|                                                         |
//-----------------------------------------------------------

//dolaczanie plikow naglowkowych
#include <iostream>
#include <cmath>
#include "Macierz.hpp"
#include "Macierz.cpp"
#include "stale.h"

//deklaracja funkcji
//double** stworzWektorB();
//int** stworzMacierzA(int a1, int a2, int a3);
//int** mnozMacierze(int** mac1, int wie1, int kol1, int** mac2, int wie2, int kol2);
//template <class t> void drukujMacierz(t** macierz, int wiersze, int kolumny);
double** obliczDopelnienie(int** macierz, int danyWiersz, int danaKolumna, int rozmiar);

//glowna funkcja
int main()
{   
    //zad A
    Macierz<int> a = Macierz<int>(N, N, true);
    a.stworzMacierzA(a1A, a2, a3);
    a.drukujMacierz();
    Macierz<double> b = Macierz<double>(1, N, false);
    b.stworzWektorB();
    b.drukujMacierz();
    //double** bA = stworzWektorB();
    //int** AA = stworzMacierzA(a1A, a2, a3);
    ////drukujMacierz(AA, N, N);
    //double** dop = obliczDopelnienie(AA, 5, 5, N);
    ////drukujMacierz(dop, N, N);
    //for(int i = 0; i < N; i++) delete[] AA[i];
    //delete[] AA;
    //for (int i = 0; i < N; i++) delete[] bA[i];
    //delete[] bA;
}


//definicje funkcji
//double** stworzWektorB() {
//    double** wektor = new double*[N];
//    for (int i = 0; i < N; i++) wektor[i] = new double[N];
//    for (int i = 0; i < N; i++) {
//        wektor[0][i] = sin(i * (f + 1));
//    }
//    return wektor;
//}

//int** stworzMacierzA(int a1, int a2, int a3) {
//    int** macierz = new int*[N];
//    for (int i = 0; i < N; i++) { 
//        macierz[i] = new int[N]; 
//    }
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            macierz[i][j] = 0;
//        }
//    }
//    int j = 0;
//    for (int i = 0; i < N; i++) {
//        if(j-2 >= 0) macierz[i][j - 2] = a3;
//        if(j-1 >= 0) macierz[i][j - 1] = a2;
//        macierz[i][j] = a1;
//        if(j+1 < N) macierz[i][j + 1] = a2;
//        if(j+2 < N) macierz[i][j + 2] = a3;
//        j++;
//    }
//    return macierz;
//}

//int** mnozMacierze(int** mac1, int wie1, int kol1, int** mac2, int wie2, int kol2)
//{
//    int** rezultat = new int*[kol2];
//    for (int i = 0; i < kol1; i++) rezultat[i] = new int[kol1];
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            rezultat[i][j] = 0;
//        }
//    }
//    for (int i = 0; i < wie1; i++) {
//        for (int j = 0; j < kol2; j++) {
//            for (int k = 0; k < wie2; k++) {
//                rezultat[i][j] += mac1[i][k] * mac2[k][j];
//            }
//        }
//    }
//    return rezultat;
//}

//template <class t> void drukujMacierz(t** macierz, int wiersze, int kolumny) {
//    if (wiersze < 6 && kolumny < 6) {
//        for (int i = 0; i < wiersze; i++) {
//            for (int j = 0; j < kolumny; j++) {
//                printf("%f\t", (double)macierz[i][j]);
//            }
//            printf("\n");
//        }
//    }
//    else if (wiersze < 6) {
//        for (int i = 0; i < wiersze; i++) {
//            for (int j = 0; j < 7; j++) {
//                if (j < 5) printf("%f\t", (double)macierz[i][j]);
//                else if (j == 5) printf("...\t\t");
//                else printf("%f\t", (double)macierz[i][kolumny-1]);
//            }
//            printf("\n");
//        }
//    }
//    else if (kolumny < 6) {
//        for (int i = 0; i < 7; i++) {
//            if (i < 5) {
//                for (int j = 0; j < kolumny; j++) {
//                    printf("%f\t", (double)macierz[i][j]);
//                }
//            }
//            else if (i == 5) {
//                for (int j = 0; j < kolumny; j++) {
//                    printf("...\t\t");
//                }
//            }
//            else {
//                for (int j = 0; j < kolumny; j++) {
//                    printf("%f\t", (double)macierz[wiersze-1][j]);
//                }
//            }
//            printf("\n");
//        }
//    }
//    else {
//        for (int i = 0; i < 7; i++) {
//            if (i < 5) {
//                for (int j = 0; j < 7; j++) {
//                    if (j < 5) printf("%f\t", (double)macierz[i][j]);
//                    else if (j == 5) printf("...\t\t");
//                    else printf("%f\t", (double)macierz[i][kolumny-1]);
//                }
//            }
//            else if (i == 5) {
//                for(int j = 0; j < 7; j++) printf("...\t\t");
//            }
//            else {
//                for (int j = 0; j < 7; j++) {
//                    if (j < 5) printf("%f\t", (double)macierz[wiersze-1][j]);
//                    else if (j == 5) printf("...\t\t");
//                    else printf("%f\t", (double)macierz[wiersze-1][kolumny-1]);
//                }
//            }
//            printf("\n");
//        }
//
//    }
//    printf("\n");
//}

double** obliczDopelnienie(int** macierz, int danyWiersz, int danaKolumna, int rozmiar)
{
    int i = 0, j = 0;

    double** macierzDop = new double* [rozmiar];
    for (int k = 0; k < rozmiar; k++) {
        macierzDop[k] = new double[rozmiar];
    }
    for (int y = 0; y < rozmiar; y++) {
        for (int x = 0; x < rozmiar; x++) {
            macierzDop[y][x] = 0;
        }
    }

    for (int row = 0; row < rozmiar; row++) {
        for (int col = 0; col < rozmiar; col++) {
            if (row != danyWiersz && col != danaKolumna) {
                macierzDop[i][j++] = (double)macierz[row][col];
                if (j == rozmiar - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return macierzDop;
}