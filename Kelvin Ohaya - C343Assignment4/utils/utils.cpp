#include "utils.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

//gives index of character in alphabet array
int getCharIndex(char c) {
    if (!std::isalpha(static_cast<unsigned char>(c))) return -1;
    return std::tolower(static_cast<unsigned char>(c)) - 'a';
}

// Function to clean a word by removing punctuation and converting to lowercase
std::string cleanWord(const std::string &word) {
    std::string out;
    out.reserve(word.size());
    for (char ch : word) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

// Function to parse words from a file into the array of sequences
void parseFromDictionary(stringSequence (&dictionary)[26]) {

    std::ifstream ifs;
    ifs.open("txtFiles/random_dictionary.txt");

    // Check if file opened successfully
    if (!ifs.is_open()) {
        std::cerr << "Warning: No dictionary file found." << std::endl;
        return;
    }

    std::string word;
    while (ifs >> word) {
        std::string w = cleanWord(word);
        if (w.empty()) continue;
        int idx = getCharIndex(w.front());
        if (idx < 0 || idx >= 26) continue;
        try {
            dictionary[idx].add(w, dictionary[idx].length());
        } catch (...) {}
    }

    ifs.close();
    std::cerr << "Loaded dictionary from: txtFiles/random_dictionary.txt\n";
}

