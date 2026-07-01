//
// Created by Marcel Auer on 27.02.2025.
//

#include "Wordle.h"
#include <sstream>
#include <random>
#include <unordered_map>
/**
 * @brief Constructs a Wordle object and initializes the game data.
 *
 * This constructor loads the solution words, valid guesses, and determines
 * the solution word based on the provided seed.
 *
 * @param seed An integer used to select the solution word.
 */
Wordle::Wordle(const int seed)
{
  loadWordsWithEntropy();
  getWordleSolutionWord(seed);
  identifyRepeatedLetters(solution);
  //throw std::logic_error("Wordle::Wordle is not implemented yet.");
}

/**
 * @brief Loads all words with entropy from words-with-entropy.csv.
 *
 * Reads words from the file `../data/words-with-entropy.csv`.
 * All words are stored in `wordle_valid_guesses`.
 * Words with is_solution=1 are also stored in `wordle_solution_words`.
 */
void Wordle::loadWordsWithEntropy()
{
  std::ifstream file("../data/words-with-entropy.csv");
  if (!file.is_open()) {
        throw std::runtime_error("Failed to open words-with-entropy.csv");
  }
  std::string line;
  // get the first line
  std::getline(file, line);
  

  while (std::getline(file, line))
  {
    std::stringstream values(line);
    std::string word, is_solution, first_entropy;
    getline(values, word, ',');
    getline(values, is_solution, ',');
    getline(values, first_entropy);
    wordle_valid_guesses.insert(word);
    if(is_solution=="1"){
      wordle_solution_words.insert(word);
    }
  }
  
  
  //throw std::logic_error("Wordle::loadWordsWithEntropy is not implemented yet.");
}

/**
 * @brief Selects the solution word based on the provided seed.
 *
 * Uses the seed to determine the solution word from the set of solution words.
 * Also identifies letters with multiple occurrences in the solution word.
 *
 * @param seed An integer used to select the solution word.
 */
void Wordle::getWordleSolutionWord(const int seed)
{
  int randomIndex = seed % wordle_solution_words.size();
  solution = *std::next(wordle_solution_words.begin(), randomIndex);
}

/**
 * @brief Identifies letters with multiple occurrences in the solution word.
 *
 * Scans the solution word and adds any letter that appears more than once
 * to the `letters_with_multiple_occurrences` set.
 *
 * @param solution The solution word to analyze.
 */
void Wordle::identifyRepeatedLetters(std::string solution)
{
  // clear the old data
  letters_with_multiple_occurrences.clear();
  std::unordered_map<char, int> temp_counts;
  for(char letter:solution){
    temp_counts[letter]++;
  }
  for(const auto& pair:temp_counts ){
    if(pair.second>=2){
      letters_with_multiple_occurrences.insert(pair.first);
    }
    
  }
  //throw std::logic_error("Wordle::identifyRepeatedLetters is not implemented yet.");
}

// ===== IGameData Implementation =====

/**
 * @brief Returns the current solution word.
 *
 * @return The solution word as std::string
 */
std::string Wordle::getSolutionWord() const
{
  return solution;
  //throw std::logic_error("Wordle::getSolutionWord is not implemented yet.");
}

/**
 * @brief Returns the set of valid guesses.
 *
 * @return Constant reference to the set of all valid Wordle words
 */
const std::unordered_set<std::string>& Wordle::getValidGuesses() const
{
  return wordle_valid_guesses;
  // throw std::logic_error("Wordle::getValidGuesses is not implemented yet.");
}

/**
 * @brief Returns the letters with multiple occurrences.
 *
 * @return Constant reference to the set of repeated letters
 */
const std::unordered_set<char>& Wordle::getRepeatedLetters() const
{ 
  return letters_with_multiple_occurrences;
  //throw std::logic_error("Wordle::getRepeatedLetters is not implemented yet.");
}
