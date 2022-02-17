#ifndef HANDDETECTION_H
#define HANDDETECTION_H

void hand_tostring(card* hand);
int *getRanklist(card* hand);
char *getSuitlist(card* hand);
void sort(int arr[], int n);
int determineHand(card* hand);
int isRoyalFlush(card* hand);
int isStraightFlush(card* hand);
int isFourKind(card* hand);
int isFullHouse(card* hand);
int isFlush(card* hand);
int isStraight(card* hand);
int isThreeKind(card* hand);
int isTwoPair(card* hand);
int isPair(card* hand);


#endif