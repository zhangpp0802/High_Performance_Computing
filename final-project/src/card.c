#include <stdio.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"


#define NUM_CARDS 52
#define HAND_CARDS 5

char *card_tostring(card c)
{
    char *card_value;
    char *card_suit;
    char *retval = NULL;

    switch (c.rank)
    {
	case 2:
		card_value = "Two ";
		break;
	case 3:
		card_value = "Three ";
		break;
	case 4:
		card_value = "Four ";
		break;
	case 5:
		card_value = "Five ";
		break;
	case 6:
		card_value = "Six ";
		break;
	case 7:
		card_value = "Seven ";
		break;
	case 8:
		card_value = "Eight ";
		break;
	case 9:
		card_value = "Nine ";
		break;
	case 10:
		card_value = "Ten ";
		break;
	case 11:
		card_value = "Jack ";
		break;
	case 12:
		card_value = "Queen ";
		break;
	case 13:
		card_value = "King ";
		break;
	case 14:
		card_value = "Ace ";
		break;
    }

    if (c.suit == 'd') card_suit = "Diamonds";
    if (c.suit == 'c') card_suit = "Clubs";
    if (c.suit == 's') card_suit = "Spades";
    if (c.suit == 'h') card_suit = "Hearts";

    retval = (char*) malloc (sizeof(char) * (strlen(card_value) + strlen(card_suit) + 5)); //magic number 5 is to put in " of " and \0.
	// retval = card_value + card_suit;
	strcpy(retval, card_value);
    strcat(retval, card_suit);
    // printf("%s of %s", card_value, card_suit);
	return retval;


};

int get_rank(card c){
	return c.rank;
}

int get_suit(card c){
	return c.suit;
}


card card_new(char suit, int rank)
{
	card c;

	c.suit = suit;
	c.rank = rank;

	return c;
}

int rand_comparison(const void *a, const void *b)
{
    (void)a; (void)b;

    return rand() % 2 ? +1 : -1;
}

card *generate_new_deck()
{
	int i;
    card *deck_array = calloc(NUM_CARDS,sizeof(card));
	// int a, b;
	// card *tmp;

	for (i = 0; i < 13; i ++){
		// printf("%d", i+1);
        deck_array[i*4] = card_new('d', i+2);
		// card_tostring(deck_array[i*4]);
        deck_array[i*4+1] = card_new('c', i+2);
        deck_array[i*4+2] = card_new('s', i+2);
        deck_array[i*4+3] = card_new('h', i+2);
    }
	shuffle(deck_array, NUM_CARDS);
    return deck_array;

}

void shuffle(card *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          card t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void printList(card *hand, int n){
	int k;
    for (k = 0; k < n; k++){
        card_tostring(hand[k]);
		printf("\n");
    }
}

int equals(card a, card b){
	if ((a.rank == b.rank) && (a.suit == b.suit)){
		return 1;
	}
	return 0;
}

card *getAHand(card* deck, int n){
	card *hand = calloc(5,sizeof(card));
	hand[0] = deck[rand() % NUM_CARDS];
	hand[1] = deck[rand() % NUM_CARDS];
	hand[2] = deck[rand() % NUM_CARDS];
	hand[3] = deck[rand() % NUM_CARDS];
	hand[4] = deck[rand() % NUM_CARDS];
	return hand;

}

// int main(){
// 	// char s = 'd';
// 	// int r = 14;
// 	// card c = card_new(s,r);
// 	// card_tostring(c);
// 	card *deck = calloc(NUM_CARDS,sizeof(card));
// 	deck = generate_new_deck();
// 	// int k;
//     // for (k = 0; k < NUM_CARDS; k++){
//     //     card_tostring(deck[k]);
// 	// 	printf("\n");
//     // }
// 	card *hand = calloc(HAND_CARDS,sizeof(card));
// 	hand = getAHand(deck,HAND_CARDS);
// 	int k;
//     for (k = 0; k < HAND_CARDS; k++){
//         card_tostring(hand[k]);
// 		printf("\n");
//     }
// 	return 0;
// }
