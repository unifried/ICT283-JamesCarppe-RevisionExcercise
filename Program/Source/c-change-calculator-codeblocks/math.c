/*!
 * Author: James Carppe
 * Date: 03/03/2024
 * Version: 1.0.0
 *
 * @brief Supporting math functions
 */

#include "math.h"

// Takes an input & a divisibility rule and find the closest number that is divisible
int math_get_closest_divisible_number(const int base_number, const int divisibility) {
    // Check if the base number meets the divisibility
    if (base_number % divisibility == 0) return base_number;

    // Defines the two numbers that will increment in each direction
    int add_number = base_number;
    int sub_number = base_number;

    // Boolean like value
    int not_divisible = base_number % divisibility;

    // Loop counter
    int loop_counter = 0;

    // Max loop iterations - in theory, the max number of iterations needed is the divisibility number
    const int max_loop_iterations = divisibility + 1;

    // Define the result
    int result = 0;

    // Loop
    while (not_divisible != 0 && loop_counter <= max_loop_iterations) {
        // Increment the values
        loop_counter++;
        add_number++;
        sub_number--;

        // Test add & sub if they are divisibly
        if ((sub_number > 0) && (sub_number % divisibility == 0)) {
            // Divisible
            not_divisible = 0;
            result = sub_number;
        }

        if ((add_number > 0) && (add_number % divisibility == 0)) {
            // Divisible
            not_divisible = 0;
            result = add_number;
        }
    }

    return result;
}
