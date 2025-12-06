/**
 * @file car_database.c
 * @brief Implementation of functions for managing a car database.
 */

#include "car_database.h"
#include <stdio.h>
#include <stdlib.h>
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
        *set = NULL;
        *count = 0;
        return;
    }

    int capacity = 1;
    *set = (struct Cars *)malloc(capacity * sizeof(struct Cars));
    if (!*set) {
        fprintf(stderr, "Memory allocation error.\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fscanf(fptr, "%99s %99s %d %d %99s %99s %99s",
                  (*set)[i].brand,
                  (*set)[i].model,
                  &(*set)[i].year,
                  &(*set)[i].capacity,
                  (*set)[i].fuel,
                  (*set)[i].type,
                  (*set)[i].registration) == 7) {
        i++;
        if (i >= capacity) {
            capacity *= 2;
            struct Cars *tmp = (struct Cars *)realloc(*set, capacity * sizeof(struct Cars));
            if (!tmp) {
                fprintf(stderr, "Memory reallocation error.\n");
                free(*set);
                fclose(fptr);
                exit(EXIT_FAILURE);
            }
            *set = tmp;
        }
    }

    *count = i;
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

    struct Cars *tmp = (struct Cars *)realloc(*set, (*count + 1) * sizeof(struct Cars));
    if (!tmp) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    *set = tmp;

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
 * @brief Prints details of a single car.
 *
 * This is an internal helper function used to display
 * all fields of a single car in a consistent format.
 *
 * @param car Pointer to the car to print.
 * @param index Zero-based index of the car in the array (used to display car number).
 */
static void printCar(const struct Cars *car, int index) {
    printf("\nCar number: %d\n", index + 1);
    printf("Brand: %s\n", car->brand);
    printf("Model: %s\n", car->model);
    printf("Year: %d\n", car->year);
    printf("Engine capacity: %d cm^3\n", car->capacity);
    printf("Fuel: %s\n", car->fuel);
    printf("Vehicle type: %s\n", car->type);
    printf("Registration number: %s\n", car->registration);
}

/**
 * @brief Displays information about cars in the database.
 *
 * This function prints information about each car in the car database, including its number, brand,
 * model, year, engine capacity, fuel type, vehicle type, and registration number.
 *
 * @param set Pointer to the car database (not modified).
 * @param count Number of cars in the database.
 */
void showCars(const struct Cars *set, int count) {
    if (count == 0) {
        printf("No cars in the database.\n");
        return;
    }

    printf("List of cars in the database:\n");

    for (int i = 0; i < count; i++) {
        printCar(&set[i], i);
    }

    printf("\n");
}

/**
 * @brief Saves the car database to a file.
 *
 * This function saves the car database to a file named "base.txt". It writes the details of each
 * car to the file.
 *
 * @param set Pointer to the car database (not modified).
 * @param count Number of cars in the database.
 */
void saveCars(const struct Cars *set, int count) {
    FILE *fptr = fopen("base.txt", "w");
    if (!fptr) {
        printf("Unable to open the file for writing.\n");
        return;
    }

    for (int j = 0; j < count; j++) {
        fprintf(fptr, "%s\n%s\n%d\n%d\n%s\n%s\n%s%s",
                set[j].brand,
                set[j].model,
                set[j].year,
                set[j].capacity,
                set[j].fuel,
                set[j].type,
                set[j].registration,
                (j == count - 1) ? "" : "\n");
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
 *
 * For each criterion, the user can choose to search for an exact match or a partial match.
 *
 * @param set Pointer to the car database (not modified).
 * @param count Number of cars in the database.
 * @param choice User's choice for the search criterion.
 */
void search(const struct Cars *set, int count, char choice) {
    if (count == 0) {
        printf("No cars in the database.\n");
        return;
    }

    int searchOption;
    char searchTerm[100];

    switch (choice) {
        case '1': {  // Brand
            printf("Choose 1 if you want to search for the entire entered name, or 2 if you only know a part:\n");
            if (scanf("%d", &searchOption) != 1) {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                while (getchar() != '\n');
                break;
            }

            if (searchOption == 1) {
                printf("Enter the entire brand name:\n");
            } else if (searchOption == 2) {
                printf("Enter a part of the brand name:\n");
            } else {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                break;
            }

            scanf("%99s", searchTerm);

            for (int i = 0; i < count; i++) {
                if ((searchOption == 1 && strcmp(set[i].brand, searchTerm) == 0) ||
                    (searchOption == 2 && strstr(set[i].brand, searchTerm) != NULL)) {
                    printCar(&set[i], i);
                }
            }
            break;
        }

        case '2': {  // Model
            printf("Choose 1 if you want to search for the entire entered name, or 2 if you only know a part:\n");
            if (scanf("%d", &searchOption) != 1) {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                while (getchar() != '\n');
                break;
            }

            if (searchOption == 1) {
                printf("Enter the entire model name:\n");
            } else if (searchOption == 2) {
                printf("Enter a part of the model name:\n");
            } else {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                break;
            }

            scanf("%99s", searchTerm);

            for (int i = 0; i < count; i++) {
                if ((searchOption == 1 && strcmp(set[i].model, searchTerm) == 0) ||
                    (searchOption == 2 && strstr(set[i].model, searchTerm) != NULL)) {
                    printCar(&set[i], i);
                }
            }
            break;
        }

        case '3': {  // Year
            printf("Choose 1 if you want to search for a specific year, or 2 if you want to search within a range of years.\n");
            if (scanf("%d", &searchOption) != 1) {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                while (getchar() != '\n');
                break;
            }

            if (searchOption == 1 || searchOption == 2) {
                int min, max, year;

                if (searchOption == 2) {
                    printf("Enter the minimum year to search for:\n");
                    if (scanf("%d", &min) != 1) {
                        printf("Invalid year.\n");
                        while (getchar() != '\n');
                        break;
                    }

                    printf("Enter the maximum year to search for:\n");
                    if (scanf("%d", &max) != 1) {
                        printf("Invalid year.\n");
                        while (getchar() != '\n');
                        break;
                    }
                } else { // searchOption == 1
                    printf("Enter the year to search for:\n");
                    if (scanf("%d", &year) != 1) {
                        printf("Invalid year.\n");
                        while (getchar() != '\n');
                        break;
                    }
                }

                for (int i = 0; i < count; i++) {
                    if ((searchOption == 2 && set[i].year >= min && set[i].year <= max) ||
                        (searchOption == 1 && set[i].year == year)) {
                        printCar(&set[i], i);
                    }
                }
            } else {
                printf("You should have chosen 1 or 2!\n");
            }
            break;
        }

        case '4': {  // Engine Capacity
            printf("Choose 1 if you want to search for a specific engine capacity, or 2 if you want to search within a range of engine capacities.\n");
            if (scanf("%d", &searchOption) != 1) {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                while (getchar() != '\n');
                break;
            }

            if (searchOption == 1 || searchOption == 2) {
                int minCapacity, maxCapacity, capacity;

                if (searchOption == 2) {
                    printf("Enter the minimum engine capacity to search for (in cm^3):\n");
                    if (scanf("%d", &minCapacity) != 1) {
                        printf("Invalid capacity.\n");
                        while (getchar() != '\n');
                        break;
                    }

                    printf("Enter the maximum engine capacity to search for (in cm^3):\n");
                    if (scanf("%d", &maxCapacity) != 1) {
                        printf("Invalid capacity.\n");
                        while (getchar() != '\n');
                        break;
                    }
                } else { // searchOption == 1
                    printf("Enter the engine capacity to search for (in cm^3):\n");
                    if (scanf("%d", &capacity) != 1) {
                        printf("Invalid capacity.\n");
                        while (getchar() != '\n');
                        break;
                    }
                }

                for (int i = 0; i < count; i++) {
                    if ((searchOption == 2 && set[i].capacity >= minCapacity && set[i].capacity <= maxCapacity) ||
                        (searchOption == 1 && set[i].capacity == capacity)) {
                        printCar(&set[i], i);
                    }
                }
            } else {
                printf("You should have chosen 1 or 2!\n");
            }
            break;
        }

        case '5': {  // Fuel
            printf("Choose 1 if you want to search for a full fuel name, or 2 if you know only a part of it:\n");
            if (scanf("%d", &searchOption) != 1) {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                while (getchar() != '\n');
                break;
            }

            if (searchOption == 1) {
                printf("Enter the full name of the fuel:\n");
            } else if (searchOption == 2) {
                printf("Enter the full fuel name or a part of it:\n");
            } else {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                break;
            }

            char fuel[50];
            scanf("%49s", fuel);

            for (int i = 0; i < count; i++) {
                if ((searchOption == 2 && strstr(set[i].fuel, fuel) != NULL) ||
                    (searchOption == 1 && strcmp(set[i].fuel, fuel) == 0)) {
                    printCar(&set[i], i);
                }
            }
            break;
        }

        case '6': {  // Vehicle Type
            printf("Choose 1 if you want to search for a full vehicle type name, or 2 if you know only a part of it:\n");
            if (scanf("%d", &searchOption) != 1) {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                while (getchar() != '\n');
                break;
            }

            if (searchOption == 1) {
                printf("Enter the full name of the vehicle type:\n");
            } else if (searchOption == 2) {
                printf("Enter the full vehicle type name or a part of it:\n");
            } else {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                break;
            }

            char type[50];
            scanf("%49s", type);

            for (int i = 0; i < count; i++) {
                if ((searchOption == 2 && strstr(set[i].type, type) != NULL) ||
                    (searchOption == 1 && strcmp(set[i].type, type) == 0)) {
                    printCar(&set[i], i);
                }
            }
            break;
        }

        case '7': {  // Registration Number
            printf("Choose 1 if you want to search for a full registration number, or 2 if you know only a part of it:\n");
            if (scanf("%d", &searchOption) != 1) {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                while (getchar() != '\n');
                break;
            }

            if (searchOption == 1) {
                printf("Enter the full registration number:\n");
            } else if (searchOption == 2) {
                printf("Enter the full registration number or a part of it:\n");
            } else {
                printf("Invalid option. You should have chosen 1 or 2!\n");
                break;
            }

            char reg[50];
            scanf("%49s", reg);

            for (int i = 0; i < count; i++) {
                if ((searchOption == 2 && strstr(set[i].registration, reg) != NULL) ||
                    (searchOption == 1 && strcmp(set[i].registration, reg) == 0)) {
                    printCar(&set[i], i);
                }
            }
            break;
        }

        case '8':
        default:
            // Option 8 (back to menu) is handled in the menu layer.
            break;
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
    if (*count == 0) {
        printf("No cars to remove.\n");
        return;
    }

    printf("Which car number do you want to remove?\n");
    int carNumberToRemove;

    while (1) {
        if (scanf("%d", &carNumberToRemove) == 1 &&
            carNumberToRemove > 0 &&
            carNumberToRemove <= *count) {
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

    struct Cars *tmp = (struct Cars *)realloc(*set, *count * sizeof **set);
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
