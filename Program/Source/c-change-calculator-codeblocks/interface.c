/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief User interface for the program.
 */

#include <stdio.h>
#include <stdlib.h>

#include "customer.h"
#include "currency.h"
#include "calculator.h"
#include "currency.h"
#include "interface.h"

#include <string.h>

#include "currency.h"

// Outputs a Customers name, amount, and currency
void interface_output_customer(const Customer *target) {
    // Gets the currency string from an int
    char *currency_string = (char *) malloc(CURRENCY_NAME_CHAR_LENGTH);

    string_from_currency(target->currency, &currency_string);

    // Output the information
    printf("%s %i cents in %s\n", target->name, target->amount, currency_string);

    // Free memory
    if (currency_string == NULL) return;
    free(currency_string);
}

// Outputs a Change table
void interface_output_change(const Change *target) {
    // Print the array values
    for (int coin = 0; coin < target->length; coin++) {
        // Skip if the coin quantity is less than 1
        if (target->data[coin] < 1) continue;

        // Output the coin value and quantity
        printf("%i cents: %i\n", CURRENCY_COINS_TABLE[target->currency][coin], target->data[coin]);
    }
}

// Outputs a Customer and their respective change owed
void interface_output_complete_customer(Customer *target) {
    printf("\n-- -- --\n");
    printf("<CUSTOMER>\n");

    // Outputs the customers information
    interface_output_customer(target);

    printf("<CHANGE>\n");

    // Outputs the customer's change
    Change customer_change = calculate_change(target->amount, currency_type_from_int(target->currency));

    if (customer_change.flag != 0) {
        // Error with change calculation
        printf("[FLAG: %i] An error has occured!\n", customer_change.flag);
    } else {
        // No error - print the change
        interface_output_change(&customer_change);
    }

    printf("-- -- --\n");

    // Free the Change memory
    free_Change(&customer_change);
}

void interface_show_menu() {
    // Padding
    printf("\n-- - -- - -- - --\n");
    // Show the menu
    printf("1. Enter name\n");
    printf("2. Exit\n");
}

int interface_use_menu() {
    // Show the menu
    interface_show_menu();

    // Get the input
    printf("\nDesired option: ");

    int option;
    int read_result = scanf("%d", &option);

    // Check input
    if (read_result == EOF) {
        // Bad input
        printf("Bad input!\n");
        return 2;
    }

    return option;
}

void interface_get_name(char *name) {
    // Prompt
    printf("\nEnter the customer's name: ");

    // Read
    char buffer[CHAR_NAME_BUFFER];
    scanf("%s", &buffer);
    (buffer)[CHAR_NAME_BUFFER - 1] = '\0';

    // Copy
    strcpy(name, buffer);
}