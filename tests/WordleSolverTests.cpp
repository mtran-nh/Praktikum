//
// Created by Marcel Auer on 01.06.2025.
//


#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_approx.hpp>
#include "../include/WordleSolver.h"
#include "../include/Checker.h"
#include "../include/GameExceptions.h"
#include <iostream>

// Feedback constants for readability
constexpr int Absent = 0;
constexpr int Present = 1;
constexpr int Correct = 2;

struct WordleSolverFixture {
  /**
   * @brief Constructor for WordleSolverFixture.
   *
   * Initializes the WordleSolver instance for testing.
   */
  WordleSolverFixture() {
    solver = std::make_unique<WordleSolver>();
    solver->loadWords();
  }
  std::unique_ptr<WordleSolver> solver;  ///< Pointer to the WordleSolver instance.
  Checker checker;                        ///< Checker instance for feedback calculation.
};

TEST_CASE_METHOD(WordleSolverFixture, "WordleSolver_FilteringAndEntropy") {
    std::vector<std::string> words = {"apple", "apply", "angle", "amble"};

    SECTION("AbsentLettersDetected") {
        solver->addAbsentLetters("apple", {Absent, Absent, Absent, Absent, Present});
        auto& absent = solver->absentLetters;
        REQUIRE(absent.count('a') == 1);
        REQUIRE(absent.count('p') == 1);
        REQUIRE(absent.count('l') == 1);
        REQUIRE(absent.count('e') == 0);
    }
    SECTION("NextGuessReturnsWord") {
        std::string guess = solver->nextGuess();
        REQUIRE_FALSE(guess.empty());
    }
    SECTION("FeedbackPatternMatchesChecker") {
        auto fb = checker.check("apple", "apply");
        auto fb2 = checker.check("apple", "apply");
        REQUIRE(fb == fb2);
    }
}

TEST_CASE_METHOD(WordleSolverFixture, "WordleSolver_EntropyCalculation") {
    std::vector<std::string> words = {"apple", "apply", "angle", "amble", "ample", "place", "plate", "table"};

    SECTION("EntropyForGuess") {
        double entropy = solver->calculateEntropy("apple", words);
        REQUIRE(entropy > 0.0);
    }

    SECTION("EntropyForDifferentGuesses") {
        double entropy1 = solver->calculateEntropy("aaaaa", words);
        double entropy2 = solver->calculateEntropy("apply", words);
        REQUIRE(entropy1 < entropy2);
    }
}

TEST_CASE_METHOD(WordleSolverFixture, "WordleSolver_EntropyFirstGuess") {
    std::vector<std::pair<std::string, double>> expected = {
        {"raise", 5.877910},
        {"slate", 5.855775},
        {"crate", 5.834874},
        {"irate", 5.831397},
        {"trace", 5.830549},
        {"arise", 5.820940},
        {"stare", 5.807280},
        {"snare", 5.770089},
        {"arose", 5.767797},
        {"least", 5.751646},
        {"alert", 5.745837},
        {"crane", 5.742782},
        {"stale", 5.738573},
        {"saner", 5.733713},
        {"alter", 5.713171},
        {"later", 5.706089},
        {"react", 5.696354},
        {"leant", 5.684574},
        {"trade", 5.681561},
        {"learn", 5.656074},
        {"cater", 5.646715},
        {"roast", 5.645193},
        {"aisle", 5.636828}
    };

    SECTION("EntropyOfFirstGuessMatchesReference") {
        for (const auto& [word, ref_entropy] : expected) {
            double entropy = solver->calculateEntropy(word, solver->possibleWords);
            REQUIRE(entropy == Catch::Approx(ref_entropy).epsilon(0.0006));
        }
    }
}

TEST_CASE_METHOD(WordleSolverFixture, "WordleSolver_FeedbackPattern") {
    SECTION("FeedbackPattern_Correct") {
        auto feedback = checker.check("apple", "apple");
        REQUIRE(feedback == std::array<int, 5>{Correct, Correct, Correct, Correct, Correct});
    }
    SECTION("FeedbackPattern_PresentAndAbsent") {
        auto feedback = checker.check("apple", "lemon");
        REQUIRE(feedback[0] == Absent);
        REQUIRE(feedback[1] == Absent);
        REQUIRE(feedback[2] == Absent);
        REQUIRE(feedback[3] == Present);
        REQUIRE(feedback[4] == Present);
    }
}

TEST_CASE_METHOD(WordleSolverFixture, "WordleSolver_UpdatePossibleWords") {
    SECTION("UpdatePossibleWords_FiltersCorrectly") {
        std::vector<std::string> before = solver->possibleWords;
        std::string guess = before.front();
        auto feedback = checker.check(guess, before[1]);
        solver->updatePossibleWords(guess, feedback);
        // At least one word should be removed
        REQUIRE(solver->possibleWords.size() < before.size());
        // Check that the guess is not in the possible words anymore
        REQUIRE(std::find(solver->possibleWords.begin(), solver->possibleWords.end(), guess) == solver->possibleWords.end());
    }
}

TEST_CASE_METHOD(WordleSolverFixture, "WordleSolver_NextGuess") {
    SECTION("NextGuess_ReturnsValidWord_WithUseAllWords") {
        solver->useAllWordsForFirstGuess = true;
        std::string guess = solver->nextGuess();
        // When useAllWordsForFirstGuess=true, first guess can be from allValidWords
        REQUIRE(std::find(solver->allValidWords.begin(), solver->allValidWords.end(), guess) != solver->allValidWords.end());
    }

    SECTION("NextGuess_ReturnsValidWord_WithoutUseAllWords") {
        solver->useAllWordsForFirstGuess = false;
        std::string guess = solver->nextGuess();
        // When useAllWordsForFirstGuess=false, guess must be from possibleWords
        REQUIRE(std::find(solver->possibleWords.begin(), solver->possibleWords.end(), guess) != solver->possibleWords.end());
    }

    SECTION("NextGuess_AfterFirstGuess_AlwaysFromPossibleWords") {
        solver->useAllWordsForFirstGuess = true;
        std::string firstGuess = solver->nextGuess();
        // Simulate feedback to reduce possibleWords
        std::array<int, 5> feedback = {0, 0, 0, 0, 0}; // All absent
        solver->updatePossibleWords(firstGuess, feedback);

        // Second guess must be from possibleWords (hard mode requirement)
        std::string secondGuess = solver->nextGuess();
        REQUIRE(std::find(solver->possibleWords.begin(), solver->possibleWords.end(), secondGuess) != solver->possibleWords.end());
    }
}

TEST_CASE("WordleSolver_ThrowsOnEmptyWordList") {
    WordleSolver emptySolver;
    emptySolver.loadWords();
    emptySolver.possibleWords.clear();
    REQUIRE_THROWS_AS(emptySolver.nextGuess(), NoValidGuessesLeftException);
}

TEST_CASE_METHOD(WordleSolverFixture, "WordleSolver_AddAbsentLetters_DoesNotAddIfPresentElsewhere") {
    // Example: guess = "apple", feedback = [Absent, Correct, Absent, Absent, Absent]
    // The 'p' at position 0 is Absent, but at position 1 it is Correct -> should NOT be added to absentLetters!
    solver->addAbsentLetters("apple", {Absent, Correct, Absent, Absent, Absent});
    auto& absent = solver->absentLetters;
    // 'p' darf NICHT enthalten sein, 'a', 'l', 'e' aber schon
    REQUIRE(absent.count('p') == 0);
    REQUIRE(absent.count('a') == 1);
    REQUIRE(absent.count('l') == 1);
    REQUIRE(absent.count('e') == 1);
}
