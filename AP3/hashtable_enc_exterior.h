#pragma once

#ifndef HASHTABLE_H_EX
#define HASHTABLE_H_EX

#include <iostream>
#include <list>
#include <vector>
#include <set>

template <typename K, typename V>
class HashTableExterior {
private:
    struct HashNode {
        K key;
        V value;
        HashNode(K k, V v) : key(k), value(v) {}
    };

    std::vector<std::list<HashNode>> table;
    int capacity;
    int size;
    float loadFactorThreshold; // Fator de carga máximo

    std::set<K> orderedKeys;

    int FuncaoHash(const K& key) const {
        int hash = 7;
        int prime = 31;
        for (auto c : key) {
            hash = (hash * prime + c) % capacity;
        }
        return hash;
    }

    // Função para redimensionar a tabela

    void resize() {
        int newCapacity = capacity * 2; // Dobra a capacidade
        std::vector<std::list<HashNode>> newTable(newCapacity); // Cria nova tabela

        // Reinsere todos os elementos na nova tabela com a nova capacidade
        for (const auto& chain : table) {
            for (const auto& node : chain) {
                int newIndex = FuncaoHash(node.key) % newCapacity; // Recalcula o índice
                newTable[newIndex].emplace_back(node.key, node.value); // Insere na nova tabela
            }
        }

        // Substitui a tabela antiga pela nova e atualiza a capacidade
        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    HashTableExterior(int cap = 500) : capacity(cap), size(0), loadFactorThreshold(0.75f) {
        table.resize(capacity);
    }

    ~HashTableExterior() {
        clear();
    }

    void add(const K& key, const V& value) {
        if (static_cast<float>(size) / capacity > loadFactorThreshold) {
            resize(); // Redimensiona se o fator de carga for excedido
        }

        int index = FuncaoHash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }

        table[index].emplace_back(key, value);
        orderedKeys.insert(key);
        size++;
    }

    void Insert(const K& key) {
        V value;
        if (search(key, value)) add(key, value + 1);
        else add(key, 1);
    }

    bool search(const K& key, V& value) const {
        int index = FuncaoHash(key);
        for (const auto& node : table[index]) {
            if (node.key == key) {
                value = node.value;
                return true;
            }
        }
        return false;
    }

    void remove(const K& key) {
        int index = FuncaoHash(key);
        auto& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                orderedKeys.erase(key);
                size--;
                return;
            }
        }
    }

    void clear() {
        for (auto& chain : table) {
            chain.clear();
        }
        orderedKeys.clear();
        size = 0;
    }

    void Show() const {
        for (const auto& key : orderedKeys) {
            V value;
            if (search(key, value)) {
                std::cout << key << ": " << "[" << value << "]" << std::endl;
            }
        }
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }
};

#endif
