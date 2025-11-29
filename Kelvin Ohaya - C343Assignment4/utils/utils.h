#pragma once

#include <string>
#include <cctype>
#include <algorithm>
#include <array>
#include "../Sequence/Sequence.h"

using stringSequence = Sequence<std::string>;

/**
 * Convert a letter to its 0-based index ('a' -> 0). Returns -1 for non-letters.
 */
int getCharIndex(char c);

/**
 * Normalize/clean a word (e.g., lowercase, strip non-alpha).
 */
std::string cleanWord(const std::string &word);

/**
 * Parse dictionary file/source and fill the provided array of 26 sequences.
 * Signature preserved as a C-array to match existing callers.
 */
void parseFromDictionary(stringSequence (&dictionary)[26]);