cmake_minimum_required(VERSION 3.15)

project(BalancedDeck)

# library definition
add_library(BalancedDeck
    src/BalancedDeck.cpp
    include/BalancedDeck/BalancedDeck.h)
target_compile_features(BalancedDeck PUBLIC cxx_std_17)
target_include_directories(BalancedDeck
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# library installation
install(TARGETS BalancedDeck EXPORT BalancedDeckTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(DIRECTORY include/BalancedDeck
        DESTINATION include)

add_library(BalancedDeck::BalancedDeck ALIAS BalancedDeck)
