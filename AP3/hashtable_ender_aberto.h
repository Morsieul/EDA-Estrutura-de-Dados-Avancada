#pragma once

#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <iostream>
#include <vector>
#include <optional>

template<typename K, typename V>
class HashTableAberto {
private:
    // Estrutura para armazenar um par chave-valor, junto com um flag de ocupação
    struct HashNode {
        K key;
        V value;
        bool isDeleted;

        HashNode(const K& k, const V& v) : key(k), value(v), isDeleted(false) {}
    };

    // Vetor de ponteiros para HashNodes
    std::vector<std::optional<HashNode>> table;
    int capacity;
    int size;

    // Função hash primária
    int hashFunction(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

    // Rehashing - aumenta o tamanho da tabela e reinserir elementos
    void rehash() {
        int oldCapacity = capacity;
        capacity *= 2; // Dobra a capacidade
        std::vector<std::optional<HashNode>> oldTable = table;

        // Reinicializa a tabela com o dobro do tamanho
        table.clear();
        table.resize(capacity);
        size = 0;

        // Reinsere os elementos antigos
        for (int i = 0; i < oldCapacity; ++i) {
            if (oldTable[i] && !oldTable[i]->isDeleted) {
                insert(oldTable[i]->key, oldTable[i]->value);
            }
        }
    }

public:
    // Construtor para inicializar a tabela com uma capacidade inicial
    HashTableAberto(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    // Inserir um par chave-valor na tabela
    void insert(const K& key, const V& value) {
        if (size >= capacity / 2) {
            rehash(); // Rehash se a tabela estiver pela metade cheia
        }

        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        // Probing linear para encontrar um espaço vazio ou atualizar a chave
        while (table[index] && !table[index]->isDeleted && table[index]->key != key) {
            index = (originalIndex + ++i) % capacity;
        }

        // Se for uma nova inserção, aumenta o tamanho
        if (!table[index] || table[index]->isDeleted) {
            size++;
        }

        // Insere ou atualiza o valor
        table[index] = HashNode(key, value);
    }

    // Remover um par pela chave
    void remove(const K& key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        // Probing linear para encontrar o elemento
        while (table[index] && (table[index]->key != key || table[index]->isDeleted)) {
            index = (originalIndex + ++i) % capacity;
        }

        if (table[index] && !table[index]->isDeleted) {
            table[index]->isDeleted = true;
            size--;
        }
    }

    // Buscar um valor pela chave
    bool search(const K& key, V& value) const {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;

        // Probing linear para encontrar o elemento
        while (table[index] && (table[index]->key != key || table[index]->isDeleted)) {
            index = (originalIndex + ++i) % capacity;
        }

        if (table[index] && !table[index]->isDeleted) {
            value = table[index]->value;
            return true;
        }

        return false;
    }

    // Limpar a tabela hash
    void clear() {
        table.clear();
        table.resize(capacity);
        size = 0;
    }

    // Mostrar o conteúdo da hash table
    void show() const {
        for (int i = 0; i < capacity; ++i) {
            if (table[i] && !table[i]->isDeleted) {
                std::cout << "Bucket " << i << ": [" << table[i]->key << ": " << table[i]->value << "]" << std::endl;
            } else {
                std::cout << "Bucket " << i << ": [vazio]" << std::endl;
            }
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
