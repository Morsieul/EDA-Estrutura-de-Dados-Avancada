 #pragma once

#ifndef SET_H
#define SET_H

template<typename T>
struct AVLNode {
    public:
    T data;
    int contagem = 1;
    int height;
    AVLNode<T>* left{nullptr};
    AVLNode<T>* right{nullptr};

};  


template<typename T>
class DicionarioAVL {
    
    AVLNode<T>* root;
   
    int height(AVLNode<T>* N){  
    if (N == nullptr) return 0;  
    return N->height;  
    }  

    int getBalance(AVLNode<T>* N) {  
        if (N == nullptr) return 0;  
        return height(N->left) - height(N->right);  
    }  

    bool isEmpty(AVLNode<T>* root) {
        return root == nullptr;
    }

    void makeEmpty(AVLNode<T>*& p) {
        if (p != nullptr) {
            // std::cout << "Cleaning " << p->data << std::endl; 
            makeEmpty(p->left);
            makeEmpty(p->right);
            delete p;
            p = nullptr;
        }
    }

    int size(AVLNode<T>* p) {
        if (p == nullptr) return 0;
        return 1 + size(p->left) + size(p->right);
    }


    bool contains(AVLNode<T>* root, const T& x) {
        AVLNode<T>* current = root;
        while (current != nullptr) {
            if (x == current->data) return true;
            if (x < current->data) current = current->left;
            else current = current->right;
        }
        return false;
    }

    AVLNode<T>* newNode(const T& x) {
        AVLNode<T>* no = new AVLNode<T>();
        no->data = x;
        no->left = nullptr;
        no->right = nullptr;
        no->height = 1;

        return no;
    }

    AVLNode<T>* findMin(AVLNode<T>* t){
        if(t == nullptr) return nullptr;
        else if(t->left == nullptr) return t;
        else return findMin(t->left);
    }

    AVLNode<T>* findMax(AVLNode<T>* t) {
        if(t == nullptr) return nullptr;
        else if(t->right == nullptr) return t;
        else return findMax(t->right);
    }

    AVLNode<T>* singleRightRotation ( AVLNode<T>* p ) {
        if (p == nullptr || p->left == nullptr) return p;
        AVLNode<T>* u = p->left;
        AVLNode<T>* T2 = u->right;

        // std::cout << "SingRightRotation on " << p->data << std::endl;

        u->right = p;
        p->left = T2;

        p->height = std::max( height(p->left), height(p->right)) + 1;
        u->height = std::max(height(u->left), height(u->right) ) + 1;

        return u;
    }

    AVLNode<T>* doubleRightRotation(AVLNode<T>* p){
        p->left = singleLeftRotation(p->left);
        return singleRightRotation(p);
    }

    AVLNode<T>* singleLeftRotation ( AVLNode<T>* p ) {
        AVLNode<T>* u = p->right;
        AVLNode<T>* T2 = u->left;

        // std::cout << "SingLEFTRotation on " << p->data << std::endl;
        u->left = p;
        p ->right = T2;
        p->height = std::max(height(p->left), height(p->right))+1;
        u->height = std::max(height(u->left), height(u->right))+1 ;
        return u;
    }

    AVLNode<T>* doubleLeftRotation(AVLNode<T>* p) {
        p->right = singleRightRotation(p->right);
        return singleLeftRotation(p);
    }

    AVLNode<T>* add ( AVLNode<T>* p , const T& x ) {
        if (p == nullptr) return newNode(x);
        
        if (x < p->data) {
            // std::cout << "Going left from " << p->data << " to add " << x << std::endl;
            p->left = add(p->left, x);
        } else if (x > p->data) {
            // std::cout << "Going right from " << p->data << " to add " << x << std::endl;
            p->right = add(p->right, x);
        } else {
            p->contagem ++;
            return p;
        }

        p->height = std::max(height(p->left), height(p->right)) + 1;

        int balance = getBalance(p);

        if(balance > 1 && p->left != nullptr && x < p->left->data) return (singleRightRotation(p));

        if(balance < -1 && p->right != nullptr && x > p->right->data) return (singleLeftRotation(p));

        if(balance > 1 && p->left != nullptr && x > p->left->data) return (doubleRightRotation(p));

        if(balance < -1 && p->right != nullptr && x < p->right->data) return doubleLeftRotation(p);

        return p;
    }

    AVLNode<T>* remove(AVLNode<T>* p, const T& x) {
        AVLNode<T>* temp = nullptr;

        if(p == nullptr) return nullptr;

        else if( x < p->data) p->left = remove( p->left, x);
        else if( x > p->data) p->right = remove(p->right, x);

        // Elemento encontrado com 2 criancas

        else if(p->left && p->right) {
            temp = findMin(p->right);
            p->data = temp->data;
            p->right = remove( p->right, p->data);
        }

        else {
            temp = p;
            if(p->left == nullptr) p = p->right;
            else if(p->right == nullptr) p = p->left;
            delete temp;
        }

        if(p == nullptr) return p;

        p->height = std::max(height(p->left), height(p->right)) + 1;

        if(height(p->left) - height(p->right) == 2) {
            if(height(p->left->left) - height(p->left->right) == 1) return singleLeftRotation(p);
            else return doubleLeftRotation(p);
        }

        else if(height(p->right) - height(p->left) == 2) {
            if(height(p->right->right) - height(p->right->left) == 1) return singleRightRotation(p);
            else return doubleRightRotation(p);
        }

        return p;
    }

    AVLNode<T>* search(AVLNode<T>* p, const T& x) {
        if( p == nullptr || p->data == x) return p;
        else if( p -> data > x) return search(p->left, x);
        else return search(p->right, x);
    }

    AVLNode<T>* successor(AVLNode<T>* p, const T& x) {
        AVLNode<T>* no = search(p, x);
        if (no == nullptr) {
            throw std::runtime_error("Node not found");
        }

        if (no->right != nullptr) {
            return findMin(no->right);
        }

        AVLNode<T>* succ = nullptr;
        AVLNode<T>* ancestor = root;
        while (ancestor != no) {
            if (no->data < ancestor->data) {
                succ = ancestor;
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }

        if (succ == nullptr) {
            throw std::runtime_error("Successor does not exist");
        }

        return succ;
    }

    AVLNode<T>* predecessor(AVLNode<T>* p, const T& x) {
        AVLNode<T>* no = search(p, x);
        if (no == nullptr) throw std::runtime_error("Node not found");
        if (no->left != nullptr)  return findMax(no->left);
        
        AVLNode<T>* pred = nullptr;
        AVLNode<T>* ancestor = root;
        while (ancestor != no) {
            if (no->data > ancestor-> data) {
                pred = ancestor;
                ancestor = ancestor->right;
            } else {
                ancestor = ancestor->left;
            }
        }

        if (pred == nullptr)  throw std::runtime_error("Predecessor does not exist");

        return pred;
    }

    void inorder(AVLNode<T>* p) {
	    if (p != nullptr) {
            inorder(p->left);
            // std::cout << "Visiting node with data: " << p->data << std::endl;
            std::cout << p->data  << ": " << "[" << p->contagem << "]" << std::endl;
            inorder(p->right);
        } else return;
    }

public:

    DicionarioAVL() : root(nullptr) {}

    ~DicionarioAVL() {
        Clear();
    }

    AVLNode<T>* Head() {
        return this->root;
    }

    void Insert(const T& x) {
        root = add(root, x);
    }

    void Erase(const T& x) {
        remove(root, x);
    }

    bool Contains(const T& x) {
        return contains(root, x);
    }

    void Clear() {
        makeEmpty(root);
    }

    void Minimum() {
        AVLNode<T>* t = findMin(root);
	    std::cout << t->data << std::endl;
    }

    void Maximum() {
        AVLNode<T>* t = findMax(root);
	    std::cout << t->data << std::endl;
    }

    void Successor(const T& x) {
        try {
			AVLNode<T>* p = successor(root, x);
			std::cout << p->data << std::endl;
	    } catch (std::runtime_error e) {
			std::cout << e.what() << std::endl;
	    }
    }

    void Predecessor( const T& x) {
        try {
		AVLNode<T>* p = predecessor(root, x);
		std::cout << p->data << std::endl;
        } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
        }
    }

    void Empty() {
        isEmpty(root) ? std::cout << "Sim\n" << std::endl : std::cout << "Nao\n" << std::endl;
    }

    int Size() {
        return size(root);
    }

    void Show() {
        inorder(root);
	    std::cout << std::endl;
    }
};

#endif