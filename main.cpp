#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>

std::vector<int> generateRandomData(int size) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000000);
    for (int i = 0; i < size; ++i) {
        data[i] = distrib(gen);
    }
    return data;
}

// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Sequential Search
int sequentialSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Binary Search
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    std::cout << "Running algorithm analysis...\n";

    std::ofstream bubble_sort_results("bubble_sort_results.csv");
    std::ofstream insertion_sort_results("insertion_sort_results.csv");
    std::ofstream sequential_search_results("sequential_search_results.csv");
    std::ofstream binary_search_results("binary_search_results.csv");

    bubble_sort_results << "n,time_ns\n";
    insertion_sort_results << "n,time_ns\n";
    sequential_search_results << "n,time_ns\n";
    binary_search_results << "n,time_ns\n";

    std::vector<int> input_sizes = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000};
    int num_repetitions = 5;

    for (int n : input_sizes) {
        long long total_bubble_time = 0;
        long long total_insertion_time = 0;
        long long total_sequential_search_time = 0;
        long long total_binary_search_time = 0;

        for (int i = 0; i < num_repetitions; ++i) {
            std::vector<int> data = generateRandomData(n);
            std::vector<int> data_copy_for_sort = data;
            std::vector<int> data_copy_for_search = data;

            auto start = std::chrono::high_resolution_clock::now();
            bubbleSort(data_copy_for_sort);
            auto end = std::chrono::high_resolution_clock::now();
            total_bubble_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            data_copy_for_sort = data;

            start = std::chrono::high_resolution_clock::now();
            insertionSort(data_copy_for_sort);
            end = std::chrono::high_resolution_clock::now();
            total_insertion_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            int target = data_copy_for_search[rand() % n];
            std::sort(data_copy_for_search.begin(), data_copy_for_search.end());

            start = std::chrono::high_resolution_clock::now();
            sequentialSearch(data, target);
            end = std::chrono::high_resolution_clock::now();
            total_sequential_search_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            binarySearch(data_copy_for_search, target);
            end = std::chrono::high_resolution_clock::now();
            total_binary_search_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        bubble_sort_results << n << "," << total_bubble_time / num_repetitions << "\n";
        insertion_sort_results << n << "," << total_insertion_time / num_repetitions << "\n";
        sequential_search_results << n << "," << total_sequential_search_time / num_repetitions << "\n";
        binary_search_results << n << "," << total_binary_search_time / num_repetitions << "\n";
        std::cout << "Processed n = " << n << "\n";
    }

    bubble_sort_results.close();
    insertion_sort_results.close();
    sequential_search_results.close();
    binary_search_results.close();

    std::cout << "Analise completa.\n";

    return 0;
}