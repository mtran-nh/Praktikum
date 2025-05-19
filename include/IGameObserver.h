//
// Created by janni on 05.01.2026.
//

#ifndef IGAMEOBSERVER_H
#define IGAMEOBSERVER_H
#include <GameFactory.h>

/**
 * @brief Observer interface for game events.
 *
 * This interface allows observers to be notified when a game is finished.
 */
class IGameObserver {
public:
    /**
     * @brief Called when a game is finished.
     * @param attempts Number of attempts/guesses used
     * @param won Whether the game was won
     * @param mode Game mode (0=Easy, 1=Normal, 2=Hard)
     */
    virtual void onGameFinished(int attempts, bool won, GameFactory::GameMode mode) = 0;

    virtual ~IGameObserver() = default;
};

#endif //IGAMEOBSERVER_H
