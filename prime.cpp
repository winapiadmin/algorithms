//-funroll-loops -ffast-math -O3 -march=native -mtune=native -pipe -flto -fwhole-program -fwhole-file -fomit-frame-pointer
#include <cstring>
#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <immintrin.h>  // For SIMD (AVX, SSE4.1)
#include <bitset>
#include <smmintrin.h>  // SSE4.1
using namespace std;
using ll=long long;
/// Optimized Modular Multiplication (eliminates overhead)
inline ll modMulOptimized(ll a, ll b, ll mod) {
    return (ll)((__int128)a * b % mod);
}

/// Optimized Modular Exponentiation
inline ll powerOptimized(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = modMulOptimized(res, base, mod);
        base = modMulOptimized(base, base, mod);
        exp >>= 1;
    }
    return res;
}

/// Optimized Miller-Rabin Primality Test
bool millerRabin(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return (n == 2);
    
    ll d = n - 1;
    int r = __builtin_ctzll(d);
    d >>= r;

    auto witness = [&](ll a) {
        ll x = powerOptimized(a, d, n);
        if (x == 1 || x == n - 1) return false;

        for (int i = 0; i < r - 1; i += 2) {
            x = modMulOptimized(x, x, n);
            if (x == n - 1) return false;
            x = modMulOptimized(x, x, n);
            if (x == n - 1) return false;
        }
        return true;
    };

    static const vector<int> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (int a : bases) {
        if (a >= n) break;
        if (n % a == 0 || witness(a)) return false;
    }
    return true;
}

// 6k ± 1 Prime Test
bool isPrime6k1(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

// Wheel Factorization Prime Test
bool isPrimeWheel(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3 || n == 5) return true;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) return false;

    static const int wheel[] = {4, 2, 4, 2, 4, 6, 2, 6};
    int index = 0;
    for (long long i = 7; i * i <= n; i += wheel[index++]) {
        if (n % i == 0) return false;
        index&=7;
    }
    return true;
}
bool isPrime6k1_asm(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    ll i = 5;
    ll prime = 1;

    __asm__ __volatile__ (
        "movq $1, %[prime]\n\t"  // Assume prime = true

        "1:\n\t"
        "movq %[i], %%rax\n\t"
        "imulq %%rax, %%rax\n\t"
        "cmpq %[n], %%rax\n\t"
        "jg 2f\n\t"  // If i * i > n, exit loop

        // Check n % i == 0
        "movq %[n], %%rax\n\t"
        "xorq %%rdx, %%rdx\n\t"
        "divq %[i]\n\t"
        "testq %%rdx, %%rdx\n\t"
        "jz 3f\n\t"  // If n % i == 0, jump to not prime

        // Check n % (i + 2) == 0
        "addq $2, %[i]\n\t"
        "movq %[n], %%rax\n\t"
        "xorq %%rdx, %%rdx\n\t"
        "divq %[i]\n\t"
        "testq %%rdx, %%rdx\n\t"
        "jz 3f\n\t"  // If n % (i+2) == 0, jump to not prime

        "addq $4, %[i]\n\t"  // i += 6 (5 → 7 → 11, etc.)
        "jmp 1b\n\t"         // Loop

        "2:\n\t"  // Prime confirmed
        "jmp 4f\n\t"

        "3:\n\t"  // Not prime
        "movq $0, %[prime]\n\t"

        "4:\n\t"
        : [prime] "=&r"(prime), [i] "+&r"(i)
        : [n] "r"(n)
        : "rax", "rdx"
    );

    return prime;
}

const int MAX_TEST = 500000;
const int LIM = MAX_TEST / 2; // Store only odd numbers

std::bitset<LIM> sieve; // Bitset storage

inline void setComposite(int i) {
    sieve.set(i / 2); // Store only odd indices
}

inline bool isPrime(int n) {
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    return !sieve[n / 2]; // Check bit directly
}

void bitwiseSieve(int n) {
    sieve.reset(); // Clear all bits

    for (int i = 3; i * i <= n; i += 2) {
        if (!sieve[i / 2]) { // Prime check
            for (int j = i * i; j <= n; j += i * 2) {
                if (j / 2 < LIM) sieve.set(j / 2); // Ensure in bounds
            }
        }
    }
}

void testAccuracy() {
    bitwiseSieve(MAX_TEST + 1);
    
    int _6k1_asmCorrect = 0, millerCorrect = 0, wheelCorrect = 0, sixKCorrect = 0;
    int totalTests = 0;

    for (ll n = 1; n <= MAX_TEST; n++) {
        bool expected = isPrime(n);
        bool _6k1_asmResult = isPrime6k1_asm(n);
        bool wheelResult = isPrimeWheel(n);
        bool millerResult = millerRabin(n);
        bool _6k1 = isPrime6k1(n);

        // Track accuracy
        if (_6k1_asmResult == expected) _6k1_asmCorrect++;
        if (millerResult == expected) millerCorrect++;
        if (wheelResult == expected) wheelCorrect++;
        if (_6k1 == expected) sixKCorrect++;

        // If there's a disagreement, print all results
        if (!(_6k1_asmResult == millerResult &&
              millerResult == wheelResult &&
              wheelResult == _6k1 &&
              _6k1 == expected)) {
            printf("Disagreement at     : %lld\n", n);
            printf("Sieve (Expected)    : %d\n", expected);
            printf("6k ± 1 with assembly: %d\n", _6k1_asmResult);
            printf("Miller-Rabin        : %d\n", millerResult);
            printf("Wheel Method        : %d\n", wheelResult);
            printf("6k ± 1 Method       : %d\n", _6k1);
            printf("--------------------------------\n");
        }

        totalTests++;
    }

    printf("Accuracy of Optimized Wheel Method: %.6f%%\n", (double)_6k1_asmCorrect / totalTests * 100.0);
    printf("Accuracy of Miller-Rabin: %.6f%%\n", (double)millerCorrect / totalTests * 100.0);
    printf("Accuracy of Wheel Method: %.6f%%\n", (double)wheelCorrect / totalTests * 100.0);
    printf("Accuracy of 6k ± 1 Method: %.6f%%\n", (double)sixKCorrect / totalTests * 100.0);
}

// Benchmark function
typedef bool (*PrimeFunc)(ll);
ll benchmark(PrimeFunc func, double timeLimit) {
    ll count = 0, num = 2;
    auto start = chrono::high_resolution_clock::now();
    while (true) {
        if (func(num)) count++;
        num++;
        auto now = chrono::high_resolution_clock::now();
        if (chrono::duration<double>(now - start).count() >= timeLimit) break;
    }
    return count;
}

int main() {
    double timeLimit = 1; // 1 second per test
    cout << "Benchmarking each method for " << timeLimit << " second(s)...\n";
    
    cout << "Miller-Rabin: " << benchmark(millerRabin, timeLimit) << " primes found\n";
    cout << "6k ± 1 Method: " << benchmark(isPrime6k1, timeLimit) << " primes found\n";
    cout << "Wheel Method: " << benchmark(isPrimeWheel, timeLimit) << " primes found\n";
    cout << "6k ± 1 with assembly method: " << benchmark(isPrime6k1_asm, timeLimit) << " primes found\n";

    cout << "\nRunning accuracy test...\n";
    testAccuracy();

    return 0;
}
