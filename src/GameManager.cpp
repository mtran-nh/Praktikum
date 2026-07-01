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
<<<<<<< HEAD
  if (m_game) {
    return true; // Already initialized
  }
  m_game = GameFactory::createGame(m_gameMode, m_guessCount, m_seed);
  if (!m_game) {
    return false; // Failed to create game
  }
  m_player = std::make_unique<CLI>(m_game.get(), m_statistics.get());
  m_game->addObserver(m_statistics.get());
  return true;
=======
  GameFactory gameFactory;
  try{
    m_player = std::make_unique<CLI>(gameFactory.createGame(m_gameMode, m_guessCount, m_seed));
    return true;
  }
  catch(const std::exception& e){
    return false;
  }
>>>>>>> 324efc17d255f05bf3fcc00feb072a467eec2b18
  // throw std::logic_error("GameManager::initialize is not implemented yet.");
}

bool GameManager::newGame(int seed, int guessCount, GameFactory::GameMode gameMode) {
<<<<<<< HEAD
  m_seed = seed;
  m_guessCount = guessCount;
  m_gameMode = gameMode;
  m_game = GameFactory::createGame(m_gameMode, m_guessCount, m_seed);
  if (!m_game) {
    return false; // Failed to create game
  }
  m_player = std::make_unique<CLI>(m_game.get(), m_statistics.get());
  m_game->addObserver(m_statistics.get());
  return true; 
  throw std::logic_error("GameManager::newGame is not implemented yet.");
=======
  GameFactory gameFactory;
  m_seed = seed;
  m_guessCount = guessCount;
  m_gameMode = gameMode;
  try{
    m_player = std::make_unique<CLI>(gameFactory.createGame(m_gameMode, m_guessCount, m_seed));
    return true;
  }
  catch(const std::exception& e){
    return false;
  }
  // throw std::logic_error("GameManager::newGame is not implemented yet.");
>>>>>>> 324efc17d255f05bf3fcc00feb072a467eec2b18
}

/**
 * @brief Starts the game loop.
 *
 * Delegates to the Interface instance to handle the actual game flow.
 * This method should only be called after initialize() returns true.
 */
void GameManager::startGame() {
<<<<<<< HEAD
  if (!m_player) {
    throw std::runtime_error("GameManager::startGame called before initialization.");
  }
  m_player->start();  // Start the game loop in the CLI interface               
  throw std::logic_error("GameManager::startGame is not implemented yet.");
=======
  if(initialize()){
    m_player->start();
  }
  // throw std::logic_error("GameManager::startGame is not implemented yet.");
>>>>>>> 324efc17d255f05bf3fcc00feb072a467eec2b18
}

/**
 * @brief Gets the current game instance.
 *
 * @return Pointer to the Game instance (or nullptr if not initialized)
 */
Game* GameManager::getGame() const {
<<<<<<< HEAD
  return (m_game.get());
  //changing from unique pointer to raw pointer
  throw std::logic_error("GameManager::getGame is not implemented yet.");
=======
  return m_game.get();
  // throw std::logic_error("GameManager::getGame is not implemented yet.");
>>>>>>> 324efc17d255f05bf3fcc00feb072a467eec2b18
}

/**
 * @brief Gets game mode.
 *
 * @return The current game mode
 */
GameFactory::GameMode GameManager::getGameMode() const {
<<<<<<< HEAD
  return (m_gameMode);
  throw std::logic_error("GameManager::getGameMode is not implemented yet.");
=======
  return m_gameMode;
  // throw std::logic_error("GameManager::getGameMode is not implemented yet.");
>>>>>>> 324efc17d255f05bf3fcc00feb072a467eec2b18
}

/**
 * @brief Gets guess count.
 *
 * @return The number of guesses allowed
 */
int GameManager::getGuessCount() const {
  return m_guessCount;
  // throw std::logic_error("GameManager::getGuessCount is not implemented yet.");
}

/**
 * @brief Gets seed.
 *
 * @return The random seed used
 */
int GameManager::getSeed() const {
  return m_seed;
  // throw std::logic_error("GameManager::getSeed is not implemented yet.");
}

GameStatistics* GameManager::getStatistics() const {
  return m_statistics.get();
  // throw std::logic_error("GameManager::getStatistics is not implemented yet.");
}

//not yet
void GameManager::recordGameResult() {
  if (!m_game || !m_statistics) {
    return;
  }
  m_statistics->onGameFinished(m_game->usedGuesses(), m_game->won(), m_game->getGameMode());
  // throw std::logic_error("GameManager::recordGameResult is not implemented yet.");
}


bool GameManager::saveStatistics(const std::string& filename) {
  if (!m_statistics)
    return false;
  return true;
  throw std::logic_error("GameManager::saveStatistics is not implemented yet.");
}


std::map<std::string, int> GameManager::loadStatistics(const std::string& filename) {
  if (!m_statistics)
    return {};
  auto loadedStats = m_statistics->loadFromFile(filename);
  return loadedStats;
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

