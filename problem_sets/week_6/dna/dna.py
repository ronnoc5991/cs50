import csv
import sys


def main():

    if not len(sys.argv) == 3:
        sys.exit("Please provide both a file containing the STR counts and a DNA sequence to ID.")

    people = []
    sequence = ''
    str_names = []
    sequence_str_lengths = {}

    with open(sys.argv[1]) as csvfile:
        reader = csv.DictReader(csvfile)

        for row in reader:
            people.append(row)
        
        str_names = reader.fieldnames
        str_names.pop(0)
        
        for str_name in str_names:
            sequence_str_lengths[str_name] = 0


    with open(sys.argv[2]) as sequencefile:
        sequence = sequencefile.read().rstrip()

    for str in str_names:
        sequence_str_lengths[str] = longest_match(sequence, str)

    for person in people:
        is_match = True
        for str in str_names:
            if not int(person[str]) == sequence_str_lengths[str]:
                is_match = False
                break
        if is_match:
            print("Match found: ", person['name'])
            return

    print("No match found!")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
