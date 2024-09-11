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
    RBNode<S>* NIL;

    RBNode<S>* buscar(RBNode<S>* n, S& x){}

    void fixDelete(RBNode<S>* n) {}

    void fixInsert(RBNode<S>* n) {}

    void RightRotate(RBNode<S>* x) {
        RBNode<S>* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)  root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void LeftRotate(RBNode<S>* x) {
        RBNode<S>* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void DoubleRightRotate(RBNode<S>* n) {}

    void DoubleLeftRotate(RBNode<S>* n) {}

    void add(RBNode<S>* n, S& x) {}

    void remove(RBNode<S>* n, S& x) {

    }

    void inorder(RBNode<S>* r) {}
    
    //Metodos publicos:
    public:

    DicionarioRBT() {
        NIL = new RBNode<S>*();
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    ~DicionarioRBT() {}
    
    void Search(S& x) {
        buscar(root, x);
    }

    void Insert(S& x) {
        add(root, x);
    }

    void Remove(S& x) {
        remove(root, x);
    }

    void Show() {
        inorder(root);
    }

};

#endif