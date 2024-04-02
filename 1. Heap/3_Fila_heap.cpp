#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void troca(pair<int, int>& a, pair<int, int>& b) {
    pair<int, int> temp = a;
    a = b;
    b = temp;
}

class MaxHeap {
private: 
    vector<pair<int, int>> heap;

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
        heap.push_back(make_pair(key, value));
        int i = heap.size() - 1;
        while (i > 0 && heap[i].first > heap[(i - 1) / 2].first) {
            troca(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    pair<int, int> removeMax() {
        if (heap.empty()) {
            return make_pair(-1, -1);
        }
        pair<int, int> max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        MaxHeapify(0);
        return max;
    }

    bool IsEmpty() {
        return heap.empty();
    }

    void showHeap() {
        for (pair<int, int> p : heap) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << "\n";
    }
};

class FilaHeap {
private:
    MaxHeap maxHeap;
    int chaveAtual;

public:
    FilaHeap() : chaveAtual(0) {}

    void enqueue(int valor) {
        maxHeap.insert(chaveAtual--, valor); // Inverte a chave para garantir a ordem correta de saída
    }

    int dequeue() {
        if (maxHeap.IsEmpty()) {
            cout << "A fila está vazia!" << endl;
            return -1; // Retorna um valor inválido
        }
        pair<int, int> front = maxHeap.removeMax();
        return front.second; // Retorna o valor associado à chave
    }

    bool isEmpty() {
        return maxHeap.IsEmpty();
    }
};

int main() {
    FilaHeap fila;

    // Adicionando elementos à fila
    fila.enqueue(32);
    fila.enqueue(1);
    fila.enqueue(66);

    // Removendo e exibindo os elementos da fila
    while (!fila.isEmpty()) {
        cout << "Elemento removido: " << fila.dequeue() << endl;
    }

    return 0;
}
