#include <iostream>
#include <queue>

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

void percorrerEmOrdem(No* root) {
    if (root == NULL)
        return;

    std::queue<No*> fila;
    fila.push(root);
    fila.push(NULL);

    while(true) {
        No* no = fila.front();
        fila.pop();
        
        if(no != NULL) { //Verifica se há elemento nessa posição
        
            std::cout << no->data;
            
            if (no->left != NULL) { fila.push(no->left);  }
            
            if (no->right != NULL) { fila.push(no->right); }
        } else {
                if(fila.empty()) break;
                fila.push(NULL);
                std::cout << " ";
        }
    }
   
    std::cout << "\n";
    std::cout << "\n";
}

int main() {

    int nCasos;
    // std::vector<No*> arvores;

    std::cin >> nCasos;
    
    for (int caso = 0; caso < nCasos; caso++) {
        int tamArvore;
        No* no_raiz = NULL;
        std::cin >> tamArvore;
        int num;
        for(int i = 0; i < tamArvore; i++) {
            std::cin >> num;
            no_raiz = inserir(no_raiz, num);

        }

            std::cout << "Case " << caso + 1 << ":" << std::endl;
            percorrerEmOrdem(no_raiz);
        
       
    }

    // for (int i = 0; i < arvores.size(); i++) {
    //     std::cout << "Case " << i + 1 << ":" << std::endl;
    //     percorrerEmOrdem(arvores[i]);
    // }

    return 0;
}