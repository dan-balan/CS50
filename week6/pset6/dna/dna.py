"""
A program that identifies a person based on their DNA
Usage: python dna.py databases/large.csv sequences/5.txt
Short Tandem Repeats (STRs)
DNA bases nucleotides: bases: adenine (A), cytosine (C), guanine (G), or thymine (T).
repetitions of different STR(s)

"""

import csv
import sys
import re


def main():
    """ """

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read DNA database into memory from file
    dna_database = []
    filename = sys.argv[1]
    with open(filename, "r") as file:
        reader = csv.DictReader(file)
        for individualsDna in reader:
            for key, val in individualsDna.items():
                if key != "name":
                    individualsDna[key] = int(individualsDna[key])
            dna_database.append(individualsDna)

    # Read individual DNA sequence
    dna_filename = sys.argv[2]
    with open(dna_filename, 'r') as f:
        read_data = f.read()

    # print(read_data) # debug :)

    # a list with analysed STR(s) based on DNA database
    dna_profiling = []
    for key in dna_database[0].keys():
        if key != 'name':
            dna_profiling.append(key)

    # parsing the STR(s) of given DNA sequence
    dna_bases_dict = {}
    for dnabase in dna_profiling:
        stroccurrence = find_dna_pattern(read_data, dnabase)
        dna_bases_dict[dnabase] = stroccurrence
        # print(stroccurrence)

    """
    # debug :)
    for dnabase in dna_bases_dict.keys():
        print(f'{dnabase} : {dna_bases_dict[dnabase]}')
    """

    # return the name of match DNA/individual from DNA database
    found = False
    for individual in dna_database:
        for key in dna_profiling:
            if dna_bases_dict[key] != individual[key]:
                found = False
                break
            found = True
        if found:
            print(individual['name'])
            break
    if not found:
        print('No match')


def find_dna_pattern(dna_sequence, dna_str):
    """  """

    pattern = '(?:' + dna_str + ')+'
    dnastr_occurrences = re.findall(pattern, dna_sequence)
    if len(dnastr_occurrences) != 0:
        repetitions = len(max(dnastr_occurrences, key=len))
    return 0 if len(dnastr_occurrences) == 0 else repetitions // len(dna_str)


if __name__ == "__main__":
    main()