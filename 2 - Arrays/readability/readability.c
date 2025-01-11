#include <cs50.h>
#include <stdio.h>
#include <string.h>

int letters(string l);
int words(string w);
int sentences(string s);
int approximate(float any);

int main(void){

    string text = get_string("Text: ");

    int ql = letters(text);
    int qw = words(text);
    int qs = sentences(text);

    float L = ((float) ql/qw) * 100;
    float S = ((float) qs/qw) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    index = approximate(index);

    if(index < 1) printf("Before Grade 1\n");
    else if(index > 16) printf("Grade 16+\n");
    else printf("Grade %i\n", (int) index);

}

int letters(string l){

    int total = 0;

    for(int i = 0, len = strlen(l); i < len; i++){
        if((l[i] >= 'A' || l[i] >= 'a') && (l[i] <= 'Z' || l[i] <= 'z')) total++;
    }

    return total;
}

int words(string w){
    int total = 1;

    for(int i = 0, len = strlen(w); i < len; i++){
        if(w[i] == ' ') total++;
    }

    return total;
}

int sentences(string s){
    int total = 0;

    for(int i = 0, len = strlen(s); i < len; i++){
        if(s[i] == '?' || s[i] == '.' || s[i] == '!') total++;
    }

    return total;
}

int approximate(float any){

    any *= 1000;

    int number = any/1000;

    if ( (int) any%1000 > 500) number++;

    return number;
}
