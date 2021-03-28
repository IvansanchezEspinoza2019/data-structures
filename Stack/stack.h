/*
    This is a dynamic linked stack 
*/

#ifndef STACK_H
#define STACK_H
#include <iostream>
#include<exception>
#include"node.h"


template<class T>
class Stack{
  private:
   Node<T>* anchor;
   void copyAll(const Stack<T> &s); // copy a stack

  public:
    // constructors
    Stack(); 
    Stack(const Stack<T>&); 
    ~Stack();

    //exception class
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
    void push(const T&);
    T pop();
    T getTop();
    size_t size();

    void deleteAll();
    Stack& operator = (const Stack<T> &); 

};

template<class T>
Stack<T>::Stack() : anchor(nullptr){} //init anchor

template<class T>
Stack<T>::Stack(const Stack<T> &s){ //copy constructor
    copyAll(s);
}


template<class T>
bool Stack<T>::isEmpty(){  //empty
    return anchor == nullptr;
}

template<class T>
size_t Stack<T>::size(){      // return the stack size
	
	Node<T>* aux= anchor;
	size_t tam= 0;

	while(aux!=nullptr){
        tam= tam+1;
		aux = aux->getNext();
	}	
	return tam;
}

template<class T>
void Stack<T>::push(const T& e){  // push an element to the front
    Node<T>* aux= new Node<T>(e);
    if(aux ==nullptr){
        throw Exception("No memory available, push()");
    }
    aux->setNext(anchor); 
    anchor = aux;   //at first position
}

template<class T>
T Stack<T>::pop(){   // return an deletes the front of the stack
    if(isEmpty()){
        throw Exception("Empty stack, pop()");
    }
   T result(anchor->getData()); // get the front
   Node<T>* aux(anchor);        // auxiliar node

   anchor = anchor->getNext();  // anchor is going to be the next elem

   delete aux;                  // deletes the aux node

   return result;               // return the front
}

template<class T>
T Stack<T>::getTop(){  // only return the data, but no dellete it
    if(isEmpty()){
        throw Exception("Empty stack, getTop()");
    }
    return anchor->getData();
}

template<class T>
void Stack<T>::deleteAll() // delete the stack
{
    Node<T>* aux;
    while(anchor!= nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
}

template<class T>
void Stack<T>::copyAll(const Stack<T> &s)  // copy all elements from other list
{
    if(s.anchor == nullptr){
        anchor = nullptr;
        return;
    }

    Node<T>* aux(s.anchor);
    Node<T>* lastInserted(nullptr);
    Node<T>* newNode;
    while (aux!=nullptr) {
        newNode = new Node<T>(aux->getData());
        if(newNode == nullptr){
            throw Exception("No memory available, copyAll()");
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
Stack<T>& Stack<T>::operator =(const Stack<T> &t) // copy a hole stack
{
    copyAll(t);
    return *this;
}

template<class T>
Stack<T>::~Stack() {  // deletes all data
   deleteAll();
}


#endif // STACK_H
