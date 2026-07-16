//
// Created by Linus Reuter on 13.06.24.
//

#include "NormalGame.h"

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
  throw std::logic_error("NormalGame::enterWord is not implemented yet.");
}
