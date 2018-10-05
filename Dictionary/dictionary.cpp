//
//  dictionary.cpp
//  assignment3
//
//  Created by Derrick Marshall on 2/15/17.
//  Copyright © 2017 Derrick Marshall. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"


dictionary :: dictionary(){
	root = NULL;
	numWords = 0;
}

dictionary :: dictionary(string file){
	ifstream inFile;
	string command;
	
	root = NULL;
	numWords = 0;
	
	inFile.open(file.c_str());
	
	if (inFile.is_open()) {
		inFile >> command;
		
		while (inFile.peek() != -1) {
			addWord(command);
			inFile >> command;
		}
		
		inFile.close();
	}
}

void dictionary:: addWord(string word){
	int arrIndex = 0, index;
	Node* newNode;
	Node* currNode;
	
	if (root == NULL){
		Node* creatNode = new Node();
		root = creatNode;
	}
	
	currNode = root;
	
	for (index = 0; index < word.length(); index++) {
		
		arrIndex = (int)word[index] - ASCII;
	
		if (currNode -> path[arrIndex] == NULL) {
			newNode = new Node();
			(currNode -> path[arrIndex]) = newNode;
			currNode = newNode;
		}
		else
			currNode = (currNode-> path[arrIndex]);
	}
	
	if(word.length() == index){
		currNode -> wordFlag[arrIndex] = true;
	}
	
	numWords++;
	
}

bool dictionary:: isWord(string word){
	bool found = false;
	int arrIndex = 0;
	Node* currNode = root;
	
	if(currNode == NULL){
		return found;
	}

	for (int index = 0; index < word.length(); index++) {
		arrIndex = (int)word[index] - ASCII;
		
		if(currNode -> path[arrIndex] == NULL)
			return found;
		
		currNode = currNode -> path[arrIndex];
	}
	
	if(currNode -> wordFlag[arrIndex] == true)
		return found = true;
	
	return found;
	
}

bool dictionary:: isPrefix(string word){
	bool found = false;
	int arrIndex = 0, index;
	Node *currNode = root;
	
	if(currNode == NULL)
		return found;
	
	for (index  = 0; index < word.length(); index++) {
		arrIndex = (int)word[index] - ASCII;
		
		if(currNode == NULL)
			return found;
		
		currNode = currNode -> path[arrIndex];
	}
	
	if (currNode != NULL && word.length() == index) {
		return found = true;
	}
	
	return found;
}

void dictionary:: PrintWords(string prefix){

}


int dictionary:: wordCount(){
	return numWords;
}


dictionary :: ~dictionary(){
	
}

