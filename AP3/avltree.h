 #pragma once

#ifndef SET_H
#define SET_H

/*
Inicialmente foi tentado usar um mesmo template para todas as estuturas, com uma mesma letra K para o typename, porem foi percebido durante a compilaçao
que tal abordagem gerava problemas, pois isto era visto como uma redefiniçao das variaveis. Assim, para cada implementaçao da estrutura de dados foi utilizado um template
com uma letra diferente para evitar confusoes.
*/

/*
Para a implementaçao da arvore, usamos o no e a arvore em si, com o mesmo tipo de dado generico T para nao haver problemas.
Na main() quando e declarado que criaremos uma arvore AVL de tipo string, automaticamente o tipo do AVLNode ja e determinado, ja que no construtor temos que o root
'e um ponteiro de um AVLNode tipo T.
A classe dicionario em si, apenas possui a raiz e toda a construçao decorre apartir disto, uma vez que funçoes como size() calculam o resultado percorrendo nos
AVLNode nos quais guardam as informaçoes relevantes para manter o balanceamento como altura e navegaçao, filho esquerdo e direito. 
*/

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

    /*
    O balanço e calculado a partir da altura dos dois filhos de um no. 
    Ele e essencial, pois a partir se seu valor for maior que 1 signifca que a arvore esta desbalanceada,
    sendo preciso aplicar rotaçao para manter a propriedade da arvore AVL, onde cada no tem altura menor ou igual a 1
    e fazer com que o tempo de busca nessa estrutura seja de Log(n).
    */

    int getBalance(AVLNode<T>* N) {  
        if (N == nullptr) return 0;  
        return height(N->left) - height(N->right);  
    }  

    bool isEmpty(AVLNode<T>* root) {
        return root == nullptr;
    }

    /*
    Esvazia uma arvore apartir de um no, de forma recursiva, verifica se o no em questao e 
    um nullptr para evitar problemas de segmentation fault.
    Funçao auxiliar da de chamada publica Clear(), essencial para o destrutor da estrutura de dados.
    */
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

    /*
    Essencial quando estiver usando template declarar que estamos usando o tipo dado no typename, do contrario isso acarreta
    erros de compilaçao.
    */

    AVLNode<T>* newNode(const T& x) {
        AVLNode<T>* no = new AVLNode<T>();
        no->data = x;
        no->left = nullptr;
        no->right = nullptr;
        no->height = 1;

        return no;
    }

    /*
    As funçoes de finMin e findMax percorrem a arvore recursivamente, pela esquerda para encotrar
    o menor valor e pela direita para encontrar o maior valor. Isso deve por conta dos principios
    de uma arvore binaria de busca, onde o maior elemento de um no se encontra a direita e o menor
    se encontra a esquerda. Essa busca se encerra ate encontrar um no filho que seja nulo, o que
    indica que nao e possivel explorar mais da arvore por falta de filhos e portanto tem-se o valor
    procurado, principio semelhante e usado na funçao search() de busca.  
    */
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

    /*
    A rotaçao simples a direita e feita quando, foi adicionada um no
    da sub-arvore esquerda de uma sub-arvore esquerda. 

    Uma forma ludica de ver isso e imaginar uma seta saindo de um no A e percorrer uma
    reta passando por outros dois nos, todos a esquerda de A.
    */
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

    /*
    A rotaçao dupla a direita ou rotaçao Esquerda-Direita ocorre quando na sub-arvore direita 
    de uma sub-arvore esquerda ha um no. 

    Imaginando o exemplo da reta saindo de A no item anterior, e como se tivessemos agora 
    um V e nao uma reta.
    */
    AVLNode<T>* doubleRightRotation(AVLNode<T>* p){
        p->left = singleLeftRotation(p->left);
        return singleRightRotation(p);
    }

    /*
    Ocorre quando a partir de um No A ha uma sequencia de nos na sub-arvore direita de uma sub-arvore direita.
    Tambem formando uma reta.
    */

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

    /*
    Tambem chamada de rotaçao Direita-Esquerda, corre quando na sub-arvore direita 
    de uma sub-arvore esquerda ha um no
    */
    AVLNode<T>* doubleLeftRotation(AVLNode<T>* p) {
        p->right = singleRightRotation(p->right);
        return singleLeftRotation(p);
    }

    /*
    E adicionado um novo item x, do tipo T, em uma arvore representada pelo No.
    Se o no for nullptr, significa que a arvore esta vazia naquele ponto e se cria um
    novo no do tipo com o valor de x.

    Caso contrario percorre pela esquerda ou a direita a partir da comparaçao com o valor de 
    p->data, ate que se chegue em um no vazio que possa acomodar x.

    No caso do dicionario, como poderiam ocorrer palavras iguais, o contator de recorrencias
    incrementa no no que possuir x, caso este ja exista e tente se colocar um novo no.

    Com o no em posiçao, calcula-se o balanço, a partir do resultado do balanço e da 
    verificaçao sobre onde termina a arvore p e a comparaçao dos filhos de p com x, sera decidido qual rotaçao sera utilizada.

    Se o balanço for positivo, a esquerda de p estiver ocupada e x e menor que a esquerda de p, significa
    que estamos fazendo um  percurso de sub-arvore esquerda da sub-arvore esquerda, assim utiliza-se rotaçao simples a direita.

    Se o balanço for negativo, a direita de p estiver ocupada e x for maior que a direita de p, significa que 
    estamos lidando com um percurso de sub-arvore direita da sub-arvore direita, assim utiliza-se a rotaçao simples a esquerda.

    Se o balanço for positivo, a esquerda de p estiver ocupada e x e for maior que a esquerda de p, significa
    que estamos fazendo um  percurso de sub-arvore direita da sub-arvore esquerda, assim utiliza-se rotaçao dupla a direita.

    Se o balanço for negativo, a direita de p estiver ocupada e x e for menor que a direita de p, significa
    que estamos fazendo um  percurso de sub-arvore esquerda da sub-arvore direita, assim utiliza-se rotaçao dupla a esquerda.
    */
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

    /*
    Remoçao faz uma busca por x na arvore em questao, a partir do no p. 
    Se o elemento for encontrado e este tiver dois filhos, sera preciso determinar qual e o menor
    para ser colocado no lugar de x, tornando-o no novo pai e o maior ficara a sua direita. 
    Caso tenha apenas um filho, este assume o lugar do pai.

    Apos isso verifica-se o balanço a partir da altura das sub-arvores e por fim, faz-se o balancemento 
    usando as devidas rotaçoes se for preciso.
    */

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

    /*
    Percurso simples em ordem de uma arvore binaria de busca.
    */

    void inorder(AVLNode<T>* p) {
	    if (p != nullptr) {
            inorder(p->left);
            // std::cout << "Visiting node with data: " << p->data << std::endl;
            std::cout << p->data  << ": " << "[" << p->contagem << "]" << std::endl;
            inorder(p->right);
        } else return;
    }

public:

    //Funçoes de chamada publica, servem para interagir com  o dicionario fora da classe.

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