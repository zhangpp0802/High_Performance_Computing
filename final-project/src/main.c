
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <omp.h>
#include <math.h>  

#include "card.h"
#include "handDetection.h"

#define NUM_CARDS 52
#define HAND_CARDS 5
#define KINDS 10


// Num of combinations:
// Royal flush: 4
// Straight flush: 32
// Four a kind: 624
// Full house: 3744
// Flush: 5112
// Straight: 9180
// Three a kind: 54,912
// Two pair: 123,552
// Pair: 1,098,240
// High: 1303560

// make to compile
// ./poker to run


void hand_tostring(card* hand)
{
    int k;
    // char *retval = (char*) malloc (sizeof(char) * (strlen(card_value) + strlen(card_suit) + 5)*HAND_CARDS);
    for (k = 0; k < HAND_CARDS; k++){
        char *out = card_tostring(hand[k]);
		printf("| %s ",out);
    }
	printf("\n");

}

int *possibilities(card *deck, int nthreads){
	int *keeptrack = calloc(KINDS,sizeof(int));
	int i,j,k,m,n;
	#pragma omp parallel num_threads(nthreads) private(i,j,k,m,n)
	for (i = 0; i <NUM_CARDS;i++){
		for(j = i+1; j<NUM_CARDS;j++){
			for(k = j+1; k<NUM_CARDS;k++){
				for(m = k+1; m<NUM_CARDS;m++){
					for(n = m+1; n<NUM_CARDS;n++){
						card *hand = calloc(HAND_CARDS,sizeof(card));
						hand[0] = deck[i];
						hand[1] = deck[j];
						hand[2] = deck[k];
						hand[3] = deck[m];
						hand[4] = deck[n];
						// hand_tostring(hand);
						int x = determineHand(hand);
						// printf("%d",x);
						keeptrack[x] += 1;
					}
				}
			}
		}
	}
	return keeptrack;
}

int summ(int *numbers, int size){
	int i = 0;
	int sum = 0;
	for(i = 0; i < size; i++){
		sum += numbers[i];
	}
	return sum;
}

double *calculate(int *number, int size){
	int sum = summ(number,size);
	double *types = calloc(size,sizeof(double));
	types[0] = (double)number[0]/sum;
	types[1] = (double)number[1]/sum;
	types[2] = (double)number[2]/sum;
	types[3] = (double)number[3]/sum;
	types[4] = (double)number[4]/sum;
	types[5] = (double)number[5]/sum;
	types[6] = (double)number[6]/sum;
	types[7] = (double)number[7]/sum;
	types[8] = (double)number[8]/sum;
	types[9] = (double)number[9]/sum;
	return types;

}

int countt(int *ranks, int search){
	int i;
	int count = 0;
	for(i = 0; i < HAND_CARDS; i++){
		if(ranks[i] == search){
			count += 1;
		}
	}
	return count;
}

int min(int x, int y)
{
return y ^ ((x ^ y) & -(x < y));
}

int max(int x, int y)
{
return x ^ ((x ^ y) & -(x < y));
}

double calculateHand(int x, double* types, int *number, int *ranks, char *suits){
	long double returnposs = 100;
	int countlarger = 0;
	if (x != 0){
		//straight flush
		returnposs -= types[0]*100;
		if (x == 1){
			int i;
			for(i = ranks[0];i<10;i++){
				if(i>ranks[4]){
					countlarger +=4;
				}
				else{
					countlarger += 3;
				}
			}
			printf("%d of the %d other straight flush would win this.\n",countlarger,number[1]);
			return returnposs - ((double)countlarger/number[1])*types[1]*100;
		}
		//four kind
		else if (x == 2){
			returnposs -= types[1];
			int i;
			for(i = ranks[0];i<=14;i++){
				if((i!=ranks[4]) && (i!=ranks[0])){
					countlarger +=43;
				}
			}
			printf("%d of the %d other four a kind would win this.\n",countlarger,number[2]);
			return returnposs - ((double)countlarger/number[2])*types[2]*100;

		}
		//full house
		else if (x == 3){
			returnposs -= types[1]*100;
			returnposs -= types[2]*100;
			int i;
			int threecompare;
			int twocompare;
			if (countt(ranks,ranks[0]) == 3){
				threecompare = ranks[0];
				twocompare = ranks[3];
			}
			else{
				threecompare = ranks[2];
				twocompare = ranks[0];
			}
			countlarger += (14-threecompare)*4*52;
			countlarger += (14-twocompare)*6;
			printf("%d of the %d other full house would win this.\n",countlarger,number[3]);
			return returnposs - ((double)countlarger/number[3])*types[3]*100;
		}

		//flush
		else if (x == 4){
			returnposs -= types[1]*100;
			returnposs -= types[2]*100;
			returnposs -= types[3]*100;
			int high = ranks[4];
			// (14-high)
			int m = 0;
			if (14-ranks[4] == 0){
				m = 1;
			}
			countlarger = number[4] - m*(14-ranks[3])*(14-ranks[2])*(14-ranks[1])*(14-ranks[0])-number[0]-number[1]; //13!/(8!*5!) = 1287; 8!/(3!*5!) = 56 
			printf("%d of the %d other flush would win this.\n",countlarger,number[4]);
			return returnposs - ((double)countlarger/number[4])*types[4]*100;
		}

		//straight
		else if (x == 5){
			returnposs -= types[1];
			returnposs -= types[2];
			returnposs -= types[3];
			returnposs -= types[4];
			int i;
			for(i = ranks[0]+1;i<=10;i++){
				if(i>ranks[4]){
					countlarger +=1024;
				}
				else{
					countlarger += (pow (3, ranks[4]-i+1))*(pow(4,5-(ranks[4]-i+1)));
				}
			}
			countlarger -= 40;
			printf("%d of the %d other straight would win this.\n",countlarger,number[5]);
			return returnposs - ((double)countlarger/number[5])*types[5]*100;
		}

		//three a kind !!!
		else if (x == 6){
			returnposs -= types[1]*100;
			returnposs -= types[2]*100;
			returnposs -= types[3]*100;
			returnposs -= types[4]*100;
			returnposs -= types[5]*100;
			int threecompare;
			int bitcompare1;
			int bitcompare2;
			if (countt(ranks,ranks[0]) == 3){
				threecompare = ranks[0];
				bitcompare1 = max(ranks[3],ranks[4]);
				bitcompare2 = min(ranks[3],ranks[4]);
			}
			else if (countt(ranks,ranks[1]) == 3){
				threecompare = ranks[1];
				bitcompare1 = max(ranks[0],ranks[4]);
				bitcompare2 = min(ranks[0],ranks[4]);
			}
			else{
				threecompare = ranks[2];
				bitcompare1 = max(ranks[1],ranks[0]);
				bitcompare2 = min(ranks[1],ranks[0]);
			}
			int i;
			for(i = threecompare+1;i<=14;i++){
				countlarger += 22*43;
			}
			countlarger += 42*(14-bitcompare1);
			printf("%d of the %d other three a kind would win this.\n",countlarger,number[6]);
			return returnposs - ((double)countlarger/number[6])*types[6]*100;
		}

		//two pair
		else if (x == 7){
			returnposs -= types[1]*100;
			returnposs -= types[2]*100;
			returnposs -= types[3]*100;
			returnposs -= types[4]*100;
			returnposs -= types[5]*100;
			returnposs -= types[6]*100;
			int twocompare1;
			int twocompare2;
			int bitcompare1;
			if (countt(ranks,ranks[0]) == 2){
				twocompare1 = ranks[0];
				if (countt(ranks,ranks[2]) == 2){
					twocompare2 = ranks[2];
					bitcompare1 = ranks[4];
				}
				else{
					twocompare2 = ranks[3];
					bitcompare1 = ranks[2];
				}
			}
			else{
				bitcompare1 = ranks[0];
				twocompare1 = ranks[1];
				twocompare2 = ranks[3];
			}
			int i;
			for(i = twocompare2+1;i<=14;i++){
				countlarger += 23*43;
			}
			for(i = twocompare1+1;i<=14;i++){
				countlarger += 43;
			}
			return returnposs - ((double)countlarger/number[7])*types[7]*100;
		}

		//pair
		else if (x == 8){
			returnposs -= types[1]*100;
			returnposs -= types[2]*100;
			returnposs -= types[3]*100;
			returnposs -= types[4]*100;
			returnposs -= types[5]*100;
			returnposs -= types[6]*100;
			returnposs -= types[7]*100;
			int twocompare1;
			int bitcompare1;
			int bitcompare2;
			int bitcompare3;
			if (countt(ranks,ranks[0]) == 2){
				twocompare1 = ranks[0];
				bitcompare1 = ranks[2];
				bitcompare2 = ranks[3];
				bitcompare3 = ranks[4];
			}
			else if (countt(ranks,ranks[1]) == 2){
				twocompare1 = ranks[1];
				bitcompare1 = ranks[0];
				bitcompare2 = ranks[3];
				bitcompare3 = ranks[4];
			}
			else if (countt(ranks,ranks[2]) == 2){
				twocompare1 = ranks[2];
				bitcompare1 = ranks[0];
				bitcompare2 = ranks[1];
				bitcompare3 = ranks[4];
			}
			else{
				twocompare1 = ranks[3];
				bitcompare1 = ranks[0];
				bitcompare2 = ranks[1];
				bitcompare3 = ranks[2];
			}
			int i;
			for(i = twocompare1+1;i<=14;i++){
				countlarger += 22*43*15;
			}
			countlarger += (14-bitcompare3)*22*43;
			countlarger += (14-bitcompare2)*43;
			printf("%d of the %d other pair would win this.\n",countlarger,number[8]);
			return returnposs - ((double)countlarger/number[8])*types[8]*100;
		}

		//high
		else if (x == 9){
			returnposs -= types[1]*100;
			returnposs -= types[2]*100;
			returnposs -= types[3]*100;
			returnposs -= types[4]*100;
			returnposs -= types[5]*100;
			returnposs -= types[6]*100;
			returnposs -= types[7]*100;
			returnposs -= types[8]*100;
			countlarger += (14-ranks[4])*23*15*11*43;
			countlarger += (14-ranks[3])*22*15*43;
			countlarger += (14-ranks[3])*22*43;
			// int s = number[0]+number[1]+number[2]+number[3]+number[4]+number[5]+number[6]+number[7]+number[8];
			// countlarger -= s;
			printf("%d of the %d other high cards would win this.\n",countlarger,number[9]);
			return returnposs - ((double)countlarger/number[9])*types[9]*100;
		}
	}
	return returnposs;
}


int main(int argc, char *argv[]){
	// double *types = calloc(10,sizeof(double));
	char *pokers[KINDS] = {"royal flush", "straight flush", "four a kind", "full house","flush","straight","three a kind","two pair","pair", "high cards"};
	card *deck = calloc(NUM_CARDS,sizeof(card));
	deck = generate_new_deck();
	card *hand = calloc(HAND_CARDS,sizeof(card));
	int nthreads = 1;
  	if (argc == 2){
		nthreads = strtol(argv[1],NULL,10);
		hand = getAHand(deck,HAND_CARDS);}
	else if (argc == 12){
		char *inputsuit = calloc(HAND_CARDS,sizeof(char));;
   		int *inputrank = calloc(HAND_CARDS,sizeof(int));;
		int i;
		int countting = 0;
		for(i = 2;i<12;i +=2){
			inputrank[countting] = strtol(argv[i],NULL,10);
			countting += 1;
		}
		countting = 0;
		for(i = 3;i <=12;i +=2){
			inputsuit[countting] = *argv[i];
			countting += 1;
		}
		nthreads = strtol(argv[1],NULL,10);
		hand[0] = card_new(inputsuit[0],inputrank[0]);
		hand[1] = card_new(inputsuit[1],inputrank[1]);
		hand[2] = card_new(inputsuit[2],inputrank[2]);
		hand[3] = card_new(inputsuit[3],inputrank[3]);
		hand[4] = card_new(inputsuit[4],inputrank[4]);
		}
	else if (argc == 11){
		char *inputsuit = calloc(HAND_CARDS,sizeof(char));;
   		int *inputrank = calloc(HAND_CARDS,sizeof(int));;
		int i;
		int countting = 0;
		for(i = 1;i<11;i +=2){
			inputrank[countting] = strtol(argv[i],NULL,10);
			countting += 1;
		}
		countting = 0;
		for(i = 2;i <=11;i +=2){
			inputsuit[countting] = *argv[i];
			countting += 1;
		}
		nthreads = strtol(argv[1],NULL,10);
		hand[0] = card_new(inputsuit[0],inputrank[0]);
		hand[1] = card_new(inputsuit[1],inputrank[1]);
		hand[2] = card_new(inputsuit[2],inputrank[2]);
		hand[3] = card_new(inputsuit[3],inputrank[3]);
		hand[4] = card_new(inputsuit[4],inputrank[4]);
		}
	else{
		hand = getAHand(deck,HAND_CARDS);
	}
	srand(time(NULL));
	// clock_t startTime = clock();

	int *keep = calloc(KINDS,sizeof(int));
	keep = possibilities(deck,nthreads);
	// keep[0] = 4;
	// keep[1] = 32;
	// keep[2] = 624;
	// keep[3] = 3744;
	// keep[4] = 5112;
	// keep[5] = 9180;
	// keep[6] = 54912;
	// keep[7] = 123552;
	// keep[8] = 1098240;
	// keep[9] = 1303560;
	int royalflush = keep[0];
	int straightflush = keep[1];
	int fourkind = keep[2];
	int fullhouse = keep[3];
	int flush = keep[4];
	int straight = keep[5];
	int threekind = keep[6];
	int twopair = keep[7];
	int pair = keep[8];
	int high = keep[9];
	double *types = calloc(KINDS,sizeof(double));
	types = calculate(keep,KINDS);

	// clock_t endTime = clock();
	// double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
	// printf("That took %f ms\n",elapsed);
	// printf("\n");
	hand_tostring(hand);

	double returnposs = 100;
	int x = determineHand(hand);
	printf("This is a %s hand.\n",pokers[x]);
	int *ranklist = calloc(HAND_CARDS,sizeof(int));
	ranklist = getRanklist(hand);
	sort(ranklist,HAND_CARDS);
	char *suitlist = calloc(HAND_CARDS,sizeof(char));
	suitlist = getSuitlist(hand);
	printf("possibility: %f percent\n", calculateHand(x,types,keep,ranklist,suitlist));

	return 0;

}
