#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>      //  For toupper
#include <algorithm>   //  For transform function
#include "wordsearch.h"

//  Reads words from a text file and places them into a vector.
//  Returns the resulting vector of words.
//  The first token in the text file is an integer representing 
//  the number of words in the file.
std::vector<std::string> get_words_from_file(const std::string& filename) {
	std::vector<std::string> result;   //  List of words to populate
	std::ifstream fin(filename);  //  Open input stream from file
	//  Do (or continue to do) loop while the stream has data
	while (fin) {
		std::string word;
		fin >> word;   //  Read a word
		if (fin) {
			//  Ensure all letters are uppercase
			std::transform(begin(word), end(word), begin(word), toupper);
			//  Add word to the list
			result.push_back(word);
		}
	}
	return result;  //  Return the list of words from the file
}


int main() {
	std::vector<std::string> word_list = get_words_from_file("wordlist.txt");
	//  Build a 20 x 20 word search key
	LetterMatrix key = make_key(word_list, 20, 20);
	//  Build a corresponding puzzle from the key
	LetterMatrix puz = make_puzzle(key);
	//  Print the list of words
	for (auto word : word_list)
		std::cout << word << '\n';
	std::cout << '\n';
	//  Print the puzzle
	std::cout << puz << '\n';
	//  Print the key
	std::cout << key << '\n';
}
