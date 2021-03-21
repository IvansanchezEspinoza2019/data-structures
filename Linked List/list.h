#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>
#include "node.h"

template<class T>
class List {
    private:
       Node<T>* anchor;  //ancla

        bool isValidPos(Node<T> *);
        void copyAll(const List<T>&);
    public:
        List(); //constructor
        List(const List<T> &); //constructor copia
        List<T>& operator = (const List<T>&);
        ~List(); //destructor

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
        //operaciones de la lista
        bool isEmpty();

        void insertData(Node<T>*, const T&);
        void deleteData(Node<T>*);
        Node<T>* getFirst();
        Node<T>* getLast();
        Node<T>* getPrevPos(Node<T>*);
        Node<T>* getNextPos(Node<T>*);
        T retrieve(Node<T>*); //retorna un valor de tipo T

        void deleteAll();
        std::string toString(); //convierte un objeto en cadena


        Node<T>* findData(const T&);//busqueda lineal

    };

#include "list.h"

using namespace std;

template<class T>
bool List<T>::isValidPos(Node<T>* p) {
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
List<T>::List():anchor(nullptr){
}

template<class T>
List<T>::List(const List<T> &s)
{
    copyAll(s);
}


template<class T>
bool List<T>::isEmpty() {
    return anchor == nullptr;
}

template<class T>
void List<T>::insertData(Node<T>* p, const T &e) {
    if(p != nullptr and !isValidPos(p)){
        throw Exception("Posicion incvalida");
    }
    Node<T>* aux(new Node<T>(e));
    if(aux == nullptr){
        throw Exception("Memoria no disponible, insertData()");
    }
    if(p == nullptr){//insertar al principio
        aux->setNext(anchor);
        anchor = aux;
    }
    else{//cualquier otra posicion
    aux->setNext(p->getNext());
    p->setNext(aux);
    }
}

template<class T>
void List<T>::deleteData(Node<T>* p) {
if(!isValidPos(p)){
    throw Exception("posicion invalida, delete()");
    }
if(p == anchor){//eliminar el primero
    anchor = anchor->getNext();
}
else{//eliminando cualquier otra
    getPrevPos(p)->setNext(p->getNext());
}
delete p;
}
template<class T>
Node<T>* List<T>::getFirst() {
return anchor;
    }

template<class T>
Node<T>* List<T>::getLast() {
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
Node<T>* List<T>::getPrevPos(Node<T>* p) {
    if(p == anchor){//p es el primero
        return nullptr;
    }
    Node<T>* aux(anchor);
    while(aux!= nullptr and aux->getNext()!=p){
        aux = aux->getNext();
    }
    return aux;
    }

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p) {
    if(!isValidPos(p)){
        return nullptr;
    }

    return p->getNext();
    }

template<class T>
T List<T>::retrieve(Node<T>* p){
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, retrieve");
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
            throw Exception("Memoria no disponible, copy all()");
        }
        if(lastInserted == nullptr){
            anchor = newNode;
        }
        else{
            lastInserted->setNext(newNode);
        }
        lastInserted = newNode;
        aux = aux->getNext();
    }
}

//to string
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

//busqueda lineal
template<class T>
Node<T>* List<T>::findData(const T& e){
    Node<T>* aux(anchor);
    while(aux!= nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

//template<class T>
//int List<T,ARRAYSIZE>::findDataBin(const T &e){

//}

template<class T>
 List<T> &List<T>::operator =(const List<T>& l){
     deleteAll();
     copyAll(l);
     return *this;
}
template<class T>
 List<T>::~List(){
     deleteAll();
 }
#endif // LIST_H_INCLUDED
