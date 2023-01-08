#include "BalancedDeck/BalancedDeck.h"

#include <cfloat> // FLT_MIN
#include <cstdint>

uint8_t BalancedDeck::rollDice(std::mt19937 &generator) {
    if (cardsInDeck == 0U) {
        initializeDeck();
    }

    float targetRandomNumber = std::uniform_real_distribution<float>(
        0.f, recalculateDiceProbabilities())(generator);
    for (;;) {  // non-infinite loop
        const uint8_t diceIndex = std::uniform_int_distribution<uint8_t>(
            0U, NUM_DICE_VALUES - 1U)(generator);
        const float diceProbability = _diceProbabilities[diceIndex];
        if (targetRandomNumber <= diceProbability) {
            if (_pairCounts[diceIndex] > 0U) {
                _pairCounts[diceIndex] -= 1U;
                _rollCounts[diceIndex] += 1U;
                cardsInDeck -= 1U;

                const uint8_t forgetFifthDiceRollByValue = _recentRolls[0];
                if (forgetFifthDiceRollByValue > 0U) {
                    _rollCounts[forgetFifthDiceRollByValue - 2U] -= 1U;

                    // shift all the elements to the left by one position to
                    // make room for the new roll:
                    for (uint8_t i = 0U; i < 4U; ++i) {
                        _recentRolls[i] = _recentRolls[i + 1];
                    }
                }

                _recentRolls[4] = diceIndex + 2U;

                return diceIndex + 2U;
            }
            // We will never draw a pair with Zero count
            _diceProbabilities[diceIndex] = FLT_MIN;
        }
        targetRandomNumber -= diceProbability;
    }
}

void BalancedDeck::initializeDeck() {
    cardsInDeck = NUM_CARDS_IN_DECK;
    for (uint8_t diceValue{2U}; diceValue < NUM_DICE_VALUES + 2U;
         diceValue += 1U) {
        _pairCounts[diceValue - 2U] =
            diceValue < 8U ? diceValue - 1U : 13U - diceValue;
        _rollCounts[diceValue - 2U] = 0U;
    }
}

float BalancedDeck::calculateDiceProbability(uint8_t diceIndex) const {
    const uint8_t pairCount = _pairCounts[diceIndex];
    if (pairCount == 0U) {
        return 0.f;
    }

    float probability = pairCount / cardsInDeck;

    const uint8_t rollCount = _rollCounts[diceIndex];
    if (rollCount > 0U) {
        probability *= 1.f - static_cast<float>(rollCount) *
                                 PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED;
        if (probability < 0.f) return 0.f;
    }
    return probability;
}

float BalancedDeck::recalculateDiceProbabilities() {
    float totalProbability = 0.f;

    for (uint8_t i{0U}; i < NUM_DICE_VALUES; i += 1U) {
        _diceProbabilities[i] = calculateDiceProbability(i);
        totalProbability += _diceProbabilities[i];
    }
    return totalProbability;
}
