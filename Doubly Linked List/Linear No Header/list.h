/*
    This is a Doubly Linked List Linear with No Header
*/

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>
#include "node.h"   // include the doubly linked node


template<class T>
class List {
    private:
       Node<T>* anchor;  //anchor

        bool isValidPos(Node<T>*)const;
        void copyAll(const List<T>&);

    public:
        // constructor
        List(); 
        List(const List<T> &);
        List<T>& operator = (const List<T>&);
        ~List(); 

        //clase Exception anidada
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
        //methods
        bool isEmpty();

        void insertData(Node<T>*, const T&);
        void deleteData(Node<T>*);
        Node<T>* getFirst();
        Node<T>* getLast();
        Node<T>* getPrevPos(Node<T>*);
        Node<T>* getNextPos(Node<T>*);
        T retrieve(Node<T>*) const; 
        void deleteAll();
        std::string toString(); 

        Node<T>* findData(const T&);

        void sortDataMerge();
};

#include "list.h"

using namespace std;

template<class T>
bool List<T>::isValidPos(Node<T>* p) const {
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
List<T>::List():anchor(nullptr){ // initialize the main node
}

template<class T>
List<T>::List(const List<T> &s)
{
    copyAll(s);
}

template<class T>
bool List<T>::isEmpty() {    // empty list
    return anchor == nullptr;
}

template<class T>
void List<T>::insertData(Node<T>* p, const T &e) {
    if(p != nullptr and !isValidPos(p)){
        throw Exception("Invalid position, insertData()");
    }
    Node<T>* aux(new Node<T>(e));
    if(aux == nullptr){
        throw Exception("No memory available, insertData()");
    }
    if(p == nullptr){ // insert at beginning
        // making the double link process
        aux->setNext(anchor);
        if(anchor!=nullptr){
            anchor->setPrev(aux); 
        }
        anchor = aux;
    }
    else{ // any other position
        // making the double link process
        aux->setPrev(p);
        aux->setNext(p->getNext());

        if(p->getNext()!= nullptr){
            p->getNext()->setPrev(aux);
        }
        p->setNext(aux);
    }
}

template<class T>
void List<T>::deleteData(Node<T>* p) {
    if(!isValidPos(p)){
        throw Exception("invalid position, delete()");
    }
    if(p->getPrev()!=nullptr){ // if p has a previous node
        p->getPrev()->setNext(p->getNext()); // link the two sides nodes of p
    }
    if (p->getNext() != nullptr) { // if p has next nodes
        p->getNext()->setPrev(p->getPrev()); // link the two sides nodes of p
    }
    if (p == anchor) { // if p is the anchor, then scrolls one elmenent forward
        anchor = anchor->getNext();
    }

    delete p;
}
template<class T>
Node<T>* List<T>::getFirst() {
return anchor;
    }

template<class T>
Node<T>* List<T>::getLast() { // get last one elem
    Node<T>* aux(anchor);

    if(isEmpty()){
        return nullptr;
    }
    while(aux->getNext() !=nullptr){ // linear search
        aux =aux->getNext();
    }
    return aux;
}

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p) { // get previous node of p
    if (!isValidPos(p)) {
        return nullptr;
    }
    return p->getPrev();
}

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p) {
    if(!isValidPos(p)){
        return nullptr;
    }

    return p->getNext();
}

template<class T>
T List<T>::retrieve(Node<T>* p) const {
    if(!isValidPos(p)){
        throw Exception("Invalid position, retrieve()");
    }
    return p->getData();
}


template<class T>
void List<T>::deleteAll() {
    Node<T>* aux;
    while(anchor!= nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
}

template<class T>
void List<T>::copyAll(const List<T> & s){
    Node<T>* aux(s.anchor);
    Node<T>* lastInserted(nullptr);
    Node<T>* newNode;

    while (aux!=nullptr) {
        newNode = new Node<T>(aux->getData());
        if(newNode == nullptr){
            throw Exception("No memory available, copyAll()");
        }
        if(lastInserted == nullptr){ // first elem
            anchor = newNode;
        }
        else{ // link both nodes, the new one and the previous one
            lastInserted->setNext(newNode);
            newNode->setPrev(lastInserted);
        }
        lastInserted = newNode;
        aux = aux->getNext();
    }
}

template<class T>
string List<T>::toString()
{
    string result;

    Node<T>* aux(anchor);
    while(aux != nullptr){
        result+= aux->getData().toString()+ "\n";
        aux = aux->getNext();
    }
    return result;
}


template<class T>
Node<T>* List<T>::findData(const T& e){  // linear search
    Node<T>* aux(anchor);
    while(aux!= nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
 List<T> &List<T>::operator =(const List<T>& l){ // copy a hole list
     deleteAll();
     copyAll(l);
     return *this;
}

template<class T>
 List<T>::~List(){ // destructor
     deleteAll();
 }
#endif // LIST_H_INCLUDED
