#include <cs50.h>
#include <stdio.h>

int main(void){

    int sequence[5];

    for(int i = 0; i < 5; i++){
        if(i == 0) sequence[0] = 1;
        else sequence[i] = sequence[i-1]*2;
        printf("%i ", sequence[i]);
    }
    printf("\n");
}
