#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <cstdlib>
#include <string>
#include <cmath>
#include "constants.hpp"

/* Provided functions */
int index(int row, int col) {
    /* Calculates a 1D index from a row and column.
        A 2D matrix can be represented in memory with a 1D array,
        assuming that indices 0 to COLS-1 are the items in the first row,
        indices COLS to 2*COLS-1 are the items in the second row, etc.
        So if we want to access data at a specific row and column,
        we calculate that index as row*COLS + column
    */
    return row*COLS + col;
}

int column_index(std::string field) {
    /* Uses parallel arrays to determine the integer column index 
        given the string field name.
        FIELDS is defined in constants.hpp. This function does a linear
        search over the FIELDS array to find and return the index of the
        column with the specified field name.
        Returns -1 if field name is not valid.
    */
    for (int c=0; c<COLS; c++) {
        if (FIELDS[c] == field) {
            return c;
        }
    }
    return -1;
}

void initialize(double * database) {
    /* Fills the dynamic array database with data from the constant DATA.
        Note the use of the index function to get the index for the dynamic array 
        database, versus using double brackets for the the static 2D array DATA.
    */
    for (int r=0; r<ENTRIES; r++) {
        for (int c=0; c<COLS; c++) {
            database[index(r,c)] = DATA[r][c];
        }
    }
}

/* Functions to implement */
bool search(const std::string field, const double value,
            const double *database, const int rows) {
    int col = column_index(field);
    if (col == -1) {
        return false; // Fail, invalid
    }

    // Finds val by going through each row
    for (int r = 0; r < rows; r++) {
        double current_value = database[index(r, col)];
        if (std::fabs(current_value - value) < THRESHOLD) {
            return true; // Found
        }
    }
    return false; // Not found
}

bool add_entry(const double new_row[],
               double *&database, int &rows) {
    // Check if ID is unique
    int id_col = column_index("ID");
    if (id_col == -1) {
        return false; // Invalid
    }

    double new_id = new_row[id_col];
    for (int r = 0; r < rows; r++) {
        if (std::fabs(database[index(r, id_col)] - new_id) < THRESHOLD) {
            return false; // Duplicate found
        }
    }

    // New mem for resized data
    double *new_database = new double[(rows + 1) * COLS];

    // Copy to new data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < COLS; c++) {
            new_database[index(r, c)] = database[index(r, c)];
        }
    }

    // Adds another row
    for (int c = 0; c < COLS; c++) {
        new_database[index(rows, c)] = new_row[c];
    }

    // Updates row count
    delete[] database;
    database = new_database;
    rows++;

    return true; // Successful
}

bool remove_entry(const double id, 
                  double *&database, int &rows) {
    int id_col = column_index("ID");
    if (id_col == -1) {
        return false; // Invalid ID column, double *& used to reference a pointer
    }

    // Finds specified row
    int row_to_remove = -1;
    for (int r = 0; r < rows; r++) {
        if (std::fabs(database[index(r, id_col)] - id) < THRESHOLD) {
            row_to_remove = r;
            break;
        }
    }

    if (row_to_remove == -1) {
        return false; // Failed
    }

    // New size
    double *new_database = new double[(rows - 1) * COLS];

    // Copies to new database, but skips the one to remove
    for (int r = 0, new_r = 0; r < rows; r++) {
        if (r == row_to_remove) {
            continue; // Skips
        }
        for (int c = 0; c < COLS; c++) {
            new_database[index(new_r, c)] = database[index(r, c)];
        }
        new_r++;
    }

    // Updates pointer
    delete[] database;
    database = new_database;
    rows--;

    return true; // Success
}

#endif

