#pragma once

#ifdef REDBLACK_H
#define REDBLACK_H

#include "note.h"

temmplate<typename S>

enum Color { RED, BLACK };

class RBnode : public Node {
    Color color;
    RBnode* parent;

    public:
    RBNode(T val) : Node<T>(val), color(RED), parent(nullptr) {}
};


class DicionarioRBT {
    RBNode* root;


    RBNode* buscar(RBNode* n, S& x){}

    void fixDelete(RBNode* n) {}

    void fixInsert(RBNode* n) {}

    void RightRotate(RBNode* n) {}

    void LeftRotate(RBNode* n) {}

    void DoubleRightRotate(RBNode* n) {}

    void DoubleLeftRotate(RBNode* n) {}

    void add(RBNode* n, S& x) {}

    void inorder(RBNode* r) {}

    public:

    DicionarioRBT() {}

    ~DicionarioRBT() {}
    
    void Search(S& x) {}

    void Insert(S& x) {}

    void Remove(S& x) {}

    void Show() {}

};


#endif