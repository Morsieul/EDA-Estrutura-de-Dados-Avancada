 #pragma once

#ifndef SET_H
#define SET_H
#include "node.h"

class Set {
    
    node* root;

    // int height(node* p);
    // int balance(node* p);

    node * singleRightRotation ( node * p ) ;
    node * doubleRightRotation(node* p);
    node * singleLeftRotation ( node * p ) ;
    node * doubleLeftRotation(node * p);
    node * add ( node *p , int key ) ;
    node * remove(node * p, int key);
    node * newNode(int x);
    node * fixup_node ( node *p , int key );
    node *  search(node * p, int x);
    node * successor(node * p, int x);
    node * predecessor(node * p, int x);

public:

    Set() : root(nullptr) {}

    ~Set() {
        Clear();
    }

    node * Head();
    
    void Constructor();

    void Destructor();

    void Insert(int x);

    void Erase(int x);

    bool Contains(int x);

    void Clear();

    void Minimum();

    void Maximum();

    void Successor(int x);

    void Predecessor(int x);

    void Empty();

    int Size();

    void Show();
};

#endif