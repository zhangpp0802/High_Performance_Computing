#include <stdio.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "card.h"
#include "handDetection.h"


#define NUM_CARDS 52
#define HAND_CARDS 5

char *getSuitlist(card* hand){
    char *s = calloc(HAND_CARDS,sizeof(char));
    card one = hand[0];
    card two = hand[1];
    card three = hand[2];
    card four = hand[3];
    card five = hand[4];
    s[0] = one.suit;
    s[1] = two.suit;
    s[2] = three.suit;
    s[3] = four.suit;
    s[4] = five.suit;
    return s;
}

int *getRanklist(card* hand){
    int *r = calloc(HAND_CARDS,sizeof(int));
    card one = hand[0];
    card two = hand[1];
    card three = hand[2];
    card four = hand[3];
    card five = hand[4];
    r[0] = one.rank;
    r[1] = two.rank;
    r[2] = three.rank;
    r[3] = four.rank;
    r[4] = five.rank;
    return r;
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// Function to perform Selection Sort
void sort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

int count(int *l, int find){
    int count = 0;
    int i;
    for (i = 0; i<HAND_CARDS;i++){
        if (l[i] == find){
            count ++;
        }
    }
    return count;
}
// hands: Royal flush 0, Straight flush 1, Four of a kind2, Full house3, Flush4, 
// Straight5, Three of a kind6, Two pair7, Pair8, High 9

int determineHand(card* hand){
    if (isRoyalFlush(hand)){
        return 0;
    }
    else if (isStraightFlush(hand)){
        return 1;
    }
    else if (isFourKind(hand)){
        return 2;
    }
    else if (isFullHouse(hand)){
        return 3;
    }
    else if (isFlush(hand)){
        return 4;
    }
    else if (isStraight(hand)){
        return 5;
    }
    else if (isThreeKind(hand)){
        return 6;
    }
    else if (isTwoPair(hand)){
        return 7;
    }
    else if (isPair(hand)){
        return 8;
    }
    else{
        // is high cards
        return 9;
    }
}


int isRoyalFlush(card* hand)
{
	char *s = getSuitlist(hand);
    int *r = getRanklist(hand);
    sort(r,HAND_CARDS);

    if (isFlush(hand) && isStraight(hand)){
        if ((r[0] == 10) &&(r[1] == 11) &&(r[2] == 12) && (r[3] == 13) && (r[4] == 14)){
            return 1;
        }
    }
    return 0;
}

int isStraightFlush(card* hand)
{
	char *s = getSuitlist(hand);
    int *r = getRanklist(hand);
    sort(r,HAND_CARDS);

    if (isFlush(hand) && isStraight(hand)){
        return 1;
    }
    return 0;
}

int isFourKind(card* hand)
{
    int *r = getRanklist(hand);

    if ((count(r,r[0]) == 4) || (count(r,r[1]) == 4)) {
        return 1;
    }
    return 0;
}

int isFullHouse(card* hand)
{
    int *r = getRanklist(hand);

    if ((count(r,r[0]) == 3) || (count(r,r[1]) == 3) || (count(r,r[2]) == 3)) {
        if ((count(r,r[0]) == 2) || (count(r,r[1]) == 2) || (count(r,r[2]) == 2) || (count(r,r[3]) == 2)){
            return 1;}
    }
    return 0;
}

int isFlush(card* hand)
{
	char *s = getSuitlist(hand);

    if ((s[0] == s[1]) && (s[1] == s[2]) &&(s[2]== s[3]) && (s[3]== s[4])){
        return 1;
    }
    return 0;
}

int isStraight(card* hand)
{
	int *r = getRanklist(hand);
    sort(r,HAND_CARDS);
    if ((r[0] == r[1]-1) && (r[1]== r[2]-1) && (r[2]== r[3]-1) && (r[3] == r[4]-1)){
        return 1;
    }
    return 0;
}

int isThreeKind(card* hand)
{
    int *r = getRanklist(hand);

    if ((count(r,r[0]) == 3) || (count(r,r[1]) == 3) || (count(r,r[2]) == 3)) {
        return 1;
    }
    return 0;
}

int isTwoPair(card* hand)
{
    int *r = getRanklist(hand);
    int i;
    int c = 0;
    for (i = 0; i < HAND_CARDS; i++){
        if (count(r,r[i]) == 2) {
            c ++;
        }
    }  
    if (c == 4){
        return 1;}
    else{
        return 0;}
}

int isPair(card* hand)
{
    int *r = getRanklist(hand);
    int i;
    int c = 0;
    for (i = 0; i < HAND_CARDS; i++){
        if (count(r,r[i]) == 2) {
            return 1;
        }
    } 
    return 0; 
}


