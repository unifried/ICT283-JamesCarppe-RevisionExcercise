#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "currency.h"
#include "customer.h"
#include "calculator.h"
#include "interface.h"
#include "loader.h"

// Function pulled out of main to simplify the program
Customer_Cluster get_customers(const char *file_path) {
    printf("-- -- -- -- \n");
    printf("Customers are being loaded from %s...\n", file_path);

    printf("\n<Errors>\n");
    const Customer_Cluster loaded_customers = load_customers(file_path);
    printf("<Errors>\n");

    // Check data points
    if (loaded_customers.length < 1) {
        printf("\nNo customers were in the file!\n");
    } else {
        printf("\nCustomers have been loaded!\n");
    }

    printf("-- -- -- -- \n");

    return loaded_customers;
}

void use_menu(const Customer_Cluster *loaded_customers) {
    while (1) {
        // Use the menu
        const int option = interface_use_menu();

        // Break the loop - exit selected
        if (option == 2) break;

        // Get the customers name
        char target_name[CHAR_NAME_BUFFER];
        interface_get_name(target_name);

        // Search for the customer
        int found = 0;
        for (int customer = 0; customer < loaded_customers->length; customer++) {
            if (strcmp(target_name, loaded_customers->data[customer]->name) == 0) {
                interface_output_complete_customer(loaded_customers->data[customer]);
                found++;
            }
        }

        if (found < 1) {
            printf("\nName: %s\nNot found!\n", target_name);
        }
    }

    return;
}

int main() {
    // File that will be loaded
    const char *file_path = "coins.txt";

    // Load the customers
    Customer_Cluster loaded_customers = get_customers(file_path);

    // Check for NULL
    if (loaded_customers.length > 1) {
        // Use the menu
        use_menu(&loaded_customers);
    }

    // Free heap allocated memory
    free_Customer_Cluster(&loaded_customers);
    return 0;
}
