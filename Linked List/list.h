/*
    This is a simple linked list tha uses de node.h file.
    The list can store any type of data specified by cl-
    ass T parameter.
*/

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>
#include "node.h" //list node

// exception class
class Exception : public std::exception {
    private:
        std::string msg;
    public:
        explicit Exception(const char* message) : msg(message) { }
        explicit Exception(const std::string& message) : msg(message) { }
        virtual ~Exception() throw () { }
        virtual const char* what() const throw () {
            return msg.c_str();
            }
};

template<class T>
class List {
    private:
        Node<T>* anchor;      //anchor node
        bool isValidPos(Node<T> *);
        void copyAll(const List<T>&);

    public:
        //constructors
        List(); 
        List(const List<T> &); 
        List<T>& operator = (const List<T>&);
        ~List(); 

        //methods
        bool isEmpty();
        void insertData(Node<T>*, const T&);
        void push_front(const T&);
        void push_back(const T&);
        void deleteData(Node<T>*);
        Node<T>* getFirst();
        Node<T>* getLast();
        Node<T>* getPrevPos(Node<T>*);
        Node<T>* getNextPos(Node<T>*);
        T retrieve(Node<T>*); 
        void deleteAll();
        std::string toString(); 
        void print();

        // lineal search
        Node<T>* findData(const T&); 
};

#include "list.h"

using namespace std;

template<class T>
bool List<T>::isValidPos(Node<T>* p) { // verify if a node is in the list
    Node<T>* aux(anchor);
    while (aux!= nullptr) {
        if(aux == p){
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}
template<class T>
List<T>::List():anchor(nullptr){ // init the main node
}

template<class T>
List<T>::List(const List<T> &s) 
{
    copyAll(s);
}

template<class T>
bool List<T>::isEmpty() { // verify if the list is empty
    return anchor == nullptr;
}
template<class T>
void List<T>::push_front(const T& e){
    insertData(nullptr, e); // insert at the beginning
}

template<class T>
void List<T>::push_back(const T& e){
    /*
    This inserts elements to the end of the list. but 
    it is inefficient because first we need to get the last
    node of the list and then make the link process.
    */
    insertData(getLast(), e);
}

template<class T>
void List<T>::insertData(Node<T>* p, const T &e) {
    if(p != nullptr and !isValidPos(p)){
        throw Exception("Invalid position, insertData()");
    }
    /* 
    if 'p' is equal to nullptr means that the insertion must to
    be at the beginning 
    */
    Node<T>* aux(new Node<T>(e));  // reserve memory for new elem
    if(aux == nullptr){
        throw Exception("No memory available, insertData()");
    }
    if(p == nullptr){           //insert at the begining
        aux->setNext(anchor);   // 'moves' the actual anchor
        anchor = aux;           // aux is going to be our new anchor node
    }
    else{ // other position
        aux->setNext(p->getNext());  // the next of aux is the next of p
        p->setNext(aux);             // the next of p is aux
    }
}

template<class T>
void List<T>::deleteData(Node<T>* p) {
    if(!isValidPos(p)){
        throw Exception("Invalid position, delete()");
    }
    if(p == anchor){            //delete the first elem
        anchor = anchor->getNext();
    }
    else{                       // any other position
        // linked the nodes of each side of 'p'
        getPrevPos(p)->setNext(p->getNext()); 
    }
    delete p;                   // free the space of 'p'
}

template<class T>
Node<T>* List<T>::getFirst() {  // get the first elem(anchor)
    return anchor;
}

template<class T>
Node<T>* List<T>::getLast() {   // get the last node
    Node<T>* aux(anchor);

    if(isEmpty()){
        return nullptr;
    }
    while(aux->getNext() !=nullptr){
        aux =aux->getNext();
    }
    return aux;
}

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p) { // get the previous node of p
    if(p == anchor){
        return nullptr;
    }
    Node<T>* aux(anchor);
    while(aux!= nullptr and aux->getNext()!=p){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p) { // get the next elem of p
    if(!isValidPos(p)){
        return nullptr;
    }

    return p->getNext();
}

template<class T>
T List<T>::retrieve(Node<T>* p){ // returns the elem inside of p
    if(!isValidPos(p)){
        throw Exception("Invalid position, retrieve()");
    }
    return p->getData();
}

template<class T>
void List<T>::deleteAll() { // delete all nodes
    Node<T>* aux;
    while(anchor!= nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
}

template<class T>
void List<T>::copyAll(const List<T> & s){ // copy other list
    Node<T>* aux(s.anchor);         // the anchor of snd list
    Node<T>* lastInserted(nullptr); // is our auxiliar node to copy to this list
    Node<T>* newNode;               // every new node

    while (aux!=nullptr) { 
        newNode = new Node<T>(aux->getData()); // get the elem inside the aux of 2nd list
        if(newNode == nullptr){                // no memory
            throw Exception("No memory available, copy all()");
        }
        if(lastInserted == nullptr){            // means that the anchor node does not have value yet
            anchor = newNode;
        }
        else{                                   
            lastInserted->setNext(newNode);     // linked the node
        }
        lastInserted = newNode;                 // update the last inserted node of the 1st list
        aux = aux->getNext();                   // next node of 2nd list
    }
}

template<class T>
void List<T>::print(){                      // print all elements
    Node<T>* aux(anchor);

    while(aux != nullptr){
        std::cout << aux->getData() << "-";
        aux = aux->getNext();
    }
    std::cout << std::endl;
}

template<class T>
string List<T>::toString() // converts all elems to string
{
    string result;

    Node<T>* aux(anchor);
    while(aux != nullptr){
        result+= std::to_string(aux->getData())+ "\n";
        aux = aux->getNext();
    }
    return result;
}


template<class T>
Node<T>* List<T>::findData(const T& e){ // lineal search
    Node<T>* aux(anchor);
    while(aux!= nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
 List<T> &List<T>::operator =(const List<T>& l){ // create this list based on other list
     deleteAll();
     copyAll(l);
     return *this;
}

template<class T>
 List<T>::~List(){ // destructor
     deleteAll(); // delete all
 }
#endif // LIST_H_INCLUDED
