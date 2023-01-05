#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef uint8_t byte;

char *get_file_name(int image_count)
{
    char *file_name = malloc(sizeof(char) * 9);
    int hundreds = (image_count / 100) % 10;
    int tens = (image_count / 10) % 10;
    int ones = image_count % 10;
    file_name[0] = hundreds + 48;
    file_name[1] = tens + 48;
    file_name[2] = ones + 48;
    file_name[3] = '.';
    file_name[4] = 'j';
    file_name[5] = 'p';
    file_name[6] = 'e';
    file_name[7] = 'g';
    file_name[8] = '\0';
    return file_name;
}

int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     printf("Usage: ./recover file\n");
    //     return 1;
    // }

    // char *input = argv[1];
    char *input = "card.raw";

    FILE *fp = fopen(input, "r");

    if (fp == NULL)
    {
        printf("Unable to open file: %s\n", input);
        return 1;
    }

    int image_count = 0;
    FILE *current_image;
    byte buffer[BLOCK_SIZE];
    int in_image = 0;

    while (fread(buffer, sizeof(byte), BLOCK_SIZE, fp) == sizeof(byte) * BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >> 4) == 0x0e)
        {
            if (in_image) 
                fclose(current_image);
            in_image = 1;
            image_count++;
            char *new_file_name = get_file_name(image_count);
            current_image = fopen(new_file_name, "a");
        }

        if (in_image)
            fwrite(buffer, sizeof(byte), BLOCK_SIZE, current_image);
    }

    fclose(current_image);
    fclose(fp);

    return 0;
}