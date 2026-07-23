//
// Created by Marcel Auer on 04.03.2025.
//

#include "CLI.h"
#include <iostream>

#include "Utils.h"
#include <EasyGame.h>
#include <HardGame.h>
#include <NormalGame.h>
#include <vector>
#include "WordleSolver.h"

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
  while (!game->won()&&!game->guessLimitReached())
  {
    // print the game state
    printState();

    std::string input;
    std::cin >> input;
    try{
      std::array<int, 5> result = game->enterWord(input);
      m_guesses.push_back(input);
      m_results.push_back(result);

      if(game->won()){
        std::cout << "You won!" << std::endl;
        return;
      }
      if(game->guessLimitReached()){
        std::cout << "You lost!" << std::endl;
        return;
      }
    }catch(const std::invalid_argument& e){
      std::cout << "\n Wrong" << e.what() << std::endl;
      waitForUser();
      continue;
    }
    catch(const std::exception& e){
      std::cout << "\n Wrong" << e.what() << std::endl;
      waitForUser();
      continue;
    }

  }

  std::cout << "You lost!" << std::endl;
  
  // throw std::logic_error("CLI::start is not implemented yet.");
}

/**
 * @brief Prints the game header to the console.
 *
 * Clears the screen and displays general game information, including
 * the game mode and the number of guesses left.
 */
void CLI::printGameHeader() const {
  switch (game->getGameMode())
  {
  case GameFactory::GameMode::Easy:
    std::cout << "the game mode is Easy";
    break;
  case GameFactory::GameMode::Normal:
    std::cout << "the game mode is Normal";
    break;
  case GameFactory::GameMode::Hard:
    std::cout << "the game mode is Hard";
    break;
  default:
    std::cout << "something wrong";
  }

  
  std::cout << "the number of guesses left" << game->guessLimit() - game->usedGuesses() << std::endl;

}

/**
 * @brief Starts the bot game loop where the WordleSolver plays.
 *
 * The bot automatically generates guesses using the WordleSolver,
 * processes the feedback, and updates its word list until the game ends.
 */
void CLI::startBotGame() {
  WordleSolver solver;
  try {
    solver.loadWords();
  } catch (const std::exception& e) {
    std::cerr << "WordleSolver failed to load words: " << e.what() << std::endl;
    return;
  }

  while (!game->won() && !game->guessLimitReached()) {
    std::string guess;
    try {
      guess = solver.nextGuess();
    } catch (const std::exception& e) {
      std::cerr << "No valid guess from solver: " << e.what() << std::endl;
      break;
    }

    try {
      auto result = game->enterWord(guess);
      m_guesses.push_back(guess);
      m_results.push_back(result);
      solver.updatePossibleWords(guess, result);
      printState();
    } catch (const std::exception& e) {
      std::cerr << "Bot guess failed: " << e.what() << std::endl;
      break;
    }
  }

  if (game->won()) {
    std::cout << "Bot won in " << game->usedGuesses() << " attempts." << std::endl;
  } else if (game->guessLimitReached()) {
    std::cout << "Bot failed. Solution was: ";
    game->printWordleSolution();
  }
}
