#include <stdio.h>
#include <cs50.h>

void hash(int end);

int main(void){

    int h;

    do{
        h = get_int("Height: ");
    }
    while(h<1 || h>8);

    int t = h - 1;

    for(int i = 0; i < h; i++){

        for(int j = 0; j < t; j++){
            printf(" ");
        }

        hash(h-t);
        printf("  ");
        hash(h-t);

        printf("\n");
        t--;
    }
}

void hash(int end){
    for(int i = 0; i < end; i++){
        printf("#");
    }
}
