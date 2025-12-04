/**
 * @file main.c
 * @brief Program for managing a car database.
 */

#include "car_database.h"
#include "menu.h"
#include <stdio.h>


/**
 * @brief Main function for the car database management program.
 *
 * This program allows users to manage a database of cars, including adding cars,
 * displaying the cars, saving to a file, searching, removing cars, and exiting the program.
 *
 * @return 0 on successful execution.
 */
int main() {
    struct Cars *carSet = NULL; ///< Pointer to the car database.
    int count = 0;              ///< Initial number of cars, to be increased by reference.
    char choice;                ///< User's choice for the main menu.

    // Read existing cars from a file
    readCars(&carSet, &count);

    // Main program loop
    do {
        displayMenu();          // Display the main menu
        scanf(" %c", &choice);  // Get user's choice
        executeChoice(&carSet, &count, choice);  // Execute the chosen option
    } while (choice != '6');   // Continue until the user chooses to exit

    printf("Thank you for using my program!\n");

    // Free allocated memory
    freeCarArray(carSet);

    return 0;  // Return 0 on successful execution
}
