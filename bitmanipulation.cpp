#include <iostream>
#include <vector>

using namespace std;

void printSubsets(int n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        printf("{ ");
        // Iterate through each bit position
        // and check if it is set in the current mask
        // If it is set, include the corresponding element in the subset
        // For example, if n = 3, the subsets will be:
        // {}, {0}, {1}, {2}, {0, 1}, {0, 2}, {1, 2}, {0, 1, 2}
        // The mask represents the subset, where each bit position corresponds to an element
        // If the bit is set, include that element in the subset
        // For example, if mask = 5 (binary 101), it represents the subset {0, 2}
        // The first bit (0) is set, so include element 0
        // The second bit (1) is not set, so do not include element 1
        // The third bit (2) is set, so include element 2
        // The final subset is {0, 2}
        // The number of subsets is 2^n, where n is the number of elements
        // The total number of subsets is 2^n, where n is the number of elements
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // If the ith bit is set, include element i in the subset
                printf("%d ", i);
            }
        }
        printf("}\n");
    }
}
int findSingleNumber(const vector<int>& nums) {
    int result = 0;
    // XOR all numbers in the array
    // The XOR operation has the property that a ^ a = 0 and a ^ 0 = a
    for (int num : nums) {
        result ^= num;  // XOR all numbers, duplicates cancel out
    }
    return result;
}
// Brian Kernighan’s Algorithm to count set bits
int countSetBits(int n) {
    // Using __builtin_popcount for GCC/Clang
    // This function counts the number of set bits in an integer
    // It uses the built-in function __builtin_popcount
    // which is optimized for counting set bits in a number
    // The function works by repeatedly clearing the least significant set bit
    // and counting how many times this operation can be performed
    // until the number becomes zero
    // The number of times this operation is performed is the number of set bits
    // For example, if n = 13 (binary 1101), the set bits are 3
    return __builtin_popcount(n);
}

int rightmostSetBit(int n) {
    return n & -n; // This isolates the rightmost set bit
}

constexpr bool isPowerOfTwo(int n) {
    // A number is a power of two if it has only one bit set
    // This function checks if a number is a power of two
    // by using the property that a power of two has only one bit set
    // For example, 1 (2^0), 2 (2^1), 4 (2^2), 8 (2^3), etc.
    // The function checks if the number is greater than zero
    // and if the bitwise AND of the number and (number - 1) is zero
    // If both conditions are true, the number is a power of two
    // For example, if n = 4 (binary 100), n - 1 = 3 (binary 011)
    // The bitwise AND of 4 and 3 is zero, so 4 is a power of two
    // If n = 5 (binary 101), n - 1 = 4 (binary 100)
    // The bitwise AND of 5 and 4 is not zero, so 5 is not a power of two
    // The function returns true if the number is a power of two
    // and false otherwise
    return (n > 0) && (n & (n - 1)) == 0;
}

vector<int> generateGrayCode(int n) {
    // Generate Gray code sequence for n bits
    // Gray code is a binary numeral system where two successive values differ in only one bit
    // The formula for generating Gray code is G(i) = i ^ (i >> 1)
    // where G(i) is the ith Gray code value and i is the binary number
    // The function generates the Gray code sequence for n bits
    // by iterating from 0 to 2^n - 1 and applying the formula
    // The function returns a vector of integers representing the Gray code sequence
    // For example, if n = 2, the Gray code sequence is:
    // 00, 01, 11, 10
    // which corresponds to the decimal values 0, 1, 3, 2
    // The function uses a bitwise XOR operation to generate the Gray code
    // The XOR operation has the property that a ^ a = 0 and a ^ 0 = a
    // The function iterates from 0 to 2^n - 1 and applies the formula
    // G(i) = i ^ (i >> 1) to generate the Gray code sequence
    // The function uses a vector to store the Gray code values
    // and returns the vector at the end
    // The number of Gray code values is 2^n, where n is the number of bits
    // The total number of Gray code values is 2^n, where n is the number of bits
    // The function uses a bitwise XOR operation to generate the Gray code
    vector<int> result;
    for (int i = 0; i < (1 << n); ++i) {
        result.push_back(i ^ (i >> 1)); // Apply the Gray code formula
    }
    return result;
}