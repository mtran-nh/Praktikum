//
// Created by Linus Reuter on 13.06.24.
//

#include "EasyGame.h"
#include <cctype> // for std::isalpha
#include <algorithm>
/**
 * @brief Processes the entered word and returns the result.
 *
 * This method performs the following steps:
 * 1. Validates that the entered word has exactly 5 letters.
 * 2. Checks if the word contains only letters.
 * 3. Ensures the player has not exceeded the maximum number of guesses.
 * 4. Compares the entered word with the solution using the Checker instance.
 * 5. Updates the set of wrong letters for letters not in the solution,
 *    considering letters with multiple occurrences.
 * 6. Increments the guess counter.
 * 7. Checks if the player has won by verifying if all letters are correct.
 *
 * @param word The word entered by the player to be checked.
 * @return An array of 5 integers representing the evaluation of each letter:
 *         - 0: Letter is not in the solution.
 *         - 1: Letter is in the solution but in the wrong position.
 *         - 2: Letter is correct and in the correct position.
 *
 * @throws NotAFiveLetterWordException If the entered word does not have exactly 5 letters.
 * @throws WordContainsNonLetterException If the word contains non-letter characters.
 * @throws GuessLimitReachedException If the player has reached the maximum number of guesses.
 */
std::array<int, 5> EasyGame::enterWord(std::string word) {
  // 1. Validates that the entered word has exactly 5 letters.
  if(word.length()!=5){
    throw NotAFiveLetterWordException(word);
  }
  // 2. Checks if the word contains only letters.
  const std::unordered_set<std::string>& validGuesses = m_gameData->getValidGuesses();
  for(char c: word){
    if(!std::isalpha(c)){
      throw WordContainsNonLetterException(word);
    }
  }
  // 3. Ensures the player has not exceeded the maximum number of guesses.
  if(guessLimitReached()){
    throw GuessLimitReachedException();
  }
  // 4. Compares the entered word with the solution using the Checker instance.
  std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return std::tolower(c);});
  auto compareResult = m_checker->check(word, m_gameData->getSolutionWord());

  // 5. Updates the set of wrong letters for letters not in the solution, considering letters with multiple occurrences.
  for(int i=0; i<5; i++){
    if(compareResult[i]==0){
      if(m_gameData->getSolutionWord().find(word[i])==std::string::npos){
        wrong_letters.insert(word[i]);
      }
    }
  }

  // 6. Increments the guess counter.
  m_guesses++;
  // 7. Checks if the player has won by verifying if all letters are correct.
  int sum {0};
  for(auto num:compareResult){
    sum += num;
  }
  if(sum==10){
    m_won=true;
  }
  return compareResult;
}
