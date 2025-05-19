//
// Created by Marcel Auer on 03.03.2025.
//

#ifndef EASYGAME_H
#define EASYGAME_H
#include "Game.h"
#include <stdexcept>

/**
 * @brief EasyGame-Klasse mit Dependency Injection.
 *
 * Erbt von Game und injiziert Checker und IGameData via Konstruktor.
 */
class EasyGame final : public Game
{
public:
    EasyGame(int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData);

    std::array<int, 5> enterWord(std::string word) override;

    // destructors
    ~EasyGame() override = default;
};

inline EasyGame::EasyGame(const int guessLimit, std::unique_ptr<Checker> checker, std::shared_ptr<IGameData> gameData) :
    Game(guessLimit, std::move(checker), std::move(gameData))
{
    m_gameMode = GameFactory::GameMode::Easy; // Easy mode
}

#endif //EASYGAME_H
