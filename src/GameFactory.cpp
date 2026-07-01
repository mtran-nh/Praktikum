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
  auto checker = std::make_unique<Checker>();
  auto gameData = std::shared_ptr<Wordle>(new Wordle(seed));
  switch (mode)
  {
    case GameMode::Easy:
      return std::make_unique<EasyGame>(guessCount, std::move(checker), gameData);
    case GameMode::Normal:
      return std::make_unique<NormalGame>(guessCount, std::move(checker), gameData);
    case GameMode::Hard:
      return std::make_unique<HardGame>(guessCount, std::move(checker), gameData);
    default:
      throw std::invalid_argument("Unknown game mode!");
  }
  // throw std::logic_error("GameFactory::createGame is not implemented yet.");
}
