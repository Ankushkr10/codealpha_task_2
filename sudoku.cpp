#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 9;

// Function to check if a number is safe to place at a given cell
bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    // Check for duplicates in the row
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check for duplicates in the column
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check for duplicates in the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    // Find the first empty cell
    int row, col;
    bool foundEmpty = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                foundEmpty = true;
                break;
            }
        }
        if (foundEmpty) {
            break;
        }
    }

    // If no empty cell is found, the puzzle is solved
    if (!foundEmpty) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int i = 1; i <= N; i++) {
        if (isSafe(grid, row, col, i)) {
            grid[row][col] = i;

            // Recursively solve the puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // If the current placement doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

// Function to print the solved Sudoku puzzle
void printSudoku(vector<vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printSudoku(grid);
    } else {
        cout << "No solution exists." << endl;
    }

}
