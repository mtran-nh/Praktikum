//
// Created by Linus Reuter on 13.06.24.
//

#ifndef CLI_H
#define CLI_H
#include <memory>
#include "Interface.h"
#include "WordleSolver.h"
#include <stdexcept>


class CLI final : public Interface
{
public:
    explicit CLI(std::unique_ptr<Game> game);

    void start() override;
    void startBotGame() override;

protected:
    void printGameHeader() const;
};


#endif //CLI_H
