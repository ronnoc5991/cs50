# Compute the approximate grade level needed to comprehend some text

def is_punctuation_mark(character):
    if character == '.' or character == '!' or character == '?':
        return True
    return False

def is_space(character):
    if character == ' ':
        return True
    return False

text = input("What text would you like to evaluate? ")

number_of_letters = 0
number_of_words = 0
number_of_sentences = 0

are_in_word = False

for char in text:
    if is_punctuation_mark(char):
        are_in_word = False
        number_of_sentences += 1
        number_of_words += 1
    elif is_space(char):
        if are_in_word:
            number_of_words += 1
            are_in_word = False
    elif char.isalpha():
        are_in_word = True
        number_of_letters += 1

coleman_liau_index = 0.0588 * (number_of_letters / number_of_words * 100) - 0.296 * (number_of_sentences / number_of_words * 100) - 15.8

print(round(coleman_liau_index))