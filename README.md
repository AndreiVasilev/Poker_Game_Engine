# Poker-Game-Project-Euler-54-

This is a C++ based solution for problem 54 on projecteuler.com

At this point I have only been programming for 2 months, so I'm sure my code is far less than spectacular. For one, I used global variables and a global array that gets passed between functions, which I'm guessing isn't the best idea. I also "namespace std", however that was simply to make the code more ledgible for this problem. I am aware that it is a "no-no" and I've never used it apart from this project. :)

This is also the first time I have ever posted anything to GitHub, so I figure I might as well go all out and explain the problem and my code below. I'm assuming most people won't read all of this, but oh well, it was fun nonetheless. 

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
I tried to keep my main function as simple as possible. The poker.txt file is read line by line, which brings in 10 cards at a time. The first 5 cards are player one's and the second 5 are player two's. So the line read in is split in half into two hands, each of which are then fed to the "playPoker" function. The playerPoker() function will return which player won, player 1 or player 2. The winnings are then counted and displayed at the end.


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
This function is a simple bubble sort that arranges the card number array into ascending order. This makes checking for poker hands much easier. At this point, the hand is now completely numerical and has been organized. From here we can check what type of poker hand it is.


<b>int handRank(string hand)</b>
```sh
int handRank(string hand){
	bool flushTrue = flush(hand);
	//check for straight, straight flush, or royal flush
	if(straight()){
		if(flushTrue){
			if(cardNumArray[0]==10)
				return 9;
			else
				return 8;
		}
		else
			return 4;
	} 
	//check for only flush
	else if(flushTrue)
		return 5;
	//check for 3 of a kind, 4 of a kind, and full house
	int kind = ofaKind();
	if(kind == 4)
		return 7;
	else if(kind == 3){
		if(pairs())
			return 6;
		else
			return 3;
	} 
	//check for two pair or single pair;
	else if(pairs()){
		if(pairs())
			return 2;
		else
			return 1;
	}
	//rank zero, meaning no hand and only a high card
	else
		return 0;
}
```
This function runs all of the functions actually responsible for determining what type of poker hand the current hand being tested is. Depending on what comes back as true or not, a corresponding rank will be given to the hand. 

Now lets look at the functions that test for the various types of poker hands.


<b>bool straight()</b>
```sh
bool straight(){
	for(int i=0; i<=2; i++){
		if(cardNumArray[i] == cardNumArray[i+1]-1)
			continue;
		else 
			return false;
	}
	if(cardNumArray[3]==5 && cardNumArray[4]==14)
		return true;
	else if(cardNumArray[3] == cardNumArray[4]-1)
		return true;
	else
		return false;
}
```
This function simply looks at the global integer array holding the card number values and checks to see if they are all consecutively separated by 1. If all 5 are, then its a straight. A special case also has to be tested for, which is the A,2,3,4,5 straight (called "the wheel" in poker). Ace cards are given a value of 14 and the array holding the numbers is numerically organized that means such a straight is represented in the array as 2,3,4,5,14.


<b>bool flush(string hand)</b>
```sh
bool flush(string hand){
	string temp = hand;
	temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
	temp.erase(remove_if(temp.begin(), temp.end(), ::isdigit), temp.end());
	for(int i=0; i<=3; i++){
		if(temp[i] == temp[i+1])
			continue;
		else 
			return false;	
	}
	return true;
}
```
This function tests the hand for a flush by removing all characters except for suits. If all the characters match, then the hand is a flush. Straightforward and simple.


<b>int ofaKind()</b>
```sh
int ofaKind(){
	int count=0;
	for(int i=0; i<=2; i++){
		if(cardNumArray[i]==cardNumArray[i+1]&&cardNumArray[i+1]==cardNumArray[i+2])
			count++;
	}
	if(count == 2){
		handHigh = cardNumArray[1];
		return 4;
	} 
	else if(count == 1){
		handHigh = cardNumArray[2];
		removeCards();
		organizeCards();
		return 3;
	}
	return 0;
}
```
This function tests for 3 and 4 of a kinds. It checks for 3 consecutive equal digits. If its a 4 of a kind there will be 2 sets of them, if it is a 3 of a kind there will of course only be 1 set. This function also sets the "handHigh" variable. For straights and flushes, checking to see who has the better hand is easy, just check the high card out fo the 5 (the last value of the global integer array). For other hands though, the high card doesn't necessarily determine the winner. A four of a kind 24444 will beat a 33336. This means that the high card of the winning portion of the hand (the 4 and 3 respectively) must be saved to help determine a winner.


<b>void removeCards()</b>
```sh
void removeCards(){
	for(int i=0; i<=3; i++){
		if(cardNumArray[i] == cardNumArray[i+1] && cardNumArray[i+1] == cardNumArray[i+2]){
			cardNumArray[i] = 0; 
			cardNumArray[i+1] = 0;
			cardNumArray[i+2] = 0;
		}
	}
}
```
In the event of a 3 of a kind, this function is called from within the "ofaKind()" function. It replaces the 3 repeating cards from the global integer array with zeros, leaving only 2 cards left. This makes it easier to check the remaining two cards for a pair, and in turn to see if the hand is a full house. After this function is called, the integer array is resorted so that the three zeros are at the beginning and the last two cards are at the end.

<b>bool pairs()</b>
```sh
bool pairs(){
	int count=0;
	for(int i=0; i<=3; i++){
		if(cardNumArray[i] == 0){
			count++;
			continue;
		}
		if(cardNumArray[i] == cardNumArray[i+1]){
			if(count < 3)
				handHigh = cardNumArray[i];
			cardNumArray[i] = 0; 
			cardNumArray[i+1] = 0;
			return true;
		}
	}
	return false;
}
```
This function checks for pairs. Every time it finds a pair, it replaces them with zeros. Zeros are ignored by this function. This makes it so that if the hand is a two pair, the next time the function is run, it won't find the same pair twice. Also, if the hand was not a 4 of a kind, 3 of a kind, or full house, the handHigh card is assigned here instead of in the ofaKind() function.


<b>int compareRank(int rank1, int rank2)</b>
```sh
int compareRank(int rank1, int rank2){
	if(rank1 > rank2)
		return 1;
	else if(rank2 > rank1)
		return 2;
	else
		return 3;
}
```
At this point the handRank() function will have determined what type of poker hand the hand is, and it will have assigned it a proper rank. The playPoker() function will go through this entire process twice, once for each hand. Once a rank has been given to both hands, this compareRank() function is run. If the ranks are not equal than there is a clear winner and the playPoker(). For instance a two pair vs a full house. If both players have an equal ranked hand though, a full house vs a full house, the hands must be compared.


<b>int compareHands(int handHigh1, int totalHigh1, int handHigh2, int totalHigh2)</b>
```sh
int compareHands(int handHigh1, int totalHigh1, int handHigh2, int totalHigh2){
	if(handHigh1 > handHigh2)
		return 1;
	else if(handHigh2 > handHigh1)
		return 2;
	else {
		if(totalHigh1 > totalHigh2)
			return 1;
		else
			return 2;
	}
}
```
If the ranks were equal, then that means the two players have the same type of hand. To determine a winner, the cards are looked at which were saved earlier as integer values. The handHigh value is the value such as the 4 in a full house 44466. If one player has 44466 and the other has 77722. The handhigh value of 7 will be the value of 4 and the second hand will win. In the event of a total tie, such as two equal two pairs like 24488 and 44889 then the hand with the highest card wins, which would be the 9.


#Conclusion

If you've made it this far, thanks for taking the time to read everything. Like I said at the beginning, I'm sure the code could be improved, but I had a lot of fun writing it nonetheless. Time to go use this to create an entire poker game program!  

