# Car Database Project

## Description

A simple program written in C for managing a database of cars. It allows for adding, displaying, saving to a file, searching, and removing cars, all through an intuitive menu.

## How to Run the Project

1. **Compilation:**
   - Compile the project using an appropriate C compiler, for example:

     ```bash
     gcc main.c car_database.c menu.c -o car_database
     ```

2. **Running:**
   - After compilation, run the program:

     ```bash
     ./car_database
     ```

## Dependencies

No additional dependencies. The project uses standard C language functions.

## Using the Main Functions

After running the program, use the menu by selecting the appropriate options.

### 1. Adding a Car

   - Choose option `1` from the menu.
   - Enter the brand, model, production year, engine capacity, fuel type, vehicle type, and registration number.

### 2. Displaying Cars

   - Choose option `2` from the menu.
   - The list of added cars will be displayed.

### 3. Saving to a File

   - Choose option `3` from the menu.
   - Car data will be saved to the "base.txt" file.

### 4. Searching for Cars

   - Choose option `4` from the menu.
   - Choose a search parameter: brand, model, year, capacity, fuel, type, registration number.

### 5. Removing a Car

   - Choose option `5` from the menu.
   - Enter the car number to remove.

### 6. Exit

   - Choose option `6` from the menu to exit the program.

## For Developers

If you want to browse or modify the code, use the available source files:

- `main.c`: The main file containing the `main` function.
- `car_database.c`: Implementation of database functions.
- `menu.c`: Implementation of menu handling functions.

## Author

Author: Konrad Maleńczak
