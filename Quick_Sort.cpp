#include <iostream>
#include <vector>
using namespace std;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];  // 选第一个元素为基准
    while (low < high) {
        while (low < high && arr[high] >= pivot) high--;
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) low++;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//霍尔分区法（Hoare Partition）>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int partition_hoare(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1, j = high + 1;
    while (true) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);
        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

//霍尔分区返回的是右子数组的起始位置，递归调用时边界不同
void quickSortHoare(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition_hoare(arr, low, high);
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}

//单边扫描法（Lomuto 分区）>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int partition_lomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // 选最后一个为基准
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortLomuto(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition_lomuto(arr, low, high);
        quickSortLomuto(arr, low, pi - 1);
        quickSortLomuto(arr, pi + 1, high);
    }
}

//随机化快速排序（避免最坏情况）>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int randomPartition(vector<int>& arr, int low, int high) {
    srand(time(0));
    int random = low + rand() % (high - low + 1);
    swap(arr[random], arr[high]);//随机选取数据与最后一位交换, 再通过正常的分区算法计算, 妙啊
    return partition_lomuto(arr, low, high);
}

void quickSortRandom(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        quickSortRandom(arr, low, pi - 1);
        quickSortRandom(arr, pi + 1, high);
    }
}

//尾递归优化（减少栈深度）>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void quickSortTailOptimized(vector<int>& arr, int low, int high) {
    while (low < high) {
        int pi = partition_lomuto(arr, low, high);
        if (pi - low < high - pi) {
            quickSortTailOptimized(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quickSortTailOptimized(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}


int main(){
    vector<int> nums;
    for (int k = 100000, i = 0; i <100000; --i) {
        nums[i] = k--;
    }
    quickSort(nums, 0, 100000);
}