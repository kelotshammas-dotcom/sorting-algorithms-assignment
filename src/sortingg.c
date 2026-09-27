#include <stdio.h>

// Global counters for analysis
long merge_comparisons = 0;
long merge_passes = 0;
long quick_partitions = 0;
long quick_comparisons = 0;

// --- MERGE SORT IMPLEMENTATION ---
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        merge_comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
        merge_passes++;
    }
}

// --- QUICK SORT IMPLEMENTATION ---
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing last element as pivot
    int i = (low - 1);
    quick_partitions++;

    for (int j = low; j <= high - 1; j++) {
        quick_comparisons++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Utility function to print array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int input_data[] = {324, 125, 456, 218, 102, 389, 275, 147};
    int n = sizeof(input_data) / sizeof(input_data[0]);

    // Test Merge Sort
    int arr_merge[8];
    for(int i=0; i<n; i++) arr_merge[i] = input_data[i];
    
    printf("--- Merge Sort Execution ---\n");
    mergeSort(arr_merge, 0, n - 1);
    printf("Sorted Sequence: ");
    printArray(arr_merge, n);
    printf("Total Passes/Merges: %ld\n", merge_passes);
    printf("Total Comparisons: %ld\n\n", merge_comparisons);

    // Test Quick Sort
    int arr_quick[8];
    for(int i=0; i<n; i++) arr_quick[i] = input_data[i];

    printf("--- Quick Sort Execution ---\n");
    quickSort(arr_quick, 0, n - 1);
    printf("Sorted Sequence: ");
    printArray(arr_quick, n);
    printf("Total Partitions: %ld\n", quick_partitions);
    printf("Total Comparisons: %ld\n", quick_comparisons);

    return 0;
}
