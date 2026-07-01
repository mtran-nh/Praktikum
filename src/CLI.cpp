//
// Created by Marcel Auer on 04.03.2025.
//

#include "../include/CLI.h"
#include <iostream>

#include "../include/Utils.h"
#include "../include/EasyGame.h"
#include "../include/HardGame.h"
#include "../include/NormalGame.h"
#include <vector>
#include "../include/WordleSolver.h"

/**
 * @brief Constructs a CLI interface for the game.
 *
 * Initializes the CLI with a unique pointer to a Game instance.
 *
 * @param game A unique pointer to the Game instance to be used.
 */
CLI::CLI(std::unique_ptr<Game> game) : Interface(std::move(game)) {}

/**
 * @brief Starts the game loop for the CLI interface.
 *
 * Handles user input, validates guesses, and updates the game state.
 * Displays appropriate messages for invalid input, game progress, and
 * the final result (win or lose).
 */
void CLI::start() {
  while (!game->won() && !game->guessLimitReached()) {
    printGameHeader();
    std::string guess;
    std::cout << "Enter your guess: ";
    std::getline(std::cin, guess);
    if (guess.empty()) {
      std::cout << "Empty input!" << std::endl;
      continue;
    }
    // if (game->guessLimitReached()) {
    //   std::cout << "Limit reached!" << std::endl;
    //   break;
    // }
    std::array<int, 5> result = game->enterWord(guess);
    //
    //havent implemented printing red yellow black
    game->printWrongLetters();
  }
  if (game->won())
    std::cout << "You won!" << std::endl;
  else {
    std::cout << "You lost" << std::endl;
    game->printWordleSolution();
  }
  // throw std::logic_error("CLI::start is not implemented yet.");
}

/**
 * @brief Prints the game header to the console.
 *
 * Clears the screen and displays general game information, including
 * the game mode and the number of guesses left.
 */
void CLI::printGameHeader() const {
  std::cout << "=====================\n";
  std::cout << "      WORDLE CLI     \n";
  std::cout << "=====================\n";
  std :: cout << "Guesses: " << game->usedGuesses() << "\n";
  std :: cout << "Guess Limit: " << game->guessLimit() << "\n";
  std :: cout << "Wrong letters: ";
  game->printWrongLetters();
  std :: cout << "\n\n";

  // switch (game->getGameMode())
  // {
  // case GameFactory::GameMode::Easy:
  //   std::cout << "the game mode is Easy";
  //   break;
  // case GameFactory::GameMode::Normal:
  //   std::cout << "the game mode is Normal";
  //   break;
  // case GameFactory::GameMode::Hard:
  //   std::cout << "the game mode is Hard";
  //   break;
  // default:
  //   std::cout << "something wrong";
  // }

  
  // std::cout << "the number of guesses left" << game->guessLimit() - game->usedGuesses() << std::endl;

  // throw std::logic_error("CLI::printGameHeader is not implemented yet.");
}

/**
 * @brief Starts the bot game loop where the WordleSolver plays.
 *
 * The bot automatically generates guesses using the WordleSolver,
 * processes the feedback, and updates its word list until the game ends.
 */
void CLI::startBotGame() {
  WordleSolver solver;
  solver.loadWords();
  while (!game->won() && !game->guessLimitReached()) {
    printGameHeader();
    std ::string guess = solver.nextGuess();
    std ::cout << "Bot guessed: " <<  guess << std::endl;
    std :: array<int, 5> result = game->enterWord(guess);
    solver.updatePossibleWords(guess, result);
  }
  std::cout << "\n===BOT GAME OVER===\n";
  if (game->won())
    std::cout << "You won!" << std::endl;
  else {
    std::cout << "You lost" << std::endl;
    game->printWordleSolution();
  }
  // throw std::logic_error("CLI::startBotGame is not implemented yet.");
}

//entropy related
