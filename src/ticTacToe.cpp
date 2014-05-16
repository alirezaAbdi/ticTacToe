//============================================================================
// Name        : ticTacToe.cpp
// Author      : Alireza & Olivia
// Version     :
// Copyright   : Be careful!
// Description : TicTacToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <limits>
using namespace std;

unsigned int winCombinations[8] = { 0b111000000, 0b000111000, 0b000000111, 0b100100100, 0b010010010, 0b001001001, 0b100010001, 0b001010100 };
unsigned int playerA = 0;
unsigned int playerB = 0;
const unsigned int BOARDSIZE = 9;



void publishTable() {

	cout << "Print of the board" << endl;

	for (int i = BOARDSIZE; i--; ) {
		if(playerA>>(BOARDSIZE-1-i)&1){
			cout<<"X"<<" ";
		} else if(playerB>>(BOARDSIZE-1-i)&1){
			cout<<"0"<<" ";
		} else {
			cout<<"- ";
		}

		if (i%3==0)
			cout << endl;
	}
	cout << endl;

}

bool checkIfWinningComb(unsigned int player) {
	for (int index = 0; index < 8; index++) {
		if (winCombinations[index] == (winCombinations[index] & player))
			return true;
	}

	return false;
}


//gets a state as the argument, and it should return a score for the given state
int utility(unsigned int playerA, unsigned int playerB) {
	if (checkIfWinningComb(playerA))
		return 1;
	else if (checkIfWinningComb(playerB))
		return -1;
	else
		return 0;
}


bool isPositionValid(unsigned int position) {
	if ((position > BOARDSIZE - 1) || (position < 0)) {
		cout << "position out of range!" << endl
		<< "Please enter a new correct position.";
		return false;
	}

	if (((playerA | playerB) & (1 << position)) != 0) {
		cout << "position already in use!" << endl
		<< "Please choose another position.";
		return false;
	}

	return true;
}

//is supposed to run either the Min or the Max depending on which player is to play
int decision(unsigned int playerA, unsigned int playerB) {


	int pos = max(playerA,playerB);

	cout<<"pos: "<<pos<<" "<<endl;

	return pos;
	// for each possible move ->
	// call max
	// choose the one with highest score
}

//Gets a state as the argument, and it should try all the possible successor combinations, and choose the one with lowest score
int min(unsigned int playerA, unsigned int playerB) {
	if(utility(playerA,playerB) != 0){
		return playerA;
	}

	unsigned int totalBoard = (playerA | playerB);
	unsigned int bestValue = std::numeric_limits<unsigned int>::max();
	for(int i=0;i<BOARDSIZE;i++){
		if(!(totalBoard>>i & 1)){
			// free position
			unsigned int val = max(playerA | (1 << i), playerB);
			bestValue=std::min(val,bestValue);
		}
	}

	return bestValue;
	// is it possible to make any more moves?
	// yes: for all possible moves ->
	// max(playerA',playerB)
	// then choose the one with the lowest score
	// no: return utility(playerA, playerB)
}

//Gets a state as the argument, and it should try all the possible successor combinations, and choose the one with most score
int max(unsigned int playerA, unsigned int playerB) {
	if(utility(playerA,playerB) != 0){
		return playerB;
	}

	unsigned int totalBoard = (playerA | playerB);
	unsigned int bestValue = 0;
	for(int i=0;i<BOARDSIZE;i++){
		if(!(totalBoard>>i & 1)){
			// free position
			unsigned int val = min(playerA, playerB | (1 << i));
			bestValue=std::max(val,bestValue);
		}
	}

	return bestValue;
	// is it possible to make any more moves?
	// yes: for all possible moves ->
	// min(playerA,playerB')
	// then choose the one with the highest score
	// no: return utility(playerA, playerB)
}


int main() {
	cout << "!!!Tic Tac Toe!!!" << endl;


	int position = 0;
	for (int index = 0; index < BOARDSIZE; index++) {

		if (index % 2 == 0) {
			cout << "Player A moves to position (0 to 8): ";

			do {
				cin >> position;
			} while (!isPositionValid(position));

			playerA |= (1 << position);
			if (checkIfWinningComb(playerA)) {
				cout << "Player A won!" << endl;
				break;
			}
		} else {

			position = decision(playerA, playerB);

			playerB = position;
			if (checkIfWinningComb(playerB)) {
				cout << "Player B won!" << endl;
				break;
			}

/*
			do {
				cin >> position;
			} while (!isPositionValid(position));

			playerB |= (1 << position);
			board[position] = '0';
			if (checkIfWinningComb(playerB)) {
				cout << "Player B won!" << endl;
				break;
			}
*/
		}

		publishTable();
	}

	publishTable();

	return 0;
}
