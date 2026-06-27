//
// Created by Marcel Auer 24.05.2025.
//

#include "Game.h"
#include <algorithm>

GameFactory::GameMode Game::getGameMode() const{
  return m_gameMode; 
}
/**
 * @brief Checks if the guess limit has been reached.
 *
 * @return true if the number of guesses is greater than or equal to the limit, false otherwise.
 */
bool Game::guessLimitReached()
{
  return m_guesses>=m_guessLimit;
  //throw std::logic_error("Game::guessLimitReached is not implemented yet.");
}

/**
 * @brief Returns the number of guesses used.
 *
 * @return The number of guesses used.
 */
int Game::usedGuesses()
{
  return m_guesses;
  // throw std::logic_error("Game::usedGuesses is not implemented yet.");
}

/**
 * @brief Returns the guess limit.
 *
 * @return The maximum number of allowed guesses.
 */
int Game::guessLimit()
{
  return m_guessLimit;
  //throw std::logic_error("Game::guessLimit is not implemented yet.");
}

/**
 * @brief Checks if the player has won the game.
 *
 * @return true if the player has won, false otherwise.
 */
bool Game::won()
{
  return m_won;
  //throw std::logic_error("Game::won is not implemented yet.");
}

/**
 * @brief Prints the wrong letters to the console.
 *
 * Displays all letters that were guessed but are not in the solution.
 */
void Game::printWrongLetters() const
{
  if (wrong_letters.empty()) {
        return;
    }
  for(const char& letter : wrong_letters){
    std::cout<<letter;
  }
  std::cout<<std::endl;
  // throw std::logic_error("Game::printWrongLetters is not implemented.");
}

/**
 * @brief Adds a wrong letter to the set of wrong letters.
 *
 * @param letter The letter to add.
 */
void Game::addWrongLetter(const char letter)
{
  wrong_letters.insert(letter);

  // throw std::logic_error("Game::addWrongLetter is not implemented yet.");
}

/**
 * @brief Prints the correct solution to the console.
 *
 * Displays the solution word the player was supposed to guess.
 */
void Game::printWordleSolution() const
{
  std::string solution = m_gameData->getSolutionWord();
  std::cout << solution << std::endl;
  // throw std::logic_error("Game::printWordleSolution is not implemented yet.");
}

/**
 * @brief Adds an observer to the list of observers.
 *
 * @param observer Pointer to the observer to add.
 */
void Game::addObserver(IGameObserver* observer)
{
  m_observers.push_back(observer);
  // throw std::logic_error("Game::addObserver is not implemented yet.");
}

/**
 * @brief Removes an observer from the list of observers.
 *
 * @param observer Pointer to the observer to remove.
 */
void Game::removeObserver(IGameObserver* observer)
{
  m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer),m_observers.end());
  //throw std::logic_error("Game::removeObserver is not implemented yet.");
}

/**
 * @brief Notifies all observers that the game has finished.
 */
void Game::notifyGameFinished()
{
  for(auto observer : m_observers){
    observer->onGameFinished(m_guessLimit, m_won, m_gameMode);
  }
  //throw std::logic_error("Game::notifyGameFinished is not implemented yet.");
}

