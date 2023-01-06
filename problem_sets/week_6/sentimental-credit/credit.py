# Check whether a credit card number is valid

credit_card_number_string = input("What number would you like to test? ")

digits = [int(d) for d in credit_card_number_string]

number_of_digits = len(digits)

sum_of_product_digits = 0

for i in range(number_of_digits - 2, -1, -2):
    product = digits[i] * 2
    for j in str(product):
        sum_of_product_digits += int(j)

sum_of_other_digits = 0

for i in range(number_of_digits - 1, -1, -2):
    sum_of_other_digits += digits[i]

is_valid = (sum_of_product_digits + sum_of_other_digits) % 10 == 0

if is_valid:
    print("The number is valid!")
else:
    print("The number is not valid!")