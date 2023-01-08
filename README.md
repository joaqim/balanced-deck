
# Balanced Deck

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/joaqim/balanced-deck)](https://github.com/joaqim/balanced-deck/releases/latest)
[![GitHub](https://img.shields.io/github/license/joaqim/balanced-deck)](https://github.com/joaqim/balanced-deck/blob/main/LICENSE)

A C++ library for generating random rolls of a balanced dice with values 2 to 12.

## Overview
The BalancedDeck class allows you to generate random rolls of a dice that are balanced in the sense that the probability of rolling any given dice value is proportional to the number of pairs of that value in a 36-card deck. The deck is initially shuffled and contains 3 pairs of dice values 2 to 7, and 4 pairs of dice values 8 to 12. As dice are rolled, the pairs of the rolled values are removed from the deck, and the probability of rolling those values is reduced in future rolls.

## Usage
To use the BalancedDeck class, you need to include the balanced_deck.hpp header and create an instance of the class. Then, you can call the rollDice method to generate a random dice roll. Here is an example of how to use the BalancedDeck class:

```c++
#include <BalancedDeck/BalancedDeck.h>

#include <random>
#include <cstdint>
#include <cstdio>
#include <cstdio>

void drawHistogram(uint8_t rolls[], uint32_t rollsCount);

int main() {
    std::mt19937 generator(std::random_device{}());
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
```

## Features

- 🎣 Dependency management with **Conan**
- 🍭 Build configuration with **CMake**

## Installation

To use this library in you project, you can install it in the following ways:

### Conan
```sh
# Add artifactory repository as remote:
conan remote add joaqim-conan-public https://joaqim.jfrog.io/artifactory/api/conan/conan-public
# Install  a release of `mylibrary`
conan install --remote joaqim-conan-public mylibrary/1.0.0@joaqim/stable
```

If you don't want to build & run tests when building from source, set the [CONAN_RUN_TESTS](https://docs.conan.io/en/latest/reference/env_vars.html#conan-run-tests) variable:
```sh
install --remote joaqim-conan-public balanced-deck/1.0.1@joaqim/stable -e CONAN_RUN_TESTS=0
```

Pre-Releases are available in the `beta` channel:
```sh
conan install --remote joaqim-conan-public balanced-deck/1.0.1@joaqim/beta
```
   

## Development

### Build Requirements

- Conan >= 1.30
- CMake >= 3.15
- Doxygen 1.9.1 (optional)

### Build

- **Commandline**:
  ```sh
  # Create build folder for out-of-source build
  mkdir build && cd build
  # Install Dependencies with Conan
  conan install ..
  # Configure, Build & Test
  conan build ..
  ```
- **Clion**: Install the [Conan Plugin](https://plugins.jetbrains.com/plugin/11956-conan) before configuring & building the project as usual.

### Test

This template uses [Catch2](https://github.com/catchorg/Catch2) for testing. The Unit-tests are defined in `test`.

- **Commandline**: To run just the unit-tests, you can run `conan build .. --test`.
- **CLion**: Execute the `BalancedDeck` target

### Documentation

- Doxygen documentation can be found on this repository's [Github Pages](https://joaqim.com/balanced-deck/).


### CI/CD

This template uses [Github Actions](https://github.com/features/actions) for automating the release of a new library version.

- The workflow `configureBuildTestCreateAndUpload.yaml` configures, builds, tests the library automatically on each push.
  When a new release is created in Github, the resulting artifact is automatically uploaded to [a public  artifactory repository](https://joaqim.jfrog.io/ui/repos/tree/General/conan-public%2F_%2Fbalanced-deck)
- The workflow `publish-pages.yaml` automatically builds and publishes the documentation to [Github Pages](https://joaqim.com/balanced-deck/) when a new release is created in Github.

## Credits

This repository was adapted from this template:

- [C++ Library Template - joethepro](https://github.com/jothepro/cpp-library-template)