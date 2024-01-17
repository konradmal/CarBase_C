/**
 * @file menu.h
 * @brief Header file for the menu-related functions.
 *
 * This file contains declarations for functions related to displaying the menu and executing user choices.
 */

#ifndef MENU_H
#define MENU_H

#include "car_database.h"

/**
 * @brief Displays the main menu of the program.
 *
 * This function prints the main menu options to the console.
 */
void displayMenu();

/**
 * @brief Executes the user's choice from the main menu.
 *
 * Based on the user's choice, this function performs the corresponding action.
 *
 * @param carSet Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 * @param choice The user's menu choice.
 */
void executeChoice(struct Cars **carSet, int *count, char choice);

#endif // MENU_H
