#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"

void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  case NOTHING: return "NOTHING";
  default: return "";
  }
}

char value_letter(card_t c) {
  switch(c.value){
  case 10: return '0';
  case VALUE_JACK: return 'J';
  case VALUE_QUEEN: return 'Q';
  case VALUE_KING: return 'K';
  case VALUE_ACE: return 'A';
  default: return '0'+c.value;
  }
}

char suit_letter(card_t c) {
  switch(c.suit){
  case SPADES: return 's';
  case HEARTS: return 'h';
  case DIAMONDS: return 'd';
  case CLUBS: return 'c';
  default: return '\0';
  }
}

void print_card(card_t c) {
  printf("%c%c",value_letter(c),suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t retCard;
  unsigned cvalue = 0;
  suit_t csuit = 0;
  switch(value_let){
  case '0':
    cvalue = 10;
    break;
  case 'J':
    cvalue = VALUE_JACK;
    break;
  case 'Q':
    cvalue = VALUE_QUEEN;
    break;
  case 'K':
    cvalue = VALUE_KING;
    break;
  case 'A':
    cvalue = VALUE_ACE;
    break;
  default:
    cvalue = value_let - '0';
    break;
  }

  switch(suit_let){
  case 's':
    csuit = SPADES;
    break;
  case 'h':
    csuit = HEARTS;
    break;
  case 'd':
    csuit = DIAMONDS;
    break;
  case 'c':
    csuit = CLUBS;
    break;
  default:
    csuit = suit_let - '0';
    break;
  }
  retCard.value = cvalue;
  retCard.suit = csuit;
  assert_card_valid(retCard);
  return retCard;
}

card_t card_from_num(unsigned c) {
  assert(c >= 0 && c < 52);
  unsigned cvalue = (c)%13;
  unsigned csuit = (c)/13;
  if (cvalue == 0) cvalue = 13; // 0 not used
  if (cvalue == 1) cvalue = 14; // 1 not used

  card_t retCard = {cvalue,csuit};
  assert_card_valid(retCard);
  return retCard;
}
