#pragma once

#ifndef REDBLACK_H
#define REDBLACK_H

enum Color { RED, BLACK };

template<typename S>
struct RBNode {
    public:
    Color color;
    RBNode* parent;
    S data;
    int contagem = 1;
    int height;
    RBNode* left{nullptr};
    RBNode* right{nullptr};

    
    RBNode(S val) : data(val), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

template<typename S>
class DicionarioRBT {
    RBNode<S>* root;


    RBNode<S>* buscar(RBNode<S>* n, S& x){}

    void fixDelete(RBNode<S>* n) {}

    void fixInsert(RBNode<S>* n) {}

    void RightRotate(RBNode<S>* n) {}

    void LeftRotate(RBNode<S>* n) {}

    void DoubleRightRotate(RBNode<S>* n) {}

    void DoubleLeftRotate(RBNode<S>* n) {}

    void add(RBNode<S>* n, S& x) {}

    void inorder(RBNode<S>* r) {}
    
    //Metodos publicos:
    public:

    DicionarioRBT() {}

    ~DicionarioRBT() {}
    
    void Search(S& x) {}

    void Insert(S& x) {}

    void Remove(S& x) {}

    void Show() {}


};

#include "RedBlackTree.tpp"
#endif