#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H
#include "sudoku_board.h"
class SudokuGame {
    public:
        SudokuGame(); 
        void start();                                       // Start display.
        void displayMenu();                                 // Show instruction - display.
        void playGame(Difficulty diff);                     // Game process.
    private:
        SudokuBoard board;
        //SudokuBoard solution;
        void showInstructions() const;                      // Show instructions.
        void handleInput(int row, int column, int value);   // Input value, if possible.
        bool checkWin() const;                              // Control, if sudoku is solved.
};
#endif // SUDOKU_GAME_H