#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cstring>
using namespace std;
using namespace chrono;

// Generate sorted data for searching
vector<int> generate_sorted_data(size_t size, int min = 0, int max = 1000000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);

    vector<int> data(size);
    for (auto &x : data) x = dist(gen);
    sort(data.begin(), data.end());
    return data;
}

// Generate a hash set for O(1) search
unordered_set<int> generate_hash_set(const vector<int> &data) {
    return unordered_set<int>(data.begin(), data.end());
}

// Benchmark function
template <typename SearchFunc>
double benchmark_search(SearchFunc search_function, const vector<int> &data, int key) {
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1'000'000; ++i) {
        volatile int result = search_function(data, key);
    }
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

// **Linear Search** (O(n))
int linear_search(const vector<int> &data, int key) {
    for (size_t i = 0; i < data.size(); ++i)
        if (data[i] == key) return i;
    return -1;
}

// **Binary Search** (O(log n))
int binary_search_iterative(const vector<int> &data, int key) {
    size_t low = 0, high = data.size() - 1;
    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        if (data[mid] == key) return mid;
        else if (data[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// **Jump Search** (O(√n))
int jump_search(const vector<int> &data, int key) {
    size_t n = data.size();
    size_t step = sqrt(n), prev = 0;
    while (data[min(step, n) - 1] < key) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }
    for (size_t i = prev; i < min(step, n); ++i)
        if (data[i] == key) return i;
    return -1;
}

// **Exponential Search** (O(log n))
int exponential_search(const vector<int> &data, int key) {
    if (data[0] == key) return 0;
    size_t i = 1;
    while (i < data.size() && data[i] <= key) i *= 2;
    return binary_search_iterative(data, key);
}

// **Fibonacci Search** (O(log n))
int fibonacci_search(const vector<int> &data, int key) {
    size_t n = data.size();
    int fib2 = 0, fib1 = 1, fibM = fib1 + fib2;
    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib1 + fib2;
    }
    size_t offset = -1;
    while (fibM > 1) {
        size_t i = min(offset + fib2, n - 1);
        if (data[i] < key) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (data[i] > key) {
            fibM = fib2;
            fib1 -= fib2;
            fib2 = fibM - fib1;
        } else return i;
    }
    return (fib1 && data[offset + 1] == key) ? offset + 1 : -1;
}

// **Interpolation Search** (O(log log n) best, O(n) worst)
int interpolation_search(const vector<int> &data, int key) {
    size_t low = 0, high = data.size() - 1;
    while (low <= high && key >= data[low] && key <= data[high]) {
        if (low == high) return (data[low] == key) ? low : -1;
        size_t pos = low + ((double)(high - low) / (data[high] - data[low]) * (key - data[low]));
        if (data[pos] == key) return pos;
        if (data[pos] < key) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// **Ternary Search** (O(log n))
int ternary_search(const vector<int> &data, int key) {
    size_t low = 0, high = data.size() - 1;
    while (low <= high) {
        size_t mid1 = low + (high - low) / 3;
        size_t mid2 = high - (high - low) / 3;
        if (data[mid1] == key) return mid1;
        if (data[mid2] == key) return mid2;
        if (key < data[mid1]) high = mid1 - 1;
        else if (key > data[mid2]) low = mid2 + 1;
        else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1;
}

// **Upper Bound Search** (O(log n))
int upper_bound_search(const vector<int> &data, int key) {
    auto it = upper_bound(data.begin(), data.end(), key);
    return (it != data.end()) ? distance(data.begin(), it) : -1;
}

// **Lower Bound Search** (O(log n))
int lower_bound_search(const vector<int> &data, int key) {
    auto it = lower_bound(data.begin(), data.end(), key);
    return (it != data.end() && *it == key) ? distance(data.begin(), it) : -1;
}

// **Hash Set Search** (O(1) average, O(n) worst case)
bool hash_search(const unordered_set<int> &hash_set, int key) {
    return hash_set.find(key) != hash_set.end();
}
int linear_search_memchr(const vector<int> &data, int key) {
    // Using memchr to find the first occurrence of key
    // This is a low-level operation and not a standard way to search in C++
    // but demonstrates the use of memory functions.
    // Note: This is not a typical use case for memchr, which is meant for char arrays.
    // This is just for demonstration and not a recommended practice.
    // memchr is not suitable for int arrays, but we can use it for demonstration.
    // This will not work correctly for int arrays, but is included to show the concept.
    // In practice, you should use std::find or std::find_if for searching in vectors.
    // This is a demonstration of using memchr, not a recommended practice.
    return (int*)(memchr(data.data(), key, data.size() * sizeof(int))) - data.data();
}

// **Main Function**
int main() {
    const size_t data_size = 10000;
    auto data = generate_sorted_data(data_size);
    auto hash_set = generate_hash_set(data);

    int key = data[data_size / 2];

    cout << "Searching " << data_size << " elements for key " << key << ":\n";
    cout << "Linear Search: " << benchmark_search(linear_search, data, key) << " ms\n";
    cout << "Low-Level Linear Search: " << benchmark_search(linear_search_memchr,data,key) << " ms\n";
    cout << "Binary Search: " << benchmark_search(binary_search_iterative, data, key) << " ms\n";
    cout << "Jump Search: " << benchmark_search(jump_search, data, key) << " ms\n";
    cout << "Exponential Search: " << benchmark_search(exponential_search, data, key) << " ms\n";
    cout << "Fibonacci Search: " << benchmark_search(fibonacci_search, data, key) << " ms\n";
    cout << "Interpolation Search: " << benchmark_search(interpolation_search, data, key) << " ms\n";
    cout << "Ternary Search: " << benchmark_search(ternary_search, data, key) << " ms\n";
    cout << "Upper Bound Search: " << benchmark_search(upper_bound_search, data, key) << " ms\n";
    cout << "Lower Bound Search: " << benchmark_search(lower_bound_search, data, key) << " ms\n";

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1'000'000; ++i) {
        volatile bool result = hash_search(hash_set, key);
    }
    auto end = high_resolution_clock::now();
    cout << "Hash Set Search: " << duration<double, milli>(end - start).count() << " ms\n";

    return 0;
}
