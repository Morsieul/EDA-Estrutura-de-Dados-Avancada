#include "redblacktree.h"

// Construtor da árvore
template<typename S>
DicionarioRBT<S>::DicionarioRBT() : root(nullptr) {}

// Destrutor da árvore
template<typename S>
DicionarioRBT<S>::~DicionarioRBT() {
    // Aqui você pode adicionar a lógica para desalocar os nós
}

// Função para buscar um nó na árvore
template<typename S>
RBNode<S>* DicionarioRBT<S>::buscar(RBNode<S>* n, S& x) {
    if (n == nullptr || n->data == x) {
        return n;
    }
    if (x < n->data) {
        return buscar(n->left, x);
    }
    return buscar(n->right, x);
}

// Função para corrigir o balanceamento após remoção
template<typename S>
void DicionarioRBT<S>::fixDelete(RBNode<S>* n) {
    // Lógica de correção após remoção (rebalanceamento)
}

// Função para corrigir o balanceamento após inserção
template<typename S>
void DicionarioRBT<S>::fixInsert(RBNode<S>* n) {
    // Lógica de correção após inserção (rebalanceamento)
}

// Rotação simples à direita
template<typename S>
void DicionarioRBT<S>::RightRotate(RBNode<S>* n) {
    RBNode<S>* temp = n->left;
    n->left = temp->right;
    if (temp->right != nullptr) {
        temp->right->parent = n;
    }
    temp->parent = n->parent;
    if (n->parent == nullptr) {
        root = temp;
    } else if (n == n->parent->right) {
        n->parent->right = temp;
    } else {
        n->parent->left = temp;
    }
    temp->right = n;
    n->parent = temp;
}

// Rotação simples à esquerda
template<typename S>
void DicionarioRBT<S>::LeftRotate(RBNode<S>* n) {
    RBNode<S>* temp = n->right;
    n->right = temp->left;
    if (temp->left != nullptr) {
        temp->left->parent = n;
    }
    temp->parent = n->parent;
    if (n->parent == nullptr) {
        root = temp;
    } else if (n == n->parent->left) {
        n->parent->left = temp;
    } else {
        n->parent->right = temp;
    }
    temp->left = n;
    n->parent = temp;
}

// Rotação dupla à direita
template<typename S>
void DicionarioRBT<S>::DoubleRightRotate(RBNode<S>* n) {
    LeftRotate(n->left);
    RightRotate(n);
}

// Rotação dupla à esquerda
template<typename S>
void DicionarioRBT<S>::DoubleLeftRotate(RBNode<S>* n) {
    RightRotate(n->right);
    LeftRotate(n);
}

// Função para adicionar um nó
template<typename S>
void DicionarioRBT<S>::add(RBNode<S>* n, S& x) {
    if (root == nullptr) {
        root = new RBNode<S>{x};  // raiz é sempre preta
        root->color = BLACK;
        return;
    }
    // Inserção comum
}

// Função para percorrer a árvore em ordem
template<typename S>
void DicionarioRBT<S>::inorder(RBNode<S>* r) {
    if (r == nullptr) return;
    inorder(r->left);
    std::cout << r->data << " ";
    inorder(r->right);
}

// Interface pública para busca
template<typename S>
void DicionarioRBT<S>::Search(S& x) {
    RBNode<S>* result = buscar(root, x);
    if (result != nullptr) {
        std::cout << "Encontrado: " << result->data << std::endl;
    } else {
        std::cout << "Não encontrado." << std::endl;
    }
}

// Interface pública para inserção
template<typename S>
void DicionarioRBT<S>::Insert(S& x) {
    add(root, x);
    // Ajustar a árvore para manter as propriedades da RBT
}

// Interface pública para remoção
template<typename S>
void DicionarioRBT<S>::Remove(S& x) {
    // Remover nó e chamar fixDelete para rebalancear
}

// Função pública para mostrar a árvore em ordem
template<typename S>
void DicionarioRBT<S>::Show() {
    inorder(root);
    std::cout << std::endl;
}
