#include "sudoku.h"

/* INTRODUCTION:
     This file contains several functions to be used in main.c.
     I wrote is_val_in_row, is_val_in_col, is_val_in_3x3_zone, is_val_valid, solve_sudoku.
     The first 4 essentially checks if the value is valid at the cell it is entered,
     and the last one solves the sudoku as a whole.
     is_val_in_3x3_zone calls is_val_in_row and is_val_in_col.
     solve_sudoku calls is_val_valid and itself, it's a recursive function.
*/

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

    assert(i>=0 && i<9);        // idk what does this line do?

    // BEG TODO
    // loop through every element in the row
    for (int j=0; j<9; j++) {
        if (sudoku[i][j] == val) return 1;        // if val already exsist in the row, return true
    }
    
    return 0;
    // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

    assert(j>=0 && j<9);

    // BEG TODO
    // loop through every element in the column
    for (int i=0; i<9; i++) {
        if (sudoku[i][j] == val) return 1;        // if val already exsist in the column, return true
    }
    
    return 0;
    // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
     
    assert(i>=0 && i<9);
    
    // BEG TODO
    int row, col;
    // calculate the beginning of the 3x3 zone
    row = i - i % 3;
    col = j - j % 3;

    // loop through every row in the zone
    for (int r=row; r<row+3; r++) {
        // loop through every column in the zone
        for (int c=col; c<col+3; c++) {
            if (sudoku[r][c] == val) return 1;        // if val already exsist in the zone, return true
        }
    }

    return 0;
    // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

    assert(i>=0 && i<9 && j>=0 && j<9);

    // BEG TODO
    if (is_val_in_row(val, i, sudoku)) return 0;              // return false if val is not valid in the row
    if (is_val_in_col(val, j, sudoku)) return 0;              // return false if val is not valid in the column
    if (is_val_in_3x3_zone(val, i, j, sudoku)) return 0;      // return false if val is not valid in the zone

    return 1;
    // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

    // BEG TODO.
    // follow the pseudocode provided by course wiki
    int i, j, row, col;
    int solved = 1;

    // check if all cells have been filled with numbers
    for (int r=0; r<9; r++) {
        // loop through every column in the zone
        for (int c=0; c<9; c++) {
            if (sudoku[r][c] == 0) {
                solved = 0;        // if a cell is still 0, flag solved as false
            }
        }
    }
    if (solved) return 1;         // if all cells have been filled with numbers, return true
    else {
        // check if all cells have been filled with numbers
        for (int r=0; r<9; r++) {
            // loop through every column in the zone
            for (int c=0; c<9; c++) {
                // record the row and column number if a cell is not filled with number
                if (sudoku[r][c] == 0) {
                    row = r;
                    col = c;
                    // check if a number fits into the cell
                    for (int num=1; num<=9; num++) {
                        if (is_val_valid(num, row, col, sudoku)) {
                            sudoku[row][col] = num;         // assign num to the cell if it's valid
                            if (solve_sudoku(sudoku)) return 1;    // if it is solved, return true
                        }
                        sudoku[row][col] = 0;           // sudoku[i][j] revert to 0
                    }
                    return 0;
                }
            }
        }
    }

    // check if a number fits into the cell
    /* for (int num=1; num<=9; num++) {
        if (is_val_valid(num, row, col, sudoku)) {
            sudoku[row][col] = num;         // assign num to the cell if it's valid
            if (solve_sudoku(sudoku)) return 1;    // if it is solved, return true
        }
        sudoku[row][col] = 0;           // sudoku[i][j] revert to 0
    }
    */
    return 0;
    // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
    int i, j;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            printf("%2d", sudoku[i][j]);
        }
        printf("\n");
    }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
    FILE *reader = fopen(fpath, "r");
    assert(reader != NULL);
    int i, j;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            fscanf(reader, "%d", &sudoku[i][j]);
        }
    }
    fclose(reader);
}





