# Wordle-Solver
A program that helps a user solve a wordle problem!

## Program Purpose
The purpose of this program is to filter out guesses that a user has inputted while using algorithms to search for a probable solution for the wordle.

## Layout and Structure 
The program is split into 5 functions
1. Score letter
2. Score word
3. Filter vocabulary gray
4. Filter vocabulary yellow
5. Filter vocabulary green

## Program Description
1. Score letter will loop over the vocabulary and return the number of words in which that particular letter occurs.
2. Score word will calculate the score for a given word by adding up the values of the characters present in the words, from 1-26, and does not count duplicates.
3. Filter vocabulary gray will filter down the vocabualry based on the knowledge that the specified letter *does not occur* in the secret word.
4. Filter vocabulary yellow will filter down the vocabulary based on the knowledge that the specified letter occurs in the word, *but not at this particular position*.
5. Filter vocabulary green will filter down the vocabulary based on the knowledge that the specified letter *definitely* occurs as the specified position
