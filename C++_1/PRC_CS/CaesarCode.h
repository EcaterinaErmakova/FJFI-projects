#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <set>§
#include "Dictionary.h"

class CaesarCode {
private:
    // Define lowercase alphabet
    const std::string abc = "abcdefghijklmnopqrstuvwxyz";
    // Define symbols that are not coded/decoded
    const std::set<char> symbols = {' ', ',', '.', '?', '!', ':', ';', '/', '%', '*', '(', ')', 
                                    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '&', '\''};
    // Define dictionary.
    DictionaryNode dictionary;
    // Private methods:
    // Add word to the dictionary.
    void add_word(DictionaryNode& node, const std::string& word, size_t index = 0);
    // Control, if word is in a dictionary.
    bool if_word_exists(const std::string& word, const DictionaryNode& node, size_t index = 0) const;
    // Rewrite word (code / decode) with given key.
    std::string rewriting_word(const std::string& word, const std::unordered_map<char, char>& abc_key) const;
    // Control, if given key decoded existing word.
    bool if_key_is_found(const std::vector<std::string>& words, int key, const DictionaryNode& dict, int count = 0) const;

public:
  CaesarCode(const CaesarCode &) = default;
  CaesarCode(CaesarCode &&) = default;
  CaesarCode &operator=(const CaesarCode &) = delete;
  CaesarCode &operator=(CaesarCode &&) = delete;
  // Constructor: reads file of words and adds them to rhe dictionary.
  explicit CaesarCode(const std::string &dictFilename);
  // Main functions:
  void code_text() const;
  void decode_text() const;

  // Helper functions:
  // Creat shifted alphabeth for coding with given key.
  std::unordered_map<char, char> creating_coder(int key) const;
  // Creat shifted alphabeth for decoding with given key.
  std::unordered_map<char, char> creating_decoder(int key) const;
  // Rewrite text with given key.
  std::string
  rewriting_text(const std::string &text,
                 const std::unordered_map<char, char> &abc_key) const;
  // Reconstruct text into vector with separeted words.
  std::vector<std::string> split_text(const std::string &text) const;
};