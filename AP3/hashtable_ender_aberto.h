#pragma once

#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <iostream>
#include <vector>
#include <optional>
#include <set>

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

    // Conjunto para manter as chaves ordenadas
    std::set<K> orderedKeys;

    // Função hash usando a adiçao de primos
    int FuncaoHash(const K& key) const {
        int hash = 7;
        int prime = 31;  // Um número primo
        for (auto c : key) {
            hash = (hash * prime + c) % capacity;
        }
        return hash;
    }

    // Rehashing - aumenta o tamanho da tabela e reinsere elementos
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
                add(oldTable[i]->key, oldTable[i]->value);
            }
        }
    }

public:
    // Construtor para inicializar a tabela com uma capacidade inicial
    HashTableAberto(int cap = 500) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    // Inserir um par chave-valor na tabela
    void add(const K& key, const V& value) {
        if (size >= capacity / 2)  rehash(); // Rehash se a tabela estiver pela metade cheia

        int index = FuncaoHash(key);
        int originalIndex = index;
        int i = 0;

        // Probing linear para encontrar um espaço vazio ou atualizar a chave
        while (table[index] && !table[index]->isDeleted && table[index]->key != key) {
            index = (originalIndex + ++i) % capacity;
        }

        // Se for uma nova inserção, aumenta o tamanho e adiciona à lista ordenada
        if (!table[index] || table[index]->isDeleted) {
            orderedKeys.insert(key);
            size++;
        }

        // Insere ou atualiza o valor
        table[index] = HashNode(key, value);
    }

    // Função add que incrementa ou insere a chave com valor inicial 1
    void Insert(const K& key) {
        V value;

        // Se a chave já existir, incrementa o valor
        if (search(key, value)) add(key, value + 1);
        else add(key, 1);  // Insere com valor inicial 1
        
    }

    // Remover um par pela chave
    void remove(const K& key) {
        int index = FuncaoHash(key);
        int originalIndex = index;
        int i = 0;

        while (table[index] && (table[index]->key != key || table[index]->isDeleted)) {
            index = (originalIndex + ++i) % capacity;
        }

        if (table[index] && !table[index]->isDeleted) {
            table[index]->isDeleted = true;
            orderedKeys.erase(key); // Remove a chave do conjunto ordenado
            size--;
        }
    }

    // Buscar um valor pela chave
    bool search(const K& key, V& value) const {
        int index = FuncaoHash(key);
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
        orderedKeys.clear();
        size = 0;
    }

    // Mostrar o conteúdo da hash table em ordem alfabética das chaves
    void Show() const {
        for (const auto& key : orderedKeys) {
            V value;
            if (search(key, value))  std::cout  << key << ": " << "[" << value << "]" << std::endl;
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
