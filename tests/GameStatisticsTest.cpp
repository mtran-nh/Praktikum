// filepath: c:\Users\janni\PIT2026\wordlepart1-solution\tests\GameStatisticsTest.cpp
// Created on 16.12.2025

#include <catch2/catch_all.hpp>
#include "GameStatistics.h"
#include "GameFactory.h"
#include <fstream>
#include <filesystem>

// =============================
// --- GameStatistics Tests ---
// =============================

/**
 * @brief Checks that a new GameStatistics object starts with zero games.
 */
TEST_CASE("GameStatistics_Constructor_InitiallyEmpty")
{
    GameStatistics stats;
    REQUIRE(stats.getTotalGames() == 0);
    REQUIRE(stats.getWonGames() == 0);
    REQUIRE(stats.getLostGames() == 0);
    REQUIRE(stats.getWinRate() == 0.0);
}

/**
 * @brief Verifies that collectResult correctly adds a won game.
 */
TEST_CASE("GameStatistics_CollectResult_WonGame")
{
    GameStatistics stats;
    stats.collectResult(3, true, GameFactory::GameMode::Normal);

    REQUIRE(stats.getTotalGames() == 1);
    REQUIRE(stats.getWonGames() == 1);
    REQUIRE(stats.getLostGames() == 0);
    REQUIRE(stats.getWinRate() == Catch::Approx(100.0));
}

/**
 * @brief Verifies that collectResult correctly adds a lost game.
 */
TEST_CASE("GameStatistics_CollectResult_LostGame")
{
    GameStatistics stats;
    stats.collectResult(6, false, GameFactory::GameMode::Normal);

    REQUIRE(stats.getTotalGames() == 1);
    REQUIRE(stats.getWonGames() == 0);
    REQUIRE(stats.getLostGames() == 1);
    REQUIRE(stats.getWinRate() == Catch::Approx(0.0));
}

/**
 * @brief Tests collecting multiple game results and calculating statistics.
 */
TEST_CASE("GameStatistics_CollectResult_MultipleGames")
{
    GameStatistics stats;
    stats.collectResult(3, true, GameFactory::GameMode::Normal);   // Won
    stats.collectResult(4, true, GameFactory::GameMode::Easy);   // Won
    stats.collectResult(6, false, GameFactory::GameMode::Hard);  // Lost
    stats.collectResult(5, true, GameFactory::GameMode::Normal);   // Won

    REQUIRE(stats.getTotalGames() == 4);
    REQUIRE(stats.getWonGames() == 3);
    REQUIRE(stats.getLostGames() == 1);
    REQUIRE(stats.getWinRate() == Catch::Approx(75.0));
}

/**
 * @brief Tests the clear method resets all statistics.
 */
TEST_CASE("GameStatistics_Clear_ResetsAllData")
{
    GameStatistics stats;
    stats.collectResult(3, true, GameFactory::GameMode::Normal);
    stats.collectResult(4, false, GameFactory::GameMode::Easy);

    stats.clear();

    REQUIRE(stats.getTotalGames() == 0);
    REQUIRE(stats.getWonGames() == 0);
    REQUIRE(stats.getLostGames() == 0);
    REQUIRE(stats.getWinRate() == Catch::Approx(0.0));
}

/**
 * @brief Tests saving statistics to a CSV file (Plaintext).
 */
TEST_CASE("GameStatistics_SaveToFile_Plaintext_CreatesValidFile")
{
    GameStatistics stats;
    stats.collectResult(3, true, GameFactory::GameMode::Easy);
    stats.collectResult(4, false, GameFactory::GameMode::Normal);
    stats.collectResult(5, true, GameFactory::GameMode::Hard);

    const std::string testFile = "../data/test_statistics_save.csv";

    // Clean up any existing test file
    std::filesystem::remove(testFile);

    bool success = stats.saveToFile(testFile);
    REQUIRE(success == true);

    // Verify file exists
    REQUIRE(std::filesystem::exists(testFile));

    // Read content directly
    std::ifstream file(testFile);
    REQUIRE(file.is_open());

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    // Verify CSV content
    std::stringstream ss(content);
    std::string line;

    std::getline(ss, line);
    REQUIRE(line == "attempts,won,mode");

    std::getline(ss, line);
    REQUIRE(line == "3,1,0");

    std::getline(ss, line);
    REQUIRE(line == "4,0,1");

    std::getline(ss, line);
    REQUIRE(line == "5,1,2");

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests loading statistics from a CSV file (Plaintext).
 */
TEST_CASE("GameStatistics_LoadFromFile_Plaintext_LoadsCorrectly")
{
    GameStatistics stats;
    const std::string testFile = "../data/test_load_statistics.csv";

    // Create a valid plaintext CSV file
    std::ofstream file(testFile);
    file << "attempts,won,mode\n";
    file << "3,1,0\n";
    file << "4,0,1\n";
    file << "5,1,2\n";
    file << "2,1,0\n";
    file.close();

    // Load from file (plaintext)
    auto result = stats.loadFromFile(testFile);

    REQUIRE(stats.getTotalGames() == 4);
    REQUIRE(stats.getWonGames() == 3);
    REQUIRE(stats.getLostGames() == 1);
    REQUIRE(stats.getWinRate() == Catch::Approx(75.0));

    // Verify returned map
    REQUIRE(result["totalGames"] == 4);
    REQUIRE(result["wonGames"] == 3);
    REQUIRE(result["lostGames"] == 1);
    REQUIRE(result["winRate"] == 75);

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests loading from the provided test CSV file in data directory (Plaintext).
 */
TEST_CASE("GameStatistics_LoadFromFile_Plaintext_ExistingTestFile")
{
    GameStatistics stats;

    const std::string testFile = "../data/test_game_statistics.csv";

    // Create plaintext content
    std::ofstream outFile(testFile);
    outFile << "attempts,won,mode\n";
    outFile << "3,1,0\n";
    outFile << "4,1,1\n";
    outFile << "5,0,2\n";
    outFile << "2,1,0\n";
    outFile << "6,0,1\n";
    outFile << "1,1,2\n";
    outFile << "3,1,0\n";
    outFile.close();

    // Load from the file
    auto result = stats.loadFromFile(testFile);

    // Verify statistics (file has 7 games: 5 wins, 2 losses)
    REQUIRE(stats.getTotalGames() == 7);
    REQUIRE(stats.getWonGames() == 5);
    REQUIRE(stats.getLostGames() == 2);
    REQUIRE(stats.getWinRate() == Catch::Approx(71.428571).epsilon(0.01));

    // Verify returned map
    REQUIRE(result["totalGames"] == 7);
    REQUIRE(result["wonGames"] == 5);
    REQUIRE(result["lostGames"] == 2);

  std::filesystem::remove(testFile);
}

/**
 * @brief Tests loading from a non-existent file returns empty statistics.
 */
TEST_CASE("GameStatistics_LoadFromFile_NonExistentFile")
{
    GameStatistics stats;
    stats.collectResult(1, true, GameFactory::GameMode::Normal); // Add some data first

    auto result = stats.loadFromFile("../data/non_existent_file_xyz.csv");

    // Should return empty map
    REQUIRE(result.empty());

    // Original data should NOT be cleared when file doesn't exist
    REQUIRE(stats.getTotalGames() == 1);
}

/**
 * @brief Tests loading from an empty file.
 */
TEST_CASE("GameStatistics_LoadFromFile_EmptyFile")
{
    GameStatistics stats;
    const std::string testFile = "../data/test_empty.csv";

    // Create empty file
    std::ofstream file(testFile);
    file.close();

    auto result = stats.loadFromFile(testFile);

    REQUIRE(result.empty());
    REQUIRE(stats.getTotalGames() == 0);

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests save and load roundtrip preserves data.
 */
TEST_CASE("GameStatistics_SaveAndLoad_RoundTrip")
{
    GameStatistics stats1;
    stats1.collectResult(1, true, GameFactory::GameMode::Easy);
    stats1.collectResult(2, true, GameFactory::GameMode::Normal);
    stats1.collectResult(3, false, GameFactory::GameMode::Hard);
    stats1.collectResult(4, true, GameFactory::GameMode::Easy);
    stats1.collectResult(5, false, GameFactory::GameMode::Normal);
    stats1.collectResult(6, false, GameFactory::GameMode::Hard);

    const std::string testFile = "../data/test_roundtrip.csv";

    // Save
    bool saveSuccess = stats1.saveToFile(testFile);
    REQUIRE(saveSuccess == true);

    // Load into new object
    GameStatistics stats2;
    auto result = stats2.loadFromFile(testFile);

    // Verify data matches
    REQUIRE(stats2.getTotalGames() == stats1.getTotalGames());
    REQUIRE(stats2.getWonGames() == stats1.getWonGames());
    REQUIRE(stats2.getLostGames() == stats1.getLostGames());
    REQUIRE(stats2.getWinRate() == Catch::Approx(stats1.getWinRate()));

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests that saved file is encrypted when using key. (Bonus)
 */
TEST_CASE("Bonus_GameStatistics_SaveToFile_Encrypted_FileIsEncrypted")
{
    GameStatistics stats;
    stats.collectResult(3, true, GameFactory::GameMode::Easy);
    stats.collectResult(4, false, GameFactory::GameMode::Normal);

    const std::string testFile = "../data/test_encrypted.csv";
    std::filesystem::remove(testFile);

    // Save with encryption key
    int key = 123;
    bool success = stats.saveToFile(testFile, key);
    REQUIRE(success == true);

    // Read raw file content
    std::ifstream file(testFile, std::ios::binary);
    REQUIRE(file.is_open());

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();
    file.close();

    // Verify that file does NOT contain plain text CSV header
    REQUIRE(fileContent.find("attempts,won,mode") == std::string::npos);

    // Verify that file is not empty
    REQUIRE(!fileContent.empty());

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests encryption and decryption functions independently. (Bonus)
 */
TEST_CASE("Bonus_GameStatistics_Encryption_Basic")
{
    GameStatistics stats;
    int key = 42;

    SECTION("Encrypt and decrypt simple string") {
        std::string original = "Hello World!";
        std::string encrypted = stats.encryptData(original, key);
        std::string decrypted = stats.decryptData(encrypted, key);

        REQUIRE(decrypted == original);
        REQUIRE(encrypted != original);  // Should be different after encryption
    }

    SECTION("Encrypt and decrypt CSV header") {
        std::string original = "attempts,won,mode";
        std::string encrypted = stats.encryptData(original, key);
        std::string decrypted = stats.decryptData(encrypted, key);

        REQUIRE(decrypted == original);
        REQUIRE(encrypted != original);
    }

    SECTION("Encrypt and decrypt empty string") {
        std::string original = "";
        std::string encrypted = stats.encryptData(original, key);
        std::string decrypted = stats.decryptData(encrypted, key);

        REQUIRE(decrypted == original);
    }

    SECTION("Encryption is reversible with multiple lines") {
        std::string original = "attempts,won,mode\n3,1,0\n4,0,1\n";
        std::string encrypted = stats.encryptData(original, key);
        std::string decrypted = stats.decryptData(encrypted, key);

        REQUIRE(decrypted == original);
    }
}

/**
 * @brief Tests that encrypted file can be loaded correctly using key. (Bonus)
 */
TEST_CASE("Bonus_GameStatistics_LoadFromFile_Encrypted_File")
{
    GameStatistics stats1;
    stats1.collectResult(2, true, GameFactory::GameMode::Easy);
    stats1.collectResult(4, false, GameFactory::GameMode::Normal);
    stats1.collectResult(5, true, GameFactory::GameMode::Hard);

    const std::string testFile = "../data/test_load_encrypted.csv";
    int key = 99;

    // Save encrypted file
    stats1.saveToFile(testFile, key);

    // Load into new object
    GameStatistics stats2;
    auto result = stats2.loadFromFile(testFile, key);

    // Verify data was loaded correctly
    REQUIRE(stats2.getTotalGames() == 3);
    REQUIRE(stats2.getWonGames() == 2);
    REQUIRE(stats2.getLostGames() == 1);

    REQUIRE(result["totalGames"] == 3);
    REQUIRE(result["wonGames"] == 2);
    REQUIRE(result["lostGames"] == 1);

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests that manually decrypting saved file produces valid CSV. (Bonus)
 */
TEST_CASE("Bonus_GameStatistics_Encryption_ManualDecryptionCheck")
{
    GameStatistics stats;
    stats.collectResult(3, true, GameFactory::GameMode::Easy);

    const std::string testFile = "../data/test_manual_decrypt.csv";
    std::filesystem::remove(testFile);

    int key = 7;
    stats.saveToFile(testFile, key);

    // Read encrypted content
    std::ifstream file(testFile, std::ios::binary);
    REQUIRE(file.is_open());
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string encryptedContent = buffer.str();

    // Manually decrypt
    std::string decrypted = stats.decryptData(encryptedContent, key);

    // Verify decrypted content is valid CSV
    REQUIRE(decrypted.find("attempts,won,mode") != std::string::npos);
    REQUIRE(decrypted.find("3,1,0") != std::string::npos);

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests loading file with invalid data skips bad lines. (Plaintext)
 */
TEST_CASE("GameStatistics_LoadFromFile_Plaintext_InvalidDataSkipped")
{
    GameStatistics stats;
    const std::string testFile = "../data/test_invalid.csv";

    // Create plaintext file with some invalid lines
    std::ofstream file(testFile);
    file << "attempts,won,mode\n";
    file << "3,1,0\n";
    file << "invalid,data,broken\n";  // Invalid line
    file << "4,0,1\n";
    file << "\n";  // Empty line
    file << "5,1,2\n";
    file.close();

    auto result = stats.loadFromFile(testFile);

    // Should load only valid lines
    REQUIRE(stats.getTotalGames() == 3);
    REQUIRE(stats.getWonGames() == 2);
    REQUIRE(stats.getLostGames() == 1);

    // Clean up
    std::filesystem::remove(testFile);
}

/**
 * @brief Tests win rate calculation with different scenarios.
 */
TEST_CASE("GameStatistics_WinRate_VariousScenarios")
{
    SECTION("All wins") {
        GameStatistics stats;
        stats.collectResult(1, true, GameFactory::GameMode::Normal);
        stats.collectResult(2, true, GameFactory::GameMode::Normal);
        stats.collectResult(3, true, GameFactory::GameMode::Normal);
        REQUIRE(stats.getWinRate() == Catch::Approx(100.0));
    }

    SECTION("All losses") {
        GameStatistics stats;
        stats.collectResult(6, false, GameFactory::GameMode::Normal);
        stats.collectResult(6, false, GameFactory::GameMode::Normal);
        stats.collectResult(6, false, GameFactory::GameMode::Normal);
        REQUIRE(stats.getWinRate() == Catch::Approx(0.0));
    }

    SECTION("50-50 split") {
        GameStatistics stats;
        stats.collectResult(3, true, GameFactory::GameMode::Normal);
        stats.collectResult(6, false, GameFactory::GameMode::Normal);
        REQUIRE(stats.getWinRate() == Catch::Approx(50.0));
    }

    SECTION("33.33% win rate") {
        GameStatistics stats;
        stats.collectResult(3, true, GameFactory::GameMode::Normal);
        stats.collectResult(6, false, GameFactory::GameMode::Normal);
        stats.collectResult(6, false, GameFactory::GameMode::Normal);
        REQUIRE(stats.getWinRate() == Catch::Approx(33.333).epsilon(0.01));
    }
}

/**
 * @brief Tests mode-specific statistics methods.
 */
TEST_CASE("GameStatistics_ModeSpecific_Statistics")
{
    GameStatistics stats;

    // Add games for different modes
    stats.collectResult(1, true, GameFactory::GameMode::Easy);
    stats.collectResult(2, true, GameFactory::GameMode::Easy);
    stats.collectResult(3, false, GameFactory::GameMode::Easy);

    stats.collectResult(4, true, GameFactory::GameMode::Normal);
    stats.collectResult(5, false, GameFactory::GameMode::Normal);
    stats.collectResult(6, false, GameFactory::GameMode::Normal);

    stats.collectResult(1, true, GameFactory::GameMode::Hard);
    stats.collectResult(2, false, GameFactory::GameMode::Hard);

    // Test Easy mode
    REQUIRE(stats.getTotalGames(GameFactory::GameMode::Easy) == 3);
    REQUIRE(stats.getWonGames(GameFactory::GameMode::Easy) == 2);
    REQUIRE(stats.getLostGames(GameFactory::GameMode::Easy) == 1);
    REQUIRE(stats.getWinRate(GameFactory::GameMode::Easy) == Catch::Approx(66.667).epsilon(0.01));

    // Test Normal mode
    REQUIRE(stats.getTotalGames(GameFactory::GameMode::Normal) == 3);
    REQUIRE(stats.getWonGames(GameFactory::GameMode::Normal) == 1);
    REQUIRE(stats.getLostGames(GameFactory::GameMode::Normal) == 2);
    REQUIRE(stats.getWinRate(GameFactory::GameMode::Normal) == Catch::Approx(33.333).epsilon(0.01));

    // Test Hard mode
    REQUIRE(stats.getTotalGames(GameFactory::GameMode::Hard) == 2);
    REQUIRE(stats.getWonGames(GameFactory::GameMode::Hard) == 1);
    REQUIRE(stats.getLostGames(GameFactory::GameMode::Hard) == 1);
    REQUIRE(stats.getWinRate(GameFactory::GameMode::Hard) == Catch::Approx(50.0));

    // Test overall statistics
    REQUIRE(stats.getTotalGames() == 8);
    REQUIRE(stats.getWonGames() == 4);
    REQUIRE(stats.getLostGames() == 4);
    REQUIRE(stats.getWinRate() == Catch::Approx(50.0));
}

/**
 * @brief Tests mode-specific win rate with no games.
 */
TEST_CASE("GameStatistics_ModeSpecific_NoGames")
{
    GameStatistics stats;

    REQUIRE(stats.getTotalGames(GameFactory::GameMode::Easy) == 0);
    REQUIRE(stats.getWonGames(GameFactory::GameMode::Easy) == 0);
    REQUIRE(stats.getLostGames(GameFactory::GameMode::Easy) == 0);
    REQUIRE(stats.getWinRate(GameFactory::GameMode::Easy) == 0.0);
}

/**
 * @brief Tests onGameFinished observer method.
 */
TEST_CASE("GameStatistics_OnGameFinished_Observer")
{
    GameStatistics stats;

    stats.onGameFinished(3, true, GameFactory::GameMode::Easy);
    stats.onGameFinished(5, false, GameFactory::GameMode::Normal);

    REQUIRE(stats.getTotalGames() == 2);
    REQUIRE(stats.getWonGames() == 1);
    REQUIRE(stats.getLostGames() == 1);
}

