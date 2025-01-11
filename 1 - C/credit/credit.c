#include <stdio.h>
#include <cs50.h>

bool valid(long int num);

int main(void){

    long int number = get_long("What's your credit card number? ");
    int c = 0, d_init = 0, sec_digt = 0;

    bool v = valid(number);

    while(number>0){
        if(number>=10 && number<100) sec_digt = number;
        d_init = number%10;
        number /= 10;
        c += 1;
    }

    if (c<13 || c>16) printf("INVALID\n");

    else{

        if (c == 15 && (sec_digt == 34 || sec_digt == 37)) printf("AMEX\n");

        else if(c == 16 && (sec_digt == 51 || sec_digt == 52 || sec_digt == 53 || sec_digt == 54 || sec_digt == 55)) printf("MASTERCARD\n");

        else if ((c == 13 || c == 16) && d_init == 4 && v) printf("VISA\n");

        else printf("INVALID\n");
    }
}

bool valid(long int num){
    int sum = 0, sum2 = 0, digit, j = 2;

    while(num>0){
        digit = num%10;
        num = num/10 ;

        if (j % 2 == 0) sum2 += digit;
        else if (j % 2 == 1){
            if(digit*2>9) sum += digit*2 - 9;
            else sum += digit*2;
        }
        j += 1;
    }

    sum += sum2;

    if (sum%10 == 0) return true;
    else return false;
}

