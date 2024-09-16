#pragma once

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>

// HashTable por encadeamento exterior com templates
template <typename K, typename V>
class HashTable {
private:
    // Par chave-valor armazenado nas listas
    struct HashNode {
        K key;
        V value;

        HashNode(K k, V v) : key(k), value(v) {}
    };

    // Vetor de listas (cada lista representa um "bucket")
    std::vector<std::list<HashNode>> table;
    int capacity;
    int size;

    // Função hash para calcular o índice do bucket
    int hashFunction(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

public:
    // Construtor que inicializa a tabela com um determinado número de buckets
    HashTable(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    // Destrutor
    ~HashTable() {
        clear();
    }

    // Inserir um par chave-valor na tabela
    void insert(const K& key, const V& value) {
        int index = hashFunction(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value; // Atualiza o valor se a chave já existir
                return;
            }
        }
        table[index].emplace_back(key, value); // Insere um novo par
        size++;
    }

    // Remover um par pela chave
    void remove(const K& key) {
        int index = hashFunction(key);
        auto& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                size--;
                return;
            }
        }
    }

    // Buscar um valor pela chave
    bool search(const K& key, V& value) const {
        int index = hashFunction(key);
        for (const auto& node : table[index]) {
            if (node.key == key) {
                value = node.value;
                return true;
            }
        }
        return false;
    }

    // Limpar a tabela hash
    void clear() {
        for (auto& chain : table) {
            chain.clear();
        }
        size = 0;
    }

    // Mostrar o conteúdo da hash table
    void show() const {
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& node : table[i]) {
                std::cout << "[" << node.key << ": " << node.value << "] ";
            }
            std::cout << std::endl;
        }
    }

    // Retornar o tamanho atual da tabela
    int getSize() const {
        return size;
    }

    // Retornar a capacidade da tabela
    int getCapacity() const {
        return capacity;
    }
};

#endif
