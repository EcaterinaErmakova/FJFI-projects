#include <iostream>
#include "sudoku_game.h"
#include "sudoku_const.h"
#include "sudoku_board.h"
#include "termcolor.hpp"

SudokuGame::SudokuGame() {}

void SudokuGame::start() {
    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: playGame(EASY); break;
            case 2: playGame(MEDIUM); break;
            case 3: playGame(HARD); break;
            case 4: showInstructions(); break;
            case 5: return;
            default: std::cout << termcolor::red <<"Invalid choice!\n" <<termcolor::reset;
        }
    }
}

void SudokuGame::displayMenu() {
    std::cout << "\n! Sudoku Game ! \n";
    std::cout << "1. Easy level\n";
    std::cout << "2. Medium level\n";
    std::cout << "3. Hard level\n";
    std::cout << "4. Instructions\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

void SudokuGame::playGame(Difficulty diff) {
    /*
    1. Create playing board.
    2. Store original.
    3. While sudoku isn't solved:
    3.1. Output the board.
    3.2. Input row, column and value.
    3.3. Control validity and possibility of input.
    4. End of the game.
    */
    board.generate(diff);
    //solution = board;
    //solution.solve();
    while (true) {
        board.print();
        if (checkWin()) {
            std::cout << termcolor::green << "Congratulations! You solved the puzzle!\n" << termcolor::reset;
            return;
        }
        int row, column, value;
        std::cout << "\nEnter row, column and value (0 to clean cell): ";
        std::cin >> row >> column >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << termcolor::red << "Invalid input! Please enter numbers only.\n" << termcolor::reset;
            continue;
        }
        if (row < 1 || row > 9 || column < 1 || column > 9 || value < 0 || value > 9) {
            std::cout << termcolor::red << "Invalid input!\n" << termcolor::reset;
            continue;
        }
        handleInput(row - 1, column - 1, value);
    }
    //std::cout << termcolor::green << " The sudoku is solved ! \n" << termcolor::reset;
}

void SudokuGame::showInstructions() const {
    std::cout << "\n ! Instructions ! \n";
    std::cout << "1. Goal: Fill the 9x9 board with digits 1-9\n";
    std::cout << "2. Rules:\n";
    std::cout << "   - Each row must contain all values from 1 to 9 without repetition\n";
    std::cout << "   - Each column must contain all values from 1 to 9 without repetition\n";
    std::cout << "   - Each 3x3 square must contain all values from 1 to 9 without repetition\n";
    std::cout << "3. Controls:\n";
    std::cout << "   - Enter row, column and value separated by spaces (e.g.: 5 3 7)\n";
    std::cout << "   - Enter 0 as value to clear a cell\n";
}

void SudokuGame::handleInput(int row, int column, int value) {
    /*
    1. If cell has const value, then it's not allowed to change it.
    2. Otherwise if value is 0 or valid, then it's allowed to set it in this cell. 
    */
    if (board.isCellConst(row, column)) {
        std::cout << termcolor::red <<"Cannot modify original puzzle numbers!\n"<< termcolor::reset;
        return;
    }
    if (board.isMoveValid(row, column, value) || value == EMPTY_CELL) {board.setCell(row, column, value);} 
    else {std::cout << termcolor::red << "Invalid move! Violates Sudoku rules.\n" << termcolor::reset;}
}

bool SudokuGame::checkWin() const {return board.isSolved() && board.isValid();}