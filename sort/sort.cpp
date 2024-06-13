#include <iostream>
#include <vector>
#include <thread>
#include <functional>
using namespace std;
class MergeSort {
public:
    static void Sort(vector<int>& arr) {
        if (arr.size() <= 1) return;

        vector<int> left, right;
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i < arr.size() / 2) left.push_back(arr[i]);
            else right.push_back(arr[i]);
        }

        Sort(left);
        Sort(right);
        Merge(arr, left, right);
    }

private:
    static void Merge(vector<int>& arr, const vector<int>& left, const vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) arr[k++] = left[i++];
            else arr[k++] = right[j++];
        }
        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }
};

int main() {
    vector<int> numbers(10);
    cout << "Enter 10 integers: ";
    for (int& num : numbers) std::cin >> num;

    MergeSort mergeSort;
    auto sortFunc = [&](vector<int>& arr) { mergeSort.Sort(arr); };

    thread mergeSortThread(sortFunc, ref(numbers));
    mergeSortThread.join();

    cout << "Sorted array: ";
    for (int num : numbers) std::cout << num << " ";
    cout << endl;

    return 0;
}