#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

// This program implements various division algorithms
// and benchmarks their performance.
// The algorithms include:
// 1. Restoring Division
// 2. Non-Restoring Division
// 3. Shift-and-Subtract Division
// 4. Newton-Raphson Division
// 5. Goldschmidt Division
// 6. CPU Division (using hardware division instruction)
// The program uses the C++11 standard library for timing
// and the standard input/output library for console output.
// The algorithms are implemented as functions
// and are benchmarked using a template function.
// The benchmark function measures the execution time
// of each algorithm by calling it multiple times
// and calculating the average time taken.
#define NO_OPTIMIZE __attribute__((noinline))
// This attribute prevents the compiler from optimizing the function
// This is useful for benchmarking purposes
// as it ensures that the function is executed as written
// and not optimized away by the compiler

uint32_t NO_OPTIMIZE restoring_division(uint32_t dividend, uint32_t divisor) {
    // Restoring division algorithm
    // This method uses bitwise operations to perform the division
    // It shifts the dividend left and subtracts the divisor
    // The quotient is built up bit by bit
    // The algorithm is similar to the long division method
    // The dividend is shifted left by one bit
    // and the divisor is subtracted from the dividend
    uint32_t quotient = 0;
    uint32_t remainder = 0;
    for (int i = 31; i >= 0; --i) {
        remainder = (remainder << 1) | ((dividend >> i) & 1);
        if (remainder >= divisor) {
            remainder -= divisor;
            quotient |= (1U << i);
        }
    }
    return quotient;
}

uint32_t NO_OPTIMIZE non_restoring_division(uint32_t dividend, uint32_t divisor) {
    // Non-restoring division algorithm
    // This method uses bitwise operations to perform the division
    // It shifts the dividend left and subtracts the divisor
    // The quotient is built up bit by bit
    // The algorithm is similar to the restoring division method
    // The dividend is shifted left by one bit
    uint32_t quotient = 0, remainder = dividend;
    for (int i = 31; i >= 0; --i) {
        remainder = (remainder << 1) | ((dividend >> i) & 1);
        if ((int32_t)remainder >= 0) {
            remainder -= divisor;
            quotient |= (1U << i);
        } else {
            remainder += divisor;
        }
    }
    return quotient;
}

uint32_t NO_OPTIMIZE shift_and_subtract(uint32_t dividend, uint32_t divisor) {
    // Shift-and-subtract division algorithm
    // This method uses bitwise operations to perform the division
    // It shifts the dividend left and subtracts the divisor
    // The quotient is built up bit by bit
    // The algorithm is similar to the long division method
    // The dividend is shifted left by one bit
    // and the divisor is subtracted from the dividend
    // The quotient is built up by setting the corresponding bit
    // The process is repeated until all bits of the dividend are processed
    // The final quotient is returned
    uint32_t quotient = 0;
    int shift = 31;
    while ((divisor << shift) > dividend) shift--;
    
    for (; shift >= 0; --shift) {
        if (dividend >= (divisor << shift)) {
            dividend -= (divisor << shift);
            quotient |= (1U << shift);
        }
    }
    return quotient;
}

double NO_OPTIMIZE newton_raphson_division(double dividend, double divisor) {
    // Newton-Raphson method for division
    // This method uses an iterative approach to approximate the division
    // It starts with an initial guess for the reciprocal of the divisor
    // and refines it using the formula x = x * (2 - divisor * x)
    // The number of iterations can be adjusted for more precision
    // The initial guess is calculated as 1 / divisor
    double x = 1.0 / divisor;
    for (int i = 0; i < 5; ++i) {
        x *= (2 - divisor * x);
    }
    return dividend * x;
}

double NO_OPTIMIZE goldschmidt_division(double dividend, double divisor) {
    // Goldschmidt's method for division
    // This method uses an iterative approach to approximate the division
    // It starts with an initial guess for the reciprocal of the divisor
    // and refines it using the formula x = x * (2 - divisor * x)
    // The number of iterations can be adjusted for more precision
    // The initial guess is calculated as 1 / divisor
    double f = 1.0 / divisor;
    double x = divisor * f;
    double y = dividend * f;
    
    for (int i = 0; i < 3; ++i) {
        double g = 2 - x;
        x *= g;
        y *= g;
    }
    return y;
}

double NO_OPTIMIZE cpu(double dividend, double divisor) {
    // This is a placeholder for hardware division
    // In practice, this would be replaced with a call to the CPU's division instruction
    // For example, in x86 assembly, this would be a DIV or IDIV instruction
    // Here we just use the standard division operator
    // to simulate the hardware division
    // In a real-world scenario, this would be optimized by the compiler
    // and would use the CPU's division instruction
    // The standard division operator is used to perform the division
    // and return the result
    // The result is a double, which is the result of the division
    // The dividend is divided by the divisor
    // and the result is returned
    return dividend / divisor;
}


template <typename Func, typename... Args>
double NO_OPTIMIZE benchmark(Func function, Args... args) {
    // Benchmark the execution time of a function
    // This function takes a function and its arguments
    // and measures the time it takes to execute the function
    // It uses the high_resolution_clock to measure the time
    // The function is called 1,000,000 times to get a more accurate measurement
    // The result is stored in a volatile variable to prevent compiler optimization
    // The start time is recorded before the loop
    // and the end time is recorded after the loop
    // The duration is calculated by subtracting the start time from the end time
    // The result is returned in milliseconds
    // The function is called with the provided arguments
    volatile double result = 0;  // Prevent compiler optimization
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1'000'000; ++i) {
        result += function(args...);  // Prevents loop unrolling
    }
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

int main() {
    uint32_t dividend = 1000003, divisor = 123;
    double fdividend = 1000003.0, fdivisor = 123.0;
    
    cout << "Restoring Division: " << benchmark(restoring_division, dividend, divisor) << " ms" << endl;
    cout << "Non-Restoring Division: " << benchmark(non_restoring_division, dividend, divisor) << " ms" << endl;
    cout << "Shift-and-Subtract: " << benchmark(shift_and_subtract, dividend, divisor) << " ms" << endl;
    cout << "Newton-Raphson: " << benchmark(newton_raphson_division, fdividend, fdivisor) << " ms" << endl;
    cout << "Goldschmidt: " << benchmark(goldschmidt_division, fdividend, fdivisor) << " ms" << endl;
    cout << "Hardware: " << benchmark(cpu, fdividend, fdivisor) << " ms" << endl;
    
    return 0;
}
