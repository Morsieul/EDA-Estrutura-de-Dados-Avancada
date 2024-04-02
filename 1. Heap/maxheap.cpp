#include<iostream>
#include<vector>

void troca(int a, int b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

class MaxHeap {
    private: 
    std::vector<int> heap;
   

  void MaxHeapify(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap.size() && heap[left] > heap[largest]) {
      largest = left;
    }

    if (right < heap.size() && heap[right] > heap[largest]) {
      largest = right;
    }

    if (largest != i) {
      troca(heap[i], heap[largest]);
      MaxHeapify(largest);
    }
  }

public:
    MaxHeap() {}

  void BuildMaxHeap() {
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
      MaxHeapify(i);
    }
  }
  
   void insert(int key) {

    heap.push_back(key);
    int i = heap.size() - 1;
    while (i > 0 && heap[i] > heap[(i - 1) / 2]) {
      troca(heap[i], heap[(i - 1) / 2]);
      i = (i - 1) / 2;
    }

   }

     int removeMax() {
        if (heap.empty()) {
        return -1;
        }
        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        MaxHeapify(0);
        return max;
  }

  bool IsEmpty() {
    return heap.empty();
  }

  void showHeap() {
    for (int i : heap) {
      std:: cout << i << " ";
    }
    std::cout << "\n";
  }

};

