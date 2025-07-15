/**
 * @file car_database.c
 * @brief Implementation of functions for managing a car database.
 */

#include "car_database.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * @brief Reads cars from a file and initializes the car database.
 *
 * This function reads car data from a file named "base.txt". It dynamically allocates memory
 * for the car database, and each car is stored in a struct Cars array. The function keeps expanding
 * the memory as needed.
 *
 * @param set Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 */
void readCars(struct Cars **set, int *count) {
    FILE *fptr = fopen("base.txt", "r");
    if (!fptr) {
        printf("Unable to open the file for reading.\n");
        return;
    }

    int capacity = 1;
    *set = (struct Cars *)malloc(capacity * sizeof(struct Cars));
    if (!*set) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (fscanf(fptr, "%s %s %d %d %s %s %s",
                  (*set)[i].brand, (*set)[i].model, &(*set)[i].year, &(*set)[i].capacity,
                  (*set)[i].fuel, (*set)[i].type, (*set)[i].registration) == 7) {
        i++;
        if (i >= capacity) {
            capacity *= 2;
            *set = (struct Cars *)realloc(*set, capacity * sizeof(struct Cars));
            if (!*set) {
                fprintf(stderr, "Memory reallocation error.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    *count = i;
    if (!*set) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    printf("Loaded %d records from the file.\n", i);
    fclose(fptr);
}

/**
 * @brief Adds a new car to the database.
 *
 * This function adds a new car to the car database. It dynamically reallocates memory to accommodate
 * the new car entry.
 *
 * @param set Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 */
void addCar(struct Cars **set, int *count) {
    int i = *count;
    *set = realloc(*set, (*count + 1) * sizeof(struct Cars));
    if (*set == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    printf("This will be car number %d\n", i + 1);
    printf("Enter brand: ");
    scanf("%99s", (*set)[i].brand);
    printf("Enter model: ");
    scanf("%99s", (*set)[i].model);
    printf("Enter year: ");
	while (scanf("%d", &(*set)[i].year) != 1) {
	    printf("Invalid input. Please enter a valid year: ");
	    while (getchar() != '\n');
	}
	printf("Enter capacity: ");
	while (scanf("%d", &(*set)[i].capacity) != 1) {
	    printf("Invalid input. Please enter a valid capacity: ");
	    while (getchar() != '\n');
	}
    printf("Enter fuel: ");
    scanf("%99s", (*set)[i].fuel);
    printf("Enter vehicle type: ");
    scanf("%99s", (*set)[i].type);
    printf("Enter registration number: ");
    scanf("%99s", (*set)[i].registration);
    (*count)++;
}

/**
 * @brief Displays information about cars in the database.
 *
 * This function prints information about each car in the car database, including its number, brand,
 * model, year, engine capacity, fuel type, vehicle type, and registration number.
 *
 * @param set Pointer to the car database.
 * @param count Number of cars in the database.
 */
void showCars(const struct Cars *set, int count) {
    if (count == 0) {
        printf("No cars in the database.\n");
        return;
    }
    printf("List of cars in the database:\n");
    int i = 0;
    for (; i < count; i++) {
        printf("\nCar number: %d\nBrand: %s\nModel: %s\nYear: %d\nEngine capacity: %d cm^3\nFuel: %s\nVehicle type: %s\nRegistration number: %s\n",
               i + 1, set[i].brand, set[i].model, set[i].year, set[i].capacity, set[i].fuel, set[i].type, set[i].registration);
    }
    printf("\n");
}

/**
 * @brief Saves the car database to a file.
 *
 * This function saves the car database to a file named "base.txt". It writes the details of each
 * car to the file.
 *
 * @param set Pointer to the car database.
 * @param count Number of cars in the database.
 */
void saveCars(const struct Cars *set, int count) {
    FILE *fptr = fopen("base.txt", "w");
    if (!fptr) {
        printf("Unable to open the file for writing.\n");
        return;
    }
    int j = 0;
    for (; j < count; j++) {
        fprintf(fptr, "%s\n%s\n%d\n%d\n%s\n%s\n%s%s",
                set[j].brand, set[j].model, set[j].year, set[j].capacity,
                set[j].fuel, set[j].type, set[j].registration, (j == count - 1) ? "" : "\n");
    }
    fclose(fptr);
}

/**
 * @brief Searches for cars in the database based on user-specified criteria.
 *
 * This function allows the user to search for cars in the database based on different criteria:
 * 1. Brand
 * 2. Model
 * 3. Year
 * 4. Engine Capacity
 * 5. Fuel
 * 6. Vehicle Type
 * 7. Registration Number
 * 8. Return to the main menu
 *
 * For each criterion, the user can choose to search for an exact match or a partial match.
 *
 * @param set Pointer to the car database.
 * @param count Number of cars in the database.
 * @param choice User's choice for the search criterion.
 */
void search(struct Cars *set, int count, char choice) {
	int i = 0;
	int searchOption;
	char searchTerm[100];
    switch (choice) {
		case '1':  // Brand
		    printf("Choose 1 if you want to search for the entire entered name, or 2 if you only know a part:\n");
		    scanf("%d", &searchOption);
		    if (searchOption == 1) {
		        printf("Enter the entire brand name:\n");
		    } else if (searchOption == 2) {
		        printf("Enter a part of the brand name:\n");
		    } else {
		        printf("Invalid option. You should have chosen 1 or 2!\n");
		        break;
		    }
		    scanf("%99s", searchTerm);
		    for (; i < count; i++) {
		        if ((searchOption == 1 && strcmp(set[i].brand, searchTerm) == 0) ||
		            (searchOption == 2 && strstr(set[i].brand, searchTerm) != NULL)) {
		            printf("\nCar number: %d\n", i + 1);
		            printf("Brand: %s\n", set[i].brand);
		            printf("Model: %s\n", set[i].model);
		            printf("Year: %d\n", set[i].year);
		            printf("Engine capacity: %d cm^3\n", set[i].capacity);
		            printf("Fuel: %s\n", set[i].fuel);
		            printf("Vehicle type: %s\n", set[i].type);
		            printf("Registration number: %s\n", set[i].registration);
		        }
		    }
		    break;
		case '2':  // Model
		    printf("Choose 1 if you want to search for the entire entered name, or 2 if you only know a part:\n");
		    scanf("%d", &searchOption);

		    if (searchOption == 1) {
		        printf("Enter the entire model name:\n");
		    } else if (searchOption == 2) {
		        printf("Enter a part of the model name:\n");
		    } else {
		        printf("Invalid option. You should have chosen 1 or 2!\n");
		        break;
		    }
		    scanf("%99s", searchTerm);
		    for (; i < count; i++) {
		        if ((searchOption == 1 && strcmp(set[i].model, searchTerm) == 0) ||
		            (searchOption == 2 && strstr(set[i].model, searchTerm) != NULL)) {
		            printf("\nCar number: %d\n", i + 1);
		            printf("Brand: %s\n", set[i].brand);
		            printf("Model: %s\n", set[i].model);
		            printf("Year: %d\n", set[i].year);
		            printf("Engine capacity: %d cm^3\n", set[i].capacity);
		            printf("Fuel: %s\n", set[i].fuel);
		            printf("Vehicle type: %s\n", set[i].type);
		            printf("Registration number: %s\n", set[i].registration);
		        }
		    }
		    break;
        case '3':  // Year
		    printf("Choose 1 if you want to search for a specific year, or 2 if you want to search within a range of years.\n");
		    scanf("%d", &searchOption);
		    if (searchOption == 1 || searchOption == 2) {
		        int min, max, year;
		        if (searchOption == 2) {
		            printf("Enter the minimum year to search for:\n");
		            scanf("%d", &min);
		            printf("Enter the maximum year to search for:\n");
		            scanf("%d", &max);
		        } else {
		            printf("Enter the year to search for:\n");
		            scanf("%d", &year);
		        }
		        for (; i < count; i++) {
		            if ((searchOption == 2 && set[i].year >= min && set[i].year <= max) ||
		                (searchOption == 1 && set[i].year == year)) {
		                printf("\nCar number: %d\n", i + 1);
		                printf("Brand: %s\n", set[i].brand);
		                printf("Model: %s\n", set[i].model);
		                printf("Year: %d\n", set[i].year);
		                printf("Engine capacity: %d cm^3\n", set[i].capacity);
		                printf("Fuel: %s\n", set[i].fuel);
		                printf("Vehicle type: %s\n", set[i].type);
		                printf("Registration number: %s\n", set[i].registration);
		            }
		        }
		        break;
		    } else {
		        printf("You should have chosen 1 or 2!\n");
		        break;
		    }
		case '4':  // Engine Capacity
		    printf("Choose 1 if you want to search for a specific engine capacity, or 2 if you want to search within a range of engine capacities.\n");
		    scanf("%d", &searchOption);
		    if (searchOption == 1 || searchOption == 2) {
		        int minCapacity, maxCapacity, capacity;
		        if (searchOption == 2) {
		            printf("Enter the minimum engine capacity to search for (in cm^3):\n");
		            scanf("%d", &minCapacity);
		            printf("Enter the maximum engine capacity to search for (in cm^3):\n");
		            scanf("%d", &maxCapacity);
		        } else {
		            printf("Enter the engine capacity to search for (in cm^3):\n");
		            scanf("%d", &capacity);
		        }
		        for (; i < count; i++) {
		            if ((searchOption == 2 && set[i].capacity >= minCapacity && set[i].capacity <= maxCapacity) ||
		                (searchOption == 1 && set[i].capacity == capacity)) {
		                printf("\nCar number: %d\n", i + 1);
		                printf("Brand: %s\n", set[i].brand);
		                printf("Model: %s\n", set[i].model);
		                printf("Year: %d\n", set[i].year);
		                printf("Engine capacity: %d cm^3\n", set[i].capacity);
		                printf("Fuel: %s\n", set[i].fuel);
		                printf("Vehicle type: %s\n", set[i].type);
		                printf("Registration number: %s\n", set[i].registration);
		            }
		        }
		        break;
		    } else {
		        printf("You should have chosen 1 or 2!\n");
		        break;
		    }
		case '5':  // Fuel
		    printf("Choose 1 if you want to search for a full fuel name, or 2 if you know only a part of it:\n");
		    scanf("%d", &searchOption);
		    if (searchOption == 1) {
		        printf("Enter the full name of the fuel:\n");
		    } else if (searchOption == 2) {
		        printf("Enter the full fuel name or a part of it:\n");
		    } else {
		        printf("Invalid option. You should have chosen 1 or 2!\n");
		        break;
		    }
		    char fuel[50];
		    scanf("%s", fuel);
		    for (; i < count; i++) {
		        if ((searchOption == 2 && strstr(set[i].fuel, fuel) != NULL) ||
		            (searchOption == 1 && strcmp(set[i].fuel, fuel) == 0)) {
		            printf("\nCar number: %d\n", i + 1);
		            printf("Brand: %s\n", set[i].brand);
		            printf("Model: %s\n", set[i].model);
		            printf("Year: %d\n", set[i].year);
		            printf("Engine capacity: %d cm^3\n", set[i].capacity);
		            printf("Fuel: %s\n", set[i].fuel);
		            printf("Vehicle type: %s\n", set[i].type);
		            printf("Registration number: %s\n", set[i].registration);
		        }
		    }
		    break;
		case '6':  // Vehicle Type
		    printf("Choose 1 if you want to search for a full vehicle type name, or 2 if you know only a part of it:\n");
		    scanf("%d", &searchOption);

		    if (searchOption == 1) {
		        printf("Enter the full name of the vehicle type:\n");
		    } else if (searchOption == 2) {
		        printf("Enter the full vehicle type name or a part of it:\n");
		    } else {
		        printf("Invalid option. You should have chosen 1 or 2!\n");
		        break;
		    }
		    char type[50];
		    scanf("%s", type);
		    for (; i < count; i++) {
		        if ((searchOption == 2 && strstr(set[i].type, type) != NULL) ||
		            (searchOption == 1 && strcmp(set[i].type, type) == 0)) {
		            printf("\nCar number: %d\n", i + 1);
		            printf("Brand: %s\n", set[i].brand);
		            printf("Model: %s\n", set[i].model);
		            printf("Year: %d\n", set[i].year);
		            printf("Engine capacity: %d cm^3\n", set[i].capacity);
		            printf("Fuel: %s\n", set[i].fuel);
		            printf("Vehicle type: %s\n", set[i].type);
		            printf("Registration number: %s\n", set[i].registration);
		        }
		    }
		    break;
		case '7':  // Registration Number
		    printf("Choose 1 if you want to search for a full registration number, or 2 if you know only a part of it:\n");
		    scanf("%d", &searchOption);
		    if (searchOption == 1) {
		        printf("Enter the full registration number:\n");
		    } else if (searchOption == 2) {
		        printf("Enter the full registration number or a part of it:\n");
		    } else {
		        printf("Invalid option. You should have chosen 1 or 2!\n");
		        break;
		    }
		    char reg[50];
		    scanf("%s", reg);
		    for (; i < count; i++) {
		        if ((searchOption == 2 && strstr(set[i].registration, reg) != NULL) ||
		            (searchOption == 1 && strcmp(set[i].registration, reg) == 0)) {
		            printf("\nCar number: %d\n", i + 1);
		            printf("Brand: %s\n", set[i].brand);
		            printf("Model: %s\n", set[i].model);
		            printf("Year: %d\n", set[i].year);
		            printf("Engine capacity: %d cm^3\n", set[i].capacity);
		            printf("Fuel: %s\n", set[i].fuel);
		            printf("Vehicle type: %s\n", set[i].type);
		            printf("Registration number: %s\n", set[i].registration);
		        }
		    }
		    break;
        case '8': break;  // Return to the main menu
    }
}

/**
 * @brief Removes a car from the database based on the user-specified car number.
 *
 * This function allows the user to remove a car from the database by specifying the car number.
 * The user is prompted to enter the car number they want to remove, and the function will remove
 * the corresponding car entry from the database. Memory is reallocated to adjust the size of the database.
 *
 * @param set Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 */
void removeCar(struct Cars **set, int *count) {
    printf("Which car number do you want to remove?\n");
    int carNumberToRemove;
    while (1) {
        if (scanf("%d", &carNumberToRemove) == 1 && carNumberToRemove > 0 && carNumberToRemove <= *count) {
            break;
        } else {
            printf("Invalid input. Please enter a valid car number.\n");
            while (getchar() != '\n');
        }
    }
    int j = carNumberToRemove - 1;
    for (; j < *count - 1; j++) {
        (*set)[j] = (*set)[j + 1];
    }
    (*count)--;
    if (*count == 0) {
        free(*set);
        *set = NULL;
        return;
    }
    struct Cars *tmp = realloc(*set, *count * sizeof **set);
    if (!tmp) {
        fprintf(stderr, "Memory reallocation error.\n");
        exit(EXIT_FAILURE);
    }
    *set = tmp;
}

/**
 * @brief Frees the memory allocated for the car database.
 *
 * This function frees the memory allocated for the car database array.
 * It should be called before exiting the program to avoid memory leaks.
 *
 * @param set Pointer to the car database.
 */
void freeCarArray(struct Cars *set) {
    free(set);
}
