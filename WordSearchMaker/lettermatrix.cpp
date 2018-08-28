#include <string>
#include "lettermatrix.h"

//  Prints a 2D matrix of letters.  Used to print the puzzle or key.
//  os: the output stream to send the data (can be the console or a text file).
//  mat: the matrix to print.
//  Returns the output stream object (for chaining purposes).
std::ostream& operator<<(std::ostream& os, const LetterMatrix& mat) {
	for (auto row : mat) {
		for (auto letter : row)
			os << letter;
		os << std::endl;
	}
	return os;
}


//  Reads a 2D matrix of letters from an input stream.
//  is: the input stream providing the letters (can be the console or a text file).
//  mat: the matrix to fill.
//  Does not return anything; therefore, it does not support chaining.
void operator>>(std::istream& is, LetterMatrix& mat) {
	mat.clear();  //  Empty out the current puzzle
	while (is) {
		std::string line;
		std::getline(is, line);
		std::vector<char> vec;
		for (char ch : line)
			vec.push_back(ch);
		mat.push_back(vec);
	}
}


//  Compares two letter matrices to see if they contain exactly the same letters in
//  exactly the same locations.
//  m1: a matrix of letters
//  m2: another matrix of letters
//  Returns true if the m1 and m2 are identical; otherwise, returns false
bool operator==(const LetterMatrix& m1, const LetterMatrix& m2) {
	if (m1.size() != m2.size())  //  Different number of rows?
		return false;   //  Cannot be equal if number of rows differ
	for (size_t row = 0; row < m1.size(); row++) {  //  Scan each row
		if (m1[row].size() != m2[row].size()) // Different number of entries in this row?
			return false; // Cannot be equal if the number elements in corresponding rows differ
		for (size_t col = 0; col < m1[row].size(); col++) {
			if (m1[row][col] != m2[row][col])
				return false;  //  Mismatch found
		}
	}
	return true;  // All corresponding elements the same
}