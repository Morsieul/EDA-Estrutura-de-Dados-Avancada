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

    RBNode<S>* buscar(RBNode<S>* p, S& x) {
        if( p == NIL || p->data == x) return p;

        else if( p -> data > x) return buscar(p->left, x);
        else return buscar(p->right, x);
    }

    void fixDelete(RBNode<S>* x) {
        RBNode<S>* s;
        while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
            s->color = BLACK;
            x->parent->color = RED;
            leftRotate(x->parent);
            s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
            s->color = RED;
            x = x->parent;
            } else {
            if (s->right->color == BLACK) {
                s->left->color = BLACK;
                s->color = RED;
                RightRotate(s);
                s = x->parent->right;
            }

            s->color = x->parent->color;
            x->parent->color = BLACK;
            s->right->color = BLACK;
            LeftRotate(x->parent);
            x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == RED) {
            s->color = BLACK;
            x->parent->color = RED;
            RightRotate(x->parent);
            s = x->parent->left;
            }

            if (s->right->color == BLACK && s->right->color == BLACK) {
            s->color = RED;
            x = x->parent;
            } else {
            if (s->left->color == BLACK) {
                s->right->color = BLACK;
                s->color = RED;
                LeftRotate(s);
                s = x->parent->left;
            }

            s->color = x->parent->color;
            x->parent->color = BLACK;
            s->left->color = BLACK;
            RightRotate(x->parent);
            x = root;
            }
        }
        }
        x->color = BLACK;
    }

    void rbTransplant(RBNode<S>* x, RBNode<S>* y) {
        if (x->parent == NIL) {
        root = y;
        } else if (x == x->parent->left) {
        x->parent->left = y;
        } else {
        x->parent->right = y;
        }
        y->parent = x->parent;
    }

    void fixInsert(RBNode<S>* k) {
        while (k != root && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
               RBNode<S>* u = k->parent->parent->right; // uncle
                if (u->color == RED) {
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        LeftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    RightRotate(k->parent->parent);
                }
            }
            else {
                RBNode<S>* u = k->parent->parent->left; // uncle
                if (u->color == RED) {
                    k->parent->color = BLACK;
                    u->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        RightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    LeftRotate(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void RightRotate(RBNode<S>* x) {
        RBNode<S>* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL)  root = y;
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
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void add(RBNode<S>* n, S& x) {
        RBNode<S>* new_node = new RBNode<S>(x);
        new_node->left = NIL;
        new_node->right = NIL;

        RBNode<S>* parent = NIL;
        RBNode<S>* current = n;

        // BST insert
        while (current != NIL) {
            parent = current;
            if(current->data == new_node->data) {
                current->contagem++;
                return;
            }
            else if (new_node->data < current->data) current = current->left;
            else current = current->right;
        }

        new_node->parent = parent;

        if (parent == NIL) {
            root = new_node;
        }
        else if (new_node->data < parent->data) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        if (new_node->parent == NIL) {
            new_node->color = BLACK;
            return;
        }

        if (new_node->parent->parent == NIL) {
            return;
        }

        fixInsert(new_node);
    }

    void remove(RBNode<S>* n, S& k) {
    RBNode<S>* z = NIL;
    RBNode<S>* x, y;
    while (n != NIL) {
      if (n->data == x) {
        z = n;
      }

      if (n->data <= x) {
        n = n->right;
      } else {
        n = n->left;
      }
    }

    if (z == NIL) {
      std::cout << "Chave inexistente" << std::endl;
      return;
    }

    y = z;
    Color y_original_color = y->color;
    if (z->left == NIL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == NIL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK) {
      fixDelete(x);
    }

    }

    void inorder(RBNode<S>* p) {
        if (p != NIL) {
        inorder(p->left);
        // std::cout << "Visiting node with data: " << p->data << std::endl;
        std::cout << p->data <<  ": [" << p->contagem << "]" << std::endl;
        inorder(p->right);
    } else return;
    }
    
    //Metodos publicos:
    public:

    DicionarioRBT() {
        NIL = new RBNode<S>(S()); 
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    ~DicionarioRBT() {
        deleteTree(root);  
        delete NIL;        
    }

    void deleteTree(RBNode<S>* node) {
        if (node != NIL) {  
            deleteTree(node->left);   
            deleteTree(node->right);  
            //std::cout << "Deletando no " <<  node->data << std::endl;
            delete node;              
        }
    }
    
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