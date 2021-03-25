/*
    This is a Linear Doubly Linked List with No Header
*/

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>
#include "node.h"   // include the list node


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

        // iterator class and methods
        class Iterator;

        Iterator begin(){ return Iterator(anchor); }
        Iterator end(){ return Iterator(nullptr);}
        

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
        void insert(Node<T>*, const T&);
        void push_front(const T&);
        void push_back(const T &);
        void deleteData(const T&);
        void erase(Node<T>*);
        void deleteAll();
        T retrieve(Node<T>*) const; 

        Node<T>* getFirst();  // first elem
        Node<T>* getLast();   // last elem
        Node<T>* getPrevPos(Node<T>*);
        Node<T>* getNextPos(Node<T>*);
        Node<T>* find(const T&);
       
        // iterator class
        class Iterator{
            private:
                Node<T>* _iter;

            public:
                Iterator():_iter(nullptr){} // init iterator
                Iterator( Node<T>* _e) : _iter(_e){}

                Node<T>* getIter(){
                    return _iter;
                }

                Iterator& operator=(const Node<T>* &_e){
                    this->_iter = _e;
                    return *this;
                }

                bool operator != (const Iterator &_e){
                    return _iter != _e._iter;
                }

                bool operator == (const Iterator &_e){
                    return _iter == _e._iter;
                }

                T operator *(){
                    if(_iter == nullptr){
                        throw Exception("Empty List, iterator");
                    }
                    return _iter->getData();
                }
                // prefix overload
                Iterator& operator++(){ // first make the increment, then return the object
                    _iter = _iter->getNext();
                    return *this;
                }
                // postfix overload
                Iterator operator++(int){ // first asign the object, then make the increment
                    Iterator temp = *this;
                    _iter = _iter->getNext();
                    return temp;
                }
        };     
};

#include "list.h"

using namespace std;

template<class T>
bool List<T>::isValidPos(Node<T>* p) const { // if a given position is valid
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
List<T>::List(const List<T> &s) // copy a hole list
{
    copyAll(s);
}

template<class T>
bool List<T>::isEmpty() {    // empty list
    return anchor == nullptr;
}

template<class T>
void List<T>::push_front(const T&e){  // add elements on the front
    insert(nullptr, e);
}

template<class T>
void List<T>::push_back(const T&e){  // add at the end
    insert(getLast(), e);
}

template<class T>
void List<T>::insert(Node<T>* p, const T &e) { // inserts a element in a given position
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
void List<T>::deleteData(const T &e){  // delete a element finding its position on the list
    erase(find(e));
}

template<class T>
void List<T>::erase(Node<T>* p) {   // erase a given postion of the list
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
Node<T>* List<T>::getFirst() { // get the first elem
    return anchor;
}

template<class T>
Node<T>* List<T>::getLast() { // get the last one elem
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
Node<T>* List<T>::getNextPos(Node<T>* p) { // get next node of p
    if(!isValidPos(p)){
        return nullptr;
    }

    return p->getNext();
}

template<class T>
T List<T>::retrieve(Node<T>* p) const { // returs the data inside a node
    if(!isValidPos(p)){
        throw Exception("Invalid position, retrieve()");
    }
    return p->getData();
}


template<class T>
void List<T>::deleteAll() {   // delete all nodes
    Node<T>* aux;
    while(anchor!= nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
}

template<class T>
void List<T>::copyAll(const List<T> & s){ // copy an entire list
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
Node<T>* List<T>::find(const T& e){  // linear search
    Node<T>* aux(anchor);
    while(aux!= nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

template<class T>
List<T> &List<T>::operator =(const List<T>& l){ // copy a hole list
     deleteAll();  // first delete this elements before coping the new ones
     copyAll(l);  // call the method tha copies the list
     return *this;
}

template<class T>
List<T>::~List(){ // destructor
     deleteAll();
 }
#endif // LIST_H_INCLUDED
