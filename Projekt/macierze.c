#include <stdio.h>
#define MAX 20
#define OK 0
#define BLAD_OTWARCIA 1
#define BLAD_ZAKRES 2
#define BLAD_ZA_MALO 3
#define BLAD_ELEMENT 4
#define BLAD_ZAPISU 5

void wypisz(double M[][MAX], int w, int k)
{
    int i;
    int j;
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            printf("%8.2f", M[i][j]);
        }
        printf("\n");
    }
}
void dodaj(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k)
{
    int i;
    int j;
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
void odejmij(double A[][MAX], double B[][MAX], double C[][MAX], int w, int k)
{
    int i;
    int j;
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}
void pomnoz(double A[][MAX], double B[][MAX], double C[][MAX], int wA, int kA, int kB)
{
    int i, j, n;
    double suma;
    for (i = 0; i < wA; i++)
    {
        for (j = 0; j < kB; j++)
        {
            suma = 0.0;
            for (n = 0; n < kA; n++)
            {
                suma += A[i][n] * B[n][j];
            }
            C[i][j] = suma;
        }
    }
}
int czytaj_dane(FILE *f, double M[][MAX], int *w, int *k)
{
    int i, j, wynik;

    if (fscanf(f, "%d %d", w, k) != 2)
    {
        return BLAD_ZA_MALO;
    }
    if (*w < 1 || *w > MAX || *k < 1 || *k > MAX)
    {
        return BLAD_ZAKRES;
    }
    for (i = 0; i < *w; i++)
    {
        for (j = 0; j < *k; j++)
        {
            wynik = fscanf(f, "%lf", &M[i][j]);
            if (wynik == EOF)
                return BLAD_ZA_MALO;
            if (wynik != 1)
                return BLAD_ELEMENT;
        }
    }
    return OK;
}
int wczytaj_macierz(const char *nazwa, double M[][MAX], int *w, int *k)
{
    FILE *f = fopen(nazwa, "r");
    if (f == NULL)
        return BLAD_OTWARCIA;

    int kod = czytaj_dane(f, M, w, k);
    fclose(f);
    return kod;
}
int zapisz_macierz(const char *nazwa, double M[][MAX], int w, int k)
{
    int i, j;
    FILE *f = fopen(nazwa, "w");
    if (f == NULL)
        return BLAD_ZAPISU;

    fprintf(f, "%d %d\n", w, k);
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < k; j++)
        {
            if (j > 0)
                fprintf(f, " ");
            fprintf(f, "%.2f", M[i][j]);
        }
        fprintf(f, "\n");
    }
    int blad = ferror(f);
    if (fclose(f) != 0)
    {
        blad = 1;
    }
    return blad ? BLAD_ZAPISU : OK;
}
int main()
{
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int wA, kA, wB, kB, wC, kC;
    int operacja, kod;
    if ((kod = wczytaj_macierz("A.txt", A, &wA, &kA)) != OK)
    {
        printf("Blad odczytu pliku A (kod %d)\n", kod);
        return 1;
    }
    if ((kod = wczytaj_macierz("B.txt", B, &wB, &kB)) != OK)
    {
        printf("Blad odczytu pliku B (kod %d)\n", kod);
        return 1;
    }

    printf("Wybierz Operecje:\n1. Dodawanie (+)\n2. Odejmowanie (-)\n3. Mnozenie (*)\n");
    scanf("%d", &operacja);
    switch (operacja)
    {
    case 1:
        if (wA != wB || kA != kB)
        {
            printf("Blad: Niezgodne wymiary dla dodawania");
            return 1;
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
            printf("Blad: Niezgodne wymiary dla odejmowania");
            return 1;
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
            printf("Blad: Niezgodne wymiary dla mnozenia");
            return 1;
        }
        pomnoz(A, B, C, wA, kA, kB);
        wC = wA;
        kC = kB;
        printf(" A * B: \n");
        wypisz(C, wA, kB);
        break;
    default:
        printf("Nieznana Operacja");
        return 1;
    }
    if (zapisz_macierz("C.txt", C, wC, kC) != OK)
    {
        printf("Blad zapisu wyniku do pliku\n");
        return 1;
    }
    printf("Wynik zostal zapisany do pliku C.txt\n");
    return 0;
}