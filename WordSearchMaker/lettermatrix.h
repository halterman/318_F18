#ifndef LETTER_MATRIX_H
#define LETTER_MATRIX_H

#include <vector>
#include <iostream>

//  Convenient synonym for a 2D vector of letters
using LetterMatrix = std::vector<std::vector<char>>;

//  Prints a 2D matrix of letters.  Used to print the puzzle or key.
//  os: the output stream to send the data (can be the console or a text file).
//  mat: the matrix to print.
//  Returns the output stream object (for chaining purposes).
std::ostream& operator<<(std::ostream& os, const LetterMatrix& mat);

//  Reads a 2D matrix of letters from an input stream.
//  is: the input stream providing the letters (can be the console or a text file).
//  mat: the matrix to fill.
//  Does not return anything; therefore, it does not support chaining.
void operator>>(std::istream& is, LetterMatrix& mat);


//  Compares two letter matrices to see if they contain exactly the same letters in
//  exactly the same locations.
//  m1: a matrix of letters
//  m2: another matrix of letters
//  Returns true if the m1 and m2 are identical; otherwise, returns false
bool operator==(const LetterMatrix& m1, const LetterMatrix& m2);


#endif
