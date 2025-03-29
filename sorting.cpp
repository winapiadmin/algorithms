#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

// Generate random data
vector<int> generate_data(size_t size, int min = 0, int max = 1000000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);

    vector<int> data(size);
    for (auto &x : data) x = dist(gen);
    return data;
}

// Benchmark function
template <typename SortFunc>
double benchmark_sort(SortFunc sort_function, vector<int> data) {
    auto start = high_resolution_clock::now();
    sort_function(data);
    auto end = high_resolution_clock::now();

    if (!is_sorted(data.begin(), data.end())) {
        cerr << "Sorting failed!\n";
        return -1;
    }

    return duration<double, milli>(end - start).count();
}

// Sorting implementations
void std_sort(vector<int> &data) { sort(data.begin(), data.end()); }
void std_stable_sort(vector<int> &data) { stable_sort(data.begin(), data.end()); }

void bubble_sort(vector<int> &data) {
    size_t n = data.size();
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = 0; j < n - i - 1; ++j)
            if (data[j] > data[j + 1]) swap(data[j], data[j + 1]);
}

void insertion_sort(vector<int> &data) {
    size_t n = data.size();
    for (size_t i = 1; i < n; ++i) {
        int key = data[i];
        size_t j = i;
        while (j > 0 && data[j - 1] > key) {
            data[j] = data[j - 1];
            --j;
        }
        data[j] = key;
    }
}

void selection_sort(vector<int> &data) {
    size_t n = data.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; ++j)
            if (data[j] < data[min_idx]) min_idx = j;
        swap(data[i], data[min_idx]);
    }
}

void merge_sort_helper(vector<int> &data, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_helper(data, left, mid);
    merge_sort_helper(data, mid + 1, right);
    
    vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right)
        temp.push_back((data[i] <= data[j]) ? data[i++] : data[j++]);
    
    while (i <= mid) temp.push_back(data[i++]);
    while (j <= right) temp.push_back(data[j++]);

    copy(temp.begin(), temp.end(), data.begin() + left);
}

void merge_sort(vector<int> &data) { merge_sort_helper(data, 0, data.size() - 1); }

void quick_sort_helper(vector<int> &data, int low, int high) {
    if (low >= high) return;
    int pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
        if (data[j] < pivot) swap(data[++i], data[j]);
    swap(data[i + 1], data[high]);
    quick_sort_helper(data, low, i);
    quick_sort_helper(data, i + 2, high);
}

void quick_sort(vector<int> &data) { quick_sort_helper(data, 0, data.size() - 1); }

void heap_sort(vector<int> &data) {
    make_heap(data.begin(), data.end());
    sort_heap(data.begin(), data.end());
}

void counting_sort(vector<int> &data) {
    if (data.empty()) return;
    int min_val = *min_element(data.begin(), data.end());
    int max_val = *max_element(data.begin(), data.end());
    vector<int> count(max_val - min_val + 1, 0);

    for (int num : data) count[num - min_val]++;
    int index = 0;
    for (int i = 0; i < count.size(); ++i)
        while (count[i]-- > 0) data[index++] = i + min_val;
}

void radix_sort(vector<int> &data) {
    int max_val = *max_element(data.begin(), data.end());
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        vector<int> output(data.size());
        int count[10] = {0};

        for (int num : data) count[(num / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];

        for (int i = data.size() - 1; i >= 0; i--) {
            output[count[(data[i] / exp) % 10] - 1] = data[i];
            count[(data[i] / exp) % 10]--;
        }

        copy(output.begin(), output.end(), data.begin());
    }
}

void shell_sort(vector<int> &data) {
    size_t n = data.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2)
        for (size_t i = gap; i < n; i++) {
            int temp = data[i];
            size_t j = i;
            while (j >= gap && data[j - gap] > temp) {
                data[j] = data[j - gap];
                j -= gap;
            }
            data[j] = temp;
        }
}

void bucket_sort(vector<int> &data) {
    if (data.empty()) return;
    int min_val = *min_element(data.begin(), data.end());
    int max_val = *max_element(data.begin(), data.end());
    int bucket_count = max(1, int(data.size() / 10));
    vector<vector<int>> buckets(bucket_count);

    for (int num : data) {
        int index = (bucket_count * (num - min_val)) / (max_val - min_val + 1);
        buckets[index].push_back(num);
    }

    size_t index = 0;
    for (auto &bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        for (int num : bucket) data[index++] = num;
    }
}

// Main function
int main() {
    const size_t data_size = 10000;
    auto data = generate_data(data_size);

    cout << "Sorting " << data_size << " elements:\n";
    cout << "std::sort: " << benchmark_sort(std_sort, data) << " ms\n";
    cout << "std::stable_sort: " << benchmark_sort(std_stable_sort, data) << " ms\n";
    cout << "Bubble Sort: " << benchmark_sort(bubble_sort, data) << " ms\n";
    cout << "Insertion Sort: " << benchmark_sort(insertion_sort, data) << " ms\n";
    cout << "Selection Sort: " << benchmark_sort(selection_sort, data) << " ms\n";
    cout << "Merge Sort: " << benchmark_sort(merge_sort, data) << " ms\n";
    cout << "Quick Sort: " << benchmark_sort(quick_sort, data) << " ms\n";
    cout << "Heap Sort: " << benchmark_sort(heap_sort, data) << " ms\n";
    cout << "Counting Sort: " << benchmark_sort(counting_sort, data) << " ms\n";
    cout << "Radix Sort: " << benchmark_sort(radix_sort, data) << " ms\n";
    cout << "Shell Sort: " << benchmark_sort(shell_sort, data) << " ms\n";
    cout << "Bucket Sort: " << benchmark_sort(bucket_sort, data) << " ms\n";

    return 0;
}
