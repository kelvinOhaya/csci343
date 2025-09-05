

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

SqrMatrix* SqrMatrix::operator * ( SqrMatrix* const smPtrB){
    //initialize result matrix
    auto* result = new SqrMatrix(size);
    result-> sq = new int* [size];

    //dynamically allocate memory for the result matrix based on the left matrix's size
    for (int i = 0; i < size; i++) {
        result -> sq[i] = new int [size]();//parentheses initialize all values at zero
    }



    for (int i=0; i < size; ++i) {
        for (int j=0; j< size; ++j) {
          for (int k=0; k< size; ++k) {
              result->sq[i][j] += this->sq[i][k]*smPtrB->sq[k][j];
          }
        }
    }

    return result;
}

int SqrMatrix::getElement(int i, int j){
    return 0;
}

void SqrMatrix::putElement(int val, int i, int j){
}

//make allocated memory destruct when out of scope


