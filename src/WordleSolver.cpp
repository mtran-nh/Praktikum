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
  throw std::logic_error("WordleSolver::loadWords is not implemented yet.");
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
  throw std::logic_error("WordleSolver::calculateEntropy is not implemented yet.");
}

/**
 * @brief Returns the next guess for the bot.
 */
std::string WordleSolver::nextGuess() {
  throw std::logic_error("WordleSolver::nextGuess is not implemented yet.");
}

/**
 * @brief Adds letters to the absentLetters set based on the guess and feedback.
 *        Letters are added only if they are marked as Absent and not present elsewhere as Correct or Present.
 * @param guess The guessed word.
 * @param feedback The feedback vector for the guess.
 */
void WordleSolver::addAbsentLetters(const std::string& guess, const std::array<int, 5>& feedback) {
  throw std::logic_error("WordleSolver::addAbsentLetters is not implemented yet.");
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
  throw std::logic_error("WordleSolver::updatePossibleWords is not implemented yet.");
}

/**
 * @brief Prints information about the current guessing state.
 *        Displays the number of possible solutions remaining.
 */
void WordleSolver::printGuessingInfo() const {
  throw std::logic_error("WordleSolver::printGuessingInfo is not implemented yet.");
}

/**
 * @brief Prints the entropy results for the remaining possible words.
 * @param entropyResults A vector of pairs containing words and their corresponding entropy values.
 */
void WordleSolver::printEntropyResults(const std::vector<std::pair<std::string, double>>& entropyResults) {
  throw std::logic_error("WordleSolver::printEntropyResults is not implemented yet.");
}

/**
 * @brief Prints the best guess word based on maximum entropy.
 * @param guess The best guess word.
 */
void WordleSolver::printBestGuess(const std::string& guess) {
  throw std::logic_error("WordleSolver::printBestGuess is not implemented yet.");
}


std::string WordleSolver::patternToString(const std::array<int, 5>& pattern) {
  throw std::logic_error("WordleSolver::patternToString is not implemented yet.");
}




