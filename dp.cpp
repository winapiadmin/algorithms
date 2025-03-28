#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

// --- Fibonacci ---
int fibonacci(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int fibonacci_memoization(int n, vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibonacci_memoization(n - 1, memo) + fibonacci_memoization(n - 2, memo);
    return memo[n];
}

// --- Pathfinding Problems ---
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; i++) dp[i][0] = dp[i - 1][0] + grid[i][0];
    for (int j = 1; j < n; j++) dp[0][j] = dp[0][j - 1] + grid[0][j];
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }
    return dp[m - 1][n - 1];
}

// --- Knapsack Problem (0/1 Knapsack) ---
int knapsack(int W, vector<int>& weights, vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

// --- Longest Common Subsequence ---
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

// --- Utility function to run benchmarks ---
template<typename Func, typename... Args>
void benchmark(const string& name, Func&& func, Args&&... args) {
    auto start = high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << name << " took " << duration.count() << " microseconds." << endl;
}

int main() {
    // Benchmark for Fibonacci
    int fib_n = 40;  // For Fibonacci problem, choose an n large enough
    cout << "Benchmarking Fibonacci (Bottom-Up): " << endl;
    benchmark("Fibonacci Bottom-Up", fibonacci, fib_n);

    vector<int> memo(fib_n + 1, -1);
    cout << "Benchmarking Fibonacci (Top-Down with Memoization): " << endl;
    benchmark("Fibonacci Top-Down Memoization", fibonacci_memoization, fib_n, memo);

    // Benchmark for Pathfinding Problem (Minimum Path Sum)
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << "Benchmarking Minimum Path Sum: " << endl;
    benchmark("Minimum Path Sum", minPathSum, grid);

    // Benchmark for Knapsack Problem (0/1 Knapsack)
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int W = 50;
    int n = values.size();
    cout << "Benchmarking 0/1 Knapsack: " << endl;
    benchmark("0/1 Knapsack", knapsack, W, weights, values, n);

    // Benchmark for Longest Common Subsequence (LCS)
    string text1 = "abcde";
    string text2 = "ace";
    cout << "Benchmarking Longest Common Subsequence: " << endl;
    benchmark("Longest Common Subsequence", longestCommonSubsequence, text1, text2);

    return 0;
}
