#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  unsigned num_trials = 10000;
  deck_t** hands = NULL;
  size_t n_hands = 0;
  future_cards_t* fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t* remain_deck = NULL;

  // Check command line arguments/report errors
  if (argc < 2) {
    fprintf(stderr,"Usage: at least 1 argument must be provided. eg ./count_values *file1* (optional)*num_trials*\n");
    return EXIT_FAILURE;
  }

  if (argc > 2) {
    num_trials = (unsigned)strtol(argv[2], NULL, 10);
    if (num_trials < 1) {
      fprintf(stderr,"Number of trials must be at least 1\n");
      return EXIT_FAILURE;
    }
  }

  // Open the input file and read the hands in it
  // (you just wrote read_input!)
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  hands = read_input(f, &n_hands, fc);

  // Create a deck with the remaining cards
  // (you just wrote build_remaining_deck)
  remain_deck = build_remaining_deck(hands, n_hands);

  // Create an array to count how many times each hand
  // wins, with one more element for if there was a tie
  // (so if there are 2 hands, you should have 3 elements).
  unsigned hand_wins[n_hands+1];
  unsigned temp_hand_wins[n_hands+1];

  // and initialize all its values to 0.
  for (int i = 0; i <= n_hands; i++){
    hand_wins[i] = 0;
    temp_hand_wins[i] = 0;
  }

  // Do each Monte Carlo trial (repeat num_trials times)
  for (unsigned mc_trials = 0; mc_trials < num_trials; mc_trials++){
    // Shuffle the deck of remaining cards
    // (you wrote shuffle in Course 3)
    shuffle(remain_deck);

    // Assign unknown cards from the shuffled deck
    // (you just wrote future_cards_from_deck)
    future_cards_from_deck(remain_deck, fc);

    // Use compare_hands (from Course 3) to
    // figure out which hand won. Note that
    // with potentially more than 2 hands,
    // this is much like finding the max of
    // an array, but using compare_hands
    // instead of >.

    for (int i = 0; i <= n_hands; i++){
      temp_hand_wins[i] = 0;
    }

    for (int i = 0; i < n_hands-1; i++){
      for (int j = i+1; j < n_hands;j++){
	int result = compare_hands(hands[i], hands[j]);

	// Increment the win count for the winning
	//  hand (or for the "ties" element of the array
	//  if there was a tie).
	if (result > 0){ // hand 1 win
	  temp_hand_wins[i]++;
	}
	else if(result < 0){ // hand 2 win
	  temp_hand_wins[j]++;
	}
	else{ // tie
	  temp_hand_wins[n_hands]++;
	}
      }
    }

    int win_hand_ind = 0;
    int win_hand_val = 0;
    for (int i = 0; i < n_hands; i++){
      if (temp_hand_wins[i] > win_hand_val){
	win_hand_ind = i;
	win_hand_val = temp_hand_wins[i];
      }
    }

    if (temp_hand_wins[n_hands] >= win_hand_val){
      hand_wins[n_hands]++;
    }
    else{
      hand_wins[win_hand_ind]++;
    }
  }

  // After you do all your trials, you just need
  // to print your results,
  // You should use the following format strings to report your results.
  // For each hand, you should printf
  // "Hand %zu won %u / %u times (%.2f%%)\n"
  // where the %zu is the hand number (0,1,..)  [zu is for size_t]
  // the first %u is the number of wins for that hand
  // the second %u is the total number of trials
  // the %.2f is the percentage that this win/trials ratio gives
  for (size_t i = 0; i < n_hands; i++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, hand_wins[i], num_trials, (float)hand_wins[i]*100/(float)num_trials);
  }

  // Then you should printf one more line for the ties:
  // "And there were %u ties\n"
  // Where the %u is just a count of how many ties there were
  printf("And there were %u ties\n", hand_wins[n_hands]);

  // free any memory you allocated
  for (int i = 0; i < fc->n_decks; i++){
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);

  for (int i = 0; i < n_hands; i++){
    free_deck(hands[i]);
  }
  free(hands);

  free_deck(remain_deck);

  // close any open files
  if(fclose(f) != 0){
    perror("Failed to close file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
