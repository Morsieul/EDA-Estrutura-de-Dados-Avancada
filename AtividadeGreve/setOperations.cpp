#include "node.h"
#include "set.h"
#include "set.cpp"
#include "setOperations.h"
#include <iostream>

void UnionHelper(node* root, Set& result) {
    if (root != nullptr) {
        UnionHelper(root->left, result);
        result.Insert(root->data);
        UnionHelper(root->right, result);
    }
}

Set Union(Set& s, Set& t) {
    Set n;
    UnionHelper(s.Head(), n);
    UnionHelper(t.Head(), n);
    return n;
}

void IntersecHelper(node * root, Set& t, Set& n) {
      if (root != nullptr) {
        IntersecHelper(root->left, t, n);
        if (t.Contains(root->data)) {
            n.Insert(root->data);
        }
        IntersecHelper(root->right, t, n);
    }
}

Set Intersec(Set& s, Set& t) {
    Set n;
    IntersecHelper(s.Head(), t, n );
    return n;
}

void DifferenceHelper(node * root, Set& t, Set& result) {
    if (root != nullptr) {
        DifferenceHelper(root->left, t, result);
        if (!t.Contains(root->data)) {
            result.Insert(root->data);
        }
        DifferenceHelper(root->right, t, result);
    }
}

Set Difference(Set& s, Set& t) {
    Set n;
    DifferenceHelper(s.Head(), t, n);
    return n;
}