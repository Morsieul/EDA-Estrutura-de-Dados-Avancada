#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <chrono> // Para medir o tempo
#include "avltree.h"
#include "redblacktree.h"
#include "hashtable_enc_exterior.h"
#include "hashtable_ender_aberto.h"

int main(int argc, char* argv[]) {
    // Verifica se há argumentos suficientes
    if (argc != 3) {
        std::cerr << "Uso correto: " << argv[0] << " dictionary [avl|rbt|hash_ex|hash_aberto] arquivo.txt" << std::endl;
        return 1;
    }

    std::string tipo_dicionario = argv[1];
    std::string nome_arquivo = argv[2];

    // Abre o arquivo
    std::ifstream file(nome_arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::string linha;
    typedef boost::tokenizer<boost::char_separator<char>> Tokenizer;
    boost::char_separator<char> separador(" \t\n\r\f.,;:!?()[]{}<>\"\'");

    auto start = std::chrono::high_resolution_clock::now();

    if (tipo_dicionario == "avl") {
        DicionarioAVL<std::string>* dic_avl = new DicionarioAVL<std::string>();

        while (std::getline(file, linha)) {
            Tokenizer tokens(linha, separador);
            for (const auto& palavra : tokens) {
                std::string palavra_processada = palavra;
                boost::algorithm::to_lower(palavra_processada);
                boost::algorithm::trim_if(palavra_processada, boost::is_any_of("!\"#$%&'()*+,./:;<=>?@[\\]^_`{|}~"));
                dic_avl->Insert(palavra_processada);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tempo_execucao = end - start;
        std::cout << "Dicionario usando árvore AVL:" << std::endl;
        dic_avl->Show();
        std::cout << "Tempo de inserção: " << tempo_execucao.count() << " segundos" << std::endl;

        delete dic_avl;

    } else if (tipo_dicionario == "rbt") {
        DicionarioRBT<std::string>* dic_rbt = new DicionarioRBT<std::string>();

        while (std::getline(file, linha)) {
            Tokenizer tokens(linha, separador);
            for (const auto& palavra : tokens) {
                std::string palavra_processada = palavra;
                boost::algorithm::to_lower(palavra_processada);
                boost::algorithm::trim_if(palavra_processada, boost::is_any_of("!\"#$%&'()*+,./:;<=>?@[\\]^_`{|}~"));
                dic_rbt->Insert(palavra_processada);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tempo_execucao = end - start;
        std::cout << "Dicionario usando árvore Rubro-Negra:" << std::endl;
        dic_rbt->Show();
        std::cout << "Tempo de inserção: " << tempo_execucao.count() << " segundos" << std::endl;

        delete dic_rbt;

    } else if (tipo_dicionario == "hash_ex") {
        HashTableExterior<std::string, int> dicHashEx;

        while (std::getline(file, linha)) {
            Tokenizer tokens(linha, separador);
            for (const auto& palavra : tokens) {
                std::string palavra_processada = palavra;
                boost::algorithm::to_lower(palavra_processada);
                boost::algorithm::trim_if(palavra_processada, boost::is_any_of("!\"#$%&'()*+,./:;<=>?@[\\]^_`{|}~"));
                dicHashEx.Insert(palavra_processada);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tempo_execucao = end - start;
        std::cout << "Dicionario usando tabela hash (encadeamento exterior):" << std::endl;
        dicHashEx.Show();
        std::cout << "Tempo de inserção: " << tempo_execucao.count() << " segundos" << std::endl;

    } else if (tipo_dicionario == "hash_aberto") {
        HashTableAberto<std::string, int> dicHashAberto;

        while (std::getline(file, linha)) {
            Tokenizer tokens(linha, separador);
            for (const auto& palavra : tokens) {
                std::string palavra_processada = palavra;
                boost::algorithm::to_lower(palavra_processada);
                boost::algorithm::trim_if(palavra_processada, boost::is_any_of("!\"#$%&'()*+,./:;<=>?@[\\]^_`{|}~"));
                dicHashAberto.Insert(palavra_processada);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tempo_execucao = end - start;
        std::cout << "Dicionario usando tabela hash (endereçamento aberto):" << std::endl;
        dicHashAberto.Show();
        std::cout << "Tempo de inserção: " << tempo_execucao.count() << " segundos" << std::endl;

    } else {
        std::cerr << "Tipo de dicionário não reconhecido. Use 'avl', 'rbt', 'hash_ex' ou 'hash_aberto'." << std::endl;
        return 1;
    }

    return 0;
}
