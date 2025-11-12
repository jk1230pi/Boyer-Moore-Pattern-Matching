# Boyer-Moore-Pattern-Matching
Project Title: Boyer–Moore String Matching Algorithm
Language Used: C

Description:
This project implements the Boyer–Moore string matching algorithm to search for a specific pattern within a large text file.
The algorithm is based on two heuristics – the Bad Character Rule and the Good Suffix Rule – which allow it to skip unnecessary comparisons and perform efficient pattern searching.
It is faster than the naive string matching approach, especially for long texts and patterns.

Files Used:

boyer_moore.c : Main source code file containing the implementation of the algorithm.

data.txt : Dataset file containing the text (The Adventures of Sherlock Holmes from Project Gutenberg).

pattern.txt : File containing the pattern or word to be searched in the dataset.

boyer_moore.exe : Executable file created after compiling the source code.

Steps to Run the Program:

Open the command prompt or PowerShell.

Navigate to the folder containing the files.

Compile the code using the command:
gcc boyer_moore.c -o boyer_moore

Run the program using:
.\boyer_moore

The program reads the dataset from data.txt and the pattern from pattern.txt.

It then displays:

Total occurrences of the pattern

Positions of matches

Number of character comparisons

Execution time in milliseconds

Example Input:
pattern.txt → Holmes

Example Output:
Pattern found 87 time(s).
Total character comparisons: 1245
Execution time: 5.321 ms

Dataset Source:
The Adventures of Sherlock Holmes – Project Gutenberg (https://www.gutenberg.org/files/1661/1661-0.txt
)

Created by: Lakshya
