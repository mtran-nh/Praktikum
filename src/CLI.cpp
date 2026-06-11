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
  throw std::logic_error("CLI::start is not implemented yet.");
}

/**
 * @brief Prints the game header to the console.
 *
 * Clears the screen and displays general game information, including
 * the game mode and the number of guesses left.
 */
void CLI::printGameHeader() const {
  throw std::logic_error("CLI::printGameHeader is not implemented yet.");
}

/**
 * @brief Starts the bot game loop where the WordleSolver plays.
 *
 * The bot automatically generates guesses using the WordleSolver,
 * processes the feedback, and updates its word list until the game ends.
 */
void CLI::startBotGame() {
  throw std::logic_error("CLI::startBotGame is not implemented yet.");
}
