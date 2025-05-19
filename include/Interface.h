//
// Created by Linus Reuter on 13.06.24.
//

#ifndef INTERFACE_H
#define INTERFACE_H
#include "Game.h"
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <stdexcept>

class Interface {
protected:
  struct DisplaySymbols {
    char correctPosition = '=';
    char correctLetter = '-';
    char incorrect = '.';
  };
  std::unique_ptr<Game> game;
  std::vector<std::string> m_guesses = {};
  std::vector<std::array<int, 5>> m_results = {};
  DisplaySymbols m_symbols;

  void printState() const;
  void printLegend() const;
  void printPreviousGuesses() const;
  void printNextGuessPrompt() const;
  [[nodiscard]] std::string formatResult(const std::array<int, 5>& result) const;
  [[nodiscard]] char getSymbolForValue(int value) const;

public:
  explicit Interface(std::unique_ptr<Game> game) : game(std::move(game)) {}

  virtual void start() = 0;
  virtual void startBotGame() = 0;
  virtual ~Interface() = default;
};


#endif //INTERFACE_H


