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
  throw std::logic_error("GameFactory::createGame is not implemented yet.");
}
