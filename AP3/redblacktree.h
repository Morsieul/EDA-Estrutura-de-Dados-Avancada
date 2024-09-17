#pragma once

#ifndef REDBLACK_H
#define REDBLACK_H

enum Color { RED, BLACK };
/*
Como já explicado nos comentários da árvore AVL aqui seguiu-se a mesma problemática e foi decidido adotar a letra S para o template.
*/
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
/*
O NIL esta sendo impelementado como um ponteiro de um nó especial, através da inicialização do RBNode, seus valores para pai e filhos
são inicializados com nullptr. Como o NIL precisa ser um nó preto, alocamos essa cor posteriormente.
Como na árvore AVL, possui-se métodos públicos nesta implementação que serão usados para acessar e modificar a classe DicionarioRBT, os métodos privados
servem como funções auxiliares que farão o trabalho duro de computar o que for necessário.
*/
template<typename S>
class DicionarioRBT {
    RBNode<S>* root;
    RBNode<S>* NIL;

    //NIL->color = BLACK

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

    /*
    Equivalente a um swap(), troca os elementos de um no x por um no y, a partir de seus ponteiros.
    */
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

    /*
     
    */
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

    /*
    A  função add() funciona como auxiliar do método público Insert(K). Aqui, cria-se um novo nó com o valor x passado.
    Como não sabemos se ele terá filhos ou não, seus valores serão inicializados com NIL. O pai do novo nó x também 
    se inicializa em NIL.

    Para determinarmos a posição onde o novo nó deve ser posicionado, precisamos percorrer iterativamente a árvore a partir do nosso nó de entrada n.
    Percorre-se a árvore da maneira esperada para uma BST. Atualiza-se o valor de parent e current até achar a melhor posição para encaixar o novo
    nó x, caso já exista um nó com os mesmos dados(caso de palavra repetida no contexto do dicionário) irá incrementar o parâmetrp de contagem.
    Após isso é feito ajustes como colocar a cor do novo nó, pintando-o de preto se seu pai for NIL. 

    Para manter a propriedade da altura negra que garanta a busca em termos de Log(n), é chamada a função fixInsert(), responsável por refazer o rebalanceamento e
    recolorir nós se necessário, partindo do novo nó adicionado e sua posição na árvore.
    */
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

    /*
    A função remove() auxilia a Remove() que é pública.
    Inicialmente, compara-se os valores com k enquanto n for diferente de NIL, achando o valor, este é colocado ao lado adequado de n.
    x, y e z são variáveis auxiliares responsáveis por preservar os valores dos nós e suas posições para as operações seguintes ao longo 
    da árvore. 

    Se o final de tudo, y tiver sido originalmente preto, significa que é preciso rebalancear e recolorir a árvore rubro-negra para manter
    a altura e as devidas propriedades.
    */

    void remove(RBNode<S>* n, S& k) {
    RBNode<S>* z = NIL;
    RBNode<S>* x, y;
    while (n != NIL) {
      if (n->data == k) {
        z = n;
      }

      if (n->data <= k) {
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
            
        if (y_original_color == BLACK) fixDelete(x);
    
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

    /*
    RBNode<S>* Head() {
    return root;
    }
    */
    
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
