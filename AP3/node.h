#pragma once
#include<string>

struct node {
    public:
    std::string data;
    int contagem = 1;
    int height;
    node* left{nullptr};
    node* right{nullptr};
};  