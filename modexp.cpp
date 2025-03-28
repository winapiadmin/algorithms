// Efficient modular exponentiation (a^b % mod)
long long modExp(long long a, long long b, long long mod) {
    long long result = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return result;
}
// Efficient modular exponentiation (a^b % mod) using iterative method