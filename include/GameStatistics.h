//
// Created by janni on 10.12.2025.
//

#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

#include <string>
#include <map>
#include <vector>
#include "IGameObserver.h"
#include "GameFactory.h"
#include <optional>

class GameStatistics : public IGameObserver {
private:
    struct GameResult {
        int attempts;      // Number of attempts taken
        bool won;          // Whether the game was won
        GameFactory::GameMode mode;         // Game mode (e.g., Easy=0, Normal=1, Hard=2)
    };


    std::vector<GameResult> m_results;  // Collection of all game results
    bool m_trackingEnabled = true;      // If false, onGameFinished will not record results

public:
    /**
     * @brief Constructor for GameStatistics.
     */
    GameStatistics();

    /**
     * @brief Enables or disables tracking of game results.
     * @param enabled If true, game results will be recorded; if false, they will be ignored
     */
    void setTrackingEnabled(bool enabled);

    /**
     * @brief Gets whether tracking is currently enabled.
     * @return true if tracking is enabled, false otherwise
     */
    [[nodiscard]] bool isTrackingEnabled() const;

    // IGameObserver interface implementation
    void onGameFinished(int attempts, bool won, GameFactory::GameMode mode) override;

    void collectResult(int attempts, bool won, GameFactory::GameMode mode);     //called after each game to collect result

    // Speichert im Klartext
    bool saveToFile(const std::string& filename);
    // Speichert verschlüsselt mit gegebenem Key
    bool saveToFile(const std::string& filename, int encryptionKey);

    // Lädt Klartext
    std::map<std::string, int> loadFromFile(const std::string& filename);
    // Lädt verschlüsselt mit gegebenem Key
    std::map<std::string, int> loadFromFile(const std::string& filename, int encryptionKey);

    int getTotalGames(std::optional<GameFactory::GameMode> mode = std::nullopt) const;

    int getWonGames(std::optional<GameFactory::GameMode> mode = std::nullopt) const;

    int getLostGames(std::optional<GameFactory::GameMode> mode = std::nullopt ) const;

    double getWinRate(std::optional<GameFactory::GameMode> mode = std::nullopt) const;

    void clear();   //clears all collected statistics

    void statisticMenu();   //Console Menu for Statistic

    std::string encryptData(const std::string& data, int encryptionKey); // Simple encryption function
    std::string decryptData(const std::string& data, int encryptionKey); // Simple decryption function

    ~GameStatistics() = default;
};

#endif //GAMESTATISTICS_H

