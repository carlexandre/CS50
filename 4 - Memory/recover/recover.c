#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    uint8_t buffer[512];
    int count = 0;

    char filename[8] = {0};

    FILE *img = NULL;

    while (fread(buffer, 1, 512, card) == 512)
    {
        if ((buffer[0] == 0xFF) && (buffer[1] == 0xD8) && (buffer[2] == 0xFF) && ((buffer[3] & 0xf0) == 0xE0))
        {
            if (count != 0)
                fclose(img);

            sprintf(filename, "%03i.jpg", count++);
            img = fopen(filename, "w");

        }
        if(count > 0)
            fwrite(buffer, sizeof(uint8_t)*512, 1, img);
    }

    fclose(img);
    fclose(card);
}
