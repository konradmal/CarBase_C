/**
 * @file car_database.h
 * @brief Header file containing declarations for managing a car database.
 */

#ifndef CAR_DATABASE_H
#define CAR_DATABASE_H

/**
 * @struct Cars
 * @brief Structure representing a car with various attributes.
 */
struct Cars {
    char brand[100];         ///< Brand of the car.
    char model[100];         ///< Model of the car.
    int year;                ///< Year of manufacture.
    int capacity;            ///< Engine capacity in cm^3.
    char fuel[100];          ///< Type of fuel used.
    char type[100];          ///< Type of the vehicle.
    char registration[100];  ///< Registration number of the car.
};

/**
 * @brief Reads cars from a file and initializes the car database.
 * @param set Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 */
void readCars(struct Cars **set, int *count);

/**
 * @brief Adds a new car to the database.
 * @param set Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 */
void addCar(struct Cars **set, int *count);

/**
 * @brief Displays information about cars in the database.
 * @param set Pointer to the car database.
 * @param count Number of cars in the database.
 */
void showCars(const struct Cars *set, int count);

/**
 * @brief Saves the car database to a file.
 * @param set Pointer to the car database.
 * @param count Number of cars in the database.
 */
void saveCars(const struct Cars *set, int count);

/**
 * @brief Searches for cars in the database based on a specified parameter.
 * @param set Pointer to the car database.
 * @param count Number of cars in the database.
 * @param choice Parameter for searching (e.g., brand, model, year).
 */
void search(struct Cars *set, int count, char choice);

/**
 * @brief Removes a car from the database.
 * @param set Pointer to the car database.
 * @param count Pointer to the number of cars in the database.
 */
void removeCar(struct Cars **set, int *count);

/**
 * @brief Frees the memory allocated for the car database.
 * @param set Pointer to the car database.
 */
void freeCarArray(struct Cars *set);

#endif // CAR_DATABASE_H
