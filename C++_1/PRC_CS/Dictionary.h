#pragma once
#include <unordered_map>
// Structure for the dictionary tree.
struct DictionaryNode {
    // Dictionary structure: {letter, next possible letters (that also is dictionary)}.
    std::unordered_map<char, DictionaryNode> children;
    bool isEndOfWord = false;
};