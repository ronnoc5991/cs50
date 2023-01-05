#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MESSAGE_SIZE 256

int is_only_digits(char *characters);
char *get_plain_text();

int main(int argc, char **argv)
{
    if (argc != 2 || !is_only_digits(argv[1]))
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    int key = atoi(argv[1]);

    char *plain_text = get_plain_text();
    char *cipher_text = plain_text;

    int text_length = strlen(plain_text);

    for (int i = 0; i < text_length; i++)
    {
        char current_char = plain_text[i];

        if (!isalpha(current_char))
        {
            continue;
        }

        int offset = isupper(current_char) ? 65 : 97;

        cipher_text[i] = ((plain_text[i] - offset + key) % 26) + offset;
    }

    printf("ciphertext: %s\n", cipher_text);

    return 0;
}

int is_only_digits(char *characters)
{
    int string_length = strlen(characters);

    for (int i = 0; i < string_length; i++)
    {
        if (characters[i] < 48 || characters[i] > 57)
        {
            return 0;
        }
    }

    return 1;
}

char *get_plain_text()
{
    char *plain_text = malloc(MAX_MESSAGE_SIZE);
    printf("plaintext:  ");
    fgets(plain_text, MAX_MESSAGE_SIZE, stdin);
    plain_text[strlen(plain_text) - 1] = 0; // remove new line char from end of input
    return plain_text;
}