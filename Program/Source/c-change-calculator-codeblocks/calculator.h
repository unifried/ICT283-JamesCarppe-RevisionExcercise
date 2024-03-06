/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Implements converting a int amount to an array of coins.
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

/*!
 * @brief Change is used for storing an array of values that represent monetary change.
 *
 * @field length    represents the length of the data array
 * @field data      represents the array of values that represent monetary change.
 * @field flag      represents the flag defined inside the calculation - used to communicate errors,
 *                  a value of 0 means there was no error.
 * @field currency  represents the currency the change was calculated for.
 */
typedef struct Change {
    int length;
    int *data;
    int flag;
    int currency;
} Change;

/*!
 * @brief Calculates the change for a given amount & currency.
 *
 * @param total_amount const int       represents the amount of change to be calculated for.
 * @param currency     const Currency  represents the currency to calculate the change for.
 *
 * @return Change  represents the change for the amount in a given currency.
 */
struct Change calculate_change(const int total_amount, const Currency currency);

/*!
 * @brief Simple debug console print for the Change struct
 *
 * @param self Change *  represents the desired Change struct
 */
void debug_Change(Change *self);

/*!
 * @brief Frees allocated memory
 * @param self  Change *  reference to the memory that will be freed
 */
void free_Change(Change *self);

#endif //CALCULATOR_H
