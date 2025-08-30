#include <iostream>
#include <cmath>
using namespace std;

class Sudoku {
private:
    int n;
    int grid[20][20];

    bool isSafe(int row, int col, int num) {
        for (int x = 0; x < n; x++) {
            if (grid[row][x] == num) return false;
        }
        for (int x = 0; x < n; x++) {
            if (grid[x][col] == num) return false;
        }
        int root = sqrt(n);
        if (root * root == n) {
            int startRow = row - row % root;
            int startCol = col - col % root;
            for (int i = 0; i < root; i++) {
                for (int j = 0; j < root; j++) {
                    if (grid[startRow + i][startCol + j] == num)
                        return false;
                }
            }
        }
        return true;
    }

    bool solveSudoku() {
        int row, col;
        if (!findEmptyCell(row, col)) return true;
        for (int num = 1; num <= n; num++) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;
                if (solveSudoku()) return true;
                grid[row][col] = 0;
            }
        }
        return false;
    }

    bool findEmptyCell(int &row, int &col) {
        for (row = 0; row < n; row++) {
            for (col = 0; col < n; col++) {
                if (grid[row][col] == 0) return true;
            }
        }
        return false;
    }

public:
    Sudoku(int size) {
        if (size < 3) size = 3;
        n = size;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                grid[i][j] = 0;
    }

    void inputGrid() {
        cout << "Enter " << n << "x" << n << " Sudoku puzzle (0 for empty):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }
    }

    void solve() {
        if (solveSudoku()) {
            cout << "\nSolved Sudoku:\n";
            printGrid();
        } else {
            cout << "\nNo solution exists!\n";
        }
    }

    void printGrid() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int size;
    cout << "Enter size of Sudoku grid (minimum 3): ";
    cin >> size;

    Sudoku s(size);
    s.inputGrid();

    cout << "\nInitial Sudoku:\n";
    s.printGrid();

    cout << "\nSolving...\n";
    s.solve();

    return 0;
}
