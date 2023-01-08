#include "BalancedDeck/BalancedDeck.h"

#include <chrono>
#include <random>

int main()
{
    std::mt19937 generator{
        std::chrono::system_clock::now().time_since_epoch().count()};

    BalancedDeck deck{};

    deck.rollDice(generator);

    return 0;
}
