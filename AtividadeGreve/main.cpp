#include<iostream>
#include<string>
#include<vector>
#include <string>
#include<sstream>
// #include "set.h"
// #include "set.cpp"
#include "setOperations.cpp"

void printMenu() {
    std::cout << "Menu\n";
    std::cout << "0. exit\n";
    std::cout << "1. help\n";
    std::cout << "2. create\n";
    std::cout << "3. show setIndex\n";
    std::cout << "4. size setIndex\n";
    std::cout << "5. max setIndex\n";
    std::cout << "6. min setIndex\n";
    std::cout << "7. empty setIndex\n";
    std::cout << "8. clear setIndex\n";
    std::cout << "9. insert setIndex number\n";
    std::cout << "10. erase setIndex number\n";
    std::cout << "11. contains setIndex number\n";
    std::cout << "12. successor setIndex number\n";
    std::cout << "13. predeccessor setIndex number\n";
    std::cout << "14. union setIndex1 setIndex2\n";
    std::cout << "15. intersec setIndex1 setIndex2\n";
    std::cout << "16. differ setIndex1 setIndex2\n";
    std::cout << "17. swap setIndex1 setIndex2\n";
}

int main() {

    std::vector<Set*> sets;
    std::string userinput;

    while(true) {

        std::getline(std::cin, userinput);

        std::stringstream ss(userinput);
        std::string command;
        std::string strint1, strint2; //Usar como indices quando usar as operacoes com mais de um conjunto. Usar como indice do set e o numero a adicionar, etc
        int sint1, sint2;

        ss >> command;

        if (command == "exit") {
            break;
        } else if (command == "help") {
            printMenu();
        } else if (command == "create") {
            sets.push_back(new Set());
            std::cout << "Set created. Total sets: " << sets.size() << "\n";
        } else {
            std::string strIndex1, strIndex2;
            ss >> strIndex1 >> strIndex2;
            try {
                int index1 = std::stoi(strIndex1);
                if (index1 >= 0 && index1 < sets.size()) {
                    if (command == "show") {
                        sets[index1]->Show();
                    } else if (command == "size") {
                        std::cout << sets[index1]->Size() << std::endl;
                    } else if (command == "max") {
                        sets[index1]->Maximum();
                    } else if (command == "min") {
                        sets[index1]->Minimum();
                    } else if (command == "clear") {
                        sets[index1]->Clear();
                    } else if (command == "empty") {
                        sets[index1]->Empty();
                    } else if (command == "insert") {
                        int value = std::stoi(strIndex2);
                        sets[index1]->Insert(value);
                    } else if (command == "erase") {
                        int value = std::stoi(strIndex2);
                        sets[index1]->Erase(value);
                    } else if (command == "contains") {
                        int value = std::stoi(strIndex2);
                        sets[index1]->Contains(value);
                    } else if (command == "successor") {
                        int value = std::stoi(strIndex2);
                        sets[index1]->Successor(value);
                    } else if (command == "predecessor") {
                        int value = std::stoi(strIndex2);
                        sets[index1]->Predecessor(value);
                    }else if (command == "swap") {
                        int index2 = std::stoi(strIndex2);
                        if (index2 >= 0 && index2 < sets.size()) 
                            sets[index1]->Swap(*sets[index2]);
                        else 
                            std::cout << "Invalid second set index.\n";
                    }else if (command == "union") {
                        int index2 = std::stoi(strIndex2);
                        if (index2 >= 0 && index2 < sets.size())
                            sets.push_back( new Set(Union(*sets[index1], *sets[index2])));
                        else 
                            std::cout << "Invalid second set index.\n";
                    } else if (command == "intersection") {
                        int index2 = std::stoi(strIndex2);
                        if (index2 >= 0 && index2 < sets.size()) 
                            sets.push_back(new Set(Intersec(*sets[index1], *sets[index2])));
                        else  std::cout << "Invalid second set index.\n";
                    } else if (command == "difference") {
                        int index2 = std::stoi(strIndex2);
                        if (index2 >= 0 && index2 < sets.size()) 
                            sets.push_back(new Set(Difference(*sets[index1], *sets[index2])));
                        else 
                            std::cout << "Invalid second set index.\n";
                    }  else {
                        std::cout << "Unknown command.\n";
                    }
                } else {
                    std::cout << "Invalid first set index.\n";
                }
            } catch (std::invalid_argument&) {
                std::cout << "Invalid input. Indices and values must be integers.\n";
            }
        }
    }

}

   //if(command == "exit") break;
    //     else if (command == "help") printMenu();
    //     else if (command == "create") {
    //         sets.push_back(new Set());
    //     } 
    //     try {
    //             sint1 = std::stoi(strint1); //indice do set
    //             sint2 = std::stoi(strint2); // inteiro a ser inserido
    //             if(sint1 >= 0 && sint1 < sets.size() ) { // Se o indice for valido, e possivel realizar as operacoes de Insert, Contains, Erase, etc
    //                 if(command == "show") sets[sint1]->Show();
    //                 else if(command == "max") sets[sint1]->Maximum();
    //                 else if(command == "min") sets[sint1]->Minimum();
    //                 else if(command == "clear") sets[sint1]->Clear();
    //                 else if(command == "empty") sets[sint1]->Empty();
    //                 else if(command == "insert") sets[sint1]->Insert(sint2);
    //                 else if(command == "erase") sets[sint1]->Erase(sint2);
    //                 else if(command == "contains") sets[sint1]->Contains(sint2);
    //                 else if(command == "successor") sets[sint1]->Sucessor(sint2);
    //                 else if(command == "predeccessor") sets[sint1]->Predecessor(sint2);
                    
    //             } else std::cout << "Comando desconhecido\n";
    //         } catch (std::invalid_argument& e) {
    //             std::cout << "Invalid set indices.\n";
    //         }
    // }

// sets.push_back(new Set());

    // sets[0]->Insert(10);
    // sets[0]->Size();

    // Set a, b;

    // a.Insert(12);
    // a.Insert(8);
    // a.Insert(18);
    // a.Insert(5);
    // a.Insert(11);
    // a.Insert(17);
    // a.Insert(4);
    // a.Insert(20);
    // a.Insert(9);
    // a.Erase(4);
    // a.Insert(20);
    // a.Insert(10);
    // a.Insert(3);
    // a.Insert(33);
    // a.Insert(40);
    // a.Insert(2);
    // a.Insert(21);
    // a.Insert(14);

    // a.Show();
    // b.Insert(24);
    // b.Insert(16);
    // b.Insert(66);
    // b.Insert(37);
    // b.Insert(5);
    // b.Insert(4);

    // sets.push_back(new Set(Difference(b, a)));
    // sets[0]->Show();
    // sets.push_back(new Set(Intersec(a, b)));
    // sets[0]->Show();
    // sets.push_back(new Set(Union(a, b)));
    // sets[0]->Show();

    // if(sets[0]->Contains(66)) std::cout << "Sim, contem\n";
    // else std::cout << "Nao contem\n";
    // a.Contains(12);
    // a.Contains(5);
    // a.Sucessor(12);
    // a.Sucessor(5);
    // a.Predecessor(5);
    // a.Predecessor(33);
    // a.Size();
    // b.Size();

    // a.Swap(b);

    // std::cout << a.Size() << std::endl;