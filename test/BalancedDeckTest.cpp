
#include "BalancedDeck/BalancedDeck.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <memory>

SCENARIO("BalancedDeck testing", "[test]")
{
    GIVEN("can create a BalancedDeck instance")
    {

        std::mt19937 generator{static_cast<long unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())};

        auto deck = std::make_shared<BalancedDeck>();

        WHEN("calling rollDice()")
        {
            auto result = deck->rollDice(generator);
            THEN("result should be non-zero")
            {
                REQUIRE(result > 0);
            }
            THEN("result should be an integer [2..12]")
            {
                REQUIRE(result >= 2);
                REQUIRE(result <= 12);
            }
            THEN("cards in deck should have been reduced by one") {
                REQUIRE(deck->cardsInDeck == deck->NUM_CARDS_IN_DECK - 1U);
            }
        }
    }
}