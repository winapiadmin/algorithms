#include <iostream>
#include <vector>

using namespace std;

// Multiply two 2x2 matrices
vector<vector<long long>> matrixMultiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B, long long mod) {
    vector<vector<long long>> C(2, vector<long long>(2));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

// Matrix exponentiation
vector<vector<long long>> matrixPow(const vector<vector<long long>>& M, int n, long long mod) {
    vector<vector<long long>> result = {{1, 0}, {0, 1}};  // Identity matrix
    vector<vector<long long>> base = M;

    while (n > 0) {
        if (n % 2 == 1) {
            result = matrixMultiply(result, base, mod);
        }
        base = matrixMultiply(base, base, mod);
        n /= 2;
    }
    return result;
}

// Fibonacci using Matrix Exponentiation
long long fibonacci(int n, long long mod) {
    if (n == 0) return 0;
    vector<vector<long long>> M = {{1, 1}, {1, 0}};
    vector<vector<long long>> result = matrixPow(M, n - 1, mod);
    return result[0][0];  // F(n)
}

int main() {
    int n = 100000;  // Example Fibonacci number
    long long mod = 1000000007;
    cout << "Fibonacci(" << n << ") = " << fibonacci(n, mod) << endl;
    return 0;
}
