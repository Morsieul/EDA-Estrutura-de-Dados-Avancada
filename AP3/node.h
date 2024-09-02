#pragma once
#include<string>

struct node {
    public:
    std::string data;
    int aparcoes;
    int height;
    node* left{nullptr};
    node* right{nullptr};
};  