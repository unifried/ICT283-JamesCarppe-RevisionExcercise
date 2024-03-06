/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Loads Customer's from a file.
 */

#include <stdio.h>
#include <stdlib.h>

#include "currency.h"
#include "loader.h"
#include "customer.h"
#include "files.h"

// Processes a line from a given file
struct Customer* process_customer(const char *read_name, const char *read_currency, const int read_amount) {
    // Translate the currency input
    const int translated_currency = curreny_from_string(read_currency);

    // Create the customer
    Customer *new_customer = create_Customer(read_name, translated_currency, read_amount);

    // Return new_customer
    return new_customer;
}

// Loads a cluster of Customer's from a file
struct Customer_Cluster load_customers(const char *file_path) {
    // Open the file
    const ReadOnly_File file = open_readonly_file(file_path);

    // Check the file has contents
    if (file.lines < 1) {
        // File is empty or invalid
        Customer **empty_array = (Customer **)malloc(0);
        return create_Customer_Cluster(empty_array, 0);
    }

    // File has contents and is valid

    // Create an array to store the Customer's
    Customer **array = (Customer **) malloc(file.lines * sizeof(Customer));

    // Create buffers
    const int char_buffer = 100;

    char read_name[char_buffer];
    char read_currency[char_buffer];
    int read_amount;

    // Create counters
    int current_line = 1;
    int unique_customers = 0;

    // Loop over the file
    while (fscanf(file.pointer, "%s %i cents in %s", read_name, &read_amount, read_currency) != EOF) {
        // Alert the client if the amount is greater than 99
        if (read_amount > 99) {
            printf("Line %i, contains an incorrect value! Amounts should not exceed 99! Amount will be set to 99.\n", current_line);
        }

        // Process the line
        Customer *new_customer = process_customer(read_name, read_currency, read_amount);

        // Check if customer already exists
        int exists = -1;

        for (int customer = 0; customer < unique_customers; customer++) {
            const int EQUAL = 0;
            if (customer_compare(new_customer, array[customer]) == EQUAL) {
                exists = customer;
                break;
            }
        }

        if (exists == -1) {
            array[unique_customers] = new_customer;
            unique_customers++;
        } else {
            customer_merge(array[exists], new_customer);
        }

        // Increment the current line
        current_line++;
    }

    // Collate data into struct
    const Customer_Cluster loaded_customers = create_Customer_Cluster(array, unique_customers);

    // Return the struct
    return loaded_customers;
}
