#include<iostream>
#include "maxheap.cpp"

int main() {
    MaxHeap myheap;
    std::string priority = "P R I O * R * * I * T * Y * * * Q U E * * * U * E";


    for(int i = 0; i < priority.size(); i++) {

        if(priority[i] == 'E' ) {
            myheap.insert(5);
        }
        else if(priority[i] == 'I' ) {
            myheap.insert(9);
        }
        else if(priority[i] == 'O' ) {
            myheap.insert(15);
        }
        else if(priority[i] == 'P' ) {
            myheap.insert(16);
        }
        else if(priority[i] == 'Q' ) {
            myheap.insert(17);
        }
        else if(priority[i] == 'R' ) {
            myheap.insert(18);
        }
        else if(priority[i] == 'T' ) {
            myheap.insert(20);
        }
        else if(priority[i] == 'U' ) {
            myheap.insert(21);
        }
        else if(priority[i] == 'Y' ) {
            myheap.insert(25);
        }
        else if(priority[i] == '*' ) {
            myheap.removeMax();
        }
    }

    myheap.showHeap();

}