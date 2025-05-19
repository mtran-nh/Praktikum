//
// Created by Marcel Auer on 04.03.2025.
//

#include "HardGame.h"


/**
 * @brief Processes the player's word guess and returns the result.
 *
 * This method performs several checks:
 * 1. Verifies that the entered word has exactly 5 letters.
 * 2. Checks if the word contains only letters.
 * 3. Checks if the maximum number of guesses has been reached.
 * 4. Converts the entered word to lowercase.
 * 5. Checks if the entered word is a valid guess.
 * 6. Compares the entered word with the solution and checks:
 *    - If correct letters from the previous round are reused.
 *    - If yellow letters from the previous round are reused.
 * 7. Updates the game state (e.g., number of guesses, win status).
 *
 * @param word The word entered by the player to be checked.
 * @return An array of 5 values representing the status of each letter compared
 *         to the solution:
 *         - 0: Letter does not appear in the solution.
 *         - 1: Letter appears in the solution but in the wrong position.
 *         - 2: Letter is correct and in the correct position.
 *
 * @throws NotAFiveLetterWordException If the entered word does not have exactly 5 letters.
 * @throws WordContainsNonLetterException If the entered word contains non-letter characters.
 * @throws GuessLimitReachedException If the maximum number of guesses has been reached.
 * @throws NotAValidWordException If the entered word is not a valid guess.
 * @throws GreenLetterNotReusedException If correct letters from the previous round are not reused.
 * @throws YellowLetterNotReusedException If yellow letters from the previous round are not reused.
 */
std::array<int, 5> HardGame::enterWord(std::string word) {
  throw std::logic_error("HardGame::enterWord is not implemented yet.");
}
