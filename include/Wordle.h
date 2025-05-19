//
// Created by me3975 on 27.02.2025.
//

#ifndef WORDLE_H
#define WORDLE_H

#include <IGameData.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

/**
 * @brief Wordle-Klasse, die das IGameData-Interface implementiert.
 *
 * Verwaltet Lösungswörter, gültige Vermutungen und das aktuelle Lösungswort.
 * Ermöglicht parallele Entwicklung, da die Abhängigkeiten über IGameData abstrahiert sind.
 */
class Wordle : public IGameData
{
public:
    explicit Wordle(int seed);
    ~Wordle() = default;

    std::unordered_set<std::string> wordle_solution_words;
    std::unordered_set<std::string> wordle_valid_guesses;
    std::string solution;
    std::unordered_set<char> letters_with_multiple_occurrences;

    // IGameData-Implementierung
    std::string getSolutionWord() const override;
    const std::unordered_set<std::string>& getValidGuesses() const override;
    const std::unordered_set<char>& getRepeatedLetters() const override;

protected:
    void getWordleSolutionWord(int seed);
    void loadWordsWithEntropy();
    void identifyRepeatedLetters(const std::string solution);
};


#endif //WORDLE_H
