#include <string>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Board.h"

using namespace std;

//stream operator to output the board
inline ostream& operator<<(ostream &os,Board &b)
{

	for (int i = 0; i < b.getHeight(); i++) {
		cout << i << "  ";
	}
	
	cout << endl;

	for (int i = 0; i < b.getWidth(); i++) {
		cout << "_" << "  ";
	}

	cout << endl << endl;

	for (int i = b.getWidth() - 1; i >= 0; i--) {
		for (int j = 0; j < b.getHeight(); j++) {
			cout << b.getPiece(i, j) << "  ";
		}
		cout << endl << endl;
	}
	return os;
}

int main() {
	Board b;
	string input = "";
	int currentPlayer = 1; // 1 for Player 1, 2 for Player 2
	int winner = 0; // 0 for no winner, 1 for Player 1, 2 for Player 2
	bool AI = false; // random AI
	bool AI2 = false; // smart AI

	while (winner == 0) {
		cout << b;

		//while loop for user input
		while (input == "" && !(currentPlayer == 2 && (AI || AI2))) {
			if (!AI && !AI2) {
				cout << "To play versus a dumb computer enter '-1'!" << endl;
				cout << "To play versus a smart computer enter '-2'!" << endl;
			} else if (AI) {
				cout << "DUMB AI MODE ACTIVE!!!" << endl;
			} else {
				cout << "SMART AI MODE ACTIVE!!!" << endl;
			}

			cout << "Player " << currentPlayer << "'s turn!" << endl;
			cout << "Type the column to which you wish to drop a piece! (0 through 6):  ";
			getline(cin, input);

			if (input == "-1" && !(AI2)) {
				AI = true;
				input = "";
			}

			if (input == "-2" && !(AI)) {
				AI2 = true;
				input = "";
			}

			cout << endl;
		}

		//when valid input is provided
		try {
			//for dumb/smart AI
			if (currentPlayer == 2 && (AI || AI2)) {
				if (AI) {
					if (b.AImove()) {
						winner = currentPlayer;
					} else {
						if (currentPlayer == 1) {
							currentPlayer = 2;
						} else {
							currentPlayer = 1;
						}
					}
				} else {
					if (b.AI2move()) {
						winner = currentPlayer;
					} else {
						if (currentPlayer == 1) {
							currentPlayer = 2;
						} else {
							currentPlayer = 1;
						}
					}
				}
			} else {
				//for Human move
				if (b.dropPiece(atoi(input.c_str()), currentPlayer)) {
					winner = currentPlayer;
				} else {
					if (currentPlayer == 1) {
						currentPlayer = 2;
					} else {
						currentPlayer = 1;
					}
				}
			}
			//to catch exceptions thrown in dropPiece()
		} catch (fullColumnException &e) {
			cerr << endl << endl << e.what();
		}catch (out_of_range &e) {
			cerr << endl << endl << e.what();
		}

		//reset input
		input = "";

		cout << endl << endl << endl;
	}

	
	cout << b;

	cout << "Player " << winner << " wins!" << endl;
}