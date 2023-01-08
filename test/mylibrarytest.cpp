
#include "BalancedDeck/BalancedDeck.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <memory>


SCENARIO("BalancedDeck testing", "[test]") {
    GIVEN("an Example instance") {

        std::mt19937 generator{
        std::chrono::system_clock::now().time_since_epoch().count()};

        auto example = std::make_shared<BalancedDeck>();

        WHEN("calling test()") {
            auto result = example->rollDie(generator);
            THEN("result should be an integer [2..12]") {
                REQUIRE(result >=2 && result <= 12 );
            }
        }
    }
}