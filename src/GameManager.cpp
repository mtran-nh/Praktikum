//
// Created by janni on 25.11.2025.
//

#include "../include/GameManager.h"
#include "../include/CLI.h"
#include "../include/GameStatistics.h"

/**
 * @brief Constructor for GameManager.
 *
 * Stores the configuration parameters for later use.
 *
 * @param seed Random seed for Wordle generation
 * @param guessCount Number of allowed guesses
 * @param gameMode Game difficulty mode
 */
GameManager::GameManager(int seed, int guessCount, GameFactory::GameMode gameMode)
        : m_seed(seed), m_guessCount(guessCount), m_gameMode(gameMode), m_statistics(std::make_unique<GameStatistics>()) {}

/**
 * @brief Initializes the game and creates all necessary dependencies.
 *
 * Orchestrates the creation of:
 * - Game instance via GameFactory (which in turn creates Wordle and Checker)
 * - CLI Interface instance
 *
 * @return true if initialization was successful, false otherwise
 */
bool GameManager::initialize() {
  throw std::logic_error("GameManager::initialize is not implemented yet.");
}

bool GameManager::newGame(int seed, int guessCount, GameFactory::GameMode gameMode) {
  throw std::logic_error("GameManager::newGame is not implemented yet.");
}

/**
 * @brief Starts the game loop.
 *
 * Delegates to the Interface instance to handle the actual game flow.
 * This method should only be called after initialize() returns true.
 */
void GameManager::startGame() {
  throw std::logic_error("GameManager::startGame is not implemented yet.");
}

/**
 * @brief Gets the current game instance.
 *
 * @return Pointer to the Game instance (or nullptr if not initialized)
 */
Game* GameManager::getGame() const {
  // return (m_game.get());
  //changing from unique pointer to raw pointer
  throw std::logic_error("GameManager::getGame is not implemented yet.");
}

/**
 * @brief Gets game mode.
 *
 * @return The current game mode
 */
GameFactory::GameMode GameManager::getGameMode() const {
  // return (m_gameMode);
  throw std::logic_error("GameManager::getGameMode is not implemented yet.");
}

/**
 * @brief Gets guess count.
 *
 * @return The number of guesses allowed
 */
int GameManager::getGuessCount() const {
  // return (m_guessCount);
  throw std::logic_error("GameManager::getGuessCount is not implemented yet.");
}

/**
 * @brief Gets seed.
 *
 * @return The random seed used
 */
int GameManager::getSeed() const {
  // return (m_seed);
  throw std::logic_error("GameManager::getSeed is not implemented yet.");
}

GameStatistics* GameManager::getStatistics() const {
  // return (m_statistics.get());
  throw std::logic_error("GameManager::getStatistics is not implemented yet.");
}

//not yet
void GameManager::recordGameResult() {
  // if (!m_game || !m_statistics) {
  //   return;
  // }
  throw std::logic_error("GameManager::recordGameResult is not implemented yet.");
}


bool GameManager::saveStatistics(const std::string& filename) {
  // if (!m_statistics)
  //   return false;
  // return true;
  throw std::logic_error("GameManager::saveStatistics is not implemented yet.");
}


std::map<std::string, int> GameManager::loadStatistics(const std::string& filename) {
  throw std::logic_error("GameManager::loadStatistics is not implemented yet.");
}


void GameManager::startBotGame() {
  throw std::logic_error("GameManager::startBotGame is not implemented yet.");
}

void GameManager::setTrackBotStatistics(bool track) {
  throw std::logic_error("GameManager::setTrackBotStatistics is not implemented yet.");
}

bool GameManager::getTrackBotStatistics() const {
  throw std::logic_error("GameManager::getTrackBotStatistics is not implemented yet.");
}

