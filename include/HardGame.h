//
// Created by Linus Reuter on 13.06.24.
//

#ifndef HARDGAME_H
#define HARDGAME_H
#include "Game.h"
#include <array>
#include <stdexcept>

/**
 * @brief HardGame-Klasse mit Dependency Injection.
 *
 * Erbt von Game und injiziert Checker und IGameData via Konstruktor.
 */
class HardGame final : public Game
{
public:
    HardGame(int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData);

    std::array<int, 5> enterWord(std::string word) override;

    // destructors
    ~HardGame() override = default;

private:
    std::array<int, 5> lastRes = {0, 0, 0, 0, 0}; // array with result from previous round
    std::string lastGuess = "aaaaa"; // last guess
};

inline HardGame::HardGame(const int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData) :
    Game(guessLimit, std::move(checker), std::move(gameData))
{
    m_gameMode = GameFactory::GameMode::Hard; // Hard mode
}


#endif //HARDGAME_H
