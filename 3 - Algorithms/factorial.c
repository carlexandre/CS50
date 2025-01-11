#include <cs50.h>
#include <stdio.h>

int factorial(int n);

int main(void)
{
    int num = get_int("Number of factorial: ");

    printf("Value of factorial: %i\n",factorial(num));
}

int factorial(int n)
{
    if(n <= 1) return 1;
    else return n * factorial(n-1);
}
