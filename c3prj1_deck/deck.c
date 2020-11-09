#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

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
  for (int i=0;i<d->n_cards;i++){
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
