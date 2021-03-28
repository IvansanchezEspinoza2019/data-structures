/*
    This is a small demo demostration of
    the main functions of the linked list.
*/

#include<iostream>
#include"list.h" // put your list DIRECTORY


void printList(List<string> &);

int main(){
    // instance of the Linked List
    List<string> strings; 

    // adding elements at the beginning 
    strings.push_front("Carlos");
    strings.push_front("Pepe");
    strings.push_front("Edgar");
    strings.push_front("Ivan");

    // adding elements to the end
    strings.push_back("Juan");
    strings.push_back("Maria");

    // print the list
    std::cout << "List: " << std::endl;
    printList(strings);
    std::cout << std::endl;

    // to search into the list
    string name = "Edgar"; 

    if(strings.findData(name) != nullptr){ // if the value of 'name' is found

        string result;   // to store the result

        ////// find the next string element of 'name' //////
        if(strings.getNextPos(strings.findData(name)) != nullptr){ // if 'name' has next node
            // then, get the name of the next node
            result = strings.retrieve(strings.getNextPos(strings.findData(name))); 
            std::cout << "The next name after '"<< name << "' is: '"<< result <<"'"<< std::endl;
        }
        else{
            // last element
            std::cout << "'"<< name <<"' is the last name of the list" << std::endl;
        }

        ///// find the previus string element of 'name' ////
        if(strings.getPrevPos(strings.findData(name)) != nullptr){
            result = strings.retrieve(strings.getPrevPos(strings.findData(name)));
            std::cout << "The name before '"<< name << "' is: '"<< result <<"'"<< std::endl;
        }
        else{
            //first element
            std::cout << "'"<<name << "' is the first element of the list"<< std::endl;
        }
        /// delete data //
        std::cout << "\nDeleting '" << name << "'..." << std::endl;
        strings.deleteData(strings.findData(name)); // delete 'name', but first search its position
        
        //final list
        std::cout << "List updated: " << std::endl;
        printList(strings);
        std::cout << std::endl;
    }
    else{
        // not in the list
        std::cout << "Could not find '" << name << "' into the list..." <<std::endl;
    }

    strings.~List(); // delete everything
   
    return 0;
}

void printList(List<string> &list){  // print all elements by using the iterator method
    for(auto it = list.begin(); it != list.end(); it++){
        std::cout << *it <<"-";
    }
}