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
  switch (mode) {
    case GameMode ::Easy :
        return std:: make_unique<EasyGame>(guessCount, seed);
    case GameMode ::Normal :
        return std:: make_unique<NormalGame>(guessCount, seed);
    case GameMode ::Hard :
        return std:: make_unique<HardGame>(guessCount, seed);
    default :
      throw std::logic_error("GameFactory::createGame is not implemented yet.");
  }
}
