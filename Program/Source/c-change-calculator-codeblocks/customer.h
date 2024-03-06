/*!
* Author: James Carppe
 * Date: 29/02/2024
 * Version: 1.0.0
 *
 * @brief Implements the customer functionality.
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

// The max size of a customer's name
#define CHAR_NAME_BUFFER 100

/*!
 * @brief Represents a customer
 *
 * @field name          char ** represents the customer's name
 * @field currency      int     represents the customer's currency
 * @field amount        int     represents the customer's amount
 */
typedef struct Customer {
    char *name;
    int currency;
    int amount;
} Customer;

/*!
 * @brief Represents multiple customers
 *
 * @field data      customer *   represents the array of customers
 * @field length    int          represents the number of customers stored in data
 */
typedef struct Customer_Cluster {
    Customer **data;
    int length;
} Customer_Cluster;

/*!
 * @brief Simple debug console print for the Customer struct
 *
 * @param self Change *  represents the desired Customer struct
 */
void debug_Customer(Customer *self);

/*!
 * @brief Simple debug console print for the Customer_Cluster struct
 *
 * @param self Change *  represents the desired Customer_Cluster struct
 */
void debug_Customer_Cluster(Customer_Cluster *self);

/*!
 * @brief Frees allocated memory
 * @param self  Customer *  reference to the memory that will be freed
 */
void free_Customer(Customer *self);

/*!
 * @brief Frees allocated memory
 * @param self  Customer_Cluster *  reference to the memory that will be freed
 */
void free_Customer_Cluster(Customer_Cluster *self);

/*!
 * @brief Creates a Customer struct
 *
 * @param input_name       const char *   customer's name
 * @param input_currency   const int      customer's currency
 * @param input_amount     const int      customer's amount
 *
 * @return Customer*  pointer to a heap allocated Customer struct
 */
struct Customer* create_Customer(const char *input_name, const int input_currency, const int input_amount);

/*!
 * @brief Creates a Customer_Cluster struct
 *
 * @param array          Customer **   Pointer to an array filled with customers - use malloc
 * @param array_length   const int     Array length
 *
 * @return
 */
struct Customer_Cluster create_Customer_Cluster(Customer **array, const int array_length);

/*!
 * @brief Adds an amount to an existing Customer struct
 *
 * @param self     Customer *  reference to the Customer struct
 * @param amount   int         amount to add
 */
void customer_add_amount(Customer *self, const int amount);

/*!
 * @brief Comparison function for comparing Customer structs
 *
 * @param self   Customer *         reference to a Customer struct
 * @param other  const Customer *   reference to a Customer struct
 *
 * @return int comparision result - 0 means equal
 */
int customer_compare(const Customer *self, const Customer *other);

/*!
 * @brief Merge function for merging two Customer's structs amounts
 *
 * @param self   Customer *         reference to a Customer struct - This struct will be updated
 * @param other  const Customer *   reference to a Customer struct
 */
void customer_merge(Customer *self, const Customer *other);

#endif //CUSTOMER_H
