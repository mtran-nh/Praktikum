
#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include <memory>
#include "Game.h"
class Game;
class GameFactory {
public:
    enum class GameMode {
        Easy,
        Normal,
        Hard
    };

    /**
     * @brief Creates a new game instance based on the specified mode.
     *
     * This factory method orchestrates the creation of all necessary dependencies
     * (Wordle, Checker) and creates the corresponding Game object.
     *
     * @param mode The game mode (Easy, Normal, Hard)
     * @param guessCount The number of allowed guesses
     * @param seed The seed for Wordle generation
     * @return A unique_ptr to the new Game object
     */
    static std::unique_ptr<Game> createGame(GameMode mode, int guessCount, int seed);
};

#endif //GAMEFACTORY_H
