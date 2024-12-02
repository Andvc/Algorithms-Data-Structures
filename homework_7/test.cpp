#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "HeapSort.h"

template <typename T>
bool checkSorted(const std::vector<T>& sortedData) {
    for (size_t i = 1; i < sortedData.size(); ++i) {
        if (sortedData[i-1] > sortedData[i]) {
            return false;
        }
    }
    return true;
}

std::vector<int> generateRandomSequence(size_t size) {
    std::vector<int> data(size);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(size));
    for(auto &num : data) {
        num = dist(rng);
    }
    return data;
}

std::vector<int> generateOrderedSequence(size_t size) {
    std::vector<int> data(size);
    for(size_t i = 0; i < size; ++i) {
        data[i] = static_cast<int>(i);
    }
    return data;
}

std::vector<int> generateReverseSequence(size_t size) {
    std::vector<int> data(size);
    for(size_t i = 0; i < size; ++i) {
        data[i] = static_cast<int>(size - i);
    }
    return data;
}

std::vector<int> generateRepetitiveSequence(size_t size) {
    std::vector<int> data(size);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(size / 100)); // 频繁重复
    for(auto &num : data) {
        num = dist(rng);
    }
    return data;
}

template <typename T, typename SortFunction>
double testSort(std::vector<T>& data, SortFunction sortFunction) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

int main() {
    const size_t SIZE = 1000000;

    // 生成测试序列
    std::vector<int> randomSeq = generateRandomSequence(SIZE);
    std::vector<int> orderedSeq = generateOrderedSequence(SIZE);
    std::vector<int> reverseSeq = generateReverseSequence(SIZE);
    std::vector<int> repetitiveSeq = generateRepetitiveSequence(SIZE);

    // 定义一个lambda用于 std::sort_heap
    auto sortHeapStd = [](std::vector<int>& data) {
        // 使用 std::make_heap 和 std::sort_heap
        std::make_heap(data.begin(), data.end());
        std::sort_heap(data.begin(), data.end());
    };

    // 定义一个lambda用于 HeapSort
    auto sortHeapMy = [](std::vector<int>& data) {
        HeapSort<int>::sort(data);
    };

    // 测试函数结构
    struct TestResult {
        std::string name;
        double myTime;
        double stdTime;
    };

    std::vector<TestResult> results;

    // 测试随机序列
    {
        std::vector<int> data = randomSeq; // 创建独立副本
        double myTime = testSort(data, sortHeapMy);
        bool correct = checkSorted(data);
        if (!correct) {
            std::cerr << "HeapSort failed on random sequence!" << std::endl;
        }

        // 使用 std::sort_heap
        std::vector<int> dataStd = randomSeq; // 创建独立副本
        double stdTime = testSort(dataStd, sortHeapStd);
        bool correctStd = checkSorted(dataStd);
        if (!correctStd) {
            std::cerr << "std::sort_heap failed on random sequence!" << std::endl;
        }

        results.push_back({"Random Sequence", myTime, stdTime});
        std::cout << "Random Sequence: HeapSort Time = " << myTime << " s, std::sort_heap Time = " << stdTime << " s" << std::endl;
    }

    // 测试有序序列
    {
        std::vector<int> data = orderedSeq; // 创建独立副本
        double myTime = testSort(data, sortHeapMy);
        bool correct = checkSorted(data);
        if (!correct) {
            std::cerr << "HeapSort failed on ordered sequence!" << std::endl;
        }

        // 使用 std::sort_heap
        std::vector<int> dataStd = orderedSeq; // 创建独立副本
        double stdTime = testSort(dataStd, sortHeapStd);
        bool correctStd = checkSorted(dataStd);
        if (!correctStd) {
            std::cerr << "std::sort_heap failed on ordered sequence!" << std::endl;
        }

        results.push_back({"Ordered Sequence", myTime, stdTime});
        std::cout << "Ordered Sequence: HeapSort Time = " << myTime << " s, std::sort_heap Time = " << stdTime << " s" << std::endl;
    }

    // 测试逆序序列
    {
        std::vector<int> data = reverseSeq; // 创建独立副本
        double myTime = testSort(data, sortHeapMy);
        bool correct = checkSorted(data);
        if (!correct) {
            std::cerr << "HeapSort failed on reverse sequence!" << std::endl;
        }

        // 使用 std::sort_heap
        std::vector<int> dataStd = reverseSeq; // 创建独立副本
        double stdTime = testSort(dataStd, sortHeapStd);
        bool correctStd = checkSorted(dataStd);
        if (!correctStd) {
            std::cerr << "std::sort_heap failed on reverse sequence!" << std::endl;
        }

        results.push_back({"Reverse Sequence", myTime, stdTime});
        std::cout << "Reverse Sequence: HeapSort Time = " << myTime << " s, std::sort_heap Time = " << stdTime << " s" << std::endl;
    }

    // 测试部分元素重复序列
    {
        std::vector<int> data = repetitiveSeq; // 创建独立副本
        double myTime = testSort(data, sortHeapMy);
        bool correct = checkSorted(data);
        if (!correct) {
            std::cerr << "HeapSort failed on repetitive sequence!" << std::endl;
        }

        // 使用 std::sort_heap
        std::vector<int> dataStd = repetitiveSeq; // 创建独立副本
        double stdTime = testSort(dataStd, sortHeapStd);
        bool correctStd = checkSorted(dataStd);
        if (!correctStd) {
            std::cerr << "std::sort_heap failed on repetitive sequence!" << std::endl;
        }

        results.push_back({"Repetitive Sequence", myTime, stdTime});
        std::cout << "Repetitive Sequence: HeapSort Time = " << myTime << " s, std::sort_heap Time = " << stdTime << " s" << std::endl;
    }

    return 0;
}
