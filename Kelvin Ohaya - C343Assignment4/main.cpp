#include <bits/stdc++.h>
#include "Sequence/Sequence.h"
#include "utils/utils.h"
#include <chrono>

typedef Sequence<std::string> stringSequence;

//function to get average
float getAverage (int total, int size) {
    if (size == 0) return 0.0f;
    return static_cast<float>(total) / static_cast<float>(size);
}

//main spellchecking function
void spellChecker(std::string filename, stringSequence (&dictionary)[26],
    int &totalFoundWords, int &totalNotFoundWords, int &totalFoundComparisons,
    int &totalNotFoundComparisons) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string word;
    //read words from file
    while (file >> word) {
        int comparisons = 0;
        std::string cleanedWord = cleanWord(word);
        if (cleanedWord.empty()) continue;
        int index = getCharIndex(cleanedWord[0]);
        if (index == -1) continue; // skip non-alphabetic

        //search for word in dictionary sequence
        bool found = false;
        for (int i = 0; i < dictionary[index].length(); ++i) {
            auto dictEntry = dictionary[index].entry(i);
            //increment comparisons for each check
            ++comparisons;                             
            if (dictEntry && *dictEntry == cleanedWord) {
                found = true;
                break;
            }
        }

        //update totals based on search result
        if (found) {
            ++totalFoundWords;
            totalFoundComparisons += comparisons;
        } else {
            ++totalNotFoundWords;
            totalNotFoundComparisons += comparisons;
        }
    }
    file.close();
}

int main()
{
    //dictionary will hold 26 sequences, one for each letter of the alphabet
    stringSequence randomDictionary[26];
    int totalFoundWords = 0;
    int totalNotFoundWords = 0;
    int totalFoundComparisons = 0;
    int totalNotFoundComparisons = 0;
    float averageFoundComparisons = 0.0f;
    float averageNotFoundComparisons = 0.0f;

    //populate dictionary from file
    parseFromDictionary(randomDictionary);
    //spellcheck sample file with timer
    auto t0 = std::chrono::steady_clock::now();
    spellChecker("txtFiles/oliverSample.txt", randomDictionary, totalFoundWords,
                 totalNotFoundWords, totalFoundComparisons, totalNotFoundComparisons);
    auto t1 = std::chrono::steady_clock::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::chrono::duration<double> sec = t1 - t0;
    std::cout << "spellChecker: " << ms << " ms (" << sec.count() << " s)\n";

    //calculate averages
    averageFoundComparisons = getAverage(totalFoundComparisons, totalFoundWords);
    averageNotFoundComparisons = getAverage(totalNotFoundComparisons, totalNotFoundWords);
    //print results
    std::cout << "Total words found: " << totalFoundWords << std::endl;
    std::cout << "Total words not found: " << totalNotFoundWords << std::endl;
    std::cout << "Average comparisons for found words: " << averageFoundComparisons << std::endl;
    std::cout << "Average comparisons for not found words: " << averageNotFoundComparisons << std::endl;

    return 0;
}