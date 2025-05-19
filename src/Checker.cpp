//
// Created by Marcel Auer 24.05.2025.
//

#include "Checker.h"


/**
 * @brief Compares a guessed word with the solution and evaluates the match.
 *
 * This method checks the guessed word against the solution word and returns
 * an array indicating the correctness of each letter:
 * - 0: Letter is not in the solution.
 * - 1: Letter is in the solution but in the wrong position.
 * - 2: Letter is correct and in the correct position.
 *
* * If a letter appears multiple times in the solution, the method ensures that each occurrence is correctly accounted for.
  * For example, if the guess is "speed", the result will correctly reflect the positions and counts of 'e'.
  * A) Solution: "abide" -> Guess: "speed" -> Result: {0, 0, 1, 0, 1}
  * B) Solution: "erase" -> Guess: "speed" -> Result: {1, 0, 1, 1, 0}
  * C) Solution: "steal" -> Guess: "speed" -> Result: {2, 0, 2, 0, 0}
  * D) Solution: "crepe" -> Guess: "speed" -> Result: {0, 1, 2, 1, 0}
 *
 * @param guess The guessed word (must be exactly 5 characters long).
 * @param solution The solution word (must be exactly 5 characters long).
 * @return An array of 5 integers representing the evaluation of each letter.
 *
 * @throws NotAFiveLetterWordException If either the solution or the guess
 *         is not exactly 5 characters long.
 */
std::array<int, 5> Checker::check(const std::string guess,
                                  const std::string solution) {
  throw std::logic_error("Checker::check is not implemented yet.");
}
