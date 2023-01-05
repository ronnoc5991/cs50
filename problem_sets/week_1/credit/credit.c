#include <stdio.h>
#include <math.h>
#include <stdbool.h>

long get_card_number();
bool is_valid_card_number(long card_number);
bool is_american_express(long card_number);
bool is_visa(long card_number);
bool is_mastercard(long card_number);
int get_number_of_digits_in_long(long number);

int main(void)
{
    long card_number = get_card_number();

    bool is_valid = is_valid_card_number(card_number);

    if (!is_valid)
    {
        printf("INVALID\n");
    }
    else if (is_american_express(card_number))
    {
        printf("AMEX\n");
    }
    else if (is_visa(card_number))
    {
        printf("VISA\n");
    }
    else if (is_mastercard(card_number))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("VALID\n");
    }
}

long get_card_number()
{
    long user_input;

    do
    {
        printf("Enter card number: ");
        scanf("%ld", &user_input);
    } while (user_input < 0);

    return user_input;
}

bool is_valid_card_number(long card_number)
{
    int final_sum = 0;
    int digit_count = 0;

    while (card_number > 0)
    {
        int least_significant_digit = card_number % 10;
        digit_count++;
        card_number /= 10;

        if (digit_count % 2 == 0)
        {
            int sum = 0;
            int digit_multiplied_by_two = least_significant_digit * 2;

            while (digit_multiplied_by_two > 0)
            {
                int last_digit = digit_multiplied_by_two % 10;
                sum += last_digit;
                digit_multiplied_by_two /= 10;
            }
            final_sum += sum;
        }
        else
        {
            final_sum += least_significant_digit;
        }
    }

    return final_sum % 10 == 0;
}

bool is_american_express(long card_number)
{
    int number_of_digits = get_number_of_digits_in_long(card_number);
    int first_two_digits = card_number / pow(10, number_of_digits - 2);
    return first_two_digits == 34 || first_two_digits == 37;
}

bool is_visa(long card_number)
{
    int number_of_digits = get_number_of_digits_in_long(card_number);
    int first_digit = card_number / pow(10, number_of_digits - 1);
    return first_digit == 4;
}

bool is_mastercard(long card_number)
{
    int number_of_digits = get_number_of_digits_in_long(card_number);
    int first_two_digits = card_number / pow(10, number_of_digits - 2);
    return first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 || first_two_digits == 54 || first_two_digits == 55;
}

int get_number_of_digits_in_long(long number)
{
    int length = 0;

    do
    {
        number /= 10;
        ++length;
    } while (number != 0);

    return length;
}