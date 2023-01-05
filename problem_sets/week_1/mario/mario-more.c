#include <stdio.h>

void print_character(char character, int number);

int main(void)
{
    int userInput;

    do
    {
        printf("Height: ");
        scanf("%d", &userInput);
    } while (userInput < 1 || userInput > 8);

    for (int rowNumber = 1; rowNumber <= userInput; rowNumber++)
    {
        int paddingSpaces = userInput - rowNumber;
        print_character(' ', paddingSpaces);
        print_character('#', rowNumber);
        print_character(' ', 2);
        print_character('#', rowNumber);
        print_character(' ', paddingSpaces);
        printf("\n");
    }
}

void print_character(char character, int number)
{
    for (int i = number; i > 0; i--)
    {
        printf("%c", character);
    }
}