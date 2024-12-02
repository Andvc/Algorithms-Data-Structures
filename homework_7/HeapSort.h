#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <algorithm>

template <typename T>
class HeapSort {
public:

    static void sort(std::vector<T>& data) {
        buildMaxHeap(data);
        for (size_t end = data.size() - 1; end > 0; --end) {
            // 交换堆顶与堆的最后一个元素
            std::swap(data[0], data[end]);
            // 调整堆
            siftDown(data, 0, end);
        }
    }

private:

    static void buildMaxHeap(std::vector<T>& data) {
        size_t n = data.size();
        // 从最后一个非叶子节点开始，向上调整
        for (int i = static_cast<int>(n / 2) - 1; i >= 0; --i) {
            siftDown(data, i, n);
        }
    }


    static void siftDown(std::vector<T>& data, size_t start, size_t end) {
        size_t root = start;
        while (true) {
            size_t child = 2 * root + 1; // 左子节点
            if (child >= end) break;

            // 如果有右子节点，且右子节点更大
            if (child + 1 < end && data[child] < data[child + 1]) {
                child++;
            }

            // 如果根节点已经大于等于最大的子节点，则堆性质满足
            if (data[root] >= data[child]) {
                break;
            }

            // 交换根节点与子节点
            std::swap(data[root], data[child]);
            root = child;
        }
    }
};

#endif // HEAPSORT_H
