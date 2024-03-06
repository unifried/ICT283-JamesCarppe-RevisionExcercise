/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Implements converting a int amount to an array of coins.
 */

#include <stdio.h>
#include <stdlib.h>

#include "currency.h"
#include "calculator.h"

// Simple debug print for the Change struct
void debug_Change(Change *self) {
    printf("-- -- --\n");
    printf("CHANGE STRUCT DEBUG\n");
    printf("Pointer: %p\n", self);
    printf("Data Pointer: %p\n", self->data);
    printf("Data Length: %i\n", self->length);
    printf("Currency: %i\n", self->currency);
    printf("Flag: %i\n", self->flag);
    printf("-- -- --\n");
}

// Function to free memory allocated in Change
void free_Change(Change *self) {
    free(self->data);
    self->length = 0;
}

// Calculates the change for a amount based on a currency
struct Change calculate_change(const int total_amount, const Currency currency) {
    // Casts the currency to an integer
    const int currency_int = (int) currency;

    // Create the array of coins - Initialise all values to 0
    int *coins = (int *) malloc(NUMBER_OF_COINS_PER_CURRENCY * sizeof(int));

    // Set all the values to 0
    for (int i = 0; i < NUMBER_OF_COINS_PER_CURRENCY; i++) {
        coins[i] = 0;
    }

    // Initialise two copy amount variables
    int amount_primary = total_amount;
    int amount_secondary = total_amount;

    // Intitalise the flag variable
    /*
     * STATES:
     * 0 = No problem
     * 1 = Calculation error
     * 2 = Loop break triggered
     */
    int flag = 0;

    // Define the indexes
    int coin = 0;

    // Defines the variables that ensure that loop will eventually stop
    int loop_counter = 0;
    const int break_loop = 100; // After 100 loops the loop will break.

    // Loop
    while ((flag == 0) && (amount_primary > 0)) {
        // Check if the index is above the max value
        if (coin >= NUMBER_OF_COINS_PER_CURRENCY) {
            // Invalid index -> trigger flag 1
            flag = 1;
        }

        // Check the loop counter
        if (loop_counter > break_loop) {
            // Too many loops -> trigger flag 2
            flag = 2;
        }
        loop_counter++;

        // Get the current coin's value
        const int coin_value = CURRENCY_COINS_TABLE[currency_int][coin];

        // Try subtract the coin value from the current amount
        amount_primary -= coin_value;

        // Check the new value
        if (amount_primary >= 0) {
            // Subtraction worked

            // Add a coin to the array & confirm the subtraction
            coins[coin] += 1;
            amount_secondary = amount_primary;
        } else {
            // Subtraction failed

            // Reset the amount & decrease the coin's value
            amount_primary = amount_secondary;
            coin++;
        }
    }

    // Construct a result
    Change result = {};

    result.length = NUMBER_OF_COINS_PER_CURRENCY;
    result.data = coins;
    result.flag = flag;
    result.currency = currency_int;

    return result;
}
