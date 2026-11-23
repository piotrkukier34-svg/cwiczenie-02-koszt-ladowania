#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "matrix_io.h"

int main(int argc, char *argv[])
{
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int wA, kA, wB, kB, wC, kC;
    int operacja, kod;
    char buf_a[256], buf_b[256], buf_c[256];
    const char *plik_a;
    const char *plik_b;
    const char *plik_c;

    if (argc == 1)
    {
        printf("Podaj nazwe pliku A: ");
        if (scanf("%255s", buf_a) != 1)
        {
            printf("Blad odczytu nazwy pliku A (kod %d)\n", BLAD_OTWARCIA);
            return BLAD_OTWARCIA;
        }
        printf("Podaj nazwe pliku B: ");
        if (scanf("%255s", buf_b) != 1)
        {
            printf("Blad odczytu nazwy pliku B (kod %d)\n", BLAD_OTWARCIA);
            return BLAD_OTWARCIA;
        }
        printf("Podaj nazwe pliku wynikowego: ");
        if (scanf("%255s", buf_c) != 1)
        {
            printf("Blad odczytu nazwy pliku wynikowego (kod %d)\n", BLAD_ZAPISU);
            return BLAD_ZAPISU;
        }
        printf("Wybierz operacje:\n1. Dodawanie (+)\n2. Odejmowanie (-)\n3. Mnozenie (*)\n");
        if (scanf("%d", &operacja) != 1)
        {
            printf("Blad odczytu operacji (kod %d)\n", BLAD_OPERACJI);
            return BLAD_OPERACJI;
        }
        plik_a = buf_a;
        plik_b = buf_b;
        plik_c = buf_c;
    }
    else if (argc == 5)
    {
        plik_a = argv[1];
        plik_b = argv[2];
        plik_c = argv[3];

        if (strcmp(argv[4], "+") == 0 || strcmp(argv[4], "1") == 0)
            operacja = 1;
        else if (strcmp(argv[4], "-") == 0 || strcmp(argv[4], "2") == 0)
            operacja = 2;
        else if (strcmp(argv[4], "*") == 0 || strcmp(argv[4], "3") == 0)
            operacja = 3;
        else
        {
            printf("Blad: nieznana operacja '%s' (kod %d)\n", argv[4], BLAD_OPERACJI);
            return BLAD_OPERACJI;
        }
    }
    else
    {
        printf("Blad: zla liczba argumentow (kod %d)\n", BLAD_ARGUMENTOW);
        printf("Uzycie: %s [plik_A plik_B plik_wynik operacja(+|-|*)]\n", argv[0]);
        return BLAD_ARGUMENTOW;
    }

    if ((kod = wczytaj_macierz(plik_a, A, &wA, &kA)) != OK)
    {
        printf("Blad odczytu pliku A (kod %d)\n", kod);
        return kod;
    }
    if ((kod = wczytaj_macierz(plik_b, B, &wB, &kB)) != OK)
    {
        printf("Blad odczytu pliku B (kod %d)\n", kod);
        return kod;
    }

    switch (operacja)
    {
    case 1:
        if (wA != wB || kA != kB)
        {
            printf("Blad: Niezgodne wymiary dla dodawania (kod %d)\n", BLAD_WYMIAROW);
            return BLAD_WYMIAROW;
        }
        dodaj(A, B, C, wA, kA);
        wC = wA;
        kC = kA;
        printf("Suma A + B:\n");
        wypisz(C, wA, kA);
        break;
    case 2:
        if (wA != wB || kA != kB)
        {
            printf("Blad: Niezgodne wymiary dla odejmowania (kod %d)\n", BLAD_WYMIAROW);
            return BLAD_WYMIAROW;
        }
        odejmij(A, B, C, wA, kA);
        wC = wA;
        kC = kA;
        printf("Roznica A - B:\n");
        wypisz(C, wA, kA);
        break;
    case 3:
        if (kA != wB)
        {
            printf("Blad: Niezgodne wymiary dla mnozenia (kod %d)\n", BLAD_WYMIAROW);
            return BLAD_WYMIAROW;
        }
        pomnoz(A, B, C, wA, kA, kB);
        wC = wA;
        kC = kB;
        printf("A * B:\n");
        wypisz(C, wA, kB);
        break;
    default:
        printf("Nieznana operacja (kod %d)\n", BLAD_OPERACJI);
        return BLAD_OPERACJI;
    }

    if ((kod = zapisz_macierz(plik_c, C, wC, kC)) != OK)
    {
        printf("Blad zapisu wyniku do pliku (kod %d)\n", kod);
        return kod;
    }

    printf("Wynik zostal zapisany do pliku %s\n", plik_c);
    return OK;
}