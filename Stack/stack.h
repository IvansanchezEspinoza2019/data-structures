#ifndef STACK_H
#define STACK_H
#include <iostream>
#include<exception>
#include"node.h"


template<class T>
class Stack{
  private:
   Node<T>* anchor;
   void copyAll(const Stack<T> &s); //metodo copiar

  public:
    Stack(); //constructor
    Stack(const Stack<T> &s); //constructor copia
    ~Stack(); //destructor

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

    //metodos
    bool isEmpty();
    void push(const T&);
    T pop();
    T getTop();
    size_t getTam();

    void deleteAll();
    Stack& operator = (const Stack<T> &); //operador de asignacion

};
template<class T>
Stack<T>::Stack() : anchor(nullptr){}

template<class T>
bool Stack<T>::isEmpty(){
    return anchor == nullptr;
}
template<class T>
size_t Stack<T>::getTam(){
	
	Node<T>* aux= anchor;
	size_t tam= 0;
	while(aux!=nullptr){
                tam= tam+1;
		aux = aux->getNext();
	}	
	return tam;
}
template<class T>
void Stack<T>::push(const T& e){
    Node<T>* aux= new Node<T>(e);
    if(aux ==nullptr){
        throw Exception("Memoria no disponible, push()");
    }
    aux->setNext(anchor);
    anchor = aux;
}

template<class T>
T Stack<T>::pop(){
    if(isEmpty()){
        throw Exception("Insuficiencia de datos, pop()");
    }
   T result(anchor->getData());
   Node<T>* aux(anchor);

   anchor = anchor->getNext();

   delete aux;

   return result;
}

template<class T>
T Stack<T>::getTop(){
    if(isEmpty()){
        throw Exception("Insuficiencia de datos, getTop");
    }
    return anchor->getData();
}

template<class T>
void Stack<T>::deleteAll()
{
    Node<T>* aux;
    while(anchor!= nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
}


template<class T>
void Stack<T>::copyAll(const Stack<T> &s)
{
    Node<T>* aux(s.anchor);
        Node<T>* lastInserted(nullptr);
        Node<T>* newNode;
        while (aux!=nullptr) {
            newNode = new Node<T>(aux->getData());
            if(newNode == nullptr){
                throw Exception("Memoria no disponible, copyAll()");
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

template<class T>
Stack<T>::Stack(const Stack<T> &s){
    copyAll(s);
}
template<class T>
Stack<T>& Stack<T>::operator =(const Stack<T> &t)
{
    copyAll(t);
    return *this;
}

template<class T>
Stack<T>::~Stack() {
   deleteAll();
}


#endif // STACK_H
