#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  /*As you read the input, if you encounter future cards
   (?0, ?1, ...), you should use add_empty_card to
   create a placeholder in the hand, and then add_future_card
   to make sure you will update it correctly when you draw
   later.  Also remember that you wrote add_card_to
   earlier in this course, as well as card_from_letters
   in Course 2.  These will both be handy here!
   I abstracted out the code to take one single line
   and parse it into a hand*/
  char* line = malloc((strlen(str)+1)*sizeof(*line));
  strcpy(line, str);

  char* oneCard = NULL;
  int countCard = 0;
  card_t tempCard = card_from_num(0);
  long int stringvalue = 0;

  deck_t* hand = malloc(sizeof(*hand));
  hand->cards = NULL;
  hand->n_cards = 0;

  oneCard = strtok(line," ");
  while (oneCard != NULL){
    if(oneCard[0] == '?'){
      stringvalue = strtol(&oneCard[1], NULL, 10);
      add_future_card(fc, stringvalue, add_empty_card(hand));
    }
    else{
      tempCard = card_from_letters(oneCard[0], oneCard[1]);
      add_card_to(hand, tempCard);
    }
    countCard++;
    oneCard = strtok(NULL, " ");
  }

  free(line);

  if (countCard < 5){
    fprintf(stderr, "Not enough number of card passed in!");
    exit(EXIT_FAILURE);
  }
  return hand;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  /*This function reads the input from f.  Recall that the input
   file has one hand per line (and that we represent a hand
   with a deck_t).  You should allocate a deck_t for each hand
   and place it into an array of pointers to deck_ts, which is your
   answer.
   This function needs to tell its caller how many hands it read.
   We could return a struct, but we are going to do this a
   different way: it will fill in *n_hands with the number
   of hands.  This is a bit different, but you have seen it
   before: this is how getline "returns" the string it
   read and the size of the space allocated to that string.*/
  deck_t ** deckarr = NULL;
  size_t n_deckarr = 0;
  char* line = NULL;
  size_t sz = 0;

  while(getline(&line, &sz, f) >= 0){
    if (line[strlen(line)-1] == '\n'){
      line[strlen(line)-1] = '\0';
    }
    deckarr=realloc(deckarr, (n_deckarr+1)*sizeof(*deckarr));
    deckarr[n_deckarr] = hand_from_string(line, fc);
    n_deckarr++;
  }
  free(line);

  *n_hands = n_deckarr;
  return(deckarr);
}
