#include "avltree.h"
#include<iostream>

int height(node *N)  
{  
    if (N == nullptr)  
        return 0;  
    return N->height;  
}  

int getBalance(node *N)  
{  
    if (N == nullptr)  
        return 0;  
    return height(N->left) - height(N->right);  
}  

bool isEmpty(node * root) {
	return root == nullptr;
}

void makeEmpty(node*& p) {
	if (p != nullptr) {
		// std::cout << "Cleaning " << p->data << std::endl; 
        makeEmpty(p->left);
        makeEmpty(p->right);
        delete p;
        p = nullptr;
    }
}

int size(node * p) {
	if (p == nullptr) return 0;
    return 1 + size(p->left) + size(p->right);
}

node * DicionarioAVL::singleRightRotation(node* p) {
	if (p == nullptr || p->left == nullptr) return p;
	node * u = p->left;
	node * T2 = u->right;

	// std::cout << "SingRightRotation on " << p->data << std::endl;

	u->right = p;
	p->left = T2;

	p->height = std::max( height(p->left), height(p->right)) + 1;
	u->height = std::max(height(u->left), height(u->right) ) + 1;

	return u;

}

node * DicionarioAVL::doubleRightRotation(node* p) {
	    p->left = singleLeftRotation(p->left);
        return singleRightRotation(p);

}

node * DicionarioAVL::singleLeftRotation(node * p) {
	node* u = p->right;
    node * T2 = u->left;

	// std::cout << "SingLEFTRotation on " << p->data << std::endl;
    u->left = p;
	p ->right = T2;
        p->height = std::max(height(p->left), height(p->right))+1;
        u->height = std::max(height(u->left), height(u->right))+1 ;
        return u;
}

node * DicionarioAVL::doubleLeftRotation(node * p) {
	    p->right = singleRightRotation(p->right);
        return singleLeftRotation(p);
}

node * DicionarioAVL::newNode(const std::string& x) {

	node * no = new node();
	no->data = x;
	no->left = nullptr;
	no->right = nullptr;
	no->height = 1;

	return no;

}

node* findMin(node* t){
        if(t == nullptr)
            return nullptr;
        else if(t->left == nullptr)
            return t;
        else
            return findMin(t->left);
}

node* findMax(node* t) {
        if(t == nullptr)
            return nullptr;
        else if(t->right == nullptr)
            return t;
        else
            return findMax(t->right);
}


node* DicionarioAVL::add(node* p, const std::string& x) {

	if (p == nullptr) {
        std::cout << "Adding new node: " << x << std::endl;
        return newNode(x);
    }

    if (x < p->data) {
        // std::cout << "Going left from " << p->data << " to add " << x << std::endl;
        p->left = add(p->left, x);
    } else if (x > p->data) {
        // std::cout << "Going right from " << p->data << " to add " << x << std::endl;
        p->right = add(p->right, x);
    } else {
        // p->contagem ++;
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

node * DicionarioAVL::remove(node * p, const std::string& x) {
	node * temp = nullptr;

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

node * DicionarioAVL::search(node * p, const std::string& x) {

	if( p == nullptr || p->data == x) return p;

	else if( p -> data > x) return search(p->left, x);
	else return search(p->right, x);
	
}

bool contains(node * root, const std::string& x) {
    node* current = root;
    while (current != nullptr) {
        if (x == current->data) return true;
        if (x < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

node * DicionarioAVL::successor(node * p, const std::string& x) {
	node * no = search(p, x);
    if (no == nullptr) {
        throw std::runtime_error("Node not found");
    }

    if (no->right != nullptr) {
        return findMin(no->right);
    }

    node * succ = nullptr;
    node* ancestor = root;
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

node * DicionarioAVL::predecessor(node * p, const std::string& x) {
	 node* no = search(p, x);
        if (no == nullptr) {
            throw std::runtime_error("Node not found");
        }

        if (no->left != nullptr) {
            return findMax(no->left);
        }

        node * pred = nullptr;
        node * ancestor = root;
        while (ancestor != no) {
            if (no->data > ancestor-> data) {
                pred = ancestor;
                ancestor = ancestor->right;
            } else {
                ancestor = ancestor->left;
            }
        }

        if (pred == nullptr) {
            throw std::runtime_error("Predecessor does not exist");
        }

        return pred;
}

void inorder(node * p) {
	
   if (p != nullptr) {
        inorder(p->left);
        // std::cout << "Visiting node with data: " << p->data << std::endl;
        std::cout << p->data << std::endl;
        inorder(p->right);
    } else return;
}

// Funções de chamada pública

node* DicionarioAVL::Head() {
	return this->root;
}

void DicionarioAVL::Insert(const std::string& x) {
	root = add(root, x);
	
}

void DicionarioAVL::Erase(const std::string& x) {
	remove(root, x);
}

bool DicionarioAVL::Contains(const std::string& x) {
    return contains(root, x);
}

void DicionarioAVL::Clear() {
	makeEmpty(root);
}

void DicionarioAVL::Minimum() {
	node* t = findMin(root);
	std::cout << t->data << std::endl;
}

void DicionarioAVL::Maximum() {
	node* t = findMax(root);
	std::cout << t->data << std::endl;
}

void DicionarioAVL::Successor(const std::string& x) {
	try {
			node * p = successor(root, x);
			std::cout << p->data << std::endl;
	} catch (std::runtime_error e) {
			std::cout << e.what() << std::endl;
	}
}

void DicionarioAVL::Predecessor(const std::string& x) {
	try {
		node * p = predecessor(root, x);
		std::cout << p->data << std::endl;
	} catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}
}

void DicionarioAVL::Empty() {
	isEmpty(root) ? std::cout << "Sim\n" << std::endl : std::cout << "Nao\n" << std::endl;
}
int DicionarioAVL::Size() {
	return size(root);
}
void DicionarioAVL::Show() {
	inorder(root);
	std::cout << std::endl;
}