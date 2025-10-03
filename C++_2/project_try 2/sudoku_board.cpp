#include <iostream>
#include "sudoku_board.h"
#include "sudoku_const.h"
#include "termcolor.hpp"

SudokuBoard::SudokuBoard() {clear();}

void SudokuBoard::clear() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            board[row][column].value=EMPTY_CELL;
            board[row][column].isConst=false;
        }
    }
}

void SudokuBoard::generateFirstRow() {
    /*
    1. Creat 1st row as array.
    2. Mix array.
    3. Creat 1st row from new array.
    */
    int row_1[BOARD_SIZE];
    for (int value = 0; value < BOARD_SIZE; ++value) {row_1[value] = value + 1;}
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int random = rand() % BOARD_SIZE;
        std::swap(row_1[i], row_1[random]);
    }
    for (int column = 0; column < BOARD_SIZE; ++column) {board[0][column].value = row_1[column];}
}

void SudokuBoard::generate(Difficulty diff) {
    /*
    1. Clean the board.
    2. Generate solved sudoku.
    3. Remove some values according to difficulty.
    4. Set all non-empty cells as constants.
    */
    clear(); 
    generateFirstRow();
    solve(); 
    removeCells(diff); 
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            if (board[row][column].value != EMPTY_CELL) {board[row][column].isConst = true;}
        }
    }
}

bool SudokuBoard::isCellConst(int row, int column) const {return board[row][column].isConst;}

bool SudokuBoard::solve() {return solveHelper();}

bool SudokuBoard::solveHelper() {
    /*
    1. If all sells are filled, then solved sudoku is built.
    2. Otherwise try values from 1 to 9 in the empty cell.
    3. Control if given value to be set in exact cell is valid and save ro be set.
    4. Continue repeating 1.-3. till sudoku isn't fully filled in.
    5. If sudoku isn't solved, then make a step back and set 0 in cell.
    */
    int row, column;
    if (!findEmptyCell(row, column)) {return true;} 
    for (int value = 1; value <= BOARD_SIZE; value++) {
        if (isSafe(row, column, value)) {
            board[row][column].value = value;
            if (solveHelper()) {return true;}
            board[row][column].value = EMPTY_CELL; 
        }
    }
    return false;
}

bool SudokuBoard::findEmptyCell(int& row, int& column) const {
    for (row = 0; row < BOARD_SIZE; row++) {
        for (column = 0; column < BOARD_SIZE; column++) {
            if (board[row][column].value == EMPTY_CELL) {return true;}
        }
    }
    return false;
}

bool SudokuBoard::isSafe(int row, int column, int value) const {
    /*
    1. Control if there aren't the same number in row or in column.
    2. Control if there aren't the same number in 3x3 square.
    */
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i].value == value || board[i][column].value == value) {return false;}
    }
    int extra_row = row - row % 3;
    int extra_col = column - column % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[extra_row + i][extra_col + j].value == value) {return false;}
        }
    }
    return true;
}

void SudokuBoard::removeCells(Difficulty diff) {
    /*
    1. Calculate, how many cells should be empty according to difficulty-level.
    2. Choose random position
    3. If cell isn't empty, then it should be cleaned (set 0) and defined as non-constsnt (set false). 
    4. Keep repeating 2. and 3. until we reach target (count of removed numbers is to_empty).
    */
    int to_empty = 81 - static_cast<int>(diff);
    while (to_empty > 0) {
        int row = rand() % 9;  // from 0 to 8
        int column = rand() % 9;  // from 0 to 8
        if (board[row][column].value!=EMPTY_CELL) {
            board[row][column].value = EMPTY_CELL;
            board[row][column].isConst=false; 
            to_empty--;
        }
    }
}

bool SudokuBoard::isSolved() const {
    /*
    1. Control each cell, if it isn't empty.
    2. if thera are no empty cells, then we control validity of solved board. 
    */
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int column = 0; column < BOARD_SIZE; column++) {
            if (board[row][column].value == EMPTY_CELL) {return false;}
        }
    }
    return isValid();
}

bool SudokuBoard::isValid() const {
    /*
    1. If the program finds non-empty cells, which are not filled according to rules, then sudoku has bad solving. 
    2. Otherwise it's valid.
    1. Validate all rows:
    1.1. Control each cell in current row.
    1.2. Get value from current cell.
    1.3. If value is already in this row, then board is invalid.
    1.4. Set value as used.
    2. Validate all columns (same logic).
    3. Validate all 3x3 squares (same logic).
    */
    for (int row = 0; row < BOARD_SIZE; ++row) {
        bool used[BOARD_SIZE + 1] = {false};
        for (int column = 0; column < BOARD_SIZE; ++column) {
            int value = board[row][column].value;
            if (value != EMPTY_CELL) {
                if (used[value]) {return false;}
                used[value] = true;
            }
        }
    }
    for (int column = 0; column < BOARD_SIZE; ++column) {
        bool used[BOARD_SIZE + 1] = {false};
        for (int row = 0; row < BOARD_SIZE; ++row) {
            int val = board[row][column].value;
            if (val != EMPTY_CELL) {
                if (used[val]) {return false;}
                used[val] = true;
            }
        }
    }
    for (int bl_row = 0; bl_row < 3; ++bl_row) {
        for (int bl_col = 0; bl_col < 3; ++bl_col) {
            bool used[BOARD_SIZE + 1] = {false};
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int val = board[bl_row*3 + i][bl_col*3 + j].value;
                    if (val != EMPTY_CELL) {
                        if (used[val]) {return false;}
                        used[val] = true;
                    }
                }
            }
        }
    }
    return true;
}

void SudokuBoard::setCell(int row, int column, int value) {if (value >= 0 && value <= 9) {board[row][column].value = value;}}

void SudokuBoard::print() const {
    /*
    1. Output coordinating row.
    2. Output each row in order: number of row, "|", 1st 3 numbers, "|", 2nd 3 numbers, "|", 3rd 3 numbers, "|".
    2*. If value of cell is 0, then print " " instead of value.
    2**. If value of cell is contstant, then print " ' " after the value.
    3. After each 3 rows output "----------------------".
    */
    std::cout << "\n   ";
    for (int column = 0; column < BOARD_SIZE; column++) {
        std::cout << column + 1 << " ";
        if ((column + 1) % 3 == 0) std::cout << " ";
    }
    std::cout << "\n  ----------------------\n";
    for (int row = 0; row < BOARD_SIZE; row++) {
        std::cout << row + 1 << " |";
        for (int column = 0; column < BOARD_SIZE; column++) {
            if (board[row][column].value == EMPTY_CELL) {std::cout << "  ";} 
            else {
                // Colors added!!!
                if (board[row][column].isConst) {std::cout << termcolor::green << board[row][column].value <<" "<< termcolor::reset;} 
                else {std::cout << board[row][column].value << " ";}
            }
            if ((column + 1) % 3 == 0) std::cout << "|";
        }
        std::cout << "\n";
        if ((row + 1) % 3 == 0) {std::cout << "  ----------------------\n";}
    }
}