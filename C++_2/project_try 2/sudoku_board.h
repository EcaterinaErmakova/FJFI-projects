#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H
#include <array>
#include <vector>
#include "sudoku_const.h"

struct Cell {
    int value;
    bool isConst=true; 
};

class SudokuBoard {
    public:
        SudokuBoard();
    /* Main metthods */ 
        void generateFirstRow();
        bool isMoveValid(int row, int column, int value) const {return isSafe(row, column, value);}
        void generate(Difficulty diff);                     // Create playing board.
        bool solve();                                       // Generate solved sudoku.
        bool isSolved() const;                              // Control, if there are empty cells (that contain 0).
        bool isValid() const;                               // Implement full board validation.
    /* Work with cells */
        bool isCellConst(int row, int column) const;        // Control, if it is allowed to change the value in cell.
        void setCell(int row, int column, int value);       // Controls validity of value in cell and sets it (it should be from 0 to 9).
    /* Input/Output */
        void print() const;                                 // Output the board.
        void clear();                                       // Delete all values from board (put 0).
    private:
        std::array < std::array<Cell, BOARD_SIZE>, BOARD_SIZE > board;
    /* Help-methods */
        bool isSafe(int row, int column, int value) const;  // Control, if there aren't the same number in column, row or 3x3 square.
        bool findEmptyCell(int& row, int& column) const;    // Control, if the board contains empty cells (filled with 0).
        bool solveHelper();                                 // Help to solve the sudoku.
        void removeCells(Difficulty diff);                  // Creat the playing board from solved sudoku.
};

#endif // SUDOKU_BOARD_H