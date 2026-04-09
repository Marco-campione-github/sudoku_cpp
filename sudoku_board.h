#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <array>
#include <iosfwd>
#include <string>

class SudokuBoard
{
public:
    bool loadFromFile(const std::string &path);
    void render(std::ostream &out) const;
    const std::array<std::array<char, 9>, 9> &grid() const;
    int get(int row, int col) const;
    bool isFixed(int row, int col) const;
    void play();
    void solve();

private:
    std::array<std::array<char, 9>, 9> m_grid{};
    std::array<std::array<bool, 9>, 9> m_fixed{};
    bool solveRecursive(int row, int col);
    bool isSafe(int row, int col, char num) const;
};

#endif
