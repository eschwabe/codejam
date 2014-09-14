// Problem C. Minesweeper Master
// https://code.google.com/codejam/contest/2974486/dashboard#s=p2

// TODO: 
// dynamically allocate array (two arrays?)
// keep track of adajacent ce

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

// read a line from stdin
std::stringstream ReadLine() {
    std::string tmp;
    std::getline(std::cin, tmp);
    return std::stringstream(tmp);
}

// count the number of adjacent mines and free cells
std::tuple<int, int> CountAdjacent(
        int rows,
        int cols,
        int row,
        int col,
        int grid[kMaxDimension][kMaxDimension]) {

    int mine_cells = 0;
    int free_cells = 0;

    for(int r = std::max(row-1,0); r <= std::min(row+1, rows-1); ++r) {
        for(int c = std::max(col-1,0); c <= std::min(col+1, cols-1); ++c) {
            if(r == row && c == col) {
                continue;
            } else if(grid[r][c] == MINE) {
                mine_cells++;
            } else if(grid[r][c] == FREE) {
                free_cells++;
            }
        }
    }

    return std::tuple<int, int>(free_cells, mine_cells);
}

// solve minesweeper puzzle
// return true if solvable, false if not solvable
bool SolvePuzzle(int rows, int cols, int mines, int grid[kMaxDimension][kMaxDimension]) {

    for(int m = 0; m < mines; ++m) {

        // scan for new mine position with least impact
        int target_row = -1;
        int target_col = -1;
        std::tuple<int, int> target_stats(8,8);

        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {

                // count adjacent cells
                if(grid[row][col] == FREE) {
                    std::tuple<int, int> stats = CountAdjacent(rows, cols, row, col, grid);

                    // if fewer adjacent free cells or more adjacent mine cells, set as target to mine
                    if( std::get<0>(stats) < std::get<0>(target_stats) ||
                        (std::get<0>(stats) == std::get<0>(target_stats) && std::get<1>(stats) > std::get<1>(target_stats)) ) {
                        target_stats = stats;
                        target_row = row;
                        target_col = col;
                    }
                }

            }
        }

        // set new free cell
        grid[target_row][target_col] = MINE;

    }

    bool solvable = true;

    if(rows*cols != mines+1) {
        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {
                solvable = false;
                for(int r = std::max(row-1,0); r <= std::min(row+1, rows-1); ++r) {
                    for(int c = std::max(col-1,0); c <= std::min(col+1, cols-1); ++c) {
                        if(grid[r][c] == FREE) {
                            std::tuple<int, int> stats = CountAdjacent(rows, cols, r, c, grid);
                            if(std::get<1>(stats) == 0) {
                                solvable = true;
                            }
                        }
                    }
                }
            }
        }
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

        // initialize grid with free cells and clicked cell
        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {
                grid[row][col] = FREE;
            }
        }
        grid[rows-1][cols-1] = CLICK;

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
