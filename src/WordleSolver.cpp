//
// Created by janni on 09.02.2026.
//

#include "../include/WordleSolver.h"
#include "../include/GameExceptions.h"
#include "Checker.h"
#include <cmath>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

/**
 * @brief Lädt die Wortlisten aus words-with-entropy.csv.
 *
 * Liest alle Wörter mit is_solution=1 und ihre vorberechneten Entropie-Werte.
 */
void WordleSolver::loadWords() {
  std :: ifstream file("../data/words-with-entropy.csv");
  if (!file.is_open()) {
    throw std :: runtime_error("WordleSolver::loadWords file not found.");
  }
  std:: string line;
  std::getline (file, line);
  while (std::getline(file, line)) {
    std:: stringstream ss(line);
    std:: string word;
    std:: string solution;
    std :: string entropy;
    std::getline(ss, word, ',');
    std::getline(ss, solution, ',');
    std::getline(ss, entropy, ',');
    allWords.push_back(word);
    allValidWords.push_back(word);

    if (solution == "1")
      possibleWords.push_back(word);
    precomputedEntropy[word] = std::stod(entropy);
  }
  // throw std::logic_error("WordleSolver::loadWords is not implemented yet.");
}

/**
 * @brief Calculates the Shannon entropy for a given guess word based on the current possible solutions.
 * The formula used is: H(X) = -Σ p(x) * log2(p(x)), where p(x) is the probability of each pattern.
 * The probability p(x) is calculated as the count of each pattern divided by the total number of possible words.
 * @param guess The guess word.
 * @param possibleWords The current set of possible solution words.
 * @return The expected entropy value.
 */
double WordleSolver::calculateEntropy(const std::string& guess, const std::vector<std::string>& possibleWords) const {
  if(possibleWords.empty())
    return 0.0;
  Checker checker;
  std::unordered_map<std::string, int> patternCount;
  for(const auto& word : possibleWords)
  {
    auto feedback = checker.check(guess, word);
    std::string pattern =
        patternToString(feedback);
    patternCount[pattern]++;
  }
  double entropy = 0.0;
  double total = static_cast<double>(possibleWords.size());
  // Shannon entropy
  for(const auto& pair : patternCount)
  {
    double probability =
        pair.second / total;
    entropy -= probability *
               std::log2(probability);
  }
  return entropy;
  // throw std::logic_error("WordleSolver::calculateEntropy is not implemented yet.");
}

/**
 * @brief Returns the next guess for the bot.
 */
std::string WordleSolver::nextGuess() {

  if (possibleWords.empty())
    throw NoValidGuessesLeftException();
  std::vector<std::string> candidates;
  if (isFirstGuess && useAllWordsForFirstGuess)
    candidates = allValidWords;
  else
    candidates = possibleWords;
  std::string bestGuess = "";
  double bestEntropy = -1.0;
  for (const auto& word : candidates) {
    double entropy;
    if (isFirstGuess && precomputedEntropy.find(word) != precomputedEntropy.end())
      entropy = precomputedEntropy.at(word);
    else
      entropy = calculateEntropy(word, possibleWords);
    if (entropy > bestEntropy) {
      bestEntropy = entropy;
      bestGuess = word;
    }
  }
  isFirstGuess = false;
  return bestGuess;
  // throw std::logic_error("WordleSolver::nextGuess is not implemented yet.");
}

/**
 * @brief Adds letters to the absentLetters set based on the guess and feedback.
 *        Letters are added only if they are marked as Absent and not present elsewhere as Correct or Present.
 * @param guess The guessed word.
 * @param feedback The feedback vector for the guess.
 */
void WordleSolver::addAbsentLetters(const std::string& guess, const std::array<int, 5>& feedback) {
  for (int i = 0; i < 5; i++)
  {
    char letter = guess[i];
    if (feedback[i] != 0)
      continue;
    bool existsElsewhere = false;
    for (int j = 0; j < 5; j++) {
      if (guess[j] == letter && feedback[j] != 0){
        existsElsewhere = true;
        break;
      }
    }
    if (!existsElsewhere)
      absentLetters.insert(letter);
  }
  // throw std::logic_error("WordleSolver::addAbsentLetters is not implemented yet.");
}



/**
 * @brief Updates the list of possible words based on feedback.
 *
 * @param guess The word that was guessed
 * @param feedback Array where:
 *   - 0 = letter not in word (grey)
 *   - 1 = letter in word but wrong position (yellow)
 *   - 2 = letter in correct position (green)
 */
void WordleSolver::updatePossibleWords(const std::string& guess, const std::array<int, 5>& feedback) {
    Checker checker;
    std::vector<std::string> filtered;
    for(const auto& word : possibleWords)
    {
      auto result =
          checker.check(guess, word);
      if(result == feedback)
        filtered.push_back(word);
    }
    possibleWords = filtered;
    addAbsentLetters(guess, feedback);
  // throw std::logic_error("WordleSolver::updatePossibleWords is not implemented yet.");
}

/**
 * @brief Prints information about the current guessing state.
 *        Displays the number of possible solutions remaining.
 */
void WordleSolver::printGuessingInfo() const {
  std::cout << "Remaining possible words: "<< possibleWords.size()<< std::endl;
  std::cout << "Absent letters: ";
  for(char c : absentLetters)
    std::cout << c << " ";
  std::cout << std::endl;
  // throw std::logic_error("WordleSolver::printGuessingInfo is not implemented yet.");
}

/**
 * @brief Prints the entropy results for the remaining possible words.
 * @param entropyResults A vector of pairs containing words and their corresponding entropy values.
 */
void WordleSolver::printEntropyResults(const std::vector<std::pair<std::string, double>>& entropyResults) {
  for(const auto& item : entropyResults)
    std::cout << item.first<< " : "<< item.second<< std::endl;
  // throw std::logic_error("WordleSolver::printEntropyResults is not implemented yet.");
}

/**
 * @brief Prints the best guess word based on maximum entropy.
 * @param guess The best guess word.
 */
void WordleSolver::printBestGuess(const std::string& guess) {
  std::cout << "Best guess: "<< guess<< std::endl;
  // throw std::logic_error("WordleSolver::printBestGuess is not implemented yet.");
}


std::string WordleSolver::patternToString(const std::array<int, 5>& pattern) {
  std::string result;
  for (int value : pattern)
    result += std::to_string(value);
  return result;
  // throw std::logic_error("WordleSolver::patternToString is not implemented yet.");
}




