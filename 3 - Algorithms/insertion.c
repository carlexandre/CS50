#include <stdio.h>

void insertionsort(int v[], int n);

int main(void)
{
    int n = 10;

    int vetor[n];

    for (int i = 0; i < n; i++)
    {
        printf("Digite um número: ");
        scanf("%i", &vetor[i]);
    }

    insertionsort(vetor, n);

    for (int i = 0; i < 10; i++)
    {
        printf("%i°: %i\n", i+1, vetor[i]);
    }
}

void insertionsort(int v[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int x, j;
        x = v[i];
        j = i;

        while (j > 0 && x < v[j - 1])
        {
            v[j] = v[j - 1];
            j--;
        }

        v[j] = x;
    }
}
