# Sudoku C++

A terminal-based Sudoku game and solver written in C++17.

```
    1 2 3   4 5 6   7 8 9
  +-------+-------+-------+
1 | 5 3 . | . 7 . | . . . |
2 | 6 . . | 1 9 5 | . . . |
3 | . 9 8 | . . . | . 6 . |
  +-------+-------+-------+
4 | 8 . . | . 6 . | . . 3 |
  ...
```

> Fixed (puzzle) numbers are highlighted in **yellow**. They cannot be edited or erased.

---

## Build

```bash
make
```

Requires `clang++` with C++17 support.

## Run

```bash
make run
# or
./main
```

On launch you'll be asked whether to **play** or **solve** the puzzle.

---

## Play mode

Enter moves as `row col value`:

| Input | Action |
|-------|--------|
| `1 3 5` | Place 5 at row 1, column 3 |
| `1 3 0` | Erase cell at row 1, column 3 |
| `quit` | Exit the game |

Rows and columns are **1-indexed**. Fixed cells are protected and cannot be overwritten.

## Solve mode

The solver uses a **backtracking algorithm** to find the solution and prints the completed board.

---

## Puzzle file

The puzzle is loaded from `sudoku.txt` — a plain text file with 9 lines of 9 characters each. Use digits `1-9` for clues and `.` for empty cells:

```
53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79
```

Swap in any valid puzzle file to play a different board.
