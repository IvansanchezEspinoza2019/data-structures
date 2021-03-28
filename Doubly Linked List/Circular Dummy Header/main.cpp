#include<iostream>
#include"list.h" // import list

void printList(List<char> &);

int main(){
    
    List<char> alphabet;

    // adding the alphabet
    for(int index = 65; index <= 90; index++){
        alphabet.push_back(char(index));
    }

    // print the alphabet
    std::cout << "\t.: ALPHABET :."<<std::endl;
    printList(alphabet);
    std::cout << std::endl;

    // to store the inverse alphabet
    List<char> inverseAlphabet;

    // inverting the alphabet
    while(!alphabet.isEmpty()){ 
        inverseAlphabet.push_front(alphabet.getFirst()->getData());     // inserting
        alphabet.erase(alphabet.getFirst());                            // deleting
    }

    // print the inverse alphabet
    std::cout << "\n\t.: INVERSE ALPHABET :."<<std::endl;
    printList(inverseAlphabet);
    std::cout << std::endl;

    // delete all nodes from memory
    inverseAlphabet.~List();
    
    return 0;
}

void printList(List<char> &list){ // print all elements
    for(List<char>::Iterator it = list.begin(); it != list.end(); it++){
        std::cout << *it << "-";
    }
}