//
// Created by Marcel Auer on 17.02.2025.
//

#include "Utils.h"
#include <random>
#include <iostream>
#include <limits>

/**
 * @brief Generates a random seed value.
 *
 * This function uses a random device and a Mersenne Twister generator
 * to produce a uniformly distributed random integer between 0 and 2315.
 *
 * @return A random integer seed value.
 */
int getRandomSeed()
{
    std::random_device random_dev;
    std::mt19937 generator(random_dev());
    std::uniform_int_distribution<> uniform_distribution(0, 2315);
    return uniform_distribution(generator);
}

void waitForUser(const std::string& prompt)
{
    std::cout << prompt;
    std::cout.flush();

    if (!std::cin.good()) {
        std::cin.clear();
    }

    if (std::cin.rdbuf()->in_avail() > 0) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string dummy;
    std::getline(std::cin, dummy);
}
