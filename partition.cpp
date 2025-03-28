#include <vector>
#include <iostream>
using namespace std;
// Partition function using DP
long long partition(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;  // There's 1 way to partition 0

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[j] += dp[j - i];
        }
    }
    return dp[n];
}

int main() {
    int n = 100;  // Example partition number
    cout << "P(" << n << ") = " << partition(n) << endl;
    return 0;
}
