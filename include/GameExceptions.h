//
// Created by Linus Reuter on 16.07.24.
//

#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H

#include <stdexcept>

class GuessLimitReachedException final : public std::runtime_error {
 public:
  explicit GuessLimitReachedException()
      : std::runtime_error("The guess limit was exceeded!") {}
};

class GreenLetterNotReusedException final : public std::runtime_error {
 public:
  explicit GreenLetterNotReusedException(const char letter)
      : std::runtime_error(std::string("The letter '") + letter +
                           "' was guessed correctly in the previous guess and "
                           "must be reused in the next guess!") {}
};

class YellowLetterNotReusedException final : public std::runtime_error {
 public:
  explicit YellowLetterNotReusedException(const char letter)
      : std::runtime_error(
            std::string("The letter '") + letter +
            "' is in the solution and must be reused in the next guess!") {}
};

class NotAValidWordException final : public std::runtime_error {
 public:
  explicit NotAValidWordException(const std::string& word)
      : std::runtime_error(
            std::string("The word '") + word +
            "' is not a valid Word. Please try again!") {}
};

class NotAFiveLetterWordException final : public std::invalid_argument {
 public:
  explicit NotAFiveLetterWordException(const std::string& word)
      : std::invalid_argument(
            "The word must be exactly 5 letters long! Entered Word:" + word) {}
};

class WordContainsNonLetterException final : public std::invalid_argument {
 public:
  explicit WordContainsNonLetterException(const std::string& word)
      : std::invalid_argument("The word '" + word + "' contains non-letter characters!") {}
};

class NoValidGuessesLeftException final : public std::runtime_error {
 public:
  explicit NoValidGuessesLeftException()
      : std::runtime_error("No valid guesses left! The word list is empty.") {}
};

class NoMaximumEntropyException final : public std::runtime_error {
 public:
  explicit NoMaximumEntropyException()
      : std::runtime_error("Could not determine a word with maximum entropy!") {}
};

#endif  // GAMEEXCEPTIONS_H
