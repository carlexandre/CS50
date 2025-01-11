#include <cs50.h>
#include <stdio.h>

int main(void){

    string name = get_string("What's your name? ");
    int age =  get_int("What's your age? ");
    string number = get_string("What's your number? ");

    printf("Name: %s\n", name);
    printf("Age: %i\n", age);
    printf("Number: %s", number);
}
