#include <stdio.h>

const int NUMBER_OF_COIN_VARIANTS = 4;
const int COIN_VALUES[] = { 25, 10, 5, 1 };

int get_number_of_coins(int cents, int value_of_coin);

int main(void)
{
    int cents;
    int number_of_coins = 0;

    do
    {
        printf("Cents: ");
        scanf("%d", &cents);
    } while (cents < 0);

    for (int i = 0; i < NUMBER_OF_COIN_VARIANTS; i ++)
    {
        int coin_variant_count = get_number_of_coins(cents, COIN_VALUES[i]);
        cents -= coin_variant_count * COIN_VALUES[i];
        number_of_coins += coin_variant_count;
    }

    printf("Number of Coins: %d\n", number_of_coins);
}

int get_number_of_coins(int cents, int value_of_coin)
{
    return cents / value_of_coin;
}