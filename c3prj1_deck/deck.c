#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

#define TOTAL_CARDS 52

void print_hand(deck_t * hand){
  for (int i = 0; i < hand->n_cards; i++){
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  int i = 0;
  while(i < d->n_cards){
    if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit){
      return 1;
    }
    i++;
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t swapcard;
  unsigned swapind;
  for (int i=0;i<d->n_cards/2;i++){
    swapind = rand()%(d->n_cards);
    swapcard = *d->cards[swapind];
    *d->cards[swapind] = *d->cards[i];
    *d->cards[i] = swapcard;
  }
}

void assert_full_deck(deck_t * d) {
  for (int i = 0; i < 52; i++){
    assert(deck_contains(d,card_from_num(i)));
  }
}

void add_card_to(deck_t * deck, card_t c){
  /* Add the particular card to the given deck (which will
     involve reallocing the array of cards in that deck*/
  deck->cards = realloc(deck->cards, (deck->n_cards+1)*sizeof(*deck->cards));
  deck->cards[deck->n_cards] = malloc(sizeof(**deck->cards));
  deck->cards[deck->n_cards]->value = c.value;
  deck->cards[deck->n_cards]->suit = c.suit;
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck){
  /* Add a card whose value and suit are both 0, and return a pointer
  to it in the deck. 
  This will add an invalid card to use as a placeholder
  for an unknown card.*/
  card_t tempCard = {0,0};
  add_card_to(deck, tempCard);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  /* Create a deck that is full EXCEPT for all the cards
   that appear in excluded_cards.  For example,
   if excluded_cards has Kh and Qs, you would create
   a deck with 50 cards---all of them except Kh and Qs.
   You will need to use malloc to allocate this deck.
   (You will want this for the next function).
   Don't forget you wrote card_t card_from_num(unsigned c)
   in Course 2 and int deck_contains(deck_t * d, card_t c)
   in Course 3!  They might be useful here.*/

  deck_t* deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;

  card_t tempCard = card_from_num(0);

  for (int i = 0; i < TOTAL_CARDS; i++){
    // create one card from 52 possible cards
    tempCard = card_from_num(i);

    if(!deck_contains(excluded_cards, tempCard)){
      add_card_to(deck, tempCard);
    }
  }

  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  /*This function takes an array of hands (remember
   that we use deck_t to represent a hand).  It then builds
   the deck of cards that remain after those cards have
   been removed from a full deck.  For example, if we have
   two hands:
      Kh Qs ?0 ?1 ?2 ?3 ?4
      As Ac ?0 ?1 ?2 ?3 ?4
   then this function should build a deck with 48
   cards (all but As Ac Kh Qs).  You can just build
   one deck with all the cards from all the hands
   (remember you just wrote add_card_to),
   and then pass it to make_deck_exclude.*/

  deck_t* excluded_cards = malloc(sizeof(*excluded_cards));
  excluded_cards->cards = NULL;
  excluded_cards->n_cards = 0;

  for (int i = 0; i < n_hands; i++){
    for (int j = 0; j < hands[i]->n_cards; j++){
      add_card_to(excluded_cards, *hands[i]->cards[j]);
    }
  }

  deck_t* deck = make_deck_exclude(excluded_cards);
  free_deck(excluded_cards);
  return deck;
}

void free_deck(deck_t * deck){
  /*Free the memory allocated to a deck of cards.
   For example, if you do
     deck_t * d = make_excluded_deck(something);
     free_deck(d);
   it should free all the memory allocated by make_excluded_deck.
   Once you have written it, add calls to free_deck anywhere you
   need to to avoid memory leaks.*/
  for(int i = 0; i < deck->n_cards; i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
