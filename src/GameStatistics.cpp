//
// Created by janni on 10.12.2025
//

#include "GameStatistics.h"

#include "Utils.h"

#include <EasyGame.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <optional>

GameStatistics::GameStatistics() {
    // Constructor - no initialization needed
}

void GameStatistics::setTrackingEnabled(bool enabled) {
  m_trackingEnabled = enabled;
  // throw std::logic_error("GameStatistics::setTrackingEnabled is not implemented yet.");
}

bool GameStatistics::isTrackingEnabled() const {
  return m_trackingEnabled;
  // throw std::logic_error("GameStatistics::isTrackingEnabled is not implemented yet.");
}

void GameStatistics::onGameFinished(int attempts, bool won, GameFactory::GameMode mode) {
  if (m_trackingEnabled) {
        collectResult(attempts, won, mode);
  }
  // throw std::logic_error("GameStatistics::onGameFinished is not implemented yet.");

}

void GameStatistics::collectResult(int attempts, bool won, GameFactory::GameMode mode) {
  GameResult gameResult = {attempts, won, mode};
  m_results.push_back(gameResult);
  // throw std::logic_error("GameStatistics::collectResult is not implemented yet.");
}

std::string GameStatistics::encryptData(const std::string& data, int encryptionKey) {
  throw std::logic_error("GameStatistics::encryptData is not implemented yet.");
}

std::string GameStatistics::decryptData(const std::string& data, int encryptionKey) {
  throw std::logic_error("GameStatistics::decryptData is not implemented yet.");
}


bool GameStatistics::saveToFile(const std::string& filename) {
  
  // throw std::logic_error("GameStatistics::saveToFile is not implemented yet.");
}


bool GameStatistics::saveToFile(const std::string& filename, int encryptionKey) {
  throw std::logic_error("GameStatistics::saveToFile with encryption is not implemented yet.");
}


std::map<std::string, int> GameStatistics::loadFromFile(const std::string& filename) {
  throw std::logic_error("GameStatistics::loadFromFile is not implemented yet.");
}


std::map<std::string, int> GameStatistics::loadFromFile(const std::string& filename, int encryptionKey) {
  throw std::logic_error("GameStatistics::loadFromFile with decryption is not implemented yet.");
}


int GameStatistics::getTotalGames(std::optional<GameFactory::GameMode> mode) const {
  int gamesNum = {};
  if(!mode.has_value()){
    return m_results.size();
  }
  for(int i=0; i<m_results.size(); i++){
    if(mode == m_results[i].mode){
      gamesNum++;
    }
  }
  return gamesNum;
  // throw std::logic_error("GameStatistics::getTotalGames is not implemented yet.");
}



int GameStatistics::getWonGames(std::optional<GameFactory::GameMode> mode) const {
  int gamesNum = {};
  if(!mode.has_value()){
    for(int i=0; i<m_results.size(); i++){
      if(m_results[i].won){
        gamesNum++;
    }
  } 
    return m_results.size();
  }
  for(int i=0; i<m_results.size(); i++){
    if(mode == m_results[i].mode && m_results[i].won){
      gamesNum++;
    }
  }
  return gamesNum;
  // throw std::logic_error("GameStatistics::getWonGames is not implemented yet.");
}



int GameStatistics::getLostGames(std::optional<GameFactory::GameMode> mode) const {
  int lostGamseNum {0};
  if(!mode.has_value()){
    lostGamseNum = getTotalGames()-getWonGames();
  }
  lostGamseNum = getTotalGames(mode)-getWonGames(mode);
  return lostGamseNum;
  // throw std::logic_error("GameStatistics::getLostGames is not implemented yet.");
}



double GameStatistics::getWinRate(std::optional<GameFactory::GameMode> mode) const {
  return getWonGames(mode)/getTotalGames();
  // throw std::logic_error("GameStatistics::getWinRate is not implemented yet.");
}

void GameStatistics::clear() {
  m_results.clear();
  // throw std::logic_error("GameStatistics::clear is not implemented yet.");
}

void GameStatistics::statisticMenu() {
  throw std::logic_error("GameStatistics::statisticMenu is not implemented yet.");
}
