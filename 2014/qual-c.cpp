// Problem C. Minesweeper Master
// https://code.google.com/codejam/contest/2974486/dashboard#s=p2

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

typedef std::vector< std::vector<int> > Puzzle;

enum CellType {
    MINE = -1
};

// read a line from stdin
std::stringstream ReadLine() {
    std::string tmp;
    std::getline(std::cin, tmp);
    return std::stringstream(tmp);
}

// print puzzle contents
// assume that grid position 0,0 was clicked
void PrintPuzzle(Puzzle& grid) {
    auto clicked = false;
    for(auto row : grid) {
        for(auto cell : row) {
            if(!clicked) {
                std::cout << "c";
                clicked = true;
            }
            else if(cell == MINE) {
                std::cout << "*";
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

// remove mine on grid and update stats
void RemoveMine(
        int row,
        int col,
        Puzzle& grid,
        int* free_cells) {

    auto rows = static_cast<int>(grid.size());
    auto cols = static_cast<int>(grid[0].size());

    grid[row][col] = 0;
    (*free_cells)--;

    // compute number of mines surrounding cell and decrease mine count on surrounding cells
    for(int r = std::max(row-1,0); r <= std::min(row+1, rows-1); ++r) {
        for(int c = std::max(col-1,0); c <= std::min(col+1, cols-1); ++c) {
            if(grid[r][c] == MINE) {
                grid[row][col]++;
            } else if(r != row || c != col) {
                grid[r][c]--;
            }
        }
    }
}

// remove mines adjacent to cell
void RemoveAdjacentMines(
        int row,
        int col,
        Puzzle& grid,
        int* free_cells) {

    auto rows = static_cast<int>(grid.size());
    auto cols = static_cast<int>(grid[0].size());

    for(int r = std::max(row-1,0); r <= std::min(row+1, rows-1); ++r) {
        for(int c = std::max(col-1,0); c <= std::min(col+1, cols-1); ++c) {
            if(grid[r][c] == MINE) {
                RemoveMine(r, c, grid, free_cells);
            }
        }
    }
}

// solve minesweeper puzzle
// return true if solvable, false if not solvable
bool GeneratePuzzle(int mines, Puzzle& grid) {

    auto rows = static_cast<int>(grid.size());
    auto cols = static_cast<int>(grid[0].size());

    int free_cells = (rows*cols) - mines;
    bool solvable = true;

    // remove mine from initial position
    RemoveMine(0, 0, grid, &free_cells);

    while(free_cells > 0) {

        int target_row = -1;
        int target_col = -1;
        int adjacent_mines = 9;
        bool found = false;

        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {
                if(grid[row][col] != MINE) {
                    // if remaining free cells matches adjacent mines, remove mines
                    if(grid[row][col] == free_cells) {
                        target_row = row;
                        target_col = col;
                        adjacent_mines = grid[row][col];
                        found = true;
                        break;
                    } 

                    // if cell has lowest number of adjacent mines, set as target
                    else if(grid[row][col] > 0 && grid[row][col] < adjacent_mines) {
                        target_row = row;
                        target_col = col;
                        adjacent_mines = grid[row][col];
                    }
                }
            }
            if(found) break;
        }

        // if not enough free cells to clear all adjacent mines, puzzle not solvable
        if(adjacent_mines > free_cells) {
            solvable = false;
            break;
        } else {
            RemoveAdjacentMines(target_row, target_col, grid, &free_cells);
        }

    }

    return solvable;
}

int main()
{
    int num_tests = 0;
    std::stringstream line = ReadLine();
    line >> num_tests;

    for(int test = 1; test <= num_tests; ++test) {
        int rows, cols, mines = 0;

        line = ReadLine();
        line >> rows >> cols >> mines;

        // initialize grid with free cells and clicked cell
        auto grid = Puzzle(rows, std::vector<int>(cols, MINE));

        // solve puzzle
        bool result = GeneratePuzzle(mines, grid);
        std::cout << "Case #" << test << ":" << std::endl;
        if(result) {
            PrintPuzzle(grid);
        } else {
            std::cout << "Impossible" << std::endl;
        }

    }

    return 0;
}
