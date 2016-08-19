# Poker-Game-Project-Euler-54-

This is a C++ based solution for problem 54 on projecteuler.com

At this point I have only been programming for 2 months, so I'm sure my code is far less than spectacular. This is also the first time I have ever posted anything to GitHub, so I figured I'd go all out and explain the problem and my code below.

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

Firstly, (because I know someone will point this out) I used "namespace std" simply to make the code more ledgible for this problem. I am aware that it is a "no-no" and I've never used it apart from this project. :)



<b>string convertHand(string hand);</b>
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




void collectNumbers(string hand);
void organizeCards();
void removeCards();
bool straight();
bool flush(string hand);
bool pairs();
int ofaKind();
int handRank(string hand);
int playPoker(string hand1, string hand2);
int compareRank(int rank1, int rank2);
int compareHands(int handHigh1, int totalHigh1, int handHigh2, int totalHigh2);
