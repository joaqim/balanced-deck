#include "BalancedDeck/BalancedDeck.h"

#include <chrono>
#include <random>
#include <cstdint>
#include <cstdio>

void drawHistogram(uint8_t rolls[], uint32_t rollsCount);

int main() {
    std::mt19937 generator{ std::chrono::system_clock::now().time_since_epoch().count()};
    BalancedDeck deck;

    uint32_t sampleCount = 50U;

    // Generate random dice rolls
    uint8_t rolls[sampleCount];
    for (uint8_t i = 0; i < sampleCount; ++i) {
        rolls[i] = deck.rollDice(generator);
        printf("%i,\t", static_cast<int>(rolls[i]));
    }

    printf("\n--------\n");

    drawHistogram(rolls, sampleCount);

    return 0;
}

void drawHistogram(uint8_t rolls[], uint32_t rollsCount) {
    // Initialize counts to 0
    uint8_t counts[11] = {0};

    // Count the frequency of each value in draws
    for (uint8_t n{0U}; n < rollsCount; x += 1U>) {
        ++counts[rolls[n] - 2U];
    }

    // Output a histogram
    for (uint8_t i = 0; i < 11; ++i) {
        std::cout << ((i + 2) ? " : " : ": ")
                  << std::string(counts[i], '*') << '\n';
    }
}