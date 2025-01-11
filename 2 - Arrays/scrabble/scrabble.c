#include <cs50.h>
#include <stdio.h>
#include <ctype.h> // TO USE TOUPPER()
#include <string.h> // TO USE STRLEN()

int sumletters(string a);

int main(void){

    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int sum1, sum2;

    sum1 = sumletters(player1);
    sum2 = sumletters(player2);

    if(sum1 > sum2) printf("Player 1 wins!\n");

    else if(sum2 > sum1) printf("Player 2 wins!\nn");

    else printf("Tie!\n");
}

int sumletters(string a){

    int sum = 0;

    for(int i = 0, len = strlen(a); i < len; i++){

        int scores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
        int ascii[26] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
        for(int j = 0; j < 26; j++){
            if(toupper(a[i]) == ascii[j]) sum += scores[j];
        }
    }

    return sum;

}
