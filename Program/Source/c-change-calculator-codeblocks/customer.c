/*!
* Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Implements the customer functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math.h"
#include "customer.h"
#include "currency.h"

// Checks if the amount is valid - if it isn't then attempts to make it valid
int validate_amount(const int input_amount, const int divisibility) {
    // Create a new variable
    int validated_amount = input_amount;

    // Clamp the variable
    if (validated_amount < 0) validated_amount = 0;

    // Check divisibility
    validated_amount = math_get_closest_divisible_number(validated_amount, divisibility);

    // Return validated amount
    return validated_amount;
}

// Checks if the amount is valid - if it isn't then attempts to make it valid
// Includes upper limit clamp
int validate_amount_limit(const int input_amount, const int limit, const int divisibility) {
    // Create a new variable
    int validated_amount = input_amount;

    // Clamp the variable
    if (validated_amount < 0) validated_amount = 0;
    if (validated_amount > limit) validated_amount = limit;

    // Check divisibility
    validated_amount = math_get_closest_divisible_number(validated_amount, divisibility);

    // Return validated amount
    return validated_amount;
}

// Simple debug print for the Customer struct
void debug_Customer(Customer *self) {
    printf("\n-- -- --\n");
    printf("CUSTOMER STRUCT DEBUG\n");
    printf("Pointer: %p\n", self);
    printf("Name: %s\n", self->name);
    printf("Currency: %i\n", self->currency);
    printf("Amount: %i\n", self->amount);
    printf("-- -- --\n");
}

// Simple debug print for the Customer_Cluster struct
void debug_Customer_Cluster(Customer_Cluster *self) {
    printf("\n-- -- --\n");
    printf("CUSTOMER_CLUSTER STRUCT DEBUG\n");
    printf("Pointer: %p\n", self);
    printf("Data Pointer: %p\n", self->data);
    printf("Data Length: %i\n", self->length);
    printf("-- -- --\n");
}

// Function used to free allocated memory in Customer
void free_Customer(Customer *self) {
    // Check if self is NULL
    if (self == NULL) {
        return;
    }

    // Free the name field
    if (self->name != NULL) {
        free(self->name);
        self->name = NULL;
    }

    // Since the struct is heap allocated, we need to free it too
    free(self);
}

// Function used to free allocated memory in Customer_Cluster
void free_Customer_Cluster(Customer_Cluster *self) {
    // Check if the Customer_Cluster pointer is NULL
    if (self == NULL) {
        return;
    }

    // Free each individual Customer pointer
    if (self->data != NULL) {
        for (int customer = 0; customer < self->length; customer++) {
            if (self->data[customer] == NULL) {
                continue;
            }
            free_Customer(self->data[customer]);
        }

        // Free the array of Customer pointers
        free(self->data);
        *self->data = NULL;
    }

    // Reset the length
    self->length = 0;
}

// Function to create Customer struct
struct Customer* create_Customer(const char *input_name, const int input_currency, const int input_amount) {
    // Allocate the struct using malloc - this means the struct will need to be freed
    Customer *new_customer = (Customer *)malloc(sizeof(Customer));
    if (new_customer == NULL) {
        return NULL;
    }

    // Set the structs fields

    // Name - allocate, set & ensure it terminates - this field needs to be freed
    new_customer->name = (char *)malloc(CHAR_NAME_BUFFER);
    if (new_customer->name == NULL) {
        // Since the new_customer has been allocated we need to free it
        free(new_customer);
        return NULL;
    }

    strncpy(new_customer->name, input_name, CHAR_NAME_BUFFER - 2);
    new_customer->name[CHAR_NAME_BUFFER - 2] = '\0';


    // Currency - validate & set
    const int customer_currency = (int) currency_type_from_int(input_currency);
    new_customer->currency = customer_currency;

    // Amount - validate & set
    const int max_initial_amount = 99;
    const int customer_amount = validate_amount_limit(input_amount, max_initial_amount,CURRENCY_COINS_TABLE[customer_currency][NUMBER_OF_COINS_PER_CURRENCY - 1]);
    new_customer->amount = customer_amount;

    return new_customer;
}

// Function to create Customer_Cluster struct
struct Customer_Cluster create_Customer_Cluster(Customer **array, const int array_length) {
    // Check if array length is negative - if it is then return a "empty" Customer_Cluster
    if (array_length < 0) {
        Customer *empty_array = (Customer *)malloc(0);
        return create_Customer_Cluster(&empty_array, 0);
    }

    // Build the struct
    const Customer_Cluster new_cluster = {
        .data = array,
        .length = array_length
    };

    // Return the struct
    return new_cluster;
}

// Simple function to add an amount to a Customer struct
void customer_add_amount(Customer *self, const int amount) {
    // Create a new amount
    int validated_amount = amount;

    // Clamp the amount
    if (validated_amount < 0) validated_amount = 0;

    // Copy the existing amount
    const int existing_amount = self->amount;

    // Add validated with existing
    validated_amount += existing_amount;

    // Validate the new sum
    validated_amount = validate_amount(validated_amount,
                                       CURRENCY_COINS_TABLE[self->currency][NUMBER_OF_COINS_PER_CURRENCY - 1]);

    // Push the new value
    self->amount = validated_amount;
}

// Comparison function for Customer type
int customer_compare(const Customer *self, const Customer *other) {
    // Initialise return variable
    int customer_differences = 0;

    // Compare Customers
    if (strcmp(self->name, other->name) != 0) {
        customer_differences += 1;
    }

    if (self->currency != other->currency) {
        customer_differences += 1;
    }

    // Return
    return customer_differences;
}

// Function to allow two equal customers to merge amounts - only self's is updated
void customer_merge(Customer *self, const Customer *other) {
    // If they are not equal - don't attempt to merge
    if (customer_compare(self, other) != 0) return;

    // Add other's amount onto self's
    customer_add_amount(self, other->amount);
}
