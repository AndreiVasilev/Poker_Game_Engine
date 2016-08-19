#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

string convertHand(string hand);
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
int cardNumArray[5]={}, handHigh=0, totalHigh=0;

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

// converts all T,J,Q,K,A into number equivalents
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

// collects all numbers from hand and puts them into cardNumArray
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

// bubble sort cardNumArray into ascending numerical order
void organizeCards(){
	int temp=0, tempHigh=0;
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

// in event of three of a kind, replace 3 repeating cards in cardNumArray with zeros
// remaining non-zero cards can then be checked for additional pair, making full house
void removeCards(){
	for(int i=0; i<=3; i++){
		if(cardNumArray[i] == cardNumArray[i+1] && cardNumArray[i+1] == cardNumArray[i+2]){
			cardNumArray[i] = 0; 
			cardNumArray[i+1] = 0;
			cardNumArray[i+2] = 0;
		}
	}
}

// checks numbers of cardNumArray for straight
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

// removes everything but suits from hand to see if flush
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

// checks numbers of cardNumArray for 3 or 4 of a kind
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

// checks for pairs in cardNumArray
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

// associates a hand with its rank against other hands
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

// tests both hands to determine what they are
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

// compares the ranks of the hands against each other to determine a winner
int compareRank(int rank1, int rank2){
	if(rank1 > rank2)
		return 1;
	else if(rank2 > rank1)
		return 2;
	else
		return 3;
}

// if hands are the same, high cards are compared to determine winner
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


