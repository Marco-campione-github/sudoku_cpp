#include "sudoku_board.h"

#include <fstream>
#include <iostream>

bool SudokuBoard::loadFromFile(const std::string &path)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        return false;
    }

    std::string line;
    for (int row = 0; row < 9; ++row)
    {
        if (!std::getline(input, line) || line.size() != 9)
        {
            return false;
        }

        for (int col = 0; col < 9; ++col)
        {
            m_grid[row][col] = line[col];
            m_fixed[row][col] = (line[col] != '.');
        }
    }

    return true;
}

const std::array<std::array<char, 9>, 9> &SudokuBoard::grid() const
{
    return m_grid;
}

int SudokuBoard::get(int row, int col) const
{
    char ch = m_grid[row][col];
    return ch == '.' ? 0 : (ch - '0');
}

bool SudokuBoard::isFixed(int row, int col) const
{
    return m_fixed[row][col];
}

bool SudokuBoard::isSafe(int row, int col, char num) const
{
    int numValue = num - '0';

    for (int x = 0; x < 9; x++)
    {
        if (get(row, x) == numValue)
            return false;
    }

    for (int y = 0; y < 9; y++)
    {
        if (get(y, col) == numValue)
            return false;
    }

    int startRow = row - (row % 3), startCol = col - (col % 3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (get(i + startRow, j + startCol) == numValue)
                return false;

    return true;
}

bool SudokuBoard::solveRecursive(int row, int col)
{
    if (row == 9)
        return true;

    if (col == 9)
        return solveRecursive(row + 1, 0);

    if (isFixed(row, col))
        return solveRecursive(row, col + 1);

    for (char num = '1'; num <= '9'; num++)
    {
        if (isSafe(row, col, num))
        {
            m_grid[row][col] = num;
            if (solveRecursive(row, col + 1))
                return true;
            m_grid[row][col] = '.';
        }
    }

    return false;
}

void SudokuBoard::solve()
{
    solveRecursive(0, 0);
    render(std::cout);
}

void SudokuBoard::render(std::ostream &out) const
{
    out << "\n    1 2 3   4 5 6   7 8 9\n";
    out << "  +-------+-------+-------+\n";
    for (int r = 0; r < 9; ++r)
    {
        out << (r + 1) << " | ";
        for (int c = 0; c < 9; ++c)
        {
            int v = get(r, c);
            char ch = v == 0 ? '.' : char('0' + v);

            if (isFixed(r, c) && v != 0)
            {
                out << "\033[33m" << ch << "\033[0m ";
            }
            else
            {
                out << ch << ' ';
            }

            if ((c + 1) % 3 == 0)
                out << "| ";
        }
        out << "\n";
        if ((r + 1) % 3 == 0)
            out << "  +-------+-------+-------+\n";
    }
}

void SudokuBoard::play()
{
    while (true)
    {
        render(std::cout);
        std::cout << "Enter move (row col value) or 'quit' to exit: ";
        std::string input;
        std::cin >> input;

        if (input == "quit")
            break;

        int row = std::stoi(input);
        int col, value;
        std::cin >> col >> value;

        if (row < 1 || row > 9 || col < 1 || col > 9)
        {
            std::cout << "Invalid position. Please enter row and column between 1 and 9.\n";
            continue;
        }

        if (isFixed(row - 1, col - 1))
        {
            std::cout << "This cell is fixed and cannot be edited.\n";
            continue;
        }

        if (value == 0)
        {
            m_grid[row - 1][col - 1] = '.';
            m_fixed[row - 1][col - 1] = false;
            std::cout << "Erased cell (" << row << ", " << col << ")\n";
        }
        else if (value >= 1 && value <= 9)
        {
            m_grid[row - 1][col - 1] = char('0' + value);
            m_fixed[row - 1][col - 1] = false;
            std::cout << "Set cell (" << row << ", " << col << ") to " << value << "\n";
        }
        else
        {
            std::cout << "Invalid value. Please enter 0 to erase or 1-9 to set a value.\n";
        }
    }
}
