// Problem C. Minesweeper Master
// https://code.google.com/codejam/contest/2974486/dashboard#s=p2

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

const int kMaxDimension = 50;

enum CellType {
    FREE = 0,
    CLICK,
    MINE,
};

std::stringstream ReadLine() {
    std::string tmp;
    std::getline(std::cin, tmp);
    return std::stringstream(tmp);
}

// count the number of mines adajacent to a free cell
int CountAdjacentMines(
        int rows,
        int cols,
        int row,
        int col,
        int grid[kMaxDimension][kMaxDimension],
        int* mine_row,
        int* mine_col) {

    int adjacent = 0;

    for(int r = std::max(row-1,0); r <= std::min(row+1, rows-1); ++r) {
        for(int c = std::max(col-1,0); c <= std::min(col+1, cols-1); ++c) {
            if(r == row && c == col) {
                continue;
            } else if(grid[r][c] == MINE) {
                adjacent++;
                *mine_row = r;
                *mine_col = c;
            }
        }
    }

    return adjacent;
}

// solve minesweeper puzzle
// return true if solvable, false if not solvable
bool SolvePuzzle(int rows, int cols, int mines, int grid[kMaxDimension][kMaxDimension]) {

    int num_free_cells = (rows*cols) - mines;
    bool solvable = false;

    for(int i = 0; i < num_free_cells; ++i) {

        // iniitalize first cell as clicked
        if(i == 0) {
            grid[0][0] = CLICK;
            solvable = true;
            continue;
        }

        // scan for mine with shortest distance to click
        //  or mine with only a single adjacent free cell
        int found = false;
        int row_to_free = kMaxDimension;
        int col_to_free = kMaxDimension;
        double distance = std::sqrt( std::pow(row_to_free, 2) + std::pow(col_to_free, 2));

        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {

                // test if 1 adjacent mine
                if(grid[row][col] != MINE) {
                    int mine_row = 0;
                    int mine_col = 0;
                    if(CountAdjacentMines(rows, cols, row, col, grid, &mine_row, &mine_col) == 1) {
                        row_to_free = mine_row;
                        col_to_free = mine_col;
                        distance = 0.0;
                        found = true;
                        break;
                    }
                }
                // compute distance to mine and set to be freed if shorter
                else if(grid[row][col] == MINE) {
                    double new_distance = std::sqrt( std::pow(row, 2) + std::pow(col, 2));
                    if(new_distance < distance) {
                        row_to_free = row;
                        col_to_free = col;
                        distance = new_distance;
                    }
                }
            }

            // stop processing if row has started with a mine
            if(grid[row][0] == MINE) {
                break;
            }

            // stop processing if found single adjacent mine cell
            if(found) {
                break;
            }
        }

        // if
        if(found) {
            solvable = true;
        } else {
            solvable = false;
        }

        // set new free cell
        grid[row_to_free][col_to_free] = FREE;

    }

    return solvable;
}

// print puzzle contents
void PrintPuzzle(int rows, int cols, int grid[kMaxDimension][kMaxDimension]) {
    for(int row = 0; row < rows; ++row) {
        for(int col = 0; col < cols; ++col) {
            if(grid[row][col] == FREE) {
                std::cout << ".";
            } else if(grid[row][col] == MINE) {
                std::cout << "*";
            } else if(grid[row][col] == CLICK) {
                std::cout << "c";
            }
        }
        std::cout << std::endl;
    }
}

int main()
{
    int num_tests = 0;
    std::stringstream line = ReadLine();
    line >> num_tests;

    for(int test = 1; test <= num_tests; ++test) {
        int rows, cols, mines = 0;
        int grid[kMaxDimension][kMaxDimension];

        line = ReadLine();
        line >> rows >> cols >> mines;

        // initialize grid with mines
        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {
                grid[row][col] = MINE;
            }
        }

        // solve puzzle
        bool result = SolvePuzzle(rows, cols, mines, grid);
        std::cout << "Case #" << test << ":" << std::endl;
        if(result) {
            std::cout << "Solved" << std::endl;
        } else {
            std::cout << "Impossible" << std::endl;
        }
        PrintPuzzle(rows, cols, grid);

    }

    return 0;
}
