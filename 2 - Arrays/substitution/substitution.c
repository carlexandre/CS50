#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string decode(string text, string cipher);

int main(int argc, string argv[]){

    if (argc!=2){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for(int i = 0, len = strlen(argv[1]); i < len; i++){

        if(argv[1][i] < 'A' || argv[1][i] > 'z' || (argv[1][i] > 'Z' && argv[1][i] < 'a')){
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        for(int j = i + 1; j < len - 1; j++){

            if(argv[1][i] == argv[1][j]){
                printf("%c %c", argv[1][i], argv[1][j]);
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = decode(plaintext, argv[1]);

    printf("ciphertext: %s\n", ciphertext);

}

string decode(string text, string cipher){

    for(int i = 0, len = strlen(text); i < len; i++){
        if (text[i] >= 65 && text[i] <= 90) text[i] = toupper(cipher[text[i] - 65]);
        else if (text[i] >= 97 && text[i] <= 122) text[i] = tolower(cipher[text[i] - 97]);
    }

    return text;
}
