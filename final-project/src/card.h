

#ifndef CARD_H
#define CARD_H

typedef struct
{
    int rank;
    char suit;   
} card;

char *card_tostring(card c);
int get_rank(card c);
int get_suit(card c);
card card_new(char suit, int rank);
void shuffle(card *array, size_t n);
card *generate_new_deck();
// int main();
card *getAHand(card* deck, int n);

#endif