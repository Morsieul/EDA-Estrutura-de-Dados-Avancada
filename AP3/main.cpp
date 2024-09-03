#include <iostream>
#include <vector>
#include "avltree.cpp"
#include <boost/locale.hpp>

int main() {
    std::vector<std::string> words = {"ação", "criança", "maçã", "força"};
    boost::locale::generator gen;
    std::locale loc = gen("pt_BR.UTF-8");

    std::sort(words.begin(), words.end(), boost::locale::comparator<char>(loc));

    for(const auto& word : words) {
        std::cout << word << std::endl;
    }

    return 0;
}
