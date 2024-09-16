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

    
    std::vector<std::list<HashNode>> table;
    int capacity;
    int size;

    // Conjunto ordenado para manter as chaves em ordem alfabética
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

public:

    HashTableExterior(int cap = 100) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    // Destrutor
    ~HashTableExterior() {
        clear();
    }

    // Inserir um par chave-valor na tabela
    void add(const K& key, const V& value) {
        int index = FuncaoHash(key);
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
        if (search(key, value)) add(key, value + 1);  // Incrementa o valor
        else add(key, 1);  // Se não existir, insere com valor inicial 1
        
    }   

    // Remover um par pela chave
    void remove(const K& key) {
        int index = FuncaoHash(key);
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
        int index = FuncaoHash(key);
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
