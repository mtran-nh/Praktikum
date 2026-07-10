//
// Created by Linus Reuter on 13.06.24.
//

#include "NormalGame.h"
#include <cctype> // for std::isalpha
#include <algorithm>
/**
 * @brief Processes the player's word guess and returns the result.
 *
 * * This method performs several checks:
 * 1. Verifies that the entered word has exactly 5 letters.
 * 2. Checks if the word contains only letters.
 * 3. Checks if the maximum number of guesses has been reached.
 * 4. Converts the entered word to lowercase.
 * 5. Checks if the entered word is a valid guess.
 * 6. Updates the game state (e.g., number of guesses, win status).
 *
 * @param word The player's guessed word.
 * @return An array of integers representing the result of the guess:
 *         - 2: Correct letter in the correct position.
 *         - 1: Correct letter in the wrong position.
 *         - 0: Incorrect letter.
 * @throws NotAFiveLetterWordException If the guessed word does not have exactly
 * 5 letters.
 * @throws GuessLimitReachedException If the player has reached the maximum
 * number of guesses.
 * @throws NotAValidWordException If the guessed word is not in the list of
 * valid guesses.
 * @throws WordContainsNonLetterException If the guessed word contains
 * non-letter characters.
 */
std::array<int, 5> NormalGame::enterWord(std::string word) {
 // 1. Verifies that the entered word has exactly 5 letters.
  if(word.length()!=5){
    std::cout << "the word is not 5 letters!!!";
    throw NotAFiveLetterWordException(word);
  }
  // 2. Checks if the word contains only letters.
  for(auto l:word){
    if(!std::isalpha(l)){
      throw WordContainsNonLetterException(word);
    }
  }
  // 3. Checks if the maximum number of guesses has been reached.
  if(guessLimitReached()){
    throw GuessLimitReachedException();
  }
  // 4. Converts the entered word to lowercase.
  std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return std::tolower(c);});
  // 5. Checks if the entered word is a valid guess.
  if(m_gameData->getValidGuesses().find(word)==m_gameData->getValidGuesses().end()){
    throw NotAValidWordException(word);
  } 
  
  // 6. Updates the game state (e.g., number of guesses, win status).
  auto result =  m_checker->check(word, m_gameData->getSolutionWord());
  int sum {0};
  for(auto num:result){
    sum += num;
  }
  if(sum==10 && !guessLimitReached()){
    m_won = true;
  }
  m_guesses++;
  return result;

  //throw std::logic_error("NormalGame::enterWord is not implemented yet.");
}
