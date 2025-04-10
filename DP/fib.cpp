#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

// Bottom-up approach (Dynamic Programming)
int fibonacciBottomUp(int n) {
    if (n <= 1) return n;

    std::vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// Top-down approach (Memoization)
int fibonacciTopDownHelper(int n, std::unordered_map<int, int>& memo) {
    if (n <= 1) return n;

    if (memo.find(n) != memo.end()) return memo[n];

    memo[n] = fibonacciTopDownHelper(n - 1, memo) + fibonacciTopDownHelper(n - 2, memo);
    return memo[n];
}

int fibonacciTopDown(int n) {
    std::unordered_map<int, int> memo;
    return fibonacciTopDownHelper(n, memo);
}

// Space-optimized approach
int fibonacciSpaceOptimized(int n) {
    if (n <= 1) return n;

    int prev2 = 0, prev1 = 1;

    for (int i = 2; i <= n; ++i) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

void benchmark(int n) {
    auto start = std::chrono::high_resolution_clock::now();
    fibonacciBottomUp(n);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Bottom-Up approach took: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    fibonacciTopDown(n);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Top-Down approach took: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    fibonacciSpaceOptimized(n);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Space-Optimized approach took: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds." << std::endl;
}

int main() {
    int n;
    std::cout << "Enter the value of n: ";
    std::cin >> n;

    std::cout << "The " << n << "th Fibonacci number using Bottom-Up is: " << fibonacciBottomUp(n) << std::endl;
    std::cout << "The " << n << "th Fibonacci number using Top-Down is: " << fibonacciTopDown(n) << std::endl;
    std::cout << "The " << n << "th Fibonacci number using Space Optimization is: " << fibonacciSpaceOptimized(n) << std::endl;

    std::cout << "\nBenchmarking results:\n";
    benchmark(n);

    return 0;
}