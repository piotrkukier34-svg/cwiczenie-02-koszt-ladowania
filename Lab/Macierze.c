#include <stdio.h>
#define MAX 20

int main()
{
    int wA = 2, kA = 3;
    double A[MAX][MAX] = {
        {1.0, 2.0, 3.0},
        {3.0, 5.0, 6.0}};
    int i, j;
    for (i = 0; i < wA; i++)
    {
        for (j = 0; j < kA; j++)
        {
            printf("%8.2lf", A[i][j]);
        }
        printf("\n");
    }
    return 0;
}
