#pragma once

#ifndef HASHTABLE_H
#define HASHTABLE_H

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

    // Vetor de listas (cada lista representa um "bucket")
    std::vector<std::list<HashNode>> table;
    int capacity;
    int size;

    // Conjunto ordenado para manter as chaves em ordem alfabética
    std::set<K> orderedKeys;

    // Função hash para calcular o índice do bucket
    int hashFunction(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

public:
    // Construtor que inicializa a tabela com um determinado número de buckets
    HashTableExterior(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    // Destrutor
    ~HashTableExterior() {
        clear();
    }

    // Inserir um par chave-valor na tabela
    void add(const K& key, const V& value) {
        int index = hashFunction(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value; // Atualiza o valor se a chave já existir
                return;
            }
        }
        table[index].emplace_back(key, value); // Insere um novo par
        orderedKeys.insert(key);
        size++;
    }

    // Função Insert que apenas insere a chave e coloca um valor padrão
    void Insert(const K& key) {
        V value;
        
        // Se a chave já existir, incrementa o valor associado
        if (search(key, value)) {
            add(key, value + 1);  // Incrementa o valor
        } else {
            add(key, 1);  // Se não existir, insere com valor inicial 1
        }
    }   

    // Remover um par pela chave
    void remove(const K& key) {
        int index = hashFunction(key);
        auto& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                orderedKeys.erase(key); // Remove a chave do conjunto ordenado
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
        orderedKeys.clear();
        size = 0;
    }

    // Mostrar o conteúdo da hash table em ordem alfabética das chaves
    void Show() const {
        for (const auto& key : orderedKeys) {
            V value;
            if (search(key, value)) {
                std::cout << key << ": " << "[" <<  value << "]" << std::endl;
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
