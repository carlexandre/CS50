#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");

    uint8_t buffer[4];

    fread(&buffer, 1, 4, f);

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", buffer[i]);
    }

    fclose(f);
}
