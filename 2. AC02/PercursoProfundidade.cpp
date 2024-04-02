#include<iostream>
#include<vector>

struct No {
    int data;
    No* left;
    No* right;
};

No* inserir(No* root, int data) {
    if (root == NULL) {
        No* novo = new No();
        novo->data = data;
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }

    if (data < root->data) {
        root->left = inserir(root->left, data);
    } else {
        root->right = inserir(root->right, data);
    }

    return root;
}

void preorder(No* root) {
    if (root == NULL)
        return;

    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);

}

void inorder(No* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

void postorder(No* root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << " ";
}

int main() {

    int nCasos;
    std::vector<No*> arvores;

    std::cin >> nCasos;
    
    for (int caso = 0; caso < nCasos; caso++) {
        int tamArvore;
        No* no_raiz = NULL;
        std::cin >> tamArvore;
        int num;
            for(int i = 0; i < tamArvore; i++) {
                std::cin >> num;
                arvores.push_back(inserir(no_raiz, num));
            }
    }

     for (int i = 0; i < arvores.size(); i++) {
            std::cout << "Caso " << i+1 << ":" << std::endl;
            std::cout << "Pre.: ";
            preorder(arvores[i]);
            std::cout << std::endl;
            std::cout << "In..: ";
            inorder(arvores[i]);
            std::cout << std::endl;
            std::cout << "Post: ";
            postorder(arvores[i]);
            std::cout << std::endl;
        }

    return 0;
}