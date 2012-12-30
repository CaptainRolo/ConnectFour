#include "Board.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <time.h>



//creates new board, initializes all pieces to 0
Board::Board() {
	srand ( time(NULL) );

	for (int i = 0; i < HEIGHT; i++) {
		board.push_back(vector< int >()); // Add a row
	}

	for (int j = 0; j < WIDTH; j++) {
		for (vector< vector< int > >::iterator p = board.begin(); p < board.end(); ++p) {
			p->push_back(0); // Add columns to all rows, initialize at 0
		}
	}
}

//start an iterator at column y, bottom row
//nmove upward till you find first open spot
//return row if exists, -1 if full
int Board::findOpenRow(int y) {
	for (int i = 0; i < HEIGHT; i++) {
		if (board[i][y] == 0) {

			//index of row
			return i;
		}
	}

	return -1;
}

//set the value at x y to piece
void Board::setPiece(int x, int y, int piece) {
	board[x][y] = piece;
}

//attempt to drop a piece at column y
//throws out_of_range exception if column is invalid
//returns false if no winner, true if there is a winner
bool Board::dropPiece(int y, int piece) {
	//if column is out of range
	if (y < 0 || y >= WIDTH) {
		throw out_of_range("Invalid Column!");

		return false;
	} else {
		int x = findOpenRow(y);

		if (x == -1) {
			throw fullColumnException("Column is full!");

			return false;
		} else {
			setPiece(x, y, piece);
			return checkWin(x, y, piece);
		}
	}
}

//dumb AI
bool Board::AImove() {
	return dropPiece(rand() % 7, 2);
}

//smart AI
bool Board::AI2move() {
	int move = -1;
	vector < vector < int > > temp = board;

	for (int i = 0; i < WIDTH; i++) {
		if (dropPiece(i, 2)) {
			move = i;
		} else {
			board = temp;
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		if (dropPiece(i, 1)) {
			move = i;
		} else {
			board = temp;
		}
	}

	board = temp;

	if (move == -1) return dropPiece(rand() % 7, 2);

	return dropPiece(move, 2);

}

//returns true if the player of piece wins with a placement at x y
bool Board::checkWin(int x, int y, int piece) {
	return (checkLeftRight(x, y, piece) || checkUpDown(x, y, piece) || checkDiagonal(x, y, piece));
}

//checks win for horizontal connect fours
bool Board::checkLeftRight(int x, int y, int piece) {
	int count = 1;
	int i = y, j = y;
	bool leftDone = false, rightDone = false;

	while ((board[x][i] == piece || board[x][j] == piece) && !(leftDone && rightDone)) {
		if (i > 0 && board[x][i] == piece) {
			i--;
		} else leftDone = true;
	

		if (j < WIDTH - 1 && board[x][j] == piece) {
			j++;
		} else rightDone = true;

		if (board[x][i] == piece && !leftDone) {
			count++;
		}

		if (board[x][j] == piece && !rightDone) {
			count++;
		}
	}

	return (count >= 4);
}

//checks win for vertical connect fours
bool Board::checkUpDown(int x, int y, int piece) {
	int count = 1;
	int i = x, j = x;
	bool upDone = false, downDone = false;

	while ((board[i][y] == piece || board[j][y] == piece) && !(upDone && downDone)) {
		if (i > 0 && board[i][y] == piece) {
			i--;
		} else downDone = true;
	

		if (j < HEIGHT - 1 && board[j][y] == piece) {
			j++;
		} else upDone = true;

		if (board[i][y] == piece && !downDone) {
			count++;
		}

		if (board[j][y] == piece && !upDone) {
			count++;
		}
	}

	return (count >= 4);
}

//checks diagonals for winning moves
bool Board::checkDiagonal(int x, int y, int piece) {
	int countTopLeftBotRight = 1;
	int countBotLeftTopRight = 1;
	int i = 0, j = 0, a = 0, b = 0;
	bool topLeftDone = false, topRightDone = false, botLeftDone = false, botRightDone = false;

	while ((board[x - i][y - i] == piece || board[x - j][y + j] == piece || board[x + a][y + a] == piece || board[x + b][y - b] == piece)
			&& !(topLeftDone && topRightDone && botLeftDone && botRightDone)) {

		if (x - i > 0 && y - i > 0 && board[x - i][y - i] == piece) {
			i++;
		} else { 
			botLeftDone = true;
		}
	

		if (x - j > 0 && y + j < HEIGHT - 1 && board[x - j][y + j] == piece) {
			j++;
		} else { 
			topLeftDone = true;
		}

		if (x + a < WIDTH - 1 && y + a < HEIGHT - 1 && board[x + a][y + a] == piece) {
			a++;
		} else { 
			topRightDone = true;
		}
	

		if (x + b < WIDTH - 1 && y - b > 0 && board[x + b][y - b] == piece) {
			b++;
		} else { 
			botRightDone = true;
		}

		if (board[x - i][y - i] == piece && !botLeftDone) {
			countBotLeftTopRight++;
		}

		if (board[x - j][y + j] == piece && !topLeftDone) {
			countTopLeftBotRight++;
		}

		if (board[x + a][y + a] == piece && !topRightDone) {
			countBotLeftTopRight++;
		}

		if (board[x + b][y - b] == piece && !botRightDone) {
			countTopLeftBotRight++;
		}
	}
	return (countTopLeftBotRight >= 4 || countBotLeftTopRight >= 4);
}

int Board::getWidth() {
	return WIDTH;
}

int Board::getHeight() {
	return HEIGHT;
}

//returns piece at x y
int Board::getPiece(int x, int y) {
	return board[x][y];
}