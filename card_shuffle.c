/*
Program: Monte Carlo Simulation of 7-Card Poker Hands

Author: Jisnu Praharaj
Date: June 2026

This program creates a standard 52-card deck using a card structure.
Each card contains a suit (enum) and a pips value. The deck is shuffled
randomly, and 7 cards are dealt to form a hand.

The program evaluates each hand to determine whether it contains:
- no pair
- one pair
- two pair
- three of a kind
- full house
- four of a kind

A Monte Carlo simulation is performed by generating 1,000,000 random
hands and counting the frequency of each hand type. These counts are then
converted into probabilities to estimate the likelihood of each hand
category occurring.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DECK_SIZE 52   // Number of cards in a standard deck
#define HAND_SIZE 7   // Number of cards in a poker hand
#define TRIALS 1000000 // Number of random hands generated for simulation

// Enumerated values used to represent the four possible suits
enum suit_value {
    Spades,
    Clubs,
    Hearts,
    Diamonds
};

// Enumerated values used as categories for evaluated poker hands.
// The values also act as indexes for the hand_counts array.
enum hand_type {
    NO_PAIR,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND
};

// Defines a card as a combination of a pips value and a suit value
typedef struct card {
    short pips;
    enum suit_value suit;
} card;


// Creates a standard 52-card deck.
// Each suit contains cards numbered 2 through Ace (14).

void std_deck(card deck[]) {
    int index = 0;
    for (int s = Spades; s <= Diamonds; s++) {
        for (short p = 2; p <= 14; p++) {
            deck[index].suit = s;
            deck[index].pips = p;
            index++;
        };
    };
}

// Randomly shuffles the deck using the Fisher-Yates shuffle algorithm.
// Each card is swapped with another randomly selected card.
void shuffle_deck(card deck[]) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Generate a random index from 0 to i
        // Swap deck[i] with deck[j]
        card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}


// Counts how many times each pips value appears in a 7-card hand.
// The counts are used to determine the poker hand category.

enum hand_type evaluate_hand(card hand[]) {

    // No pair: all cards have different pips values.
    // One pair: two cards have the same pips value.
    // Two pair: two different pairs of cards have the same pips value.
    // Three of a kind: three cards have the same pips value.
    // Full house: three cards have the same pips value and the remaining two cards have the same pips value.
    // Four of a kind: four cards have the same pips value.

    int pair_count = 0;
    int three_of_a_kind = 0;
    int four_of_a_kind = 0;
    int pips_count[15] = {0}; // Index represents card value (2-14), value stored is the number of occurrences
    for (int i = 0; i < HAND_SIZE; i++) {
        pips_count[hand[i].pips]++;
    }

    // Check how many pairs, three-of-a-kind, and four-of-a-kind combinations exist.
    for (int i = 2; i <= 14; i++) {
        if (pips_count[i] == 2) {
            pair_count++;
        }
        else if (pips_count[i] == 3) {
            three_of_a_kind++;
        }
        else if (pips_count[i] == 4) {
            four_of_a_kind++;
        }
    }
    if (four_of_a_kind) { // Check strongest hands first because some hands contain smaller combinations.
        return FOUR_OF_A_KIND;
    } else if ((three_of_a_kind >= 1 && pair_count >= 1) || (three_of_a_kind >= 2)) {
        return FULL_HOUSE;
    } else if (three_of_a_kind == 1) {
        return THREE_OF_A_KIND;
    } else if (pair_count >= 2) {
        return TWO_PAIR;
    } else if (pair_count == 1) {
        return ONE_PAIR;
    } else {
        return NO_PAIR;
    }
}
/* Main function runs the Monte Carlo simulation.
Generates one million random 7-card hands,
evaluates each hand, and records the frequency of each poker hand type. */

int main() {
    
    srand(time(NULL)); // Initialize random number generator using current time

    card deck[DECK_SIZE];
    card hand[HAND_SIZE];

    // Stores the number of times each hand type appears during simulation
    // Enum values are used as indexes, e.g. hand_counts[ONE_PAIR].
    long hand_counts[6] = {0};

    // Generate and evaluate one million random 7-card hands
    for (long trial = 0; trial < TRIALS; trial++) {

        std_deck(deck);
        shuffle_deck(deck);

        // Deal the first 7 cards from the shuffled deck
        for (int i = 0; i < HAND_SIZE; i++) {
            hand[i] = deck[i];
        }

        enum hand_type result = evaluate_hand(hand); // Determine the category of the current hand

        hand_counts[result]++; // Increment the count corresponding to the evaluated hand type
    }

    // Convert hand counts into probabilities by dividing by total trials
    printf("Results from simulation:\n");
    printf("No Pair Probability: %.6f\n", (double)hand_counts[NO_PAIR] / TRIALS);
    printf("One Pair Probability: %.6f\n", (double)hand_counts[ONE_PAIR] / TRIALS);
    printf("Two Pair Probability: %.6f\n", (double)hand_counts[TWO_PAIR] / TRIALS);
    printf("Three of a Kind Probability: %.6f\n", (double)hand_counts[THREE_OF_A_KIND] / TRIALS);
    printf("Full House Probability: %.6f\n", (double)hand_counts[FULL_HOUSE] / TRIALS);
    printf("Four of a Kind Probability: %.6f\n", (double)hand_counts[FOUR_OF_A_KIND] / TRIALS);
    return 0;
}