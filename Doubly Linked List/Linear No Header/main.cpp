#include<iostream>
#include"list.h"  //import list

void printList(List<float> &list); // print method

int main(){

    List<float> list; // instance of list

    // add to the front list
    list.push_front(12.5);
    list.push_front(45.9);
    list.push_front(150.364);

    float elem = 78.8;
    // inserts at the end
    list.push_back(elem);
    list.push_back(45.3);

    // insert next to the position of 'elem'
    list.insert(list.find(elem), elem*2);
    
    // print list
    std::cout << "List: "<<std::endl;
    printList(list);
    std::cout << std::endl;

    // search for a element
    elem = 45.3;
    if(list.find(elem) != nullptr){
        std::cout << "\nThe element '"<<elem<<"' is on the list "<< std::endl;

        std::cout<<"Deleting... '"<<elem<<"'"<<std::endl;
        // delete an elemen, internally first make a linear search and then delete the elem
        list.deleteData(elem);
        std::cout << "List Updated: "<<std::endl;
        printList(list);
        std::cout << std::endl;

    }
    else{
        std::cout << "Coul Not find '"<<elem<<"' on the list "<< std::endl;
    }

   

    if(!list.isEmpty()){ // if the list is not empty

        // get the first element of the list
        elem = list.retrieve(list.getFirst()); //retrieve first elem of the list

        // this is te 2nd way to delete data, the position is needed instead of receiving the elem
        list.erase(list.find(elem));

        std::cout << "\nDeleting first element..." <<std::endl;
        std::cout << "Final list: "<<std::endl;
        printList(list);
        std::cout << std::endl;
    }
    
    return 0;
}

void printList(List<float> &list){
    // use the list iterator 
    for(auto it = list.begin();  it != list.end(); it++){
            std::cout << *it << " - ";
    }
}