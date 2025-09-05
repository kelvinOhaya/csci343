

#include "SqrMatrix.h"
#include <iostream>
#include <iomanip>

//default constructor. basically what would run if I made SqrMatrix n with no argument;
SqrMatrix::SqrMatrix() {
    size = 1;
    sq = nullptr;
}

//this is what would run if i made SqrMatrix m(N);
SqrMatrix::SqrMatrix(int N) {
    size = N;
    sq = nullptr;
}

//Print all elements of matrix when "cout <<" is called on this object;
std::ostream& operator << (std::ostream& out, const SqrMatrix* matrix){
    //check sq for successful allocation
    if (matrix->sq != nullptr) {
        //iteratively output each cell in the 2D matrix
        for (int i = 0; i < matrix->size; i++) {
            for (int j = 0; j < matrix->size; j++) {
                out << matrix->sq[i][j] << (j!=matrix->size-1? " | ": " ");
            }
            out << std::endl;
            //row-dividing line for clarity
            if (i != matrix->size-1) {
                for (int k = 0; k < matrix->size; k++) {
                    out << "---";
                }
            }

            out << std::endl;
        }
    } else {
        out << "Unable to print matrix: Dynamic memory allocation failed";
    }


    return out;
}

//Take the input of all elements when "cin >>" is called on this object
std::istream& operator >> (std::istream& in, SqrMatrix* matrix){
    //dynamically creating the 2D matrix
    matrix-> sq = new int* [matrix->size];
    for (int i = 0; i < matrix->size; i++) {
        matrix->sq[i] = new int [matrix->size];
    }

    //Iterativiely inputting values into each cell
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            std::cout << "Input for row " << (i+1) << " column " << (j+1) << ": ";
            in >> matrix->sq[i][j];
        }
    }

    return in;
}

//Perform Matrix multiplication when "*" is used to multiply two of these objects toogether
SqrMatrix* SqrMatrix::operator * ( SqrMatrix* const smPtrB){
    //initialize result matrix
    auto* result = new SqrMatrix(size);
    result-> sq = new int* [size];

    //dynamically allocate memory for the result matrix based on the left matrix's size
    for (int i = 0; i < size; i++) {
        result -> sq[i] = new int [size]();//parentheses initialize all values at zero
    }


    /**
     *outer loop(i) = for every row in 'result's' array
     *inner loop(j) = for every row in 'this' array (columns for smPtrB)
     *second inner loop(k) = for every column in 'this' array (rows for smPtrB)
     *
     *Multiply each cell together from 'this' and 'smPtrB', and add the results
     *Store that in result->sq[i][j]
    **/
    for (int i=0; i < size; ++i) {
        for (int j=0; j< size; ++j) {
          for (int k=0; k< size; ++k) {
              result->sq[i][j] += this->sq[i][k]*smPtrB->sq[k][j];
          }
        }
    }

    return result;
}
//get an element in the matrix
int SqrMatrix::getElement(int i, int j){
    return this->sq[i][j];
}

//replace an element in the matrix
void SqrMatrix::putElement(int val, int i, int j){
    this->sq[i][j] = val;
}



