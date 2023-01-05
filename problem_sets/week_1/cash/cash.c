#include <stdio.h>

const int VALUE_OF_QUARTER = 25;
const int VALUE_OF_DIME = 10;
const int VALUE_OF_NICKEL = 5;
const int VALUE_OF_PENNY = 1;

int get_number_of_coins(int cents, int value_of_coin);

int main(void)
{
    int cents = 0;
    int number_of_coins = 0;

    do
    {
        printf("Cents: ");
        scanf("%d", &cents);
    } while (cents < 0);

    int number_of_quarters = get_number_of_coins(cents, VALUE_OF_QUARTER);
    cents -= number_of_quarters * VALUE_OF_QUARTER;
    number_of_coins += number_of_quarters;

    int number_of_dimes = get_number_of_coins(cents, VALUE_OF_DIME);
    cents -= number_of_dimes * VALUE_OF_DIME;
    number_of_coins += number_of_dimes;

    int number_of_nickels = get_number_of_coins(cents, VALUE_OF_NICKEL);
    cents -= number_of_nickels * VALUE_OF_NICKEL;
    number_of_coins += number_of_nickels;

    int number_of_pennies = get_number_of_coins(cents, VALUE_OF_PENNY);
    cents -= number_of_pennies * VALUE_OF_PENNY;
    number_of_coins += number_of_pennies;

    printf("Number of Coins: %d\n", number_of_coins);
}

int get_number_of_coins(int cents, int value_of_coin)
{
    return cents / value_of_coin;
}