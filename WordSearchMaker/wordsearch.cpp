#include "uniformrandom.h"
#include "wordsearch.h"


//-------------------------------------------------------
//  You may add any helper functions you desire.
//  If you do add your own any helper functions, declare them 
//  "static" so they will be local to this source file.
//-------------------------------------------------------



//  Constructs a puzzle key from a word list.
//  word_list: the vector of words to put into the puzzle.
//  rows: the number of rows in the puzzle
//  columns: the number of columns in the puzzle
//  Returns the newly created wordsearch puzzle key.
//  Note: The method's behavior is undefined if all the words 
//  in its list cannot be placed.
LetterMatrix make_key(const std::vector<std::string>& word_list,
	int rows, int columns) {
	//  Replace this statement with your code
	return { {'A', 'B', 'C', 'D'},
			{'E', 'F', 'G', 'H'},
			{'I', 'J', 'K', 'L'},
			{'M', 'N', 'O', 'P'} };
}


//  Constructs a puzzle from a given key.
//  key: the key from which the puzzle is to be created.
//  Returns the newly created corresponding word search puzzle.
LetterMatrix make_puzzle(const LetterMatrix& key) {
	//  Replace this statement with your code
	return key;
}
