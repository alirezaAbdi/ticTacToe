//============================================================================
// Name        : ticTacToe.cpp
// Author      : Alireza & Olivia
// Version     :
// Copyright   : Be careful!
// Description : TicTacToe in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

unsigned int winCombinations[8] = { 448, 56, 7, 292, 146, 73, 273, 84 };
unsigned int playerA = 0;
unsigned int playerB = 0;
const unsigned int BOARDSIZE = 9;
char board[BOARDSIZE];

void publishTable() {
	cout << "Print of the board" << endl;

	for (int i = 0; i < BOARDSIZE; i++) {
		cout << board[i] << " ";
		if ((i == 2) || (i == 5))
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

bool isPositionValid(unsigned int position) {
	if ((position > BOARDSIZE - 1) || (position)) {
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
	// for each possible move ->
	// call max
	// choose the one with highest score
}

//Gets a state as the argument, and it should try all the possible successor combinations, and choose the one with lowest score
int min(unsigned int playerA, unsigned int playerB) {
	// is it possible to make any more moves?
	// yes: for all possible moves ->
	// max(playerA',playerB)
	// then choose the one with the lowest score
	// no: return utility(playerA, playerB)
}

//Gets a state as the argument, and it should try all the possible successor combinations, and choose the one with most score
int max() {
	// is it possible to make any more moves?
	// yes: for all possible moves ->
	// min(playerA,playerB')
	// then choose the one with the highest score
	// no: return utility(playerA, playerB)
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

int main() {
	cout << "!!!Tic Tac Toe!!!" << endl;
	std::fill_n(board, BOARDSIZE, '-');

	int position = 0;
	for (int index = 0; index < BOARDSIZE; index++) {

		if (index % 2 == 0) {
			cout << "Player A moves to position (0 to 8): ";

			do {
				cin >> position;
			} while (!isPositionValid(position));

			playerA |= (1 << position);
			board[position] = 'X';
			if (checkIfWinningComb(playerA)) {
				cout << "Player A won!" << endl;
				break;
			}
		} else {
			cout << "Player B moves to position(0 to 8): ";

			do {
				cin >> position;
			} while (!isPositionValid(position));

			playerB |= (1 << position);
			board[position] = '0';
			if (checkIfWinningComb(playerB)) {
				cout << "Player B won!" << endl;
				break;
			}
		}

	}

	publishTable();

	return 0;
}
