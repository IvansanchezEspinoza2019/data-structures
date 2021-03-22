#ifndef NODE_H
#define NODE_H
#include<iostream>
/*
    The simple linked list uses this node, so this file
    need to be in the same directory as the list.
*/

template <class T>
class Node{
private:
    T data;
    Node<T>* next;
public:
    // constructor
    Node();
    Node(const T&);
    // methods
    T getData() const;
    Node<T>* getNext();
    void setData(const T&);
    void setNext(Node<T>*);
};

using namespace std;

template<class T>
Node<T>::Node() : next(nullptr){
}

template<class T>
Node<T>::Node(const T &e) :data(e), next(nullptr){

}

template<class T>
T Node<T>::getData() const
{
    return data;
}

template<class T>
Node<T>* Node<T>::getNext()
{
    return next;
}

template<class T>
void Node<T>::setData(const T &e)
{
    data = e;
}

template<class T>
void Node<T>::setNext(Node<T> *p)
{
    next = p;
}

#endif // NODE_H

