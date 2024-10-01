#include "search_util.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// This function loops over the vocabulary.txt
// and returns the number of words in which that particular letter
// occurs. So if there are 10 words containing the letter 'y' for the particular
// vocabulary, then this function will return 10.
int score_letter(char letter, char **vocabulary, size_t num_words) {
  int wordAmount = 0; 
  for (size_t i = 0; i < num_words; i++){
    if (vocabulary[i] == NULL) {
      continue;
    }
    if (strchr(vocabulary[i], letter) != NULL) {
      wordAmount++;
      }
    }
  return wordAmount;
}


// Calculates the score for a given word, where the letter_scores array 
// is guaranteed to be of length 26. Slot 0
// contains the score for 'a', and slot 25 contains the score for 'z'.
// The score for a word is the sum of all of the letter scores, *for unique
// letters*. So if the letter 'e' occurs three times, it only contributes to the
// score once.
int score_word(char *word, int *letter_scores) {
  int sumScores = 0;
  bool unique = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < i; j++) {
      if (word[i] == word[j]) {
        unique = 0;
      }
    }
    if (unique == 1) {
      sumScores += letter_scores[word[i] - 'a'];   
    }
  }
  return sumScores;
}

// Returns the most optimal guess
char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter *does not occur* in the secret word. So for any of the words
// in the vocabulary that do contain that letter, free their pointers and set
// the corresponding slot to NULL.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_gray(char letter, char **vocabulary, size_t num_words) {
  int grayCounter = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] != NULL) {
      if (strchr(vocabulary[i], letter) != NULL) {
        free(vocabulary[i]);
        vocabulary[i] = NULL;
        grayCounter++;
      }
    }
  }
  return grayCounter;
}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter occurs in the word, *but not at this particular position*.
// So remove any words that either don't contain the letter at all, or do
// contain it, but at the specified position.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary, size_t num_words) {
  int yellowCounter = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] != NULL) {
      if (vocabulary[i][position] == letter) {
          free(vocabulary[i]); 
          vocabulary[i] = NULL; 
          yellowCounter++;
        }
    if (vocabulary[i] != NULL) {
      if ((strchr(vocabulary[i], letter) == NULL)) {
        free(vocabulary[i]);
        vocabulary[i] = NULL; 
        yellowCounter++;
        }
      }
    }
  }
  return yellowCounter;
}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter *definitely* occurs as the specified position. So remove any
// word that does not contain, for the specified position, the specified letter.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_green(char letter, int position, char **vocabulary, size_t num_words) {
  int greenCounter = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] != NULL) {
      if (vocabulary[i][position] != letter) {
          free(vocabulary[i]); 
          vocabulary[i] = NULL; 
          greenCounter++;
      }
    }
  }
  return greenCounter;
}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
