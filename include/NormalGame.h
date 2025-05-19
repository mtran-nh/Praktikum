//
// Created by Linus Reuter on 13.06.24.
//

#ifndef NORMALGAME_H
#define NORMALGAME_H
#include "Game.h"
#include <stdexcept>

/**
 * @brief NormalGame-Klasse mit Dependency Injection.
 *
 * Erbt von Game und injiziert Checker und IGameData via Konstruktor.
 */
class NormalGame : public Game {
public:
    NormalGame(int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData);

    std::array<int, 5> enterWord(std::string word) override;

    // destructors
    ~NormalGame() override = default;
};

inline NormalGame::NormalGame(const int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData) :
    Game(guessLimit, std::move(checker), std::move(gameData))
{
    m_gameMode = GameFactory::GameMode::Normal; // Normal mode
}

#endif //NORMALGAME_H
