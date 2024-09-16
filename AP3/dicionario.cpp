#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "avltree.h"
#include "redblacktree.h"
#include "hashtable_enc_exterior.h"
#include "hashtable_ender_aberto.h"


int main() {
    
    //Inicializa o dicionario com Arvore AVL
    DicionarioAVL<std::string>* dic_avl = new DicionarioAVL<std::string>();

    // Inicializa o dicionario com Arvore rubro-negra
    DicionarioRBT<std::string>* dic_rbt = new DicionarioRBT<std::string>();

    //Inincializa a tabela hash por endereçamento exterior
    HashTableExterior<std::string, int> dicHashEx;

    //Inicializa a tabela hash por endereçamento aberto
    HashTableAberto<std::string, int> dicHashAberto;

    // Abre o arquivo
    std::ifstream file("dicionario.txt");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::string linha;

    // Define os delimitadores para o tokenizer (espaço, pontuação, etc.), mas mantém o hífen
    typedef boost::tokenizer<boost::char_separator<char>> Tokenizer;
    boost::char_separator<char> separador(" \t\n\r\f.,;:!?()[]{}<>\"\'"); // Exclui hífens

    while (std::getline(file, linha)) {
        // Cria o tokenizer para a linha atual
        Tokenizer tokens(linha, separador);
        for (const auto& palavra : tokens) {
            std::string palavra_processada = palavra;

            // Converte para minúsculas usando Boost, mantendo os hífens
            boost::algorithm::to_lower(palavra_processada);

            // Opcional: Remover pontuação residual, exceto hífens
            boost::algorithm::trim_if(palavra_processada, boost::is_any_of("!\"#$%&'()*+,./:;<=>?@[\\]^_`{|}~"));

            // Insere a palavra no dicionario em questao
            dic_avl->Insert(palavra_processada);
            dic_rbt->Insert(palavra_processada);
            
            dicHashEx.Insert(palavra_processada);
            dicHashAberto.Insert(palavra_processada);
        }
    }

    file.close();

    // Exibe as palavras inseridas na árvore AVL
    std::cout << "Dicionario usando árvore AVL:" << std::endl;
    dic_avl->Show();
    std::cout << std::endl;

    // Exibe as palavras inseridas na árvore Rubro-Negra
    std::cout << "Dicionario usando árvore Rubro-Negra:" << std::endl;
    dic_rbt->Show();
    std::cout << std::endl;

    std::cout << "Dicionario usando tabela hash(encadeamento exterior):" << std::endl;
    dicHashEx.Show();
    std::cout << std::endl;
    std::cout << "Dicionario usando tabela hash(endereçamento aberto):" << std::endl;
    dicHashAberto.Show();

    // Libera a memória alocada para o dicionário AVL e Rubro-Negro
    delete dic_avl;
    delete dic_rbt;
    return 0;
}