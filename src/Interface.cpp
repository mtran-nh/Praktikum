//
// Created by Marcel Auer on 04.03.2025.
//

#include "Interface.h"
#include <iostream>

/**
 * @brief Prints the legend for interpreting the game symbols.
 *
 * Displays the meaning of the symbols used in the game:
 * - Correct letter in the correct position.
 * - Correct letter in the wrong position.
 * - Incorrect letter.
 */
void Interface::printLegend() const {
  std::cout<< "Legend:";
  std::cout<< "=: Correct letter in correct position" << std::endl;
  std::cout<< "-: Correct letter in wrong position" << std::endl;
  std::cout<< ".: Incorrect letter" << std::endl;
  // throw std::logic_error("Interface::printLegend is not implemented yet.");
}

/**
 * @brief Prints all previous guesses and their results.
 *
 * Displays each guess made by the player along with the formatted result
 * indicating the correctness of each letter in the guess.
 * Example:
 *  <- apple
 *  -> =-..-
 */
void Interface::printPreviousGuesses() const {
  std::cout << "Previous guesses:" << std::endl;
  for (size_t i = 0; i < m_guesses.size(); i++) {
    std::cout << " <- " << m_guesses[i] << std::endl;
    std::cout << " -> " << formatResult(m_results[i]) << std::endl; 
  }
}

/**
 * @brief Prints a prompt for the next guess if the game is not yet won.
 *
 * Displays a placeholder (" <- ?????\n") for the next guess if the player has
 * not yet won the game.
 */
void Interface::printNextGuessPrompt() const {
  if (!game->won()) {
    std::cout << " <- ?????" << std::endl;
  }
}

/**
 * @brief Formats the result of a guess into a string of symbols.
 *
 * Converts the result array into a string representation using the appropriate
 * symbols for each value.
 *
 * @param result An array of integers representing the result of a guess.
 *               - 2: Correct letter in the correct position.
 *               - 1: Correct letter in the wrong position.
 *               - 0: Incorrect letter.
 * @return A string of symbols representing the result.
 */
std::string Interface::formatResult(const std::array<int, 5>& result) const {
  std::string resultString;
  for(auto i:result){
    resultString.push_back(getSymbolForValue(i));
  }
  return resultString;
  // throw std::logic_error("Interface::formatResult is not implemented yet.");
}

/**
 * @brief Retrieves the symbol corresponding to a result value.
 *
 * Maps the result value to the appropriate symbol:
 * - 2: Correct letter in the correct position.
 * - 1: Correct letter in the wrong position.
 * - 0: Incorrect letter.
 *
 * @param value The result value to map.
 * @return The corresponding symbol as a character.
 */
char Interface::getSymbolForValue(int value) const {
  switch (value)
  {
  case 2:
    return m_symbols.correctPosition;
  case 1:
    return m_symbols.correctLetter;
  case 0:
    return m_symbols.incorrect;
  default:
    return '.';
  }
}


/**
 * @brief Prints the current state of the game.
 *
 * Displays the legend, all previous guesses with their results, and a prompt
 * for the next guess if the game is not yet won.
 */
void Interface::printState() const {
  printLegend();
  printPreviousGuesses();
  printNextGuessPrompt();
  // throw std::logic_error("Interface::printState is not implemented yet.");
}
