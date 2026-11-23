#ifndef MATRIX_H
#define MATRIX_H

#define MAX 20
#define OK 0
#define BLAD_OTWARCIA 1
#define BLAD_ZAKRES 2
#define BLAD_ZA_MALO 3
#define BLAD_ELEMENT 4
#define BLAD_ZAPISU 5
#define BLAD_WYMIAROW 6
#define BLAD_OPERACJI 7
#define BLAD_ARGUMENTOW 8

void dodaj(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k);
void odejmij(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k);
void pomnoz(double A[][MAX], double B[][MAX], double C[][MAX], int wA, int kA, int kB);

#endif