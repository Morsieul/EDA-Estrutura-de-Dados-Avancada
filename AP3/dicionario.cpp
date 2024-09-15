#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "avltree.cpp"
#include "redblacktree.h"

int main() {
    // Inicializa o dicionário AVL (se ainda for necessário)
    DicionarioAVL* dic_avl = new DicionarioAVL();

    // Inicializa o dicionário Rubro-Negro para strings
    DicionarioRBT<std::string>* dic_rbt = new DicionarioRBT<std::string>();

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

            // Insere a palavra na árvore Rubro-Negra
            dic_rbt->Insert(palavra_processada);
        }
    }

    file.close();

    // Exibe as palavras inseridas na árvore Rubro-Negra
    dic_rbt->Show();

    // Libera a memória alocada para o dicionário AVL e Rubro-Negro
    delete dic_avl;
    delete dic_rbt;

    return 0;
}