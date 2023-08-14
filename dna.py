import csv
import re
import sys

def main():

    # Check for proper usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Open files
    data = csv.DictReader(open(sys.argv[1]))
    sequence = open(sys.argv[2]).read()

    # Get counts for each of the STRs
    counts = {}
    for subseq in data.fieldnames[1:]:
        counts[subseq] = longest_match(sequence, subseq)

    # Check each row for a matching profile
    for row in data:
        if all(counts[subseq] == int(row[subseq]) for subseq in counts):
            print(row["name"])
            return

    # No row matched
    print("No match")


def longest_match(sequence, subseq):
    """Returns length of longest run of subseq in sequence."""
    length = len(subseq)
    runs = {}
    best = 0

    # Look at all possible subsequences
    for i in range(len(sequence) - length + 1):

        # If subsequence matches, keep track of longest run
        if sequence[i:i + length] == subseq:
            runs[i] = runs.get(i - length, 0) + 1
            best = max(best, runs[i])

    return best

if __name__ == "__main__":
    main()
