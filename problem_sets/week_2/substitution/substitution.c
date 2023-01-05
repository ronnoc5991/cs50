#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH_OF_ALPHABET 26
#define MAX_CHARACTER_COUNT 256

int is_key_valid(char *key);
char *get_plain_text();

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./substition key\n");
        return 1;
    }

    char *key = argv[1];

    if (!is_key_valid(key))
    {
        return 1;
    }

    char *plain_text = get_plain_text();
    char *cipher_text = plain_text;

    int text_length = strlen(plain_text);

    for (int i = 0; i < text_length; i++)
    {
        char plain_char = plain_text[i];

        if (!isalpha(plain_char))
        {
            continue;
        }

        char cipher_char = toupper(key[toupper(plain_char) - 65]);

        if (islower(plain_char))
        {
            cipher_char = tolower(cipher_char);
        }

        cipher_text[i] = cipher_char;
    }

    printf("ciphertext: %s\n", cipher_text);

    return 0;
}

char *get_plain_text()
{
    char *plain_text = malloc(MAX_CHARACTER_COUNT);
    printf("plaintext: ");
    fgets(plain_text, MAX_CHARACTER_COUNT, stdin);
    plain_text[strlen(plain_text) - 1] = 0; // remove new line character
    return plain_text;
}

int is_key_valid(char *key)
{
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 0;
    }

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only contain alphabetic characters.\n");
            return 0;
        }
    }

    char *alphabet = malloc(LENGTH_OF_ALPHABET);

    for (int i = 0; i < (LENGTH_OF_ALPHABET + 1); i++)
    {
        alphabet[i] = 0;
    }

    for (int i = 0; i < LENGTH_OF_ALPHABET; i++)
    {
        alphabet[toupper(key[i]) - 65] = 1;
    }

    int unique_chars_in_key = strlen(alphabet);

    free(alphabet);

    if (unique_chars_in_key != LENGTH_OF_ALPHABET)
    {
        printf("Key must contain 26 unique characters.\n");
        return 0;
    }

    return 1;
}