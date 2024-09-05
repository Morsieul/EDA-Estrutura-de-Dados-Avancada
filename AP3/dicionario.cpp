#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "avltree.cpp"
#include "redblacktree.cpp"

int main() {
    // Inicializa o dicionário AVL
    DicionarioAVL* dic = new DicionarioAVL();

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
            // Por exemplo, se houver apóstrofos ou outros caracteres
            boost::algorithm::trim_if(palavra_processada, boost::is_any_of("!\"#$%&'()*+,./:;<=>?@[\\]^_`{|}~"));

            // Insere a palavra na árvore AVL
            dic->Insert(palavra_processada);
        }
    }

    file.close();

    dic->Show();
    // Opcional: Exibir as palavras inseridas ou outras operações
    // Por exemplo, dic->Print(); se você tiver um método para isso

    // Libera a memória alocada para o dicionário
    delete dic;

    return 0;
}
