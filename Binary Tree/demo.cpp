#include<iostream>
#include<functional>
#include<random>
#include"btree.h"   // import the binary tree


int main(){
    // to generate random numbers
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000);  //numbers between -50 and 50
    auto random = std::bind( distribution, generator );

    // creating an instance of our BTree
    BTree<int> tree;
    int tam = 10;

    std::cout <<"\nInserting "<<tam<<" elements..."<<std::endl;

    // inserting some elements
    for(int i= 0; i < tam; i++){
        // inserting randmo values
        tree.insertData(random());
    }

    // tree depth
    std::cout << "\nTree Depth: "<< tree.getHeight() << std::endl;

    // prints all elements from the minimum to the maximum value. first left, then the father, and finally the right node
    std::cout << "\n.: In-Order tree traversal :."<<std::endl;
    tree.parseInOrder();
    std::cout << std::endl;

    // pre-order tree traversal: first father, then the left, and finally the right node
    std::cout << "\n.: Pre-Order tree traversal :."<<std::endl;
    tree.parsePreOrder();
    std::cout << std::endl;

    // Post-Order tree traversal: first left, then the right, and finally the father node
    std::cout << "\n.: Post-Order tree traversal :."<<std::endl;
    tree.parsePostOrder();
    std::cout << std::endl;

    int value = 10;  // to delete later in the tree     
    cout << "\nInserting "<<value<<"..."<<std::endl;
    tree.insertData(value);
    tree.parseInOrder();
    std::cout << std::endl;

    // delete the value above
    std::cout << "\nDeleting "<<value << "..."<<std::endl;
    tree.deleteData(value);
    std::cout << "\nTree updated: "<<std::endl;
    tree.parseInOrder();
    std::cout << std::endl<<std::endl;



    return 0;
}