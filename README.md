# Poker-Game-Project-Euler-54-

This is a C++ based solution for problem 54 on projecteuler.com

At this point I have only been programming for 2 months, so I'm sure my code is far less than spectacular. For one, I used global variables and a global array that gets passed between functions, which I'm guessing isn't the best idea. I also "namespace std", however that was simply to make the code more ledgible for this problem. I am aware that it is a "no-no" and I've never used it apart from this project. :)

This is also the first time I have ever posted anything to GitHub, so I figure I might as well go all out and explain the problem and my code below.

#Problem Description from Project Euler:

In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:

High Card: Highest value card.
One Pair: Two cards of the same value.
Two Pairs: Two different pairs.
Three of a Kind: Three cards of the same value.
Straight: All cards are consecutive values.
Flush: All cards of the same suit.
Full House: Three of a kind and a pair.
Four of a Kind: Four cards of the same value.
Straight Flush: All cards are consecutive values of same suit.
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of fives. But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are compared; if the highest cards tie then the next highest cards are compared, and so on.

The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains ten cards (separated by a single space): the first five are Player 1's cards and the last five are Player 2's cards. You can assume that all hands are valid (no invalid characters or repeated cards), each player's hand is in no specific order, and in each hand there is a clear winner.

How many hands does Player 1 win?

#A Walkthrough of My Code:

I tried to break the problem down into as many simple functions as possible. I will explain them one by one below.

<b> My 'main' function </b>
```sh
int main(){
	int player1Wins=0, player2Wins=0, winner=0;
	string hands, hand1, hand2;
	
	ifstream file("p054_poker.txt");
	while(getline(file, hands)){
		hand1 = hands.substr(0, 14);
		hand2 = hands.substr(15, 14);
		winner = playPoker(hand1, hand2);
		if(winner == 1)
			player1Wins++;
		else
			player2Wins++;
	}
	cout << "Player 1 wins: " << player1Wins << endl;
	cout << "Player 2 wins: " << player2Wins << endl;
}
```
I tried to keep my main function as simple as possible. The poker.txt file is read line by line, which brings in 10 cards at a time. The first 5 cards are player one's and the second 5 are player two's. So the line read in is split in half into two hands, each of which are then fed to the "playPoker" function.

<b>int playPoker(string hand1, string hand2)</b>
```sh
int playPoker(string hand1, string hand2){
	int rank1=0, rank2=0, winner=0, handHigh1=0, 
	totalHigh1=0, handHigh2=0, totalHigh2=0;
	
	hand1 = convertHand(hand1);
	collectNumbers(hand1);
	organizeCards();
	rank1 = handRank(hand1);
	handHigh1 = handHigh, totalHigh1 = totalHigh;
	
	hand2 = convertHand(hand2);
	collectNumbers(hand2);
	organizeCards();
	rank2 = handRank(hand2);
	handHigh2 = handHigh, totalHigh2 = totalHigh;
		
	winner = compareRank(rank1, rank2);
	if(winner == 3){
		return compareHands(handHigh1, totalHigh1, handHigh2, totalHigh2);
	}
	else
		return winner;
}
```
This is one of the biggest functions. The cards come in and are tested consecutively and then compared to determine a winner. This is done through all of the smaller functions. Both hands (depending on what they are) will be given a rank from 0 to 9. This rank corresponds with the 10 different hands you can have in poker. The ranks of the hands will be compared and the hand with the higher rank wins. If the hands have the same rank (for example they are both full houses, rank 6) then the cards of the main portion of the hand (the three of a kind card for a full house) will be compared to determine a winner. If the hands are identical (for example both are a pair of queens), then the highest cards in each hand will be compared.

<b>string convertHand(string hand)</b>
```sh
string convertHand(string hand){
	char cArray[5] = {'T','J','Q','K','A'};
	string sArray[5] = {"10","11","12","13","14"};
	for(int i=0; i<=hand.length()-2; i++){
		for(int j=0; j<=4; j++){
			if(hand[i] == cArray[j])
				hand.replace(i,1, sArray[j]);
		}
	}
	return hand;
}
```
Before a hand can be tested to determine what it is, the convertHand function changes all letter based cards in the hand to a corresponding number. This makes comparing hands later on much easier.

<b>void collectNumbers(string hand)</b>
```sh
void collectNumbers(string hand){
	string subHand;
	int j=0, index=0;
	totalHigh=0;
	for(int i=0; i<=hand.length()-1; i++){
		if(hand[i]==' ')
			continue;
		if(hand[i]=='D'||hand[i]=='C'||hand[i]=='H'||hand[i]=='S'){
			cardNumArray[index]=j;
			subHand = "";
			index++;
			continue;
		}
		subHand += (to_string(hand[i]-'0'));
		j = stoi(subHand);
	}
	for(int i=0; i<=4; i++){
        if(cardNumArray[i]>totalHigh)
        	totalHigh=cardNumArray[i];
    }
}
```
This function collects all of the number values of the cards in a hand and stores them into a global integer array. It skips over any letters associated with suit and only grabs numbers. This array is then used by other functions to check for various poker hands. At this point, the high card of the hand is also saved for later to be used for a tie breaker if necessary.

<b>void organizeCards()</b>
```sh
void organizeCards(){
	int temp=0;
	for(int i=0; i<=4; i++){
		for(int j=i+1; j<=4; j++){
			if(cardNumArray[j]<cardNumArray[i]){
				temp = cardNumArray[i];
				cardNumArray[i]=cardNumArray[j];
				cardNumArray[j]=temp;
			}
		}
	}
}
```
This function is a simple bubble sort that arranges the integer card array into ascending order.


void removeCards();
bool straight();
bool flush(string hand);
bool pairs();
int ofaKind();
int handRank(string hand);
int compareRank(int rank1, int rank2);
int compareHands(int handHigh1, int totalHigh1, int handHigh2, int totalHigh2);
