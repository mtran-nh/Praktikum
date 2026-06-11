//
// Created by Marcel Auer on 24.05.2025.
//

#include <iostream>
#include <memory>
#include "../include/CLI.h"
#include "../include/Game.h"
#include "../include/GameFactory.h"
#include "../include/GameManager.h"
#include "../include/Interface.h"
#include "../include/Utils.h"

void printMenu();

GameFactory::GameMode selectMode();


/**
 * @brief Entry point of the Wordle game application.
 *
 * This function initializes the game based on command-line arguments,
 * sets up the game mode, and starts the game with either a human player
 * or a bot interface.
 *
 * @return An integer representing the exit status of the program.
 */
int main() {
  std::cout << "Welcome to Wordle!" << std::endl;
  int seed =
      getRandomSeed();  ///< Random seed for generating the Wordle puzzle.
  int guessCount = 6;   ///< Default number of guesses allowed.
  GameFactory::GameMode gameMode = GameFactory::GameMode::Normal;  ///< Default game mode.




  // Create and initialize the GameManager
  // The GameManager orchestrates the creation of all dependencies and the game flow

  GameManager gameManager(seed, guessCount, gameMode);

  /*
  if (!gameManager.initialize()) {
    std::cerr << "Failed to initialize game manager." << std::endl;
    return 1;
  }
  */
  // Load existing statistics before starting the game
  const std::string statsFilename = "../data/game_statistics.csv";
  gameManager.loadStatistics(statsFilename);

  /* // Uncomment for debugging
  std::cout << "GameMode: " << static_cast<int>(gameManager.getGameMode()) << std::endl;
  std::cout << "Seed: " << gameManager.getSeed() << std::endl;
  std::cout << "Guesses: " << gameManager.getGuessCount() << std::endl;
  */

  int inputMenu = 99;
  do {
    printMenu();
    std::cin >> inputMenu;
    switch (inputMenu) {
      case 0:
        // Save game statistics to CSV file
          if (gameManager.saveStatistics(statsFilename)) {
            std::cout << "\nGame statistics saved to: " << statsFilename << std::endl;
          } else {
            std::cerr << "\nFailed to save game statistics to: " << statsFilename << std::endl;
          }
      break;
      case 1:
          if (!gameManager.newGame(getRandomSeed(), guessCount, selectMode())) {
            std::cerr << "Failed to initialize newGame" << std::endl;
            return 1;
          }
          gameManager.startGame();
      break;
      case 2:
        gameManager.getStatistics()->statisticMenu();
      break;
      case 3:
          if (!gameManager.newGame(getRandomSeed(), guessCount, selectMode())) {
            std::cerr << "Failed to initialize newGame" << std::endl;
            return 1;
          }
          gameManager.startBotGame();
      break;
    }
  }while (inputMenu != 0) ;

  return 0;  ///< Exit the program successfully.

}


void printMenu() {
  std::cout << "Bitte treffen sie eine Auswahl:" << std::endl;
  std::cout << "1. Wordle spielen" <<std::endl;
  std::cout << "2. Statistik Menu" <<std::endl;
  std::cout << "3. Lass den Bot Spielen" <<std::endl;
  std::cout << "0. Speichern und beenden. " <<std::endl;
}
  
GameFactory::GameMode selectMode() {
        int mode;
        std::cout << "Select Game Mode: (0 = Easy, 1 = Normal, 2 = Hard): ";
        std::cin >> mode;

        switch (mode) {
          case 0:
            return GameFactory::GameMode::Easy;
          case 2:
            return GameFactory::GameMode::Hard;
          case 1:
            return GameFactory::GameMode::Normal;
          default:
            return GameFactory::GameMode::Normal;
        }
}