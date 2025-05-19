//
// Created by Marcel Auer on 04.03.2025.
//

#include <catch2/catch_all.hpp>
#include <stdexcept>
#include "Checker.h"
#include "GameExceptions.h"

/**
 * @brief Test case for exact match in the Checker class.
 *
 * Verifies that the `check` method correctly identifies all letters
 * as exact matches when the guess and solution are identical.
 */
TEST_CASE("Checker_ExactMatch")
{
  Checker checker;
  const auto result = checker.check("apple", "apple");
  REQUIRE(result == (std::array<int, 5>{2, 2, 2, 2, 2}));
}

/**
 * @brief Test case for no matching letters in the Checker class.
 *
 * Verifies that the `check` method correctly identifies no matches
 * when the guess contains no letters from the solution.
 */
TEST_CASE("Checker_NoLettersMatch")
{
  Checker checker;
  const auto result = checker.check("zzzzz", "apple");
  REQUIRE(result == (std::array<int, 5>{0, 0, 0, 0, 0}));
}

/**
 * @brief Test case for some letters matching in correct positions.
 *
 * Verifies that the `check` method correctly identifies letters
 * that match the solution in the correct positions.
 */
TEST_CASE("Checker_SomeLettersMatchCorrectPositions")
{
  Checker checker;
  const auto result = checker.check("appzz", "apple");
  REQUIRE(result == (std::array<int, 5>{2, 2, 2, 0, 0}));
}

/**
 * @brief Test case for mixed matches in correct positions.
 *
 * Verifies that the `check` method correctly identifies a mix of
 * correct and incorrect positions for matching letters.
 */
TEST_CASE("Checker_MixedCorrectAndIncorrectPositions")
{
  Checker checker;
  const auto result = checker.check("zesty", "baste");
  REQUIRE(result == (std::array<int, 5>{0, 1, 2, 2, 0}));
}

/**
 * @brief Test case for some letters matching in wrong positions.
 *
 * Verifies that the `check` method correctly identifies letters
 * that match the solution but are in the wrong positions.
 */
TEST_CASE("Checker_SomeLettersMatchWrongPositions")
{
  Checker checker;
  const auto result = checker.check("ppale", "apple");
  REQUIRE(result == (std::array<int, 5>{1, 2, 1, 2, 2}));
}

/**
 * @brief Test case for mixed correct and incorrect positions.
 *
 * Verifies that the `check` method correctly identifies a mix of
 * correct matches and non-matching letters.
 */
TEST_CASE("Checker_SomeLettersMatchCorrectPositions2")
{
  Checker checker;
  const auto result = checker.check("applz", "apple");
  REQUIRE(result == (std::array<int, 5>{2, 2, 2, 2, 0}));
}

/**
 * @brief Test case for invalid guess length (too short).
 *
 * Verifies that the `check` method throws a NotAFiveLetterWordException
 * when the guess is shorter than 5 letters.
 */
TEST_CASE("Checker_InvalidGuessLengthShort")
{
  Checker checker;
  REQUIRE_THROWS_AS(checker.check("apple", "app"), NotAFiveLetterWordException);
}

/**
 * @brief Test case for invalid guess length (too long).
 *
 * Verifies that the `check` method throws a NotAFiveLetterWordException
 * when the guess is longer than 5 letters.
 */
TEST_CASE("Checker_InvalidGuessLengthLong")
{
  Checker checker;
  REQUIRE_THROWS_AS(checker.check("apple", "appless"), NotAFiveLetterWordException);
}

/**
 * @brief Test case for invalid solution length (too long).
 *
 * Verifies that the `check` method throws a NotAFiveLetterWordException
 * when the solution is longer than 5 letters.
 */
TEST_CASE("Checker_InvalidSolutionLengthLong")
{
  Checker checker;
  REQUIRE_THROWS_AS(checker.check("appless", "apple"), NotAFiveLetterWordException);
}

/**
 * @brief Test case for an empty solution string.
 *
 * Verifies that the `check` method throws a NotAFiveLetterWordException
 * when the solution is an empty string.
 */
TEST_CASE("Checker_EmptyString")
{
  Checker checker;
  REQUIRE_THROWS_AS(checker.check("apple", ""), NotAFiveLetterWordException);
}

/**
 * @brief Test case: Solution "abide" vs Guess "speed".
 *
 * Verifies that the check method returns {0, 0, 1, 0, 1} for this input.
 */
TEST_CASE("Checker_SpeedVsAbide")
{
  Checker checker;
  const auto result = checker.check("speed", "abide");
  REQUIRE(result == (std::array<int, 5>{0, 0, 1, 0, 1}));
}

/**
 * @brief Test case: Solution "erase" vs Guess "speed".
 *
 * Verifies that the check method returns {1, 0, 1, 1, 0} for this input.
 */
TEST_CASE("Checker_SpeedVsErase")
{
  Checker checker;
  const auto result = checker.check("speed", "erase");
  REQUIRE(result == (std::array<int, 5>{1, 0, 1, 1, 0}));
}

/**
 * @brief Test case: Solution "steal" vs Guess "speed".
 *
 * Verifies that the check method returns {2, 0, 2, 0, 0} for this input.
 */
TEST_CASE("Checker_SpeedVsSteal")
{
  Checker checker;
  const auto result = checker.check("speed", "steal");
  REQUIRE(result == (std::array<int, 5>{2, 0, 2, 0, 0}));
}

/**
 * @brief Test case: Solution "crepe" vs Guess "speed".
 *
 * Verifies that the check method returns {0, 1, 2, 1, 0} for this input.
 */
TEST_CASE("Checker_SpeedVsCrepe")
{
  Checker checker;
  const auto result = checker.check("speed", "crepe");
  REQUIRE(result == (std::array<int, 5>{0, 1, 2, 1, 0}));
}