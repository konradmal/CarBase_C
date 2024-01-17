/**
 * @file menu.c
 * @brief Implementation of menu-related functions.
 *
 * This file contains the implementations of functions related to displaying the menu and executing user choices.
 */

#include "menu.h"
#include "car_database.h"
#include <stdio.h>

/**
 * @brief Displays the main menu of the program.
 *
 * This function prints the main menu options to the console.
 */
void displayMenu() {
    printf("Please select one of the following functions:\n");
    printf("1-Add a car\n");
    printf("2-Display cars\n");
    printf("3-Save to a file\n");
    printf("4-Search\n");
    printf("5-Remove a car\n");
    printf("6-Exit\n");
}

/**
 * @brief Executes the user's choice from the main menu.
 *
 * Based on the user's choice, this function performs the corresponding action.
 *
 * @param carSet Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 * @param choice The user's menu choice.
 */
void executeChoice(struct Cars **carSet, int *count, char choice) {
    switch (choice) {
    case '1':
        printf("Add a car!\n");
        addCar(carSet, count);
        break;
    case '2':
        printf("Display cars!\n");
        showCars(*carSet, *count);
        break;
    case '3':
        printf("\nSave to a file!\n");
        saveCars(*carSet, *count);
        printf("\nSaved!\n\n");
        break;
    case '4':
        printf("\nEnter the parameter to search by:\n");
        printf("1-Brand\n");
        printf("2-Model\n");
        printf("3-Year\n");
        printf("4-Capacity\n");
        printf("5-Fuel\n");
        printf("6-Type\n");
        printf("7-Registration Number\n");
        printf("8-Back to the main menu\n");
        char searchOption;
        scanf(" %c", &searchOption);
        search(*carSet, *count, searchOption);
        break;
    case '5':
        printf("Remove a car!\n");
        removeCar(carSet, count);
        break;
    }
}
