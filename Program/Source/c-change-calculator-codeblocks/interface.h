/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief User interface for the program.
 */

#ifndef INTERFACE_H
#define INTERFACE_H

void interface_output_customer(const Customer *target);

void interface_output_change(const Change *target);

void interface_output_complete_customer(Customer *target);

int interface_use_menu();

void interface_get_name(char *name);

#endif //INTERFACE_H
