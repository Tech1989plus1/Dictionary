//
//  main.cpp
//  assignment3
//
//  Created by Derrick Marshall on 2/14/17.
//  Copyright © 2017 Derrick Marshall. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "dictionary.h"
using namespace std;

#define rowSize 4
#define colSize 4

bool verbose = false;
int numWords = 0;
void SolveBoard(dictionary &dict, dictionary &wordsFound, bool printBoard, string board[4][4], int boardCount[4][4]);
void SolveBoardHelper(int row, int col, dictionary &dict, dictionary &wordFound, bool foundEnd, int letterCount, int arrIndex, string word, string board[4][4], int boardCount[4][4]);
void loadBoard(string board[4][4], int boardCount[4][4], bool);
void printGameBoard(string board[4][4], int boardCount[4][4], bool);

int main(int argc, const char * argv[]) {
	string command;
	string board[rowSize][colSize];
	int boardCount[rowSize][colSize];
	
	dictionary wordsFound;
	dictionary dict("dictionary.txt");
	
	cout << dict.wordCount() << " words loaded.\n" << endl;
	
	loadBoard(board, boardCount, true);
	cout << "Enter Board" << endl;
	cout << "-----------" << endl;
	printGameBoard(board, boardCount, true);
	cout << endl;
	
	SolveBoard(dict, wordsFound, true, board, boardCount);
	
    return 0;
}

void SolveBoard(dictionary &dict, dictionary &wordsFound, bool printBoard, string board[4][4], int boardCount[4][4]){
	string command, boggleWord, firstWord, letter;
	int boggleCount = 0;
	
	cout << "Show Board (y/n): ";
	cin >> command;
	
	if (command == "n") {
		printBoard = false;
	}
	
	for (int row = 0; row < rowSize; row++) {
		for (int col = 0; col < colSize; col++) {
			SolveBoardHelper(row, col, dict, wordsFound, false, 1, 1, "", board, boardCount);
			
			if (printBoard)
				printGameBoard(board, boardCount, 0);
			
			loadBoard(board, boardCount, 0);
			
		}
	}
	
	
		boggleCount++;
	
	

	
}

void SolveBoardHelper(int row, int col, dictionary &dict, dictionary &wordFound, bool foundEnd, int letterCount,int boggleCount, string word, string board[4][4], int boardCount[4][4]){
	
	//arrIndex = (int)(board[row][col])[0] - ASCII;
	
	
	if (dict.isWord(word + board[row][col])) {
		word = word + board[row][col];
		cout << boggleCount << " " << word << endl;
		board[row][col] = "'" + board[row][col];
		boardCount[row][col] = letterCount;
		boggleCount++;
	}
	
	if(dict.isPrefix(word + board[row][col]) == 0 && word.length() != 0)
		return;
	
	if (row < 0 || row > rowSize || col < 0 || col > colSize)
		return;
	
	if (boardCount[row][col] != 0)
		return;
	
	word = word + board[row][col];
	board[row][col] = "'" + board[row][col];
	boardCount[row][col] = letterCount;
	letterCount++;
	
	SolveBoardHelper(row - 1, col, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	SolveBoardHelper(row + 1, col, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	SolveBoardHelper(row, col - 1, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	SolveBoardHelper(row, col + 1, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	SolveBoardHelper(row - 1, col - 1, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	SolveBoardHelper(row + 1, col + 1, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	SolveBoardHelper(row - 1, col + 1, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	SolveBoardHelper(row + 1, col - 1, dict, wordFound, foundEnd, letterCount, boggleCount, word, board, boardCount);
	
}

void loadBoard(string board[4][4], int boardCount[4][4], bool trigger){
	string arr[] = {"a","u","c","o","n","l","n","i","o","s","a","e","m","a","i","e",};
	
	if (trigger) {
		for (int row = 0; row < 4; row++) {
			for (int column = 0; column < 4; column++){
				boardCount[row][column] = 0;
				board[row][column] = arr[((row * 4) + column)];
			}
		}
	}else{
		string letter, temp;
		for (int row = 0; row < 4; row++) {
			for (int column = 0; column < 4; column++){
				letter = (board[row][column])[0];
				
				if (letter == "'") {
					temp = board[row][column];
					letter = temp[1];
					board[row][column] = letter;
				}
				boardCount[row][column] = 0;
			}
		}

	}
	
}

void printGameBoard(string board[4][4], int boardCount[4][4], bool trigger){
	string letter;
	
	if (trigger) {
		for (int row = 0; row < 4; row++) {
			cout << "Row " << row << ":";
			for (int column = 0; column < 4; column++){
				cout <<setw(4) <<  board[row][column];
			}
			cout << endl;
		}
	}else{
		for (int row = 0; row < 4; row++) {
			for (int column = 0; column < 4; column++){
				cout << setw(4) << board[row][column];
			}
			cout << setw(8);
			for (int column = 0; column < 4; column++) {
				cout << boardCount[row][column] << setw(4);
			}
			cout<< setw(0) << endl;
		}
	}


}
