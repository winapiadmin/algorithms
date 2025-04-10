#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void findMaxSumPaths(vector<vector<int>>& grid, int i, int j, int currentSum, int& maxSum, vector<int>& path, vector<vector<int>>& resultPaths) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Add the current cell to the path and sum
    currentSum += grid[i][j];
    path.push_back(grid[i][j]);

    // If we reach the bottom-right corner
    if (i == rows - 1 && j == cols - 1) {
        if (currentSum > maxSum) {
            maxSum = currentSum;
            resultPaths.clear();
            resultPaths.push_back(path);
        } else if (currentSum == maxSum) {
            resultPaths.push_back(path);
        }
    } else {
        // Move down
        if (i + 1 < rows) {
            findMaxSumPaths(grid, i + 1, j, currentSum, maxSum, path, resultPaths);
        }
        // Move right
        if (j + 1 < cols) {
            findMaxSumPaths(grid, i, j + 1, currentSum, maxSum, path, resultPaths);
        }
    }

    // Backtrack
    path.pop_back();
}

vector<vector<int>> getMaxSumPaths(vector<vector<int>>& grid) {
    int maxSum = INT_MIN;
    vector<int> path;
    vector<vector<int>> resultPaths;

    findMaxSumPaths(grid, 0, 0, 0, maxSum, path, resultPaths);

    return resultPaths;
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 2},
        {1, 9, 8},
        {4, 6, 7}
    };

    vector<vector<int>> maxSumPaths = getMaxSumPaths(grid);

    cout << "Paths with maximum sum:" << endl;
    for (const auto& path : maxSumPaths) {
        for (int val : path) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}