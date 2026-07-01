//
// Created by Linus Reuter on 13.06.24.
//

#ifndef GAME_H
#define GAME_H
#include <array>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include "Checker.h"
#include "GameExceptions.h"
#include "IGameData.h"
#include "IGameObserver.h"

#include <GameFactory.h>

/**
 * @brief Base class for Wordle games using dependency injection.
 *
 * Uses dependency injection for Checker and IGameData (Wordle)
 * to avoid tight coupling and to enable parallel development.
 */
class Game
{
public:
    /**
     * @brief Constructor with dependency injection.
     * @param guessLimit The maximum number of attempts
     * @param checker The checker for word validation (move semantics)
     * @param gameData The IGameData interface for word data (shared_ptr)
     */
    Game(int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData);

    virtual bool guessLimitReached();
    virtual std::array<int, 5> enterWord(std::string word) = 0;
    virtual int usedGuesses();
    virtual int guessLimit();
    virtual bool won();
    void printWrongLetters() const;
    void addWrongLetter(char letter);
    void printWordleSolution() const;
    // added by me
    GameFactory::GameMode getGameMode() const;
    // Observer pattern methods
    void addObserver(IGameObserver* observer);
    void removeObserver(IGameObserver* observer);

    // destructors
    virtual ~Game() = default;

protected:
    int m_guessLimit; // "m_" marks member variables of the class
    int m_guesses = 0;
    bool m_won = false;
    std::unique_ptr<Checker> m_checker;
    std::shared_ptr<IGameData> m_gameData;
    std::set<char> wrong_letters;
    std::vector<IGameObserver*> m_observers; // List of observers
    GameFactory::GameMode m_gameMode = GameFactory::GameMode::Easy; // Game mode: 0=Easy, 1=Normal, 2=Hard

    // Notify all observers that the game has finished
    void notifyGameFinished();
};

inline Game::Game(const int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData) :
    m_guessLimit(guessLimit), m_checker(std::move(checker)), m_gameData(std::move(gameData))
{
}


#endif //GAME_H
