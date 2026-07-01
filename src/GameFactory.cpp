//
// Created by janni on 15.11.2025.
//

#include "../include/GameFactory.h"
#include "../include/Checker.h"
#include "../include/EasyGame.h"
#include "../include/HardGame.h"
#include "../include/NormalGame.h"
#include "../include/Wordle.h"

std::unique_ptr<Game> GameFactory::createGame(GameMode mode, int guessCount, int seed) {
    std::shared_ptr<IGameData> gameData = std::make_shared<Wordle>(seed);
    std::unique_ptr<Checker> checker = std::make_unique<Checker>(gameData);
    switch (mode) {
        case GameMode::Easy:
            return std::make_unique<EasyGame>(guessCount, std::move(checker), gameData);
        case GameMode::Normal:
            return std::make_unique<NormalGame>(guessCount, std::move(checker), gameData);
        case GameMode::Hard:
            return std::make_unique<HardGame>(guessCount, std::move(checker), gameData);
        default:
            return std::make_unique<NormalGame>(guessCount, std::move(checker), gameData);
    }
    // throw std::logic_error("GameFactory::createGame is not implemented yet.");
}
