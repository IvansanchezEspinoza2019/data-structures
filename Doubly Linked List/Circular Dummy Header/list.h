#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>
#include"node.h"

template<class T>
class List {
    private:
       Node<T>* header;  //encabezado dummie

        bool isValidPos(Node<T>*);
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

        //mezclas
        void sortDataMerge();


    };

#include "list.h"

using namespace std;

template<class T>/////////////
bool List<T>::isValidPos(Node<T>* p){

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
    if((header = new Node<T>)== nullptr){
        throw Exception("memoria no disponible,inicializar lista");
    }
    header->setPrev(header);
    header->setNext(header);
}

template<class T>
List<T>::List(const List<T> &s)
{
    copyAll(s);
}

template<class T>
bool List<T>::isEmpty() {
    return header->getNext() == header;
}

template<class T>
void List<T>::insertData(Node<T>* p, const T &e) {
    if(p != nullptr and !isValidPos(p)){
        throw Exception("Posicion incvalida");
    }

    Node<T>* aux;
    try{
    aux =new Node<T>(e);
}catch(Exception ex){//nodeException
        string msg("Error creando nuevo nodo, el sisteme informa : ");
        msg += ex.what();
        throw Exception(msg);
    }
    if(aux == nullptr){
        throw Exception("Memoria no disponible, insertData()");
    }
    if(p == nullptr){//insertar al principio
        p = header;
    }
    aux->setPrev(p);
    aux->setNext((p->getNext()));

    p->getNext()->setPrev(aux);
    p->setNext(aux);                //////////

}

template<class T>
void List<T>::deleteData(Node<T>* p) {
if(!isValidPos(p)){
    throw Exception("posicion invalida, delete()");
    }
p->getPrev()->setNext(p->getNext());
p->getNext()->setPrev(p->getPrev());


delete p;
}
template<class T>
Node<T>* List<T>::getFirst() {
    if (isEmpty()) {
        return nullptr;
    }
    return header->getNext();
    }

template<class T>
Node<T>* List<T>::getLast() {
    //Node<T>* aux(header);
    if(isEmpty()){//p es el primero
        return nullptr;
    }

    return header->getPrev();
    }

template<class T>
Node<T>* List<T>::getPrevPos(Node<T>* p) {
    if(!isValidPos(p) or p== header->getNext()){//p es el primero
        return nullptr;
    }


    return p->getPrev();
    }

template<class T>
Node<T>* List<T>::getNextPos(Node<T>* p) {
    if(!isValidPos(p) or p == header->getPrev()){
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
void List<T>::copyAll(const List<T> & s){

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
            throw Exception("Memoria no disponible, copy all()");
        }

        newNode->setPrev(header->getPrev());
        newNode->setNext(header);
        header->setPrev(newNode);
        header->getPrev()->setNext(newNode);

        aux = aux->getNext();
    }
}

//to string
template<class T>
string List<T>::toString()
{
    string result;

    Node<T>* aux(header->getNext());
    while(aux!=header) {
        result+= aux->getData().toString()+ "\n";
        aux = aux->getNext();
    }

    return result;
}

//busqueda lineal
template<class T>
Node<T>* List<T>::findData(const T& e){
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
