#include<iostream>
#include<vector>
#include<algorithm>
void troca(std::pair<int, int>& a, std::pair<int, int>& b) {
    std::pair<int, int> temp = a;
    a = b;
    b = temp;
}

class MaxHeap {
private: 
    std::vector<std::pair<int, int>> heap;

    void MaxHeapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap.size() && heap[left].first > heap[largest].first) {
            largest = left;
        }

        if (right < heap.size() && heap[right].first > heap[largest].first) {
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
  
    void insert(int key, int value) {
        heap.push_back(std::make_pair(key, value));
        int i = heap.size() - 1;
        while (i > 0 && heap[i].first > heap[(i - 1) / 2].first) {
            troca(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    std::pair<int, int> removeMax() {
        if (heap.empty()) {
            return std::make_pair(-1, -1);
        }
        std::pair<int, int> max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        MaxHeapify(0);
        return max;
    }

    bool IsEmpty() {
        return heap.empty();
    }

    void showHeap() {
        for (std::pair<int, int> p : heap) {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << "\n";
    }
};


class Stack {

    int key{0};
    MaxHeap stack;

    public:

    Stack() : key(0) {}

    void push(int n) {
        stack.insert(key++, n);
    }

    int pop() {

        if (stack.IsEmpty()) {
            std::cout << "A pilha está vazia!" <<  std::endl;
            return -1; 
        }
         std::pair<int, int> top = stack.removeMax();
        key--;
        return top.second;

    }

      bool isEmpty() {
        return stack.IsEmpty();
    }

    void showPilha() {
        stack.showHeap();
    }

};

int main() {

    Stack pilha;

    pilha.push(10);
    pilha.push(20);
    pilha.push(30);
    pilha.push(5);
    pilha.push(25);

    pilha.pop();
    // pilha.pop();
    // pilha.pop();

    pilha.showPilha();

}
