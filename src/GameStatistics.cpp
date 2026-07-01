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
  std::string result;
  result.reserve(data.size());
  const unsigned char keyByte = static_cast<unsigned char>(encryptionKey);
  for (unsigned char c : data) {
      result += static_cast<char>(c ^ keyByte);
  }
  return result;
  // throw std::logic_error("GameStatistics::encryptData is not implemented yet.");
}

std::string GameStatistics::decryptData(const std::string& data, int encryptionKey) {
  return encryptData(data, encryptionKey);
  // throw std::logic_error("GameStatistics::decryptData is not implemented yet.");
}


bool GameStatistics::saveToFile(const std::string& filename) {
  std::ofstream of(filename);
  if(!of.is_open()){
    return false;
  }
  of<<"attempts,won,mode\n";
  for(auto gameResult:m_results){
    of << gameResult.attempts << "," 
       << gameResult.won << "," 
       << static_cast<int>(gameResult.mode) << "\n";
  }
  of.close();
  return true;
  // throw std::logic_error("GameStatistics::saveToFile is not implemented yet.");
}


bool GameStatistics::saveToFile(const std::string& filename, int encryptionKey) {
  std::ostringstream plaintext;
  plaintext << "attempts,won,mode\n";
  for (const auto& gameResult : m_results) {
    plaintext << gameResult.attempts << ","
              << gameResult.won << ","
              << static_cast<int>(gameResult.mode) << "\n";
  }

  std::ofstream of(filename, std::ios::binary);
  if (!of.is_open()) {
    return false;
  }
  const std::string encrypted = encryptData(plaintext.str(), encryptionKey);
  of.write(encrypted.data(), static_cast<std::streamsize>(encrypted.size()));
  return true;
}


std::map<std::string, int> GameStatistics::loadFromFile(const std::string& filename) {
  std::ifstream inputfile(filename);
  std::map<std::string, int> result{};
  if(!inputfile.is_open()){
    // throw std::logic_error("can't open the file");
    std::cout<<getTotalGames();
    return result;
  }
  

  std::string line;
  std::getline(inputfile,line);
  std::string attempt, won, mode;

  while(std::getline(inputfile, line))
  {
    if(line.empty()) {
        continue; 
    }
    std::stringstream ss(line);
    std::getline(ss, attempt, ',');
    std::getline(ss, won, ',');
    std::getline(ss, mode, ',');  
    try{
      int attempt_int = std::stoi(attempt);
      bool won_bool = std::stoi(won)!=0?true:false;
      auto game_model = static_cast<GameFactory::GameMode>(std::stoi(mode));
      m_results.push_back({attempt_int, won_bool, game_model});
    }  
    catch(const std::exception& e){
      // throw("invalid input");
      continue;
    }
  }
  if(m_results.empty()){
    return result;
  }
  result["totalGames"]=getTotalGames();
  result["wonGames"]=getWonGames();
  result["lostGames"]=getLostGames();
  result["winRate"]=getWinRate();
  return result;
  
  // throw std::logic_error("GameStatistics::loadFromFile is not implemented yet.");
}


std::map<std::string, int> GameStatistics::loadFromFile(const std::string& filename, int encryptionKey) {
  std::ifstream inputfile(filename, std::ios::binary);
  std::map<std::string, int> result{};
  if (!inputfile.is_open()) {
    return result;
  }

  std::stringstream buffer;
  buffer << inputfile.rdbuf();
  std::stringstream csv(decryptData(buffer.str(), encryptionKey));

  std::string line;
  std::getline(csv, line);
  std::string attempt, won, mode;

  while (std::getline(csv, line)) {
    if (line.empty()) {
      continue;
    }
    std::stringstream ss(line);
    std::getline(ss, attempt, ',');
    std::getline(ss, won, ',');
    std::getline(ss, mode, ',');
    try {
      m_results.push_back({
          std::stoi(attempt),
          std::stoi(won) != 0,
          static_cast<GameFactory::GameMode>(std::stoi(mode))});
    } catch (const std::exception&) {
      continue;
    }
  }

  if (m_results.empty()) {
    return result;
  }
  result["totalGames"] = getTotalGames();
  result["wonGames"] = getWonGames();
  result["lostGames"] = getLostGames();
  result["winRate"] = static_cast<int>(getWinRate());
  return result;
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
    return gamesNum;
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
  const int total = getTotalGames(mode);
  if (total == 0) {
    return 0.0;
  }
  return static_cast<double>(getWonGames(mode)) / total * 100.0;
}

void GameStatistics::clear() {
  m_results.clear();
  // throw std::logic_error("GameStatistics::clear is not implemented yet.");
}

void GameStatistics::statisticMenu() {
  throw std::logic_error("GameStatistics::statisticMenu is not implemented yet.");
}
                                        