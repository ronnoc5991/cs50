#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_WORD_LENGTH = 15;

char *get_word_from_player();
int get_score_from_word(char *word);
int get_point_value_for_letter(char letter);

int main(void)
{
    char *player_one_word = get_word_from_player("Player One");
    char *player_two_word = get_word_from_player("Player Two");

    int player_one_score = get_score_from_word(player_one_word);
    int player_two_score = get_score_from_word(player_two_word);

    if (player_one_score > player_two_score)
    {
        printf("Player 1 Wins!");
    }
    else if (player_one_score < player_two_score)
    {
        printf("Player 2 Wins!");
    }
    else
    {
        printf("Tie!");
    }
}

char *get_word_from_player(char player_name[])
{
    char *word = malloc(MAX_WORD_LENGTH);
    printf("%s: ", player_name);
    scanf("%s", word);
    return word;
}

int get_score_from_word(char *word)
{
    int score = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {
        score += get_point_value_for_letter(word[i]);
    }

    return score;
}

int get_point_value_for_letter(char letter)
{
    switch (letter)
    {
    case 'a':
    case 'A':
        return 1;
    case 'b':
    case 'B':
        return 3;
    case 'c':
    case 'C':
        return 3;
    case 'd':
    case 'D':
        return 2;
    case 'e':
    case 'E':
        return 1;
    case 'f':
    case 'F':
        return 4;
    case 'g':
    case 'G':
        return 2;
    case 'h':
    case 'H':
        return 4;
    case 'i':
    case 'I':
        return 1;
    case 'j':
    case 'J':
        return 8;
    case 'k':
    case 'K':
        return 5;
    case 'l':
    case 'L':
        return 1;
    case 'm':
    case 'M':
        return 3;
    case 'n':
    case 'N':
        return 1;
    case 'o':
    case 'O':
        return 1;
    case 'p':
    case 'P':
        return 3;
    case 'q':
    case 'Q':
        return 10;
    case 'r':
    case 'R':
        return 1;
    case 's':
    case 'S':
        return 1;
    case 't':
    case 'T':
        return 1;
    case 'u':
    case 'U':
        return 1;
    case 'v':
    case 'V':
        return 4;
    case 'w':
    case 'W':
        return 4;
    case 'x':
    case 'X':
        return 8;
    case 'y':
    case 'Y':
        return 4;
    case 'z':
    case 'Z':
        return 10;
    default:
        return 0;
    }
}