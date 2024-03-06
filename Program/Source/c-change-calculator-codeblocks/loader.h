/*!
 * Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Loads Customer's from a file.
 */

#ifndef LOADER_H
#define LOADER_H

/*!
 * @brief Loads Customer's from a given file.
 *
 * @param file_path  const char *  file to load customers from - must be '.txt'
 *
 * @return Customer_Cluster containing all the customers inside the file
 */
struct Customer_Cluster load_customers(const char *file_path);

#endif //LOADER_H
