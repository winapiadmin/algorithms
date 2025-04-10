#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the maximum sum path in a grid
int maxSumPath(const vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> dp(rows, vector<int>(cols, 0));

    dp[0][0] = grid[0][0];

    // Fill the first row
    for (int j = 1; j < cols; ++j) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Fill the first column
    for (int i = 1; i < rows; ++i) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Fill the rest of the grid
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    return dp[rows - 1][cols - 1];
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols));
    cout << "Enter the grid values row by row:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> grid[i][j];
        }
    }

    int result = maxSumPath(grid);
    cout << "The maximum sum path is: " << result << endl;

    return 0;
}