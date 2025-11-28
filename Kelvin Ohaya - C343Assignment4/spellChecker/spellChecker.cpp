#include <bits/stdc++.h>
#include "../Sequence/Sequence.h"


typedef Sequence<std::string> stringSequence;
int main()
{
    //dictionary will hold 26 sequences, one for each letter of the alphabet
    stringSequence dictionary[26];
    std::vector<std::string> wordsToCheck;

    //current line in file reader
    std::string line;
    std::stringstream ss;
    std::ifstream dictionaryFile("../txtFiles/random_dictionary.txt");
    while (std::getline(dictionaryFile, line))
    {
        wordsToCheck.push_back(line);
        if (line.empty()) continue;

    }

    for(auto word: wordsToCheck) {
        ss << word << ", ";
    }

    std::cout << ss.str() << std::endl;

    return 0;
}