#ifndef SUDOKU_CONST_H
#define SUDOKU_CONST_H
const int BOARD_SIZE = 9;
const int EMPTY_CELL = 0;
// Levels
enum Difficulty {
    // ~45 filled cells
    EASY = 55,     
    // ~35 filled cells
    MEDIUM = 45, 
    // ~25 filled cells
    HARD = 35     
};
#endif 