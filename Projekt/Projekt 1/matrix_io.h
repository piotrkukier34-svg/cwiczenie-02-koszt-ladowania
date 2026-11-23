#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include <stdio.h>
#include "matrix.h"

void wypisz(double M[][MAX], int w, int k);
int czytaj_dane(FILE *f, double M[][MAX], int *w, int *k);
int wczytaj_macierz(const char *nazwa, double M[][MAX], int *w, int *k);
int zapisz_macierz(const char *nazwa, double M[][MAX], int w, int k);

#endif