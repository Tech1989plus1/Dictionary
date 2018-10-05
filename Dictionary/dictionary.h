//
//  dictionary.h
//  assignment3
//
//  Created by Derrick Marshall on 2/14/17.
//  Copyright © 2017 Derrick Marshall. All rights reserved.
//

#ifndef dictionary_h
#define dictionary_h

#define ALFHA 26
#define ASCII 97
#define BUFFER 256

#include <string>
#include <iostream>
using namespace std;


struct Node{
	bool wordFlag[ALFHA];
	Node *path[ALFHA];
};

class dictionary{
private:
	Node *root;
	int numWords;
	void printWordHelper(Node *&currNode, int arrIndex, int count, char *word[BUFFER]);
	
	
public:
	dictionary();
	dictionary(string file);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	void PrintWords(string prefix);
	int wordCount();
	~dictionary();
};


#endif /* dictionary_h */
