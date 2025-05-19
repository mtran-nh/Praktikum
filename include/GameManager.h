//
// Created by janni on 25.11.2025.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <memory>
#include "Game.h"
#include "GameFactory.h"
#include "GameStatistics.h"
#include "Interface.h"

/**
 * @brief GameManager orchestrates the overall game flow and manages dependencies.
 *
 * This class encapsulates the coupling between game creation, configuration,
 * and execution. It follows the Facade pattern to provide a simple interface
 * to complex subsystems (GameFactory, Game, Interface).
 *
 * Benefits:
 * - Decouples client code from direct dependency on GameFactory, Game, and Interface
 * - Simplifies testing by allowing easy mocking of dependencies
 * - Promotes loose coupling and high cohesion
 * - Centralizes game flow logic
 */
class GameManager {
private:
    int m_seed;
    int m_guessCount;
    GameFactory::GameMode m_gameMode;
    std::unique_ptr<Game> m_game;
    std::unique_ptr<Interface> m_player;
    std::unique_ptr<GameStatistics> m_statistics;

    // If false, bot games will not be recorded in statistics
    bool m_trackBotStatistics = true;

public:
    /**
     * @brief Constructor for GameManager.
     *
     * @param seed Random seed for Wordle generation
     * @param guessCount Number of allowed guesses
     * @param gameMode Game difficulty mode (Easy, Normal, Hard)
     */
    GameManager(int seed, int guessCount, GameFactory::GameMode gameMode);

    /**
     * @brief Initializes the game and creates all necessary dependencies.
     *
     * This method orchestrates the creation of:
     * - Game instance via GameFactory
     * - Interface (CLI) instance
     *
     * @return true if initialization was successful, false otherwise
     */
    bool initialize();

    bool newGame(int seed, int guessCount, GameFactory::GameMode gameMode);

    /**
     * @brief Starts the game loop.
     *
     * Delegates to the Interface instance to handle the actual game flow.
     */
    void startGame();

    /**
     * @brief Gets the current game instance.
     *
     * @return Pointer to the Game instance (or nullptr if not initialized)
     */
    [[nodiscard]] Game* getGame() const;

    /**
     * @brief Gets game mode.
     *
     * @return The current game mode
     */
    [[nodiscard]] GameFactory::GameMode getGameMode() const;

    /**
     * @brief Gets guess count.
     *
     * @return The number of guesses allowed
     */
    [[nodiscard]] int getGuessCount() const;

    /**
     * @brief Gets seed.
     *
     * @return The random seed used
     */
    [[nodiscard]] int getSeed() const;

    /**
     * @brief Gets the GameStatistics instance.
     *
     * @return Pointer to the GameStatistics instance
     */
    [[nodiscard]] GameStatistics* getStatistics() const;

    /**
     * @brief Records the result of the current game to statistics.
     *
     * Should be called after a game ends to collect the result.
     */
    void recordGameResult();

    /**
     * @brief Saves statistics to a CSV file.
     *
     * @param filename Path to the CSV file
     * @return true if successful, false otherwise
     */
    bool saveStatistics(const std::string& filename);

    /**
     * @brief Loads statistics from a CSV file.
     *
     * @param filename Path to the CSV file
     * @return Map containing loaded statistics
     */
    std::map<std::string, int> loadStatistics(const std::string& filename);

    void startBotGame();

    /**
     * @brief Sets whether bot games should be tracked in statistics.
     *
     * @param track If true, bot games are recorded in statistics; if false, they are not
     */
    void setTrackBotStatistics(bool track);

    /**
     * @brief Gets whether bot games are tracked in statistics.
     *
     * @return true if bot games are recorded, false otherwise
     */
    [[nodiscard]] bool getTrackBotStatistics() const;

    /**
     * @brief Destructor.
     */
    ~GameManager() = default;
};

#endif //GAMEMANAGER_H

