/*
    This queue uses a dummy header because the main operation:
    enqueue(insert) and dequeue(get) get simplier with this kind
    of node.
*/

#ifndef QUEUE_H
#define QUEUE_H
#include <exception>
#include <string>
#include <iostream>
#include"node.h"

template<class T>
class Queue {
    private:
       SmartNode<T>* header;            // dummy header
       void copyAll(const Queue<T>&);   // copy method

    public:
        // constructor
        Queue(); 
        Queue(const Queue<T> &e);
        ~Queue(); 

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
        // methods
        bool isEmpty();
        void enqueue(const T&); // insert
        void deleteAll();       // delete all
        size_t size();          // queue size

        T dequeue();            // delete
        T front();              // first elem
        T queue();              // last elem
        
      
        Queue<T>& operator = (const Queue<T>&);
    };

using namespace std;

template<class T>
Queue<T>::Queue(){                                // constructor
    if((header = new SmartNode<T>)== nullptr){
        throw Exception("No memory available, Queue()");
    }
    header->setPrev(header);
    header->setNext(header);
}

template<class T>
Queue<T>::Queue(const Queue<T> &e){
   copyAll(e);
}


template<class T>
bool Queue<T>::isEmpty() {           // empty queue
    return header->getNext() == header;
}

template<class T>
void Queue<T>::enqueue(const T &e) {    // inserts at the end 

    SmartNode<T>* aux;
    try{
        aux = new SmartNode<T>(e);

    }catch(NodeException ex){//SmartNodeException
        string msg("Error, system says : ");
        msg += ex.what();
        throw Exception(msg);
    }

    if(aux == nullptr){
        throw Exception("No memory available, enqueue()");
    }
    // aux is going to be the last node, so the next of aux is the header
    aux->setPrev(header->getPrev());
    aux->setNext(header);
    // link the header to the node aux
    header->getPrev()->setNext(aux);
    header->setPrev(aux);
}

template<class T>
T Queue<T>::dequeue(){  // return the front and deletes it

    if(isEmpty()){
        throw Exception("Empty queue, dequeue()");
    }
    // getting the front
    T result(header->getNext()->getData());
    SmartNode<T>* aux;
    aux = header->getNext();

    if(aux == nullptr){
        throw Exception("No memory available, dequeue()");
    }
    // linking process
    header->getNext()->getNext()->setPrev(header);
    header->setNext(header->getNext()->getNext());

    delete aux;     // delets the front
    return result;  //return the data
}

template<class T>
T Queue<T>::front() {  // get the front
    if (isEmpty()) {
        throw Exception("No data found, front()");
    }
    return header->getNext()->getData();
}

template<class T>
T Queue<T>::queue(){   // last element
    if(isEmpty()){
        throw Exception("Empty queue, queue()");
    }
    return header->getPrev()->getData();
}

template<class T>
size_t Queue<T>::size(){  /// get size of queue
    size_t cont = 0;
    SmartNode<T>* aux(header->getNext());

    while(aux != header){
        cont++;
        aux = aux->getNext();
    }
    return cont;
}

template<class T>
void Queue<T>::deleteAll() { // deletes all data
    if (isEmpty()) {
        return;
    }
    SmartNode<T>* aux;

    while(header->getNext()!=header){
        aux = header->getNext();
        header->setNext(aux->getNext());
        delete aux;
    }
   header->setPrev(header);
   header->setNext(header);

}

template<class T>
void Queue<T>::copyAll(const Queue<T> &s){ // copy all elements from other queue
    
    if(s.header->getNext() == s.header){
        return;
    }
    SmartNode<T>* aux(s.header->getNext());
    
    if(aux == nullptr){
        throw Exception("No memory available, copyAll()");
    }

    SmartNode<T>* newNode;
    while(aux!=s.header) {

        try{
            newNode = new SmartNode<T>(aux->getData());

        }catch(NodeException ex){
            string msg="Error\n";
            msg+=ex.what();
            throw Exception(msg);
        }

        if(newNode == nullptr){
            throw Exception("No memory available, copyAll()");
        }

        newNode->setPrev(header->getPrev());
        newNode->setNext(header);
        header->setPrev(newNode);
        header->getPrev()->setNext(newNode);
       
        aux = aux->getNext();
    }
}

template<class T>
 Queue<T>& Queue<T>::operator=(const Queue<T> &l){  // copy a hole queu
    deleteAll();
    copyAll(l);
    return *this;
}

template<class T>
 Queue<T>::~Queue(){
     deleteAll();
 }


#endif // QUEUE_H
