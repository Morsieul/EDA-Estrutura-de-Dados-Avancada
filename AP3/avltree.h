 #pragma once

#ifndef SET_H
#define SET_H
#include "node.h"

class DicionarioAVL {
    
    node* root;

    // int height(node* p);
    // int balance(node* p);

    node * singleRightRotation ( node * p ) ;
    node * doubleRightRotation(node* p);
    node * singleLeftRotation ( node * p ) ;
    node * doubleLeftRotation(node * p);
    node * add ( node *p , const std::string& key ) ;
    node * remove(node * p, const std::string& key);
    node * newNode(const std::string& x);
    node * fixup_node ( node *p , const std::string& key );
    node * search(node * p, const std::string& x);
    node * successor(node * p, const std::string& x);
    node * predecessor(node * p, const std::string& x);

public:

    DicionarioAVL() : root(nullptr) {}

    ~DicionarioAVL() {
        Clear();
    }

    node * Head();
    
    void Constructor();

    void Destructor();

    void Insert(const std::string& x);

    void Erase(const std::string& x);

    bool Contains(const std::string& x);

    void Clear();

    void Minimum();

    void Maximum();

    void Successor(const std::string& x);

    void Predecessor( const std::string& x);

    void Empty();

    int Size();

    void Show();
};

#endif