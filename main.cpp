#include <iostream>

#include "sudoku_board.h"

int main()
{
    SudokuBoard board;
    if (!board.loadFromFile("sudoku.txt"))
    {
        std::cerr << "Failed to load sudoku.txt\n";
        return 1;
    }

    bool playMode;
    std::cout << "Welcome to \033[33mSudoku!\033[0m\n";

    board.render(std::cout);

    std::cout << "Do you want to play or solve the board? (Insert play or solve): ";
    std::string mode;
    std::cin >> mode;

    if (mode == "play")
    {
        board.play();
    }

    if (mode == "solve")
    {
        board.solve();
    }

    return 0;
}