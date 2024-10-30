#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>  // For std::sort

using namespace std;
using namespace chrono;

// Utility function to fill the arrays
vector<int> generateBestCaseArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

vector<int> generateAverageCaseArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % size;
    }
    return arr;
}

vector<int> generateWorstCaseArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    return arr;
}

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Merge function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to measure the time taken by each sorting algorithm
template <typename SortFunction>
void measureTime(SortFunction sortFunc, const vector<int>& originalArr, const string& sortName, const string& caseType) {
    vector<int> arr = originalArr; // Create a copy of the original array for each sort
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << sortName << " (" << caseType << "): " << duration.count() << " ms" << endl;
}

// Wrapper function to execute all sorting algorithms on the arrays
void runSorts(const vector<int>& baseArray, const string& caseType) {
    measureTime([](vector<int>& a){ bubbleSort(a); }, baseArray, "Bubble Sort", caseType);
    measureTime([](vector<int>& a){ selectionSort(a); }, baseArray, "Selection Sort", caseType);
    measureTime([](vector<int>& a){ mergeSort(a, 0, a.size() - 1); }, baseArray, "Merge Sort", caseType);
    measureTime([](vector<int>& a){ quickSort(a, 0, a.size() - 1); }, baseArray, "Quick Sort", caseType);
}

int main() {
    int size = 10000;  // Increased size for measurable time differences

    // Generate the base arrays for each case
    vector<int> bestCaseArray = generateBestCaseArray(size);
    vector<int> averageCaseArray = generateAverageCaseArray(size);
    vector<int> worstCaseArray = generateWorstCaseArray(size);

    cout << "Sorting Best Case Arrays:" << endl;
    runSorts(bestCaseArray, "Best Case");

    cout << "\nSorting Average Case Arrays:" << endl;
    runSorts(averageCaseArray, "Average Case");

    cout << "\nSorting Worst Case Arrays:" << endl;
    runSorts(worstCaseArray, "Worst Case");

    return 0;
}
