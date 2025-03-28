#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <climits>
using namespace std;
using namespace chrono;

// --- Fibonacci (Dynamic Programming) ---
int fibonacciDP(int n) {
    if (n <= 1) return n;
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int fibonacciMemoization(int n, vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibonacciMemoization(n - 1, memo) + fibonacciMemoization(n - 2, memo);
    return memo[n];
}

// --- Fractional Knapsack (Greedy) ---
struct Item {
    int weight;
    int value;
    double ratio;

    Item(int w, int v) : weight(w), value(v), ratio((double)v / w) {}
};

double fractionalKnapsack(int W, vector<Item>& items) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;  // Sort items by value-to-weight ratio
    });

    double totalValue = 0.0;
    for (auto& item : items) {
        if (W == 0) break;
        if (item.weight <= W) {
            totalValue += item.value;
            W -= item.weight;
        } else {
            totalValue += item.value * ((double)W / item.weight);
            W = 0;
        }
    }
    return totalValue;
}

// --- 0/1 Knapsack Problem (Dynamic Programming) ---
int knapsackDP(int W, vector<int>& weights, vector<int>& values, int n) {
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

// --- Coin Change Problem (Greedy) ---
int coinChangeGreedy(int amount, vector<int>& coins) {
    sort(coins.rbegin(), coins.rend());  // Sort coins in descending order

    int count = 0;
    for (int coin : coins) {
        if (amount == 0) break;
        count += amount / coin;
        amount %= coin;
    }
    return count;
}

// --- Coin Change Problem (Dynamic Programming) ---
int coinChangeDP(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i - coin >= 0 && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// --- Utility function to benchmark ---
template<typename Func, typename... Args>
void benchmark(const string& name, Func&& func, Args&&... args) {
    auto start = high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << name << " took " << duration.count() << " microseconds." << endl;
}

int main() {
    // --- Fibonacci Benchmarking ---
    int fib_n = 40;
    vector<int> memo(fib_n + 1, -1);

    cout << "Benchmarking Fibonacci (DP - Bottom-Up): " << endl;
    benchmark("Fibonacci DP Bottom-Up", fibonacciDP, fib_n);

    cout << "Benchmarking Fibonacci (Memoization): " << endl;
    benchmark("Fibonacci Memoization", fibonacciMemoization, fib_n, memo);

    // --- Fractional Knapsack Benchmarking ---
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    int knapsack_capacity = 50;
    cout << "Benchmarking Fractional Knapsack (Greedy): " << endl;
    benchmark("Fractional Knapsack (Greedy)", fractionalKnapsack, knapsack_capacity, items);

    // --- 0/1 Knapsack Benchmarking ---
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int W = 50;
    int n = values.size();
    cout << "Benchmarking 0/1 Knapsack (DP): " << endl;
    benchmark("0/1 Knapsack (DP)", knapsackDP, W, weights, values, n);

    // --- Coin Change Benchmarking ---
    vector<int> coins = {1, 5, 10, 25};
    int amount = 63;

    cout << "Benchmarking Coin Change (Greedy): " << endl;
    benchmark("Coin Change (Greedy)", coinChangeGreedy, amount, coins);

    cout << "Benchmarking Coin Change (DP): " << endl;
    benchmark("Coin Change (DP)", coinChangeDP, amount, coins);

    return 0;
}
