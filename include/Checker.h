//
// Created by Linus Reuter on 13.06.24.
//

#ifndef CHECKER_H
#define CHECKER_H
#include <array>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "GameExceptions.h"

class Checker {
public:
    virtual std::array<int, 5> check(std::string guess, std::string solution);
    virtual ~Checker() = default;
};


#endif //CHECKER_H
