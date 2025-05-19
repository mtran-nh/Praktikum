//
// Created by janni on 08.11.2025.
//

#ifndef IGAMEDATA_H
#define IGAMEDATA_H
#include <string>
#include <unordered_set>

/**
 * @brief Interface for Wordle game data.
 *
 * Decouples the Game class from the concrete implementation (Wordle).
 * Enables parallel development of different components.
 */
class IGameData {
public:
    virtual ~IGameData() = default;

    /**
     * @brief Returns the solution word.
     * @return The solution word as std::string
     */
    virtual std::string getSolutionWord() const = 0;

    /**
     * @brief Returns the set of valid guesses.
     * @return Reference to the set of all valid Wordle words
     */
    virtual const std::unordered_set<std::string>& getValidGuesses() const = 0;

    /**
     * @brief Returns the letters that appear multiple times in the solution word.
     * @return Reference to the set of repeated letters
     */
    virtual const std::unordered_set<char>& getRepeatedLetters() const = 0;
};

#endif //IGAMEDATA_H
