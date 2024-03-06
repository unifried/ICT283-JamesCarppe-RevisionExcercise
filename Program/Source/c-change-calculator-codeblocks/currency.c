/*!
* Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Defines the multiple currencies the program supports.
 */

#include <stdio.h>
#include <string.h>

#include "currency.h"

/*
 * Definitions
 */

// All supported currencies' names need to be added here
const char CURRENCY_CONVERSION_TABLE[NUMBER_OF_CURRENCIES][CURRENCY_NAME_CHAR_LENGTH] = {
    "US$",
    "AU$",
    "EUR"
};

// All supported currencies' coin values need to be added here
const int CURRENCY_COINS_TABLE[NUMBER_OF_CURRENCIES][NUMBER_OF_COINS_PER_CURRENCY] = {
    {
        50, 25, 10, 1
    }, // USD
    {
        50, 20, 10, 5
    }, // AUD
    {
        20, 10, 5, 1
    } // EUR
};

/*
 * Functions
 */

// Converts a string into a currency int
int curreny_from_string(const char *currency_string) {
    // Defines the loop start and end variables
    const int loop_start = (int) FIRST;
    const int loop_end = (int) LAST;

    // Get the int from the string
    for (int currency = loop_start; currency <= loop_end; currency++) {
        if (strcmp(currency_string, CURRENCY_CONVERSION_TABLE[currency]) == 0) {
            // A match has been found - early return
            return currency;
        }
    }

    // No match was found - return the default
    return loop_start;
}

// Converts an int into a currency string
void string_from_currency(int currency_int, char **result) {
    // Define currency bounds
    const int first_currency = (int) FIRST;
    const int last_currency = (int) LAST;

    // Clamp the input int
    if (currency_int < first_currency) currency_int = first_currency;
    if (currency_int > last_currency) currency_int = last_currency;

    // Write the currency to the buffer provided
    strcpy(*result, CURRENCY_CONVERSION_TABLE[currency_int]);
}

// Converts an int into a currency type
Currency currency_type_from_int(int currency_int) {
    // Define currency bounds
    const int first_currency = (int) FIRST;
    const int last_currency = (int) LAST;

    // Clamp the input int
    if (currency_int < first_currency) currency_int = first_currency;
    if (currency_int > last_currency) currency_int = last_currency;

    // Return the enum value
    return (Currency) currency_int;
}
