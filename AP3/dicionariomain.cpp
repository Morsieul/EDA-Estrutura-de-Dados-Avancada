#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <chrono>
#include "avltree.h"
#include "redblacktree.h"
#include "hashtable_enc_exterior.h"
#include "hashtable_ender_aberto.h"

// Função para processar o arquivo e inserir as palavras em uma estrutura de dados
template<typename Dictionary>
void processarArquivo(Dictionary& dicionario, const std::string& nome_arquivo) {
    std::ifstream file(nome_arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    std::string linha;
    typedef boost::tokenizer<boost::char_separator<char>> Tokenizer;
    boost::char_separator<char> separador(" \t\n\r\f.,;:!?()[]{}<>\"\'");

    while (std::getline(file, linha)) {
        Tokenizer tokens(linha, separador);
        for (const auto& palavra : tokens) {
            std::string palavra_processada = palavra;
            boost::algorithm::to_lower(palavra_processada);
            boost::algorithm::trim_if(palavra_processada, boost::is_any_of("!\"#$%&'()*+,./:;<=>?@[\\]^_`{|}~—"));
            dicionario.Insert(palavra_processada);
        }
    }

    file.close();
}

// Função para medir o tempo de execução e exibir a estrutura
template<typename Dictionary>
void executarComTempo(Dictionary& dicionario, const std::string& nome_arquivo, const std::string& tipo_dicionario) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Processa o arquivo e insere na estrutura de dados
    processarArquivo(dicionario, nome_arquivo);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo_execucao = end - start;

    // Exibe a estrutura e o tempo de inserção
    std::cout << "Dicionario usando " << tipo_dicionario << ":" << std::endl;
    dicionario.Show();
    std::cout << "Tempo de inserção: " << tempo_execucao.count() << " segundos" << std::endl;
}

int main(int argc, char* argv[]) {
    // Verifica se há argumentos suficientes
    if (argc != 3) {
        std::cerr << "Uso correto: " << argv[0] << " [avl|rbt|hash_ex|hash_aberto] arquivo.txt" << std::endl;
        return 1;
    }

    std::string tipo_dicionario = argv[1];
    std::string nome_arquivo = argv[2];

    if (tipo_dicionario == "avl") {
        DicionarioAVL<std::string> dic_avl;
        executarComTempo(dic_avl, nome_arquivo, "árvore AVL");

    } else if (tipo_dicionario == "rbt") {
        DicionarioRBT<std::string> dic_rbt;
        executarComTempo(dic_rbt, nome_arquivo, "árvore Rubro-Negra");

    } else if (tipo_dicionario == "hash_ex") {
        HashTableExterior<std::string, int> dicHashEx;
        executarComTempo(dicHashEx, nome_arquivo, "tabela hash (encadeamento exterior)");

    } else if (tipo_dicionario == "hash_aberto") {
        HashTableAberto<std::string, int> dicHashAberto;
        executarComTempo(dicHashAberto, nome_arquivo, "tabela hash (endereçamento aberto)");

    } else {
        std::cerr << "Tipo de dicionário não reconhecido. Use 'avl', 'rbt', 'hash_ex' ou 'hash_aberto'." << std::endl;
        return 1;
    }

    return 0;
}
