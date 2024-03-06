/*!
* Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Defines the multiple currencies the program supports.
 */

#ifndef CURRENCY_H
#define CURRENCY_H

// Defines the number of currencies
#define NUMBER_OF_CURRENCIES 3

// Defines the number of coins per currency
#define NUMBER_OF_COINS_PER_CURRENCY 4

// Defines how many characters each currencies name has
#define CURRENCY_NAME_LENGTH 3

// Adds one to CURRENCY_NAME_LENGTH for end of char
#define CURRENCY_NAME_CHAR_LENGTH CURRENCY_NAME_LENGTH + 1

/*!
 * @brief Defines the supported currencies so that functions can safley use the currencies for functionality.
 */
typedef enum Currency {
    USD,
    AUD,
    EUR,
    FIRST = USD,
    LAST = EUR,
} Currency;

/*!
 * @brief Stores the names of the currencies - needs to match the enum.
 */
extern const char CURRENCY_CONVERSION_TABLE[NUMBER_OF_CURRENCIES][CURRENCY_NAME_CHAR_LENGTH];

/*!
 * @brief Stores the coin values for each currency.
 */
extern const int CURRENCY_COINS_TABLE[NUMBER_OF_CURRENCIES][NUMBER_OF_COINS_PER_CURRENCY];

/*!
 * @brief Converts a string to a currency int.
 *
 * @param currency_string const char* currency string.
 *
 * @return int representing the currency.
 */
int curreny_from_string(const char *currency_string);

/*!
 * @brief Converts an int into currency string.
 *
 * @param currency_int  int      currency int.
 * @param result        char *   pointer to where the result will be written.
 */
void string_from_currency(int currency_int, char **result);

/*!
 * @brief Converts an int into a value from the currency enum
 *
 * @param currency_int  int  currency int
 *
 * @return Currency  Currency enum value
 */
Currency currency_type_from_int(int currency_int);

#endif //CURRENCY_H
