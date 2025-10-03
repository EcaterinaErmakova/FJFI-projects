#include "CaesarCode.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

// Constructor loads the dictionary.
CaesarCode::CaesarCode(const std::string& dictFilename) {
    // Open file.
    std::ifstream file(dictFilename);
    // Define word.
    std::string word;
    // Every word from text file is added to the dictionary.
    while (std::getline(file, word)) {
        if (!word.empty()) {
            add_word(dictionary, word);
        }
    }
}
// Function to add the word in dictionary.
void CaesarCode::add_word(DictionaryNode& dict, const std::string& word, size_t index) {
    // If it's the end of the word, then instead of the last letter we define the end of the word.
    if (index == word.size()) {
        dict.isEndOfWord = true;
        return;
    }
    // Define letter in word on (index-1)(th) position.
    char letter = word[index];
    // If the first letter is NOT in the dictionary, we insert the letter as the next (first) key and create a new dictionary as its item.
    if (dict.children.find(letter) == dict.children.end()) {
        dict.children[letter] = DictionaryNode();
    }
    // If it is, then we go to the next letter and repeat algorithm till the word is not ended.
    add_word(dict.children[letter], word, index + 1);
}
// Function constructs key for coding.
std::unordered_map<char, char> CaesarCode::creating_coder(int key) const {
    // Define dictionary: letter on 'n-th' position is code for '(n+1)-th' letter of alphabeta.
    std::unordered_map<char, char> abc_key;
    // Construction of coding due formula.
    for (size_t i = 0; i < abc.size(); i++) {
        // Coding shift.
        abc_key[abc[i]] = abc[(i + key) % 26]; 
    }
    return abc_key;
}
// Function constructs key for decoding
std::unordered_map<char, char> CaesarCode::creating_decoder(int key) const {
    // Define dictionary: letter on 'n-th' position is code for '(n+1)-th' letter of alphabeta
    std::unordered_map<char, char> abc_key;
    // Construction of coding due formula.
    for (size_t i = 0; i < abc.size(); i++) {
        // Decoding shift.
        abc_key[abc[i]] = abc[(i - key + 26) % 26]; 
    }
    return abc_key;
}
// Function for rewriting the word with given key.
std::string CaesarCode::rewriting_word(const std::string& word, const std::unordered_map<char, char>& abc_key) const {
    // Define rewritten word.
    std::string new_word;
    // Rewriting the word.
    for (char letter : word) {
        // Stop if we hit a special symbol.
        if (symbols.count(letter)) break; 
        // Convert to lowercase and rewrite.
        new_word += abc_key.at(tolower(letter)); 
    }
    // The word is rewritten.
    return new_word;
}
// Function for checking if rewritten word is in dictionary
bool CaesarCode::if_word_exists(const std::string& word, const DictionaryNode& dict, size_t index) const {
    /*
    We check each letter with its order. The dictionary has construction of tree, so we are looking
    for needed word in next order:
    - If it has reached the last letter: 
        - Is there a key in its dictionary with value 'true' ? 
            If there is: this decoded word exists and return true.
            If there isn't: stop controling and return False.
    */
    if (index == word.size()) {
        return dict.isEndOfWord;
    }
    /*
    - Is first letter in dictionary?
    If it's not: stop controling and return False.
    If it is: 
        - Is next letter in first letters dictionary as a key?
            If it's not: stop controling and return False.
            If it is: Continue.
            ...
    */
    // Define word, that has to be controlled. 
    char letter = word[index];
    if (dict.children.find(letter) != dict.children.end()) {
        return if_word_exists(word, dict.children.at(letter), index + 1);
    }
    /* If we have reached the last letter 
    and still there is no key in its dictionary with value 'true', 
    then this word doesn't exist. */
    return false;
}
bool CaesarCode::if_key_is_found(const std::vector<std::string>& words, int key, const DictionaryNode& dict, int count) const {
    // There has to be at least 5 decoded words in text, that exist in English languege.
    if (count >= 5) return true;
    // If it's the end of text and number of existing decoded words is less than 5, it's not right shift. 
    if (words.empty()) return false;
    // In other case we decode 1 word and control if it exists (if it does, we increase number of right words).
    std::string word = rewriting_word(words[0], creating_decoder(key));
    if (if_word_exists(word, dictionary)) {
        count++;
    }
    /* Then we recurse the function, but with updated number of existing words (prover) and vector with 1 word less 
    (the one we have been already controled). */
    std::vector<std::string> remaining_words(words.begin() + 1, words.end());
    return if_key_is_found(remaining_words, key, dictionary, count);
}
// Function for rewriting the text with given key
std::string CaesarCode::rewriting_text(const std::string& text, const std::unordered_map<char, char>& abc_key) const {
    // Is used for coding the text or decoding the text with known key.
    // Define new text.
    std::string new_text;
    // Rewriting word by word.
    for (char word: text) {
        // Symbols are not rewritten.
        if (symbols.count(word)) {
            new_text += word;
        }
        // Upper letters are rewritten as lower and then being upper again.
        else if (isupper(word)) {
            /*char new_letter = abc_key.at(tolower(word));
            new_text += toupper(new_letter);*/
            if (abc_key.find(tolower(word)) != abc_key.end()) {
                char new_letter = abc_key.at(tolower(word));
                new_text += toupper(new_letter);
            }
            /*else {
                new_text += word; // keep original character if not in alphabet
            }*/
        }
        /*else if (islower(word)) {
            if (abc_key.find(word) != abc_key.end()) {
                new_text += abc_key.at(word);
            }
            else {
                new_text += word; // keep original character if not in alphabet
            }
        }*/
        // Lower letters are immideatly rewritten.
        else {
            new_text += abc_key.at(word);
        }
        }
    // The text is rewritten.
    return new_text;
}
// Function to split text into words
std::vector<std::string> CaesarCode::split_text(const std::string& text) const {
    // Define vector, which we will need for 'if_key_is_found'.
    std::vector<std::string> words;
    // Used for breaking text into words.
    std::stringstream ss(text);
    // Define separeted word.
    std::string word;
    // Adding each word to the last position in vector.
    while (ss >> word) {
        words.push_back(word);
    }
    // Set of words from text as vector.
    return words;
}
// Main function to code text.
void CaesarCode::code_text() const {
    // Define and enter the value of shift.
    int shift;
    std::cout << "Enter the shift number from 1 to 25: ";
    std::cin >> shift;
    std::cin.ignore();
    // Shift should be between 1 and 25 (included).
    if (shift < 1 || shift > 25) {
        std::cout << "This shift doesn't make any sense!" << std::endl;
        return;
    }
    // Define and enter text for coding.
    std::string text;
    std::cout << "Enter the text for coding (English!!!): ";
    std::getline(std::cin, text);
    // Create the key for code.
    std::unordered_map<char, char> encoder = creating_coder(shift);
    // Rewrite the text.
    std::string encoded = rewriting_text(text, encoder);
    std::cout << "Coded text: " << encoded << std::endl;
}
// Main function to decode text
void CaesarCode::decode_text() const {
    std::string text;
    std::cout << "Enter the text for decoding (English!!!): " << std::endl;
    std::getline(std::cin, text);

    // Reconstructing the text into vector.
    std::vector<std::string> words = split_text(text);
    std::cout << "Found " << words.size() << " words in input." << std::endl;

    // Text should contain at least 5 words.
    if (words.size() < 5) {
        std::cout << "The text is too short for decoding! Need at least 5 words." << std::endl;
        return;
    }
    // Searching for right key.
    bool found = false;
    for (int key = 1; key <= 25; key++) {
        if (if_key_is_found(words, key, dictionary)){
            // Create key for decoding the word.
            std::unordered_map<char, char> decoder = creating_decoder(key);
            // Decode the whole text.
            std::string decoded = rewriting_text(text, decoder);
            std::cout << "Decoded text (shift is " << key << "): " << decoded << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Could not decode the text with any Caesar shift from 1 to 26." << std::endl;
        return;
    }
}