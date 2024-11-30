#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class SortingComparison {
public:
    // Insertion Sort
    void insertionSort(std::vector<int>& arr) {
        size_t n = arr.size();
        for (size_t i = 1; i < n; ++i) {
            int key = arr[i];
            size_t j = i;
            while (j > 0 && arr[j - 1] > key) {
                arr[j] = arr[j - 1];
                --j;
            }
            arr[j] = key;
        }
    }

    // Quick Sort
    void quickSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int pivotIndex = partition(arr, left, right);
            quickSort(arr, left, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, right);
        }
    }

    // Merge Sort
    void mergeSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    // Generate random integers
    std::vector<int> generateRandomArray(int size) {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100000);
        for (int& x : arr) {
            x = dist(gen);
        }
        return arr;
    }

    // Test if the array is sorted
    bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    // Compare run times for three sorting algorithms
    void compareSortingAlgorithms() {
        std::vector<int> sizes = { 1000, 10000, 100000 }; // Data scales
        for (int size : sizes) {
            std::vector<int> arr = generateRandomArray(size);
            std::cout << "Data size: " << size << "\n";

            // Test Insertion Sort for small sizes only
            if (size <= 10000) {
                std::vector<int> arr_copy = arr;
                auto start = std::chrono::high_resolution_clock::now();
                insertionSort(arr_copy);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Insertion Sort: " << elapsed.count() << " seconds\n";
                std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";
            }
            else {
                std::cout << "Insertion Sort: Skipped for large data size\n";
            }

            // Test Quick Sort
            std::vector<int> arr_copy = arr;
            auto start = std::chrono::high_resolution_clock::now();
            quickSort(arr_copy, 0, arr_copy.size() - 1);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Quick Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";

            // Test Merge Sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            mergeSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Merge Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n\n";
        }
    }

private:
    // Partition function for Quick Sort
    int partition(std::vector<int>& arr, int left, int right) {
        int pivot = arr[right]; 
        int i = left - 1;       
        for (int j = left; j < right; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[right]); // Places the pivot in the correct position
        return i + 1;
    }

    // Merge function for Merge Sort
    void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Creates temp arrays
        std::vector<int> L(n1);
        std::vector<int> R(n2);

        // Copies the data to temp arrays L[] and R[]
        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        // Merge the temp arrays back into arr[left..right]
        int i = 0;     
        int j = 0;     
        int k = left;  

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                ++i;
            }
            else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        // Copies any remaining elements of L[]
        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        // Copies any remaining elements of R[]
        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }
};

int main() {
    SortingComparison sorter;
    sorter.compareSortingAlgorithms();
    return 0;
}
