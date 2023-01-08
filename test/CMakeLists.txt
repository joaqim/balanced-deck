cmake_minimum_required(VERSION 3.15)

project(BalancedDeckTest)

find_package(Catch2 MODULE REQUIRED)

add_executable(BalancedDeckTest
    mylibrarytest.cpp
)

target_link_libraries(BalancedDeckTest
    Catch2::Catch2
    BalancedDeck::BalancedDeck
)

add_test(BalancedDeckTest BalancedDeckTest)

target_compile_features(BalancedDeckTest PRIVATE cxx_std_17)