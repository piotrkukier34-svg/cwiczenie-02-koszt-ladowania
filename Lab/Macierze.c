#include <stdio.h>
#define MAX 20

int main()
{
    int wA = 2, kA = 2;
    int wB = 2, kB = 2;
    double A[MAX][MAX] = {
        {1.0, 2.0},
        {3.0, 4.0}};
    double B[MAX][MAX] = {
        {5.0, 6.0},
        {7.0, 8.0}};
    double C[MAX][MAX];
    if (wA < 1 || wA > MAX || kA < 1 || kA > MAX ||
        wB < 1 || wB > MAX || kB < 1 || kB > MAX)
    {
        printf("Blad: wymiary poza zakresem\n");
        return 1;
    }
    if (wA != wB || kA != kB)
    {
        printf("Blad: niezgodne wymiary\n");
        return 1;
    }
    int i, j;
    int operacja;
    printf("wybierz Operecja:\n");
    printf("1. Dodawanie (+)\n");
    printf("2. Odejmowanie\n");
    scanf("%d", &operacja);
    switch (operacja)
    {
    case 1:
        printf("Suma A + B:\n");
        for (i = 0; i < wA; i++)
        {
            for (j = 0; j < kA; j++)
            {
                C[i][j] = A[i][j] + B[i][j];
                printf("%8.2lf", C[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        break;

    case 2:
        printf("Roznoca A - B:\n");
        for (i = 0; i < wA; i++)
        {
            for (j = 0; j < kA; j++)
            {
                C[i][j] = A[i][j] - B[i][j];
                printf("%8.2lf", C[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        break;

        default: printf("Nieznana Operacja");
        return 0;
    }
}
