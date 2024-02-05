#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random card value between 1 and 11
int getCardValue() {
    return rand() % 11 + 1;
}

// Function to display the player's hand
void displayHand(int hand[], int numCards) {
    printf("Your hand: ");
    for (int i = 0; i < numCards; i++) {
        printf("%d ", hand[i]);
    }
    printf("\n");
}

// Function to calculate the total value of the hand
int calculateHandValue(int hand[], int numCards) {
    int total = 0;
    int numAces = 0;

    for (int i = 0; i < numCards; i++) {
        total += hand[i];
        if (hand[i] == 1) {
            numAces++;
        }
    }

    // Adjust the total for Aces (count as 11 if it doesn't bust, otherwise, count as 1)
    while (numAces > 0 && total + 10 <= 21) {
        total += 10;
        numAces--;
    }

    return total;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int playerHand[10]; // Array to store player's hand
    int dealerHand[10]; // Array to store dealer's hand

    int playerNumCards = 0; // Number of cards in the player's hand
    int dealerNumCards = 0; // Number of cards in the dealer's hand

    // Initial deal: Player gets two cards, dealer gets one card
    playerHand[playerNumCards++] = getCardValue();
    playerHand[playerNumCards++] = getCardValue();
    dealerHand[dealerNumCards++] = getCardValue();

    // Display initial hands
    printf("Welcome to Blackjack!\n");
    displayHand(playerHand, playerNumCards);
    printf("Dealer's hand: %d\n", dealerHand[0]);

    // Player's turn
    while (1) {
        int playerTotal = calculateHandValue(playerHand, playerNumCards);

        // Check if player busts
        if (playerTotal > 21) {
            printf("Bust! You lose.\n");
            break;
        }

        // Ask the player if they want to hit or stand
        printf("Do you want to (h)it or (s)tand? ");
        char choice;
        scanf(" %c", &choice);

        if (choice == 'h') {
            // Player chooses to hit
            playerHand[playerNumCards++] = getCardValue();
            displayHand(playerHand, playerNumCards);
        } else if (choice == 's') {
            // Player chooses to stand
            break;
        } else {
            printf("Invalid choice. Please enter 'h' or 's'.\n");
        }
    }

    // Dealer's turn
    while (calculateHandValue(dealerHand, dealerNumCards) < 17) {
        // Dealer hits
        dealerHand[dealerNumCards++] = getCardValue();
    }

    // Display final hands
    printf("\nFinal hands:\n");
    displayHand(playerHand, playerNumCards);
    displayHand(dealerHand, dealerNumCards);

    // Determine the winner
    int playerTotal = calculateHandValue(playerHand, playerNumCards);
    int dealerTotal = calculateHandValue(dealerHand, dealerNumCards);

    if (playerTotal > 21 || (dealerTotal <= 21 && dealerTotal >= playerTotal)) {
        printf("Dealer wins!\n");
    } else {
        printf("You win!\n");
    }

    return 0;
}