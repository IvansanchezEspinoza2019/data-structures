#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>
#include"node.h"

template<class T>
class List {
    private:
       Node<T>* header;     //dummy header

        bool isValidPos(Node<T>*);
        void copyAll(const List<T>&);

    public:
        // constructors
        List(); 
        List(const List<T> &); 
        List<T>& operator = (const List<T>&);
        ~List(); 

        // iterator methods
        class Iterator;

        Iterator begin(){return Iterator(getFirst()); }
        Iterator end(){return Iterator(header); }

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

        //methods
        bool isEmpty();
        void insert(Node<T>*, const T&);
        void push_back(const T&);
        void push_front(const T&);
        void erase(Node<T>*);
        void deleteData(const T&);
        void deleteAll();
        T retrieve(Node<T>*);
        Node<T>* getFirst();
        Node<T>* getLast();
        Node<T>* getPrevPos(Node<T>*);
        Node<T>* getNextPos(Node<T>*);
        Node<T>* find(const T&);//busqueda lineal

        class Iterator{
            private:
                Node<T>* _it;
            public:
                Iterator():_it(nullptr){}
                Iterator(Node<T>* init):_it(init){}  

                Node<T>* getIt(){
                    return _it;
                }

                T operator *() {
                    if(_it == nullptr){
                        throw Exception("No data found, * operator()");
                    }
                    return _it->getData();
                }

                bool operator !=(const Iterator & it){
                    return _it != it._it;
                }

                bool operator ==(const Iterator & it){
                    return _it == it._it;
                }

                // prefix overload
                Iterator& operator++(){ 
                    // first make the increment, then return the object
                    _it = _it->getNext();
                    return *this;
                }

                // postfix overload
                Iterator operator++(int){ 
                    // first asign the object, then make the increment
                    Iterator temp = *this;
                    _it = _it->getNext();
                    return temp;
                }
        };
};

#include "list.h"

using namespace std;

template<class T>
bool List<T>::isValidPos(Node<T>* p){  // valid position

    Node<T>* aux(header->getNext());
    while(aux!=header) {
        if(aux == p){
            return true;
        }
        aux = aux->getNext();
    }

    return false;
}

template<class T>
List<T>::List(){
    if((header = new Node<T>)== nullptr){  // init dummy header
        throw Exception("No memory available, List()");
    }
    header->setPrev(header); // previous node
    header->setNext(header); // next node
}

template<class T>
List<T>::List(const List<T> &s) // receive a list as parameter
{
    copyAll(s);
}

template<class T>
bool List<T>::isEmpty() {    // empty list
    return header->getNext() == header;
}

template<class T>
void List<T>::push_back(const T &e){
    insert(getLast(), e);
}

template<class T>
void List<T>::push_front(const T &e){
    insert(nullptr, e);
}

template<class T>
void List<T>::insert(Node<T>* p, const T &e) {
    if(p != nullptr and !isValidPos(p)){
        throw Exception("Invalid position, insert()");
    }

    Node<T>* aux;
    try{
        aux =new Node<T>(e);
    }catch(Exception ex){//nodeException
        string msg("Error creatin new node, the log says : ");
        msg += ex.what();
        throw Exception(msg);
    }
    if(aux == nullptr){
        throw Exception("No memory available, insert()");
    }
    if(p == nullptr){  // insert at the begininng
        p = header;
    }
    // making the linking process
    aux->setPrev(p);
    aux->setNext((p->getNext()));

    p->getNext()->setPrev(aux);
    p->setNext(aux);                

}

template<class T>
void List<T>::erase(Node<T>* p) {
    if(!isValidPos(p)){ 
        throw Exception("invalid position, erase()");
    }
    // unlinking nodes
    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());

    // delete the position
    delete p;
}

template<class T>
void List<T>::deleteData(const T &e){
    erase(find(e));
}

template<class T>
Node<T>* List<T>::getFirst() { // first element
    if (isEmpty()) {
        return nullptr;
    }
    return header->getNext();
}

template<class T>
Node<T>* List<T>::getLast() {  // last element
    if(isEmpty()){
        return nullptr;
    }
    return header->getPrev();
}

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p) { // return previous node of p
    if(!isValidPos(p) or p== header->getNext()){ 
        return nullptr;
    }
    return p->getPrev();
}

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p) {  // return the next node of p
    if(!isValidPos(p) or p == header->getPrev()){
        return nullptr;
    }
    return p->getNext();
}

template<class T>
T List<T>::retrieve(Node<T>* p){ // return the data inside a node
    if(!isValidPos(p)){
        throw Exception("Invalid position, retrieve()");
    }
    return p->getData();
}

template<class T>
void List<T>::deleteAll() {  // erase all nodes from memory
    if (isEmpty()) {
        return;
    }
    Node<T>* aux;

    while(header->getNext()!=header){
        aux = header->getNext();
        header->setNext(aux->getNext());
        delete aux;
    }
   header->setPrev(header);
}

template<class T>
void List<T>::copyAll(const List<T> & s){ // copy a list

    if (s.isEmpty()) {
        return;
    }
    Node<T>* aux(s.header->getNext());

    Node<T>* newNode;
    while(aux!=s.header) {
        try{
            newNode = new Node<T>(aux->getData());

        }catch(Exception ex){
            throw Exception("Error");
        }

        if(newNode == nullptr){
            throw Exception("No memory available, copyAll()");
        }
        //linkin nodes
        newNode->setPrev(header->getPrev());
        newNode->setNext(header);
        header->setPrev(newNode);
        header->getPrev()->setNext(newNode);

        aux = aux->getNext();
    }
}

template<class T>
Node<T>* List<T>::find(const T& e){  // finds a element into the list
    Node<T>* aux(header->getNext());

    while(aux!=header){
        if(aux->getData() == e){
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

template<class T>
 List<T> &List<T>::operator=(const List<T>& l){
     deleteAll();
     copyAll(l);
     return *this;
}

template<class T>
 List<T>::~List(){
     deleteAll();
 }
#endif // LIST_H_INCLUDED
