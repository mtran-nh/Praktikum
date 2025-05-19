//
// Created by janni on 09.02.2026.
//

#ifndef WORDLESOLVER_H
#define WORDLESOLVER_H

#include <string>
#include <vector>
#include <unordered_set>
#include <array>
#include <unordered_map>

class WordleSolver {
public:
  std::vector<std::string> possibleWords = {};
  std::vector<std::string> allWords = {};
  std::unordered_set<char> absentLetters = {};
  std::unordered_map<std::string, double> precomputedEntropy = {};
  bool isFirstGuess = true;

  // If true, use all words (including non-solutions like "soare") for FIRST guess only
  // If false, only use solution words for guessing
  // Note: After first guess, always uses possibleWords only (required for hard mode)
  bool useAllWordsForFirstGuess = true;

  // All valid words (including non-solutions) for first guess when useAllWordsForFirstGuess=true
  std::vector<std::string> allValidWords = {};


  void loadWords();
  double calculateEntropy(const std::string& guess, const std::vector<std::string>& possibleWords) const;
  void addAbsentLetters(const std::string& guess, const std::array<int, 5>& feedback);
  void printGuessingInfo() const;
  void printEntropyResults(const std::vector<std::pair<std::string, double>>& entropyResults);
  void printBestGuess(const std::string& guess);
  std::string nextGuess();
  void updatePossibleWords(const std::string& guess, const std::array<int, 5>& feedback);

private:
  // Konvertiert ein Pattern-Array zu einem String (z.B. {1,0,2,2,1} -> "10221")
  static std::string patternToString(const std::array<int, 5>& pattern);
};



#endif //WORDLESOLVER_H
