#pragma once

#include <cstdint>
#include <random>

/**
 * @class BalancedDeck
 * @brief Represents a deck of dice in which the probability of rolling a
 * certain number is balanced.
 * @note The BalancedDeck class uses a mt19937 random number generator to
 * randomly draw cards from the deck.
 * @note The indices of the private member arrays correspond to dice values
 * in the range [2, 12], where the index + 2 equals the dice value.
 * For example:
 * _pairCounts[0] refers to the number of dice pairs with a value of 2, and
 * _pairCounts[9] refers to the number of dice pairs with a value of 11.
 *
 *
 * The BalancedDeck class keeps track of the number of dice in the deck, the
 * number of each dice value left in the deck, and the probability of rolling
 * each dice value. The probabilities are recalculated each time the rollDice
 * method is called. The probabilities of dice values that have been recently
 * rolled are reduced.
 */

class BalancedDeck
{
public:
   /**
    * The probability reduction applied to dice values that have been recently
    * rolled. A dice value that has been rolled recently will have a
    * probability that is PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED times
    * smaller than a dice value that has not been rolled recently.
    */
   static constexpr float PROBABILITY_REDUCTION_FOR_RECENTLY_ROLLED = 0.3f;

   /**
    * @brief The number of possible dice values (2-12).
    */
   static constexpr uint8_t NUM_DICE_VALUES = 11U;

   /**
    * @brief The number of cards in the deck.
    */
   static constexpr uint8_t NUM_CARDS_IN_DECK = 36U;

   /**
    * @brief Construct a new Balanced Deck object.
    * Initializes the deck with 36 cards and sets the number of pairs of each dice value based on its value.
    */
   BalancedDeck() { initializeDeck(); }

   /**
    * @brief Roll a dice from the deck.
    * @param generator A std::mt19937 object used to generate random numbers.
    * @return The dice value, in the range [2, 12].
    */
   uint8_t rollDice(std::mt19937 &generator);

private:
   uint8_t _pairCounts[11];      //!< The number of pairs of each dice value in the deck.
   uint8_t _rollCounts[11];      //!< The number of times each dice value has been rolled in the past 5 rolls.
   float _diceProbabilities[11]; //!< The current probabilities of rolling each dice value.
   uint8_t _recentRolls[5];      //!< The past 5 rolls, in chronological order.
   uint8_t _cardsInDeck = 0U;    //!< The number of cards remaining in the deck, initializes in rollDie().

   /**
    * @brief Initializes the deck by resetting the number of cards in the deck
    * to the total number of cards and resetting the counts of dice pairs and
    * recent rolls.
    */

   void initializeDeck();

   /**
    * @brief Calculates the probability of a specific dice value being rolled.
    * @param diceIndex The index of the dice value in the pairCounts,
    * rollCounts and diceProbabilities arrays.
    * @return The probability of the dice value being rolled.
    */

   float calculateDiceProbability(uint8_t diceIndex) const;

   /**
    * Recalculates the probabilities of all dice values based on the current
    * state of the deck.
    * @return The sum of the probabilities of all dice values.
    */
   float recalculateDiceProbabilities();
};